#ifndef _TOUCH_H
#define _TOUCH_H
#include "sys.h"
#include "ott2001a.h"

//////////////////////////////////////////////////////////////////////////////////	 
 
//����������   
//STM32F4����-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com								   
//////////////////////////////////////////////////////////////////////////////////
						
			
						
#define FT6206_ADDR		0x70
#define TOUCH_ADD			0x70  //��ַΪ0x38Ҫ��һλ
						



void I2C1_Send_Byte(uint8_t dat);
uint8_t I2C1_Read_Byte(uint8_t ack);
uint8_t I2C1_WaitAck(void);

void I2C1_Delay_us(u16 cnt);

uint8_t CheckSum(uint8_t *buf);

uint8_t FT6206_Read_Reg(uint8_t *pbuf,uint32_t len);

void Touch_GPIO_Config(void);


u8 TP_Init(void);								//��ʼ��


#endif

