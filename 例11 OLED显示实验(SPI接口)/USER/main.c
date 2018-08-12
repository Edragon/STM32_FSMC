#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"   //显示图片的文件

//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com 出品  ********/



//STM32开发板
//OLED显示实验  




 int main(void)
 {	
	delay_init();	    	    //延时函数初始化	  
	NVIC_Configuration();   //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	LED_Init();			        //LED端口初始化
	OLED_Init();			      //初始化OLED      
	 
	 
	while(1) 
	{		

		LED=!LED;
		
		OLED_Clear();
		OLED_ShowCHinese(0,0,0);//嵌
		OLED_ShowCHinese(18,0,1);//入
		OLED_ShowCHinese(36,0,2);//式
		OLED_ShowCHinese(54,0,3);//开
		OLED_ShowCHinese(72,0,4);//发
		OLED_ShowCHinese(90,0,5);//网
		
    OLED_ShowString(0,3,"mcudev.taobao.com"); 
		OLED_ShowString(0,6,"096' OLED TEST");
		delay_ms(800);
		delay_ms(800);

		OLED_Clear();
		
		OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
		delay_ms(800);	

		OLED_DrawBMP(0,0,128,8,BMP3);
		delay_ms(800);	

		OLED_DrawBMP(0,0,128,8,BMP4);
		delay_ms(800);	

		OLED_DrawBMP(0,0,128,8,BMP5);
		delay_ms(800);	

		OLED_DrawBMP(0,0,128,8,BMP6);
		delay_ms(800);	

		
		
	}	  
	
}

