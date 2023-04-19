#include  "oled.h"
#include  "oledfont.h"
#define OLED_ADD 0x78 
void WriteCmd(uint8_t  I2C_Command)
{
	 
	HAL_I2C_Mem_Write(&hi2c1,OLED_ADD,0x00,I2C_MEMADD_SIZE_8BIT,&I2C_Command,1,100);
}
void WriteDat(uint8_t  I2C_Data)
{
	HAL_I2C_Mem_Write(&hi2c1,OLED_ADD,0x40,I2C_MEMADD_SIZE_8BIT,&I2C_Data,1,100);
}
void OLED_Set_Pos(uint8_t x,uint8_t  y)
{
	 WriteCmd(0xb0+y);
	 WriteCmd(((x&0xf0)>>4)|0x10);
	 WriteCmd((x&0x0f)|0x01); 
}
void OLED_Fill(uint8_t fill_Data)//È«ÁÁ0xff È«Ãð0x00
{
	uint8_t m,n;
	for(m=0;m<8;m++)
	{
		 WriteCmd(0xb0+m);		//page0-page1
	 WriteCmd(0x00);		//low column start address
		 WriteCmd(0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				WriteDat(fill_Data);
			}
	}
}
void OLED_Init(void)
{ 	
	HAL_Delay(100);
	
	WriteCmd(0xAE);//--display off
	WriteCmd(0x00);//---set low column address
	WriteCmd(0x10);//---set high column address
	WriteCmd(0x40);//--set start line address  
	WriteCmd(0xB0);//--set page address
	WriteCmd(0x81); // contract control
	WriteCmd(0xFF);//--128   
	WriteCmd(0xA1);//set segment remap 
	WriteCmd(0xA6);//--normal / reverse
	WriteCmd(0xA8);//--set multiplex ratio(1 to 64)
  WriteCmd(0x3F);//--1/32 duty
	WriteCmd(0xC8);//Com scan direction
	WriteCmd(0xD3);//-set display offset
	WriteCmd(0x00);//
	WriteCmd(0xD5);//set osc division
  WriteCmd(0x80);//
	WriteCmd(0xD8);//set area color mode off
	WriteCmd(0x05);//
	
	WriteCmd(0xD9);//Set Pre-Charge Period
	WriteCmd(0xF1);//
	
	WriteCmd(0xDA);//set com pin configuartion
	WriteCmd(0x12);//
	
	WriteCmd(0xDB);//set Vcomh
	WriteCmd(0x30);//
	
	WriteCmd(0x8D);//set charge pump enable
	WriteCmd(0x14);//
	WriteCmd(0xAF);//--turn on oled panel
	
	WriteCmd(0x00);
}
 
void OLED_display_char(uint8_t  x,uint8_t  y,uint8_t chr,uint8_t Char_Size)
{
		unsigned char c=0,i=0;	
		c=chr-' ';//µÃµ½Æ«ÒÆºóµÄÖµ			
		if(x>128-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			WriteDat(F8X16[c*16+i]);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			WriteDat(F8X16[c*16+i+8]);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				WriteDat(F6x8[c][i]);
				
			}
}
	
void OLED_ShowString(uint8_t  x,uint8_t  y,uint8_t ch[],uint8_t  Char_Size)
{
	uint8_t c=0,i=0,j=0;
	switch(Char_Size)
	{
		case 1:
		{
			while(ch[j]!='\0')
			{
				c=ch[j]-32;
				if(x>126)
				{
					x=0;
					y++;
				}
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
				x+=6;
				j++;
			}
		}break;
	  case 2:
		{
			while(ch[j]!='\0')
			{
				c=ch[j]-32;
				if(x>120)
				{
					x=0;
					y++;
				}
				OLED_Set_Pos(x,y);
			 for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				OLED_Set_Pos(x,y+1);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x+=8;
			 j++;
			}
		}break;
   }
}
void OLED_ShowCHinese(uint8_t  x,uint8_t  y,uint8_t  no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				WriteDat(Hzk[2*no][t]);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				WriteDat(Hzk[2*no+1][t]);
				adder+=1;
      }					
}
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    WriteDat(BMP[j++]);   	
	    }
	}
}