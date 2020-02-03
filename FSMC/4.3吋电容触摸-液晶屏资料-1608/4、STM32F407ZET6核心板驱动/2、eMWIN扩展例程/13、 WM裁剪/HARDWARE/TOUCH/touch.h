#ifndef _TOUCH_H
#define _TOUCH_H
#include "sys.h"
#include "ott2001a.h"

//////////////////////////////////////////////////////////////////////////////////	 
 
//触摸屏驱动   
//STM32F4工程-库函数版本
//淘宝店铺：http://mcudev.taobao.com								   
//////////////////////////////////////////////////////////////////////////////////
						
			
						
#define FT6206_ADDR		0x70
#define TOUCH_ADD			0x70  //地址为0x38要移一位
						



void I2C1_Send_Byte(uint8_t dat);
uint8_t I2C1_Read_Byte(uint8_t ack);
uint8_t I2C1_WaitAck(void);

void I2C1_Delay_us(u16 cnt);

uint8_t CheckSum(uint8_t *buf);

uint8_t FT6206_Read_Reg(uint8_t *pbuf,uint32_t len);

void Touch_GPIO_Config(void);


u8 TP_Init(void);								//初始化


#endif

