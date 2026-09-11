#include "main.h"

#include "protection.h"
#include "protection_config.h"
#include "protection_io.h"
#include "sensors.h"

#include <stdbool.h>
#include <stdint.h>


static SensorData sensors;

static uint8_t faults = FAULT_NONE;

static bool muted = false;
static bool startup_complete = false;

static uint32_t startup_time = 0;
static uint32_t sample_time = 0;

static uint32_t dc_left_timer = 0;
static uint32_t dc_right_timer = 0;


/* --------------------------------------------------------- */

static float AbsFloat(float value)
{
    return (value < 0.0f) ? -value : value;
}


/* ---------------------------------------------------------
 * Immediately disconnect and latch fault
 * --------------------------------------------------------- */

static void RaiseFault(uint8_t fault)
{
    faults |= fault;

    startup_complete = false;

    ProtectionIO_SpeakersOff();
}


/* ---------------------------------------------------------
 * DC persistence detector
 * --------------------------------------------------------- */

static bool DC_Fault(float voltage,
                     uint32_t *timer)
{
    uint32_t now = HAL_GetTick();

    voltage = AbsFloat(voltage);


    /* Severe DC */
    if (voltage >= DC_FAST_TRIP_VOLTAGE)
    {
        if (*timer == 0U)
            *timer = now;

        return ((now - *timer)
                >= DC_FAST_TRIP_TIME_MS);
    }


    /* Normal DC */
    if (voltage >= DC_TRIP_VOLTAGE)
    {
        if (*timer == 0U)
            *timer = now;

        return ((now - *timer)
                >= DC_TRIP_TIME_MS);
    }


    /* Healthy again */
    *timer = 0U;

    return false;
}


/* ---------------------------------------------------------
 * Check sensors for faults
 * --------------------------------------------------------- */

static void CheckFaults(void)
{
    if (!Sensors_TempValid(sensors.temp1_adc))
        RaiseFault(FAULT_TEMP1_SENSOR);


    if (!Sensors_TempValid(sensors.temp2_adc))
        RaiseFault(FAULT_TEMP2_SENSOR);


    if (Sensors_OverTemperature(sensors.temp1_adc) ||
        Sensors_OverTemperature(sensors.temp2_adc))
    {
        RaiseFault(FAULT_OVERTEMP);
    }


    if (DC_Fault(
            Sensors_DCVoltage(sensors.dc_left_adc),
            &dc_left_timer))
    {
        RaiseFault(FAULT_DC);
    }


    if (DC_Fault(
            Sensors_DCVoltage(sensors.dc_right_adc),
            &dc_right_timer))
    {
        RaiseFault(FAULT_DC);
    }
}


/* ---------------------------------------------------------
 * Conditions for speaker connection
 * --------------------------------------------------------- */

static bool SystemSafe(void)
{
    if (!Sensors_TempValid(sensors.temp1_adc))
        return false;

    if (!Sensors_TempValid(sensors.temp2_adc))
        return false;


    if (Sensors_OverTemperature(sensors.temp1_adc))
        return false;

    if (Sensors_OverTemperature(sensors.temp2_adc))
        return false;


    if (AbsFloat(
        Sensors_DCVoltage(sensors.dc_left_adc))
        > DC_SAFE_VOLTAGE)
    {
        return false;
    }


    if (AbsFloat(
        Sensors_DCVoltage(sensors.dc_right_adc))
        > DC_SAFE_VOLTAGE)
    {
        return false;
    }

    return true;
}


/* ---------------------------------------------------------
 * Conditions required to reset fault
 * --------------------------------------------------------- */

static bool ResetSafe(void)
{
    /* Temperature sensors must be working */
    if (!Sensors_TempValid(sensors.temp1_adc))
        return false;

    if (!Sensors_TempValid(sensors.temp2_adc))
        return false;


    /*
     * If an overtemperature fault occurred,
     * require cooling below approximately 90 °C
     * before allowing reset.
     */
    if (faults & FAULT_OVERTEMP)
    {
        if (!Sensors_TempCoolForReset(sensors.temp1_adc))
            return false;

        if (!Sensors_TempCoolForReset(sensors.temp2_adc))
            return false;
    }
    else
    {
        /*
         * For other faults, temperature simply
         * needs to remain below the 100 °C trip point.
         */
        if (Sensors_OverTemperature(sensors.temp1_adc))
            return false;

        if (Sensors_OverTemperature(sensors.temp2_adc))
            return false;
    }


    /* DC must be safely close to zero */
    if (AbsFloat(
            Sensors_DCVoltage(sensors.dc_left_adc))
        > DC_SAFE_VOLTAGE)
    {
        return false;
    }

    if (AbsFloat(
            Sensors_DCVoltage(sensors.dc_right_adc))
        > DC_SAFE_VOLTAGE)
    {
        return false;
    }


    return true;
}


/* --------------------------------------------------------- */

static void RestartStartup(void)
{
    ProtectionIO_SpeakersOff();

    startup_complete = false;

    startup_time = HAL_GetTick();

    dc_left_timer = 0;
    dc_right_timer = 0;
}


/* ---------------------------------------------------------
 * Decide whether speakers should be connected
 * --------------------------------------------------------- */

static void UpdateSpeakers(void)
{
    if ((faults != FAULT_NONE) ||
        muted ||
        !startup_complete)
    {
        ProtectionIO_SpeakersOff();
    }
    else
    {
        ProtectionIO_SpeakersOn();
    }
}


/* =========================================================
 * PUBLIC FUNCTIONS
 * ========================================================= */

void Protection_Init(void)
{
    ProtectionIO_Init();

    Sensors_Init();

    faults = FAULT_NONE;

    muted = false;

    sample_time = 0;

    RestartStartup();

    ProtectionIO_UpdateLEDs(
        faults,
        true
    );
}


/* ========================================================= */

void Protection_Task(void)
{
    uint32_t now = HAL_GetTick();


    /* ---------------------------------
     * MUTE / ENABLE BUTTON
     * --------------------------------- */

    if (ProtectionIO_MutePressed())
    {
        muted = !muted;

        UpdateSpeakers();
    }


    /* ---------------------------------
     * FAULT RESET BUTTON
     * --------------------------------- */

    if (ProtectionIO_ResetPressed())
    {
        if ((faults != FAULT_NONE) &&
            ResetSafe())
        {
            faults = FAULT_NONE;

            RestartStartup();
        }
    }


    /* ---------------------------------
     * SENSOR UPDATE
     * --------------------------------- */

    if ((now - sample_time)
        < SAMPLE_INTERVAL_MS)
    {
        return;
    }

    sample_time = now;


    /*
     * ADC failure = fail safe.
     */
    if (!Sensors_Read(&sensors))
    {
        RaiseFault(
            FAULT_TEMP1_SENSOR |
            FAULT_TEMP2_SENSOR |
            FAULT_DC
        );
    }
    else
    {
        CheckFaults();
    }


    /* ---------------------------------
     * 3 SECOND STARTUP DELAY
     * --------------------------------- */

    if (!startup_complete &&
        faults == FAULT_NONE)
    {
        if ((now - startup_time)
            >= STARTUP_DELAY_MS)
        {
            if (SystemSafe())
            {
                startup_complete = true;
            }
        }
    }


    /* ---------------------------------
     * RELAYS
     * --------------------------------- */

    UpdateSpeakers();


    /* ---------------------------------
     * LEDs
     * --------------------------------- */

    ProtectionIO_UpdateLEDs(
        faults,
        (!startup_complete &&
         faults == FAULT_NONE)
    );
}
