/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define Cin1_Pin GPIO_PIN_0
#define Cin1_GPIO_Port GPIOC
#define Cin2_Pin GPIO_PIN_1
#define Cin2_GPIO_Port GPIOC
#define Din1_Pin GPIO_PIN_2
#define Din1_GPIO_Port GPIOC
#define Din2_Pin GPIO_PIN_3
#define Din2_GPIO_Port GPIOC
#define motor4encoderA_Pin GPIO_PIN_0
#define motor4encoderA_GPIO_Port GPIOA
#define motor4encoderB_Pin GPIO_PIN_1
#define motor4encoderB_GPIO_Port GPIOA
#define motor2encoderA_Pin GPIO_PIN_6
#define motor2encoderA_GPIO_Port GPIOA
#define motor2encoderB_Pin GPIO_PIN_7
#define motor2encoderB_GPIO_Port GPIOA
#define Ain1_Pin GPIO_PIN_0
#define Ain1_GPIO_Port GPIOB
#define Ain2_Pin GPIO_PIN_1
#define Ain2_GPIO_Port GPIOB
#define MPUSCL_Pin GPIO_PIN_10
#define MPUSCL_GPIO_Port GPIOB
#define MPUSDA_Pin GPIO_PIN_11
#define MPUSDA_GPIO_Port GPIOB
#define key1_Pin GPIO_PIN_12
#define key1_GPIO_Port GPIOB
#define key2_Pin GPIO_PIN_13
#define key2_GPIO_Port GPIOB
#define key3_Pin GPIO_PIN_14
#define key3_GPIO_Port GPIOB
#define key4_Pin GPIO_PIN_15
#define key4_GPIO_Port GPIOB
#define PWMA_Pin GPIO_PIN_6
#define PWMA_GPIO_Port GPIOC
#define PWMB_Pin GPIO_PIN_7
#define PWMB_GPIO_Port GPIOC
#define PWMC_Pin GPIO_PIN_8
#define PWMC_GPIO_Port GPIOC
#define PWMD_Pin GPIO_PIN_9
#define PWMD_GPIO_Port GPIOC
#define Extrapwm3_Pin GPIO_PIN_9
#define Extrapwm3_GPIO_Port GPIOA
#define Extrapwm2_Pin GPIO_PIN_10
#define Extrapwm2_GPIO_Port GPIOA
#define Extrapwm1_Pin GPIO_PIN_11
#define Extrapwm1_GPIO_Port GPIOA
#define Bin1_Pin GPIO_PIN_12
#define Bin1_GPIO_Port GPIOA
#define Bin2_Pin GPIO_PIN_13
#define Bin2_GPIO_Port GPIOA
#define motor1encoderA_Pin GPIO_PIN_15
#define motor1encoderA_GPIO_Port GPIOA
#define motor1encoderB_Pin GPIO_PIN_3
#define motor1encoderB_GPIO_Port GPIOB
#define motor3encoderA_Pin GPIO_PIN_6
#define motor3encoderA_GPIO_Port GPIOB
#define motor3encoderB_Pin GPIO_PIN_7
#define motor3encoderB_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
