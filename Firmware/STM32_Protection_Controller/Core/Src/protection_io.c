#include "protection_io.h"
#include "protection_pins.h"
#include "protection_config.h"
#include "protection.h"
#include "main.h"


typedef struct
{
    GPIO_PinState raw;
    GPIO_PinState stable;
    uint32_t change_time;

} Button;


static Button mute_button;
static Button reset_button;


/* Debounced active-low pushbutton */
static bool Button_Pressed(Button *button,
                           GPIO_TypeDef *port,
                           uint16_t pin)
{
    uint32_t now = HAL_GetTick();

    GPIO_PinState state =
        HAL_GPIO_ReadPin(port, pin);


    if (state != button->raw)
    {
        button->raw = state;
        button->change_time = now;
    }


    if ((now - button->change_time)
        >= BUTTON_DEBOUNCE_MS)
    {
        if (state != button->stable)
        {
            button->stable = state;

            /* Button pressed = GPIO pulled to GND */
            if (state == GPIO_PIN_RESET)
                return true;
        }
    }

    return false;
}


void ProtectionIO_Init(void)
{
    /* Speakers must always start disconnected */
    ProtectionIO_SpeakersOff();


    mute_button.raw =
        HAL_GPIO_ReadPin(MUTE_BUTTON_PORT,
                         MUTE_BUTTON_PIN);

    mute_button.stable = mute_button.raw;
    mute_button.change_time = HAL_GetTick();


    reset_button.raw =
        HAL_GPIO_ReadPin(RESET_BUTTON_PORT,
                         RESET_BUTTON_PIN);

    reset_button.stable = reset_button.raw;
    reset_button.change_time = HAL_GetTick();
}


/* =========================================================
 * SPEAKER RELAYS
 * ========================================================= */

void ProtectionIO_SpeakersOn(void)
{
    HAL_GPIO_WritePin(RELAY_L_PORT,
                      RELAY_L_PIN,
                      GPIO_PIN_SET);

    HAL_GPIO_WritePin(RELAY_R_PORT,
                      RELAY_R_PIN,
                      GPIO_PIN_SET);
}


void ProtectionIO_SpeakersOff(void)
{
    HAL_GPIO_WritePin(RELAY_L_PORT,
                      RELAY_L_PIN,
                      GPIO_PIN_RESET);

    HAL_GPIO_WritePin(RELAY_R_PORT,
                      RELAY_R_PIN,
                      GPIO_PIN_RESET);
}


/* =========================================================
 * BUTTONS
 * ========================================================= */

bool ProtectionIO_MutePressed(void)
{
    return Button_Pressed(&mute_button,
                          MUTE_BUTTON_PORT,
                          MUTE_BUTTON_PIN);
}


bool ProtectionIO_ResetPressed(void)
{
    return Button_Pressed(&reset_button,
                          RESET_BUTTON_PORT,
                          RESET_BUTTON_PIN);
}


/* =========================================================
 * LEDs
 * ========================================================= */

void ProtectionIO_UpdateLEDs(uint8_t faults,
                             bool startup_waiting)
{
    HAL_GPIO_WritePin(
        TEMP1_LED_PORT,
        TEMP1_LED_PIN,
        (faults & FAULT_TEMP1_SENSOR)
            ? GPIO_PIN_SET
            : GPIO_PIN_RESET
    );


    HAL_GPIO_WritePin(
        TEMP2_LED_PORT,
        TEMP2_LED_PIN,
        (faults & FAULT_TEMP2_SENSOR)
            ? GPIO_PIN_SET
            : GPIO_PIN_RESET
    );


    HAL_GPIO_WritePin(
        OVERHEAT_LED_PORT,
        OVERHEAT_LED_PIN,
        (faults & FAULT_OVERTEMP)
            ? GPIO_PIN_SET
            : GPIO_PIN_RESET
    );


    HAL_GPIO_WritePin(
        DC_LED_PORT,
        DC_LED_PIN,
        (faults & FAULT_DC)
            ? GPIO_PIN_SET
            : GPIO_PIN_RESET
    );


    HAL_GPIO_WritePin(
        WAIT_LED_PORT,
        WAIT_LED_PIN,
        startup_waiting
            ? GPIO_PIN_SET
            : GPIO_PIN_RESET
    );
}
