#include "Encoder.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
void speedcaculate(void);




int g_Encoder_M1_Now = 0;
int g_Encoder_M2_Now = 0;
int g_Encoder_M3_Now = 0;
int g_Encoder_M4_Now = 0;
float motorspeed1=0.0,motorspeed2=0.0, motorspeed3=0.0, motorspeed4=0.0;

short encoderPulse[4]={0};

void Encoderinit(void)
{
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_1 | TIM_CHANNEL_2);

	HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start_IT(&htim4, TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start_IT(&htim5, TIM_CHANNEL_1 | TIM_CHANNEL_2);
}


void GetEncoderPulse(void)
{    //配合小车轮子运动方向，可进行取反操作
    encoderPulse[0] = ((short)__HAL_TIM_GET_COUNTER(&htim2)); //1号电机
    encoderPulse[1] = -((short)__HAL_TIM_GET_COUNTER(&htim3)); //2号电机
    encoderPulse[2] = ((short)__HAL_TIM_GET_COUNTER(&htim4)); //3号电机
    encoderPulse[3] = -((short)__HAL_TIM_GET_COUNTER(&htim5)); //4号电机	
 
    __HAL_TIM_GET_COUNTER(&htim2) = 0;   //计数值重新清零
    __HAL_TIM_GET_COUNTER(&htim3) = 0;  
    __HAL_TIM_GET_COUNTER(&htim4) = 0;   //计数值重新清零
    __HAL_TIM_GET_COUNTER(&htim5) = 0; 
}

void speedcaculate(void) //每10ms调用一次 ；速度单位为mm/s
{
	motorspeed1=(float)encoderPulse[0]/1320*95.8/0.01;       //10ms内的编码器读数/1320*95.8mm(diameter of wheel)/0.01s
	motorspeed2=(float)encoderPulse[1]/1320*95.8/0.01;
	motorspeed3=(float)encoderPulse[2]/1320*95.8/0.01; 
	motorspeed4=(float)encoderPulse[3]/1320*95.8/0.01; 

}

void Encoder_Update_Count(void)
{
	g_Encoder_M1_Now +=encoderPulse[0];

	g_Encoder_M2_Now +=encoderPulse[1];

	g_Encoder_M3_Now +=encoderPulse[2];

	g_Encoder_M4_Now +=encoderPulse[3];
}


void Encoder_combinationread(void)
{

	GetEncoderPulse();
	speedcaculate();
	Encoder_Update_Count();
}



























//int GetEncoder1Pulse(void)
//{    //配合小车轮子运动方向，可进行取反操作
//    encoderPulse[0] = ((short)__HAL_TIM_GET_COUNTER(&htim1)); //1号电机
// 
//    __HAL_TIM_GET_COUNTER(&htim1) = 0;   //计数值重新清零
//}

//int GetEncoder2Pulse(void)
//{    //配合小车轮子运动方向，可进行取反操作
//    //encoderPulse[0] = ((short)__HAL_TIM_GET_COUNTER(&htim1)); //1号电机
//    encoderPulse[1] = ((short)__HAL_TIM_GET_COUNTER(&htim2)); //2号电机
//    //encoderPulse[2] = ((short)__HAL_TIM_GET_COUNTER(&htim5)); //3号电机
//    //encoderPulse[3] = ((short)__HAL_TIM_GET_COUNTER(&htim8)); //4号电机	
// 
//   // __HAL_TIM_GET_COUNTER(&htim1) = 0;   //计数值重新清零
//    __HAL_TIM_GET_COUNTER(&htim2) = 0;  
//   // __HAL_TIM_GET_COUNTER(&htim5) = 0;   //计数值重新清零
//   // __HAL_TIM_GET_COUNTER(&htim8) = 0; 
//}

//int GetEncoder3Pulse(void)
//{    //配合小车轮子运动方向，可进行取反操作
//    //encoderPulse[0] = ((short)__HAL_TIM_GET_COUNTER(&htim1)); //1号电机
//    //encoderPulse[1] = ((short)__HAL_TIM_GET_COUNTER(&htim2)); //2号电机
//    encoderPulse[2] = ((short)__HAL_TIM_GET_COUNTER(&htim5)); //3号电机
//    //encoderPulse[3] = ((short)__HAL_TIM_GET_COUNTER(&htim8)); //4号电机	
// 
//   // __HAL_TIM_GET_COUNTER(&htim1) = 0;   //计数值重新清零
//   // __HAL_TIM_GET_COUNTER(&htim2) = 0;  
//    __HAL_TIM_GET_COUNTER(&htim5) = 0;   //计数值重新清零
//   // __HAL_TIM_GET_COUNTER(&htim8) = 0; 
//}


//int GetEncoder4Pulse(void)
//{    //配合小车轮子运动方向，可进行取反操作
//    //encoderPulse[0] = ((short)__HAL_TIM_GET_COUNTER(&htim1)); //1号电机
//    //encoderPulse[1] = ((short)__HAL_TIM_GET_COUNTER(&htim2)); //2号电机
//    //encoderPulse[2] = ((short)__HAL_TIM_GET_COUNTER(&htim5)); //3号电机
//    encoderPulse[3] = ((short)__HAL_TIM_GET_COUNTER(&htim8)); //4号电机	
// 
//    //__HAL_TIM_GET_COUNTER(&htim1) = 0;   //计数值重新清零
//    //__HAL_TIM_GET_COUNTER(&htim2) = 0;  
//    //__HAL_TIM_GET_COUNTER(&htim5) = 0;   //计数值重新清零
//    __HAL_TIM_GET_COUNTER(&htim8) = 0; 
//}

//short GETimer2Encoder(void)
//{
// short data=0;
// data=(short)__HAL_TIM_GET_COUNTER(&htim2)/4;
// direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2);  
// __HAL_TIM_SetCounter(&htim2,0);
// return data;
//}
//short GETimer1Encoder(void)
//{
// short data2=0;
// data2=(short)__HAL_TIM_GET_COUNTER(&htim1)/4;//这里除四是因为一个周期捕获四次脉冲
// direction2= __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim1);
// __HAL_TIM_SetCounter(&htim1,0);

// return data2;

//}


