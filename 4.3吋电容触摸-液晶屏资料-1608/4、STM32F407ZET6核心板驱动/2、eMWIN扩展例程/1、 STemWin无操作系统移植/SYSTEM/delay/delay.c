#include "delay.h"
#include "sys.h"
////////////////////////////////////////////////////////////////////////////////// 	 

//////////////////////////////////////////////////////////////////////////////////  
 
//使用SysTick的普通计数模式对延迟进行管理(支持ucosii)
//包括delay_us,delay_ms
//STM32F4工程-库函数版本
//淘宝店铺：http://mcudev.taobao.com
////////////////////////////////////////////////////////////////////////////////// 
 


static __IO uint32_t TimingDelay;



void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0)
  { 
    TimingDelay--;
  }
}


extern __IO int32_t OS_TimeMS;

//systick中断服务函数,使用GUI系统使用
void SysTick_Handler(void)
{				   

	TimingDelay_Decrement();
	OS_TimeMS++;
	
}

void SysTime_init(void)  //系统定时器初始化;
{
	if (SysTick_Config(SystemCoreClock / 1000))//初始化SYS为1ms 中断
  { 
    /* Capture error */ 
    while (1);
  }
	
}

//延时nus
//nus为要延时的us数.	
//注意:nus的值
void delay_us(u32 nus)
{		
	  unsigned short Time;
	  while(nus--)
	  {
	     for(Time=0;Time<9;Time++)__NOP();
	   }	 
}



//延时nms 
//nms:0~65535
void delay_ms(u16 nms)
{	 	 
  TimingDelay = nms;

  while(TimingDelay != 0);	
	
} 
	 



































