#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"

#include "GUI.h"
#include "Lcd_Driver.h"
#include "TFT_demo.h"


//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com       ********/
 	
 int main(void)
 {	 
 	
	u8 lcd_id[12];			//存放LCD ID字符串
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	 
	Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0," STM32 TFT 1.44 ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  嵌入式开发网   ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com "); 
	 
	 
	sprintf((char*)lcd_id,"Test TFT 1.44");//
	 
  while(1) 
	{		 
		Test_Demo();	//See the test details in QDTFT_Demo.c		
		LED=!LED;					 
		delay_ms(1000);	
	} 
}
