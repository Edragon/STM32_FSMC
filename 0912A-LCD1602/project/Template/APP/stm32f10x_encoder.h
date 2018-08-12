/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_encoder.h
* Author             : IMS Systems Lab 
* Date First Issued  : 21/11/07
* Description        : This file contains the software implementation for the
*                      encoder position and speed reading.
********************************************************************************
* History:
* 21/11/07 v1.0
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_ENCODER_H
#define __STM32F10x_ENCODER_H

/* Private typedef -----------------------------------------------------------*/
typedef enum {DISPLAY_TIMCNT = 0,DISPLAY_THETA,DISPLAY_W} DisplayType;

/* Includes ------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ENCODER_TIMER   TIM4  // Encoder unit connected to TIM3
#define ENCODER_PPR     11     // number of pulses per revolution
#define ENC_COUNTER_RESET   (u8) 0

#define COUNTER_RESET   (u16)0
#define ICx_FILTER      (u8) 6 // 6<-> 670nsec

#define TIMx_PRE_EMPTION_PRIORITY 1
#define TIMx_SUB_PRIORITY 0



/* Exported functions ------------------------------------------------------- */
void ENC_Init(void);
void ENC_CounterInit(void);
s16 ENC_GetCounter(void);
void TIM3_IRQHandler(void);;

#endif  /*__STM32F10x_ENCODER_H*/
/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
