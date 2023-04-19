#ifndef _OLED_H_
#define _OLED_H_
 
#include "main.h"
 
extern I2C_HandleTypeDef hi2c1;
void WriteCmd(uint8_t  I2C_Command);
void WriteDat(uint8_t  I2C_Data);
void OLED_Init(void);
void OLED_Fill(uint8_t fill_Data);
void OLED_Set_Pos(uint8_t x,uint8_t  y);
void OLED_ShowString(uint8_t  x,uint8_t  y,uint8_t ch[],uint8_t  Char_Size);
void OLED_ShowCHinese(uint8_t  x ,uint8_t  y,uint8_t  no);
void OLED_DrawBMP(uint8_t  x0, uint8_t  y0,uint8_t  x1, uint8_t  y1,uint8_t  BMP[]);
void OLED_display_char(uint8_t  x,uint8_t  y,uint8_t chr,uint8_t Char_Size);
void OLED_ShowCHinese(uint8_t  x,uint8_t  y,uint8_t  no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  