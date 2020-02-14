#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"

#include "GUI.h"
#include "Lcd_Driver.h"
#include "TFT_demo.h"


//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com       ********/
 	
 int main(void)
 {	 
 	
	u8 lcd_id[12];			//���LCD ID�ַ���
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	 
	Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0," STM32 TFT 1.44 ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  Ƕ��ʽ������   ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com "); 
	 
	 
	sprintf((char*)lcd_id,"Test TFT 1.44");//
	 
  while(1) 
	{		 
		Test_Demo();	//See the test details in QDTFT_Demo.c		
		LED=!LED;					 
		delay_ms(1000);	
	} 
}
