#ifndef PROTECTION_PINS_H
#define PROTECTION_PINS_H

#include "main.h"


/* =========================================================
 * ADC CHANNELS
 * ========================================================= */

#define TEMP1_ADC_CHANNEL        ADC_CHANNEL_0
#define TEMP2_ADC_CHANNEL        ADC_CHANNEL_1

#define DC_LEFT_ADC_CHANNEL      ADC_CHANNEL_4
#define DC_RIGHT_ADC_CHANNEL     ADC_CHANNEL_5


/* =========================================================
 * SPEAKER RELAYS
 * ========================================================= */

#define RELAY_L_PORT             RELAY_L_CTRL_GPIO_Port
#define RELAY_L_PIN              RELAY_L_CTRL_Pin

#define RELAY_R_PORT             RELAY_R_CTRL_GPIO_Port
#define RELAY_R_PIN              RELAY_R_CTRL_Pin


/* =========================================================
 * PUSHBUTTONS
 * ========================================================= */

#define MUTE_BUTTON_PORT         MUTE_ENABLE_GPIO_Port
#define MUTE_BUTTON_PIN          MUTE_ENABLE_Pin

#define RESET_BUTTON_PORT        FAULT_RESET_GPIO_Port
#define RESET_BUTTON_PIN         FAULT_RESET_Pin


/* =========================================================
 * FAULT / STATUS LEDs
 * ========================================================= */

#define TEMP1_LED_PORT           TEMP1_FAIL_LED_GPIO_Port
#define TEMP1_LED_PIN            TEMP1_FAIL_LED_Pin

#define TEMP2_LED_PORT           TEMP2_FAIL_LED_GPIO_Port
#define TEMP2_LED_PIN            TEMP2_FAIL_LED_Pin

#define OVERHEAT_LED_PORT        OVERHEAT_LED_GPIO_Port
#define OVERHEAT_LED_PIN         OVERHEAT_LED_Pin

#define DC_LED_PORT              DC_FAULT_LED_GPIO_Port
#define DC_LED_PIN               DC_FAULT_LED_Pin

#define WAIT_LED_PORT            WAIT_LED_GPIO_Port
#define WAIT_LED_PIN             WAIT_LED_Pin


#endif /* PROTECTION_PINS_H */
