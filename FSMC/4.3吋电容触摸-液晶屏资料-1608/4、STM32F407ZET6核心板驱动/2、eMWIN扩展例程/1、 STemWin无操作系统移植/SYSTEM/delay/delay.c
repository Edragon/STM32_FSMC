#include "delay.h"
#include "sys.h"
////////////////////////////////////////////////////////////////////////////////// 	 

//////////////////////////////////////////////////////////////////////////////////  
 
//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���(֧��ucosii)
//����delay_us,delay_ms
//STM32F4����-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com
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

//systick�жϷ�����,ʹ��GUIϵͳʹ��
void SysTick_Handler(void)
{				   

	TimingDelay_Decrement();
	OS_TimeMS++;
	
}

void SysTime_init(void)  //ϵͳ��ʱ����ʼ��;
{
	if (SysTick_Config(SystemCoreClock / 1000))//��ʼ��SYSΪ1ms �ж�
  { 
    /* Capture error */ 
    while (1);
  }
	
}

//��ʱnus
//nusΪҪ��ʱ��us��.	
//ע��:nus��ֵ
void delay_us(u32 nus)
{		
	  unsigned short Time;
	  while(nus--)
	  {
	     for(Time=0;Time<9;Time++)__NOP();
	   }	 
}



//��ʱnms 
//nms:0~65535
void delay_ms(u16 nms)
{	 	 
  TimingDelay = nms;

  while(TimingDelay != 0);	
	
} 
	 



































