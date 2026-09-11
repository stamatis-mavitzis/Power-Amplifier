/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TEMP2_FAIL_LED_Pin GPIO_PIN_9
#define TEMP2_FAIL_LED_GPIO_Port GPIOB
#define TEMP1_ADC_Pin GPIO_PIN_0
#define TEMP1_ADC_GPIO_Port GPIOA
#define TEMP2_ADC_Pin GPIO_PIN_1
#define TEMP2_ADC_GPIO_Port GPIOA
#define DC_SENSE_L_Pin GPIO_PIN_4
#define DC_SENSE_L_GPIO_Port GPIOA
#define DC_SENSE_R_Pin GPIO_PIN_5
#define DC_SENSE_R_GPIO_Port GPIOA
#define MUTE_ENABLE_Pin GPIO_PIN_0
#define MUTE_ENABLE_GPIO_Port GPIOB
#define FAULT_RESET_Pin GPIO_PIN_1
#define FAULT_RESET_GPIO_Port GPIOB
#define RELAY_L_CTRL_Pin GPIO_PIN_8
#define RELAY_L_CTRL_GPIO_Port GPIOA
#define RELAY_R_CTRL_Pin GPIO_PIN_9
#define RELAY_R_CTRL_GPIO_Port GPIOA
#define DC_FAULT_LED_Pin GPIO_PIN_11
#define DC_FAULT_LED_GPIO_Port GPIOA
#define WAIT_LED_Pin GPIO_PIN_12
#define WAIT_LED_GPIO_Port GPIOA
#define OVERHEAT_LED_Pin GPIO_PIN_4
#define OVERHEAT_LED_GPIO_Port GPIOB
#define TEMP1_FAIL_LED_Pin GPIO_PIN_8
#define TEMP1_FAIL_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
