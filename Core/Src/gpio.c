/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
#include "tim.h"
#define USE_HAL_LEGACY
#if   defined(USE_HAL_LEGACY)
#include "Legacy/stm32_hal_legacy.h"
#endif
#include <stdio.h>
#include "usart.h"
void motorpwminit(void);


int usermotor=1;
/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Cin1_Pin|Cin2_Pin|Din1_Pin|Din2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Ain1_Pin|Ain2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Bin1_Pin|Bin2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin */
  GPIO_InitStruct.Pin = Cin1_Pin|Cin2_Pin|Din1_Pin|Din2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = Ain1_Pin|Ain2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = key1_Pin|key2_Pin|key3_Pin|key4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = Bin1_Pin|Bin2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
//------------------------------------------------------FRONTLEFT-----------------------------------------------------------
int Frontleft_forward(int a)//input can be 0-10000;DO NOT BEYOND LIMIT!!!
{
 HAL_GPIO_WritePin(Bin1_GPIO_Port,Bin1_Pin,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(Bin2_GPIO_Port,Bin2_Pin,GPIO_PIN_SET);
 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2,a);
 return 0;
}

int Frontleft_backward(int a)//input can be 0-10000;DO NOT BEYOND LIMIT!!!
{
 HAL_GPIO_WritePin(Bin1_GPIO_Port,Bin1_Pin,GPIO_PIN_SET);
 HAL_GPIO_WritePin(Bin2_GPIO_Port,Bin2_Pin,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2,a);
 return 0;
}

void Frontleft_STOP(void)
{
 HAL_GPIO_WritePin(Bin1_GPIO_Port,Bin1_Pin,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(Bin2_GPIO_Port,Bin2_Pin,GPIO_PIN_RESET);
}
//--------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------FRONTRIGHT----------------------------------------------------------
int Frontright_forward(int a)//input can be 0-10000;DO NOT BEYOND LIMIT!!!
{
 HAL_GPIO_WritePin(Ain1_GPIO_Port,Ain1_Pin,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(Ain2_GPIO_Port,Ain2_Pin,GPIO_PIN_SET);
 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1,a);
 return 0;
}

int Frontright_backward(int a)//input can be 0-10000;DO NOT BEYOND LIMIT!!!
{
 HAL_GPIO_WritePin(Ain1_GPIO_Port,Ain1_Pin,GPIO_PIN_SET);
 HAL_GPIO_WritePin(Ain2_GPIO_Port,Ain2_Pin,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1,a);
 return 0;	
}

void Frontright_STOP(void)
{
 HAL_GPIO_WritePin(Ain1_GPIO_Port,Ain1_Pin,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(Ain2_GPIO_Port,Ain2_Pin,GPIO_PIN_RESET);
}
//--------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------BACKLEFT------------------------------------------------------------
int Backleft_forward(int a)//input can be 0-10000;DO NOT BEYOND LIMIT!!!
{
 HAL_GPIO_WritePin(Din1_GPIO_Port,Din1_Pin,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(Din2_GPIO_Port,Din2_Pin,GPIO_PIN_SET);
 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4,a);
 return 0;	
}

int Backleft_backward(int a)//input can be 0-10000;DO NOT BEYOND LIMIT!!!
{
 HAL_GPIO_WritePin(Din1_GPIO_Port,Din1_Pin,GPIO_PIN_SET);
 HAL_GPIO_WritePin(Din2_GPIO_Port,Din2_Pin,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4,a);
 return 0;	
}

void Backleft_STOP(void)
{
 HAL_GPIO_WritePin(Din1_GPIO_Port,Din1_Pin,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(Din2_GPIO_Port,Din2_Pin,GPIO_PIN_RESET);
}
//--------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------BACKRIGHT-----------------------------------------------------------
int Backright_forward(int a)//input can be 0-10000;DO NOT BEYOND LIMIT!!!
{
 HAL_GPIO_WritePin(Cin1_GPIO_Port,Cin1_Pin,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(Cin2_GPIO_Port,Cin2_Pin,GPIO_PIN_SET);
 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3,a);
 return 0;	
}

int Backright_backward(int a)//input can be 0-10000;DO NOT BEYOND LIMIT!!!
{
 HAL_GPIO_WritePin(Cin1_GPIO_Port,Cin1_Pin,GPIO_PIN_SET);
 HAL_GPIO_WritePin(Cin2_GPIO_Port,Cin2_Pin,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3,a);
 return 0;	
}

void Backright_STOP(void)
{
 HAL_GPIO_WritePin(Cin1_GPIO_Port,Cin1_Pin,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(Cin2_GPIO_Port,Cin2_Pin,GPIO_PIN_RESET);
}
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------CONTROL-------------------------------------------------------------
int ForwardandBackward(int speed)
{
 if(speed>=-10000&&speed<=10000)
	{
	  if(speed>=0)	 
		  {
		   Frontleft_forward(speed);
		   Frontright_backward(speed);
		   Backleft_forward(speed);
		   Backright_backward(speed);
		  }
	  else if(speed<0)
		  {
		   Frontleft_backward(-speed);
		   Frontright_forward(-speed);
		   Backleft_backward(-speed);
		   Backright_forward(-speed);   
		  }
	  return 0;	  
	}
 else
	{
     //printf("Wrong value");
	 return 1;
	 
	}
 
}

int LeftandRightRotation(int speed)
{
 if(speed>=-10000&&speed<=10000)
	{
	  if(speed>=0)//Left	 
		  {
		   Frontleft_forward(speed);
		   Frontright_forward(speed);
		   Backleft_forward(speed);
		   Backright_forward(speed);
		  }
	  else if(speed<0)//Right
		  {
		   Frontleft_backward(-speed);
		   Frontright_backward(-speed);
		   Backleft_backward(-speed);
		   Backright_backward(-speed);   
		  }
	  return 0;	  
	}
 else
	{
     //printf("Wrong value");
	 return 1;
	 
	}
 
}
int STOPALL(void)
{
 Frontleft_STOP();
 Frontright_STOP();
 Backright_STOP();
 Backleft_STOP();
 return 0;
}


void keyscan(void)
{

	  if(HAL_GPIO_ReadPin(key1_GPIO_Port,key1_Pin) == 0 )  //KEY2
	{	 
		/*等待按键释放 */
		HAL_Delay(5);
		while(HAL_GPIO_ReadPin(key1_GPIO_Port,key1_Pin) == 0)
			{

				while(HAL_GPIO_ReadPin(key1_GPIO_Port,key1_Pin) !=1);
				break;
			}

	}
	  if(HAL_GPIO_ReadPin(key2_GPIO_Port,key2_Pin) == 0 )  //KEY2
	{	 
		/*等待按键释放 */
		HAL_Delay(5);
		while(HAL_GPIO_ReadPin(key2_GPIO_Port,key2_Pin) == 0)
			{

				while(HAL_GPIO_ReadPin(key2_GPIO_Port,key2_Pin) !=1);
				break;
			}

	}
	  if(HAL_GPIO_ReadPin(key3_GPIO_Port,key3_Pin) == 0 )  //KEY2
	{	 
		/*等待按键释放 */
		HAL_Delay(5);
		while(HAL_GPIO_ReadPin(key3_GPIO_Port,key3_Pin) == 0)
			{
				STOPALL();

				while(HAL_GPIO_ReadPin(key3_GPIO_Port,key3_Pin) !=1);
				break;
			}

	}
	  if(HAL_GPIO_ReadPin(key4_GPIO_Port,key4_Pin) == 0 )  //KEY2
	{	 
		/*等待按键释放 */
		HAL_Delay(5);
		while(HAL_GPIO_ReadPin(key4_GPIO_Port,key4_Pin) == 0)
			{
				STOPALL();
				if(usermotor<=4)
				{
					usermotor++;
				}
				if(usermotor>4)
				{
					usermotor=1;
				}
				Motor_Set_Pwm(usermotor,2500);
//				HAL_UART_Transmit(&huart2,(unsigned char*)"1",2,0xff);
//			  //HAL_Delay(50);
				while(HAL_GPIO_ReadPin(key4_GPIO_Port,key4_Pin) !=1);
				break;
			}

	}







}

void motorpwminit()
{
  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
}




void Motor_Set_Pwm(uint8_t id, int16_t pulse)//这里输入的是pwm
{
    //int16_t pulse = Motor_Ignore_Dead_Zone(speed);
    // Limit input  限制输入
    if (pulse >= 10000)
        pulse = 10000;
    if (pulse <= -10000)
        pulse = -10000;

    switch (id)
    {
    case 1:
    {
        //pulse = -pulse;
        if (pulse >= 0)
        {

		 HAL_GPIO_WritePin(Ain1_GPIO_Port,Ain1_Pin,GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(Ain2_GPIO_Port,Ain2_Pin,GPIO_PIN_SET);
		 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1,pulse);
        }
        else
        {

		 HAL_GPIO_WritePin(Ain1_GPIO_Port,Ain1_Pin,GPIO_PIN_SET);
		 HAL_GPIO_WritePin(Ain2_GPIO_Port,Ain2_Pin,GPIO_PIN_RESET);
		 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1,pulse);
        }
        break;
    }
    case 2:
    {
        //pulse = -pulse;
        if (pulse >= 0)
        {
		 HAL_GPIO_WritePin(Bin1_GPIO_Port,Bin1_Pin,GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(Bin2_GPIO_Port,Bin2_Pin,GPIO_PIN_SET);
		 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2,pulse );
        }
        else
        {
		 HAL_GPIO_WritePin(Bin1_GPIO_Port,Bin1_Pin,GPIO_PIN_SET);
		 HAL_GPIO_WritePin(Bin2_GPIO_Port,Bin2_Pin,GPIO_PIN_RESET);
		 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2,pulse);
        }
        break;
    }

    case 3:
    {
        if (pulse >= 0)
        {
		 HAL_GPIO_WritePin(Cin1_GPIO_Port,Cin1_Pin,GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(Cin2_GPIO_Port,Cin2_Pin,GPIO_PIN_SET);
		 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3,pulse);
        }
        else
        {
		 HAL_GPIO_WritePin(Cin1_GPIO_Port,Cin1_Pin,GPIO_PIN_SET);
		 HAL_GPIO_WritePin(Cin2_GPIO_Port,Cin2_Pin,GPIO_PIN_RESET);
		 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3,pulse);
        }
        break;
    }
    case 4:
    {

        if (pulse >= 0)
        {
		 HAL_GPIO_WritePin(Din1_GPIO_Port,Din1_Pin,GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(Din2_GPIO_Port,Din2_Pin,GPIO_PIN_SET);
		 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4,pulse);
        }
        else
        {
		 HAL_GPIO_WritePin(Din1_GPIO_Port,Din1_Pin,GPIO_PIN_SET);
		 HAL_GPIO_WritePin(Din2_GPIO_Port,Din2_Pin,GPIO_PIN_RESET);
		 __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4,pulse);
        }
        break;		
    }

    default:
        break;
    }
}

/* USER CODE END 2 */
