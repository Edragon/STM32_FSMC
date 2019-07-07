#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"
#include "oled.h" 	
#include "oledhz.h"	
  
//Mini STM32开发板-扩展实验3
//OLED汉字显示			 
//正点原子@ALIENTEK
//2010/8/22
   
int main(void)
{				  
 	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	LED_Init();		  	 //初始化与LED连接的硬件接口
												   
	OLED_Init();			//初始化液晶     
	OLED_Refresh_Gram();	 				    		  
	OLED_ShowString22(20,10,"ALIENTEK");
	OLED_ShowString22(4,32,"STM32"); 
	OLED_ShowFont22(59,32,0,1);
	OLED_ShowFont22(81,32,1,1);
	OLED_ShowFont22(103,32,2,1);
	OLED_Refresh_Gram();	 
		
	while(1) 
	{	
		delay_ms(300);
		LED0=!LED0;
	}	  
}

























