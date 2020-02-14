//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//使用SysTick的普通计数模式对延迟进行管理
//包括delay_us,delay_ms
//冰火青云电子
//店铺地址：http://shop73023976.taobao.com/shop/view_shop.htm?tracelog=twddp&trace_log=qianniu_pc
//修改日期:2014/3/16
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 冰火青云电子2014/3/16
//All rights reserved
//********************************************************************************
#include "delay.h"
#include "oled.h"


 int main(void)
 {	u8 t;
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级// 	LED_Init();			     //LED端口初始化
	OLED_Init();			//初始化OLED      
  	OLED_ShowString(1,0, "0.96' OLED TEST");  
  	OLED_ShowString(1,16,"ICEFIRE@QINGYUN");  
   	OLED_ShowString(1,32,"2014/03/16");  
  	OLED_ShowString(1,48,"ASCII:");  
  	OLED_ShowString(63,48,"CODE:");  
	
/*	 OLED_ShowCHinese(13,16,0);
	 OLED_ShowCHinese(33,16,1);
	 OLED_ShowCHinese(53,16,2);
	 OLED_ShowCHinese(73,16,3);
	 OLED_ShowCHinese(93,16,4);
	 OLED_ShowCHinese(113,16,5);
	 OLED_ShowCHinese(33,36,6);
	 OLED_ShowCHinese(53,36,7);
	 OLED_ShowCHinese(73,36,8);
	 OLED_ShowCHinese(93,36,9);*/
//OLED_Refresh_Gram();	 
	t=' ';  
	while(1) 
	{		
		OLED_ShowChar(48,48,t,16,1);//显示ASCII字符	   	OLED_Refresh_Gram();
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,48,t,3,16);//显示ASCII字符的码值 
		delay_ms(300);
	}	  
	
}

