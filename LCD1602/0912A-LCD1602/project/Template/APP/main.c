/*******************************************************************************
* IAR Embedded Workbench 5.4  
* Chip type           : STM32F103CB
* Program type        : Application
* Clock frequency     : 8.000000 MHz
* Memory model        : 
* External SRAM size  : 
* Data Stack size     : 
*--------------文件信息---------------------------------------------------------
* File Name           : main.c
* Author              : 晓晓
* Version             : V1.0
* Date                : 2010/04/3
* Description         : Main program body
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "config.h"



s16 counter = 0;

void main(void)
{	 
    char st[]="";	//定义字符串数字
	char adc[]="";
	uint16_t adc_temp[3];
	
	/* System Clocks Configuration */
	RCC_Configuration();    
	/* NVIC configuration */
	NVIC_Configuration();
	SysTick_IntConfig();	
	UART1_Configuration();	
	CDQ02Rxx_ADC_Init();
	ENC_Init();
	

	lcd_init  ();
	lcd_clear ();	
	Delay_ms(100);	
	
	set_cursor(1,2);
    lcd_print("STM32F0912A");
	
	set_cursor(1,2);
    lcd_print("mV");
	


	while (1)
	{
		counter = ENC_GetCounter();
		sprintf(st, "%4d", counter);	//变量转化为字符串		
        set_cursor(1,2);
		lcd_print(st);	//显示字符串
		
		ADC_Read_Filter(adc_temp);
		sprintf(adc, "%4d", adc_temp[0]);	//变量转化为字符串
		set_cursor(8,2);
		lcd_print(adc);	//显示字符串		
		
		Delay_ms(100);

	}
}



/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the LED GPIO.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 
    
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);   //关闭JTAG
	
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
        
}

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
    SystemInit ();
  	
    /* Enable GPIOAclock */  
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configure the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
}


/**********************************END OF FILE*********************************/


