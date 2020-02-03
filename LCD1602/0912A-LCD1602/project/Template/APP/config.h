#ifndef _CONFIG_H_
#define _CONFIG_H_ 1


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "misc.h"
#include "systic.h"
#include "usart_printf.h"
#include "stm32f10x_encoder.h"
#include "LCD_1602_6wires.h"
#include "ADC.h"
#include <stdio.h>
 


/* Private functions ---------------------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);

#endif
