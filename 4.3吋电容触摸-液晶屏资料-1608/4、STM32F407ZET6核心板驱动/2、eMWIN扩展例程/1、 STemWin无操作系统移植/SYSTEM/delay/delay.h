#ifndef __DELAY_H
#define __DELAY_H 			   
#include <sys.h>	  
//////////////////////////////////////////////////////////////////////////////////  
 
//使用SysTick的普通计数模式对延迟进行管理(支持ucosii)
//包括delay_us,delay_ms
//STM32F4工程-库函数版本
//淘宝店铺：http://mcudev.taobao.com
//********************************************************************************
//修改说明
//无
//////////////////////////////////////////////////////////////////////////////////
void SysTime_init(void);//初始化系统定时器
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif





























