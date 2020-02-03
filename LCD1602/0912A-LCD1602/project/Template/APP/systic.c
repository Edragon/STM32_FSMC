/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name      : SysTick.c
* Author         : 晓晓
* Version        : V1.0
* Date           : 04/05/2009
* Description    : 系统定时器函数。
*******************************************************************************/

#include "config.h" 

static __IO uint32_t TimingDelay;//全局变量声明 

 
/*******************************************************************************
* Function Name  : SysTick_Config
* Description    : systick初始化函数.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
 void SysTick_IntConfig(void)
{ 
    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(SystemFrequency / 1000))
    { 
        /* Capture error */ 
        while (1);       
    }
} 
 

 
/*******************************************************************************
* Function Name  : Delay_ms
* Description    : 延迟毫秒的函数.
* Input          : nTime 需要延时的时间，单位为毫秒
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_ms(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}


/*******************************************************************************
* Function Name  : TimingDelay_Decrement
* Description    : 递减变量函数，函数名由“stm32f10x_it.c”中的中断响应函数定义
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/ 
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}