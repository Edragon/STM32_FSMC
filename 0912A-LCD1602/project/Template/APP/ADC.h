/********************************************************************************
* File Name          : ADC.h
* Author             : FXC
* Version            : V1.0
* Date               : 2011-9-3
* Description        : Header for ADC.c file.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H
#define __ADC_H 1

/* Includes ------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/*****************************************************************************
*                         ADC Core Defines
******************************************************************************/
#define ACC_ADC                  ADC1	
#define ACC_RCC_Periph_ADC       RCC_APB2Periph_ADC1
#define ACC_ADC_Port1            GPIOA
#define ACC_RCC_Port1            RCC_APB2Periph_GPIOA
#define ACC_ADC_DR_Address       ((u32)0x4001244C)

#define ACC_DMA                  DMA1	
#define ACC_RCC_Periph_DMA       RCC_AHBPeriph_DMA1
#define ACC_DMA_Channel          DMA1_Channel1	
#define ACC_DMA_IRQChannel       DMA1_Channel1_IRQChannel	
#define ACC_DMA_FLAG             DMA1_FLAG_TC1

#define ACC_VFB					GPIO_Pin_0 //PA0
#define ACC_I1					GPIO_Pin_1 //PA1
#define ACC_I2					GPIO_Pin_2 //PA2
#define ACC_VREF				GPIO_Pin_3 //PA3

#define ACC_ACD_0				ADC_Channel_0 
#define ACC_ACD_1				ADC_Channel_1
#define ACC_ACD_2				ADC_Channel_2   
#define ACC_ACD_3				ADC_Channel_3


 
#define BufferSize  4

/* Exported functions ------------------------------------------------------- */
void CDQ02Rxx_ADC_Init(void);
void ADC1_Init(void);
void ADC_DMA_Init(void);
void Vref_Read(void);
void ADC_Read(u16* out);
void ADC_Read_Filter(u16* out);

#endif 

/********************************** (C) COPYRIGHT 2011 FXC *****END OF FILE****/
