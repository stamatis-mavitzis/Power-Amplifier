#include "sensors.h"
#include "protection_config.h"
#include "protection_pins.h"
#include "main.h"

extern ADC_HandleTypeDef hadc1;


/* Read one ADC channel */
static bool ADC_ReadChannel(uint32_t channel, uint16_t *value)
{
    ADC_ChannelConfTypeDef config = {0};

    config.Channel = channel;
    config.Rank = ADC_RANK_CHANNEL_NUMBER;
    config.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;

    if (HAL_ADC_ConfigChannel(&hadc1, &config) != HAL_OK)
        return false;

    if (HAL_ADC_Start(&hadc1) != HAL_OK)
        return false;

    if (HAL_ADC_PollForConversion(&hadc1, 10) != HAL_OK)
    {
        HAL_ADC_Stop(&hadc1);
        return false;
    }

    *value = (uint16_t)HAL_ADC_GetValue(&hadc1);

    HAL_ADC_Stop(&hadc1);

    return true;
}


/* Average several ADC measurements */
static bool ADC_ReadAverage(uint32_t channel, uint16_t *value)
{
    uint32_t sum = 0;
    uint16_t sample = 0;

    for (uint8_t i = 0; i < ADC_AVERAGE_SAMPLES; i++)
    {
        if (!ADC_ReadChannel(channel, &sample))
            return false;

        sum += sample;
    }

    *value = (uint16_t)(sum / ADC_AVERAGE_SAMPLES);

    return true;
}


void Sensors_Init(void)
{
    /*
     * Calibrate ADC once after MX_ADC1_Init().
     */
    HAL_ADCEx_Calibration_Start(&hadc1);
}


bool Sensors_Read(SensorData *data)
{
    if (data == NULL)
        return false;

    if (!ADC_ReadAverage(TEMP1_ADC_CHANNEL, &data->temp1_adc))
        return false;

    if (!ADC_ReadAverage(TEMP2_ADC_CHANNEL, &data->temp2_adc))
        return false;

    if (!ADC_ReadAverage(DC_LEFT_ADC_CHANNEL, &data->dc_left_adc))
        return false;

    if (!ADC_ReadAverage(DC_RIGHT_ADC_CHANNEL, &data->dc_right_adc))
        return false;

    return true;
}


/* Detect disconnected or shorted NTC */
bool Sensors_TempValid(uint16_t adc)
{
    return (adc > TEMP_SHORT_ADC &&
            adc < TEMP_OPEN_ADC);
}


/* Trip at approximately 100 °C */
bool Sensors_OverTemperature(uint16_t adc)
{
    if (!Sensors_TempValid(adc))
        return false;

    return (adc <= TEMP_TRIP_ADC);
}


/* Allow reset only after cooling below ~90 °C */
bool Sensors_TempCoolForReset(uint16_t adc)
{
    if (!Sensors_TempValid(adc))
        return false;

    return (adc > TEMP_RESET_ADC);
}


/* Convert DC-sense ADC reading to amplifier output voltage */
float Sensors_DCVoltage(uint16_t adc)
{
    return ((float)adc - DC_CENTER_ADC)
            / DC_COUNTS_PER_VOLT;
}
