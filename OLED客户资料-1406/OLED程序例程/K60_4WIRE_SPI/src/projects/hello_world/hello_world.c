/*
 * File:		hello_world.c
 * Purpose:		Main process
 *
 */

#include "common.h"
#include"HAL_SPI.h"
#include "SPI_FLASH.H"
#include "uart.h"
#include "sysinit.h"
#include "start.h"

unsigned long Time;
/********************************************************************/
void main (void)
{
         gpio_init  (PORTB,23,GPO,HIGH); //初始化LED1引脚
      
         gpio_init  (PORTB,22,GPO,HIGH); //初始化LED2/C引脚
         
        SPI_Init(SPI0, SPI_SCK_DIV_512, 1); //选择SPI0 100Mhz /64 = 1.5Mhz
        
        OLED_Init();			//初始化OLED      
  	OLED_ShowString(1,0, "0.96' OLED TEST");  
  	OLED_ShowString(1,16,"mcudev.taobao");  
  	//"欢迎光临");  
        OLED_ShowCHinese(1,32,0);
         OLED_ShowCHinese(16,32,0);
          OLED_ShowCHinese(32,32,1);
           OLED_ShowCHinese(48,32,2);
            OLED_ShowCHinese(64,32,3);
             OLED_ShowCHinese(80,32,4);
             OLED_ShowCHinese(96,32,0);
             OLED_ShowCHinese(112,32,0);
             
        
        
        OLED_ShowString(1,48,"         2014-05");    

        
	while(1)
	{
	
          GPIO_SET(PORTB,23,0);//LED灯
          
         for(Time=0;Time<0xfffff;Time++);//延时
          
          GPIO_SET(PORTB,23,1);
          
         for(Time=0;Time<0xfffff;Time++);//延时
           
          GPIO_SET(PORTB,22,0);//LED灯
          
        for(Time=0;Time<0xfffff;Time++);//延时
    
          GPIO_SET(PORTB,22,1);
         
          
          
	} 
}








/********************************************************************/
