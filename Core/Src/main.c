/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define USE_HAL_LEGACY
#if   defined(USE_HAL_LEGACY)
#include "Legacy/stm32_hal_legacy.h"
#endif
#include<stdio.h>
#include  "oled.h"
#include "stdio.h"
#include "string.h"
#include "Encoder.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t BLUdata;
extern int g_Encoder_M1_Now;
extern int g_Encoder_M2_Now;
extern int g_Encoder_M3_Now;
extern int g_Encoder_M4_Now;
extern short encoderPulse[4];
char E1[20] ,E2[20],E3[20],E4[20];
extern float motorspeed1,motorspeed2, motorspeed3, motorspeed4;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM6_Init();
  MX_TIM4_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  __HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);
  OLED_Init();
  OLED_Fill(0x00);
  OLED_ShowString(0,0,(uint8_t*)"Ready?!!",2);  
  HAL_UART_Receive_IT(&huart3,&BLUdata,1);
  HAL_UART_Transmit(&huart3,(unsigned char*)"I am ready for your command\r\n",27,2000);
//  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
//  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
//  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
//  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
  motorpwminit();// Better 电机初始化优化为一行代码
  HAL_TIM_Base_Start_IT(&htim6);//定时器中断
  Encoderinit();
  HAL_GPIO_WritePin(key4_GPIO_Port,key4_Pin,GPIO_PIN_SET);//一个调试按钮

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  keyscan();
//	  sprintf(E1,"%d",g_Encoder_M1_Now);// Everytime use microLib，测总上电后脉冲式
//	  sprintf(E2,"%d",g_Encoder_M2_Now);
//	  sprintf(E3,"%d",g_Encoder_M3_Now);
//	  sprintf(E4,"%d",g_Encoder_M4_Now);
//	  sprintf(E1,"%d",encoderPulse[0]);//测10ms内的脉冲数变化量
//	  sprintf(E2,"%d",encoderPulse[1]);
//	  sprintf(E3,"%d",encoderPulse[2]);
//	  sprintf(E4,"%d",encoderPulse[3]);	  
	  sprintf(E1,"%.2f",motorspeed1);//测10ms内的速度
	  sprintf(E2,"%.2f",motorspeed2);
	  sprintf(E3,"%.2f",motorspeed3);
	  sprintf(E4,"%.2f",motorspeed4);	
	  HAL_UART_Transmit(&huart3,(unsigned char*)"E1:",4,0xff);
	  HAL_UART_Transmit(&huart3,(unsigned char*)E1,5,0xff);
	  HAL_UART_Transmit(&huart3,(unsigned char*)"E2:",4,0xff);
	  HAL_UART_Transmit(&huart3,(unsigned char*)E2,5,0xff);
	  HAL_UART_Transmit(&huart3,(unsigned char*)"E3:",4,0xff);
	  HAL_UART_Transmit(&huart3,(unsigned char*)E3,5,0xff);	  
	  HAL_UART_Transmit(&huart3,(unsigned char*)"E4:",4,0xff);
	  HAL_UART_Transmit(&huart3,(unsigned char*)E4,5,0xff);	
	  HAL_UART_Transmit(&huart3,(unsigned char*)"\n",3,0xff);
	  OLED_ShowString(0,5,(uint8_t*)E1,2);
	  
	  //HAL_Delay(10);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{
		HAL_UART_Receive_IT(&huart3,&BLUdata,1);
		if(huart->Instance == USART3)
			{
				if(BLUdata==0x2A)//Using Hex
					{
						//printf("slow forward");
						ForwardandBackward(2500);//negative one means forward is right,not setting in convention because of lazy
						
					}
				else if(BLUdata==0x2B)
					{
						HAL_UART_Transmit(&huart3,(unsigned char*)"Backward!\n",11,0xff); 
						ForwardandBackward(-2500);
						
					}
				else if(BLUdata==0x2d)
					{
						HAL_UART_Transmit(&huart3,(unsigned char*)"Leftrotation\n",14,0xff);
						LeftandRightRotation(-2000);
					}
				else if(BLUdata==0x2c)
					{
						HAL_UART_Transmit(&huart3,(unsigned char*)"Rightrotation\n",15,0xff);
						LeftandRightRotation(2000);						
					}
				else if(BLUdata==0x2e)
					{
						HAL_UART_Transmit(&huart3,(unsigned char*)"Stop\n",6,0xff);
						STOPALL();
					}
//				else if(BLUdata==0x2f)//Using ASCII
//					{
//						//printf("Rush\r\n"); 
//						Forwardandbackward(-400);

//						
//					}	
//				 else if(BLUdata==0x3A)//Using ASCII
//					{
//						//printf("backward 400");
//						Forwardandbackward(400);					
//						
//					}
//				 else if(BLUdata==0x3B)//Using ASCII
//					{
//						//printf("800");
//						Forwardandbackward(-900);
//						
//						
//			
//					}			
//				 else if(BLUdata==0x3C)//Using ASCII
//					{
//						//printf("backward 300");
//						Forwardandbackward(300);					
//						
//					}
//				 else if(BLUdata==0x4A)//leftside forward
//					{
//						//printf("a little leftside forward");
//						leftbackward(300);
//						Rightbackward(230);					
//						
//					}
//				 else if(BLUdata==0x4C)//forward toward a little right ----->car toward a little right while forward
//					{
//						//printf("a little rightside forward");
//						leftbackward(230);
//						Rightbackward(340);						
//					}	
//				 else if(BLUdata==0x9C)//forward toward a big right ----->car toward a big right while forward
//					{
//						//printf("Big rightside forward");
//						leftbackward(430);
//						Rightbackward(595);	
//					}
//				 else if(BLUdata==0x6C)//forward toward a big left ----->car toward a big left while forward
//					{
//						//printf("a big leftside forward");
//						leftbackward(555);
//						Rightbackward(430);						
//					}							
										
			}
		 
		
	}
	
	
	
//定时器相关中断函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) //这个是每10ms获取一次中断
	{
	if(htim == &htim6)
		{
			Encoder_combinationread();
			//HAL_UART_Transmit(&huart1,(unsigned char*)"ok\n",3,0xff);
		}
	} 
	
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
