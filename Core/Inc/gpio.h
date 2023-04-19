/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
int Frontright_forward(int a);
int Frontright_backward(int a);
void Frontright_STOP(void);
int Frontleft_forward(int a);
int Frontleft_backward(int a);
void Frontleft_STOP(void);
int Backleft_forward(int a);
int Backleft_backward(int a);
void Backleft_STOP(void);
int Backright_forward(int a);
int Backright_backward(int a);
void Backright_STOP(void);
int ForwardandBackward(int speed);
int LeftandRightRotation(int speed);
int STOPALL(void);
void keyscan(void);
void motorpwminit(void);
void Motor_Set_Pwm(uint8_t id, int16_t pulse);//这里输入的是pwm
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

