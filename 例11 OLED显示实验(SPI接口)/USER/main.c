#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"   //��ʾͼƬ���ļ�

//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com ��Ʒ  ********/



//STM32������
//OLED��ʾʵ��  




 int main(void)
 {	
	delay_init();	    	    //��ʱ������ʼ��	  
	NVIC_Configuration();   //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 	LED_Init();			        //LED�˿ڳ�ʼ��
	OLED_Init();			      //��ʼ��OLED      
	 
	 
	while(1) 
	{		

		LED=!LED;
		
		OLED_Clear();
		OLED_ShowCHinese(0,0,0);//Ƕ
		OLED_ShowCHinese(18,0,1);//��
		OLED_ShowCHinese(36,0,2);//ʽ
		OLED_ShowCHinese(54,0,3);//��
		OLED_ShowCHinese(72,0,4);//��
		OLED_ShowCHinese(90,0,5);//��
		
    OLED_ShowString(0,3,"mcudev.taobao.com"); 
		OLED_ShowString(0,6,"096' OLED TEST");
		delay_ms(800);
		delay_ms(800);

		OLED_Clear();
		
		OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
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

