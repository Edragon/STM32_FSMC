/******************** (C) COPYRIGHT 2011 FXC ***********************************
* File Name          : ADC.c
* Author             : FXC
* Version            : V1.0
* Date               : 2011-9-3
* Description        : This file provides a set of functions needed to manage the
*                      communication between STM32 ADC and CDQ03Rxx analog output
*                      using DMA .
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* THIS SOURCE CODE IS PROTECTED BY A LICENSE.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "config.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t ADC_ConvertedValue[BufferSize];
uint32_t Vref = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : CDQ03Rxx_ADC_Init
* Description    : Initializes the ADC peripheral used to drive the CDQ03Rxx
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CDQ02Rxx_ADC_Init(void)
{
  	ADC1_Init();
	ADC_DMA_Init();
	
	/* Enable ACC_ADC DMA */
	ADC_DMACmd(ACC_ADC, ENABLE);

	ADC_Cmd(ACC_ADC, ENABLE);
	DMA_Cmd(ACC_DMA_Channel, ENABLE);
	ADC_SoftwareStartConvCmd(ACC_ADC, ENABLE); 
	
	Delay_ms(1000);	
	Vref_Read();
}

/*******************************************************************************
* Function Name  : ADC_Init
* Description    : ADC Initializes
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC1_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
  ADC_InitTypeDef ADC_InitStructure;
 
  RCC_APB2PeriphClockCmd(ACC_RCC_Port1 | ACC_RCC_Periph_ADC, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = ACC_VFB | ACC_I1 | ACC_I2 | ACC_VREF;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(ACC_ADC_Port1, &GPIO_InitStructure);   

  /* ADC configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel =4;

  /* ACC_ADC regular channel configuration */ 
  ADC_RegularChannelConfig(ACC_ADC, ACC_ACD_0, 1,ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ACC_ADC, ACC_ACD_1, 2,ADC_SampleTime_239Cycles5);  
  ADC_RegularChannelConfig(ACC_ADC, ACC_ACD_2, 3,ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ACC_ADC, ACC_ACD_3, 4,ADC_SampleTime_239Cycles5);
  
  ADC_Init(ACC_ADC, &ADC_InitStructure);
  
  /* Enable ACC_ADC */
  ADC_Cmd(ACC_ADC, ENABLE);

  /* Enable ACC_ADC reset calibaration register */   
  ADC_ResetCalibration(ACC_ADC);
  /* Check the end of ACC_ADC reset calibration register */
  while(ADC_GetResetCalibrationStatus(ACC_ADC));

  /* Start ACC_ADC calibaration */
  ADC_StartCalibration(ACC_ADC);
  /* Check the end of ACC_ADC calibration */
  while(ADC_GetCalibrationStatus(ACC_ADC));
}


/*******************************************************************************
* Function Name  : DMA_Init
* Description    : Initializes the DMA peripheral used to drive the CDQ03Rxx
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_DMA_Init(void)
{
  DMA_InitTypeDef  DMA_InitStructure; 
//  NVIC_InitTypeDef NVIC_InitStructure;
  /* DMA Channel5 configuration ----------------------------------------------*/
  
  RCC_AHBPeriphClockCmd(ACC_RCC_Periph_DMA, ENABLE);

/*  if DMA interrupt is used insert here the NVIC conf es: */
  
//  NVIC_InitStructure.NVIC_IRQChannel = ACC_DMA_IRQChannel;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
 
  DMA_DeInit(ACC_DMA_Channel);
  DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)ACC_ADC_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = BufferSize;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(ACC_DMA_Channel, &DMA_InitStructure);
  
  
  /* Enable DMA Channel Transfer Complete interrupt if used  --> fill the relative IIRQ in the stm32f10x_it.c file */

//  DMA_ITConfig(ACC_DMA_Channel, DMA_IT_TC, ENABLE);
  
    /* Enable DMA Channel1 */

//  DMA_Cmd(ACC_DMA_Channel, ENABLE);

}

/*******************************************************************************
* Function Name  : Vref_Read
* Description    : Read the ADC Vref 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Vref_Read(void)
{
	uint16_t i;
	uint32_t tem = 0;

  	for(i=0; i< 256; i++)
  	{
		while(!(DMA_GetFlagStatus(ACC_DMA_FLAG)));
		DMA_ClearFlag(ACC_DMA_FLAG);
		 
		tem = 4096*2490/ADC_ConvertedValue[3];
		Vref += tem;
  	}
  	
  	Vref >>= 8;
  	
	if((Vref<3250) || (Vref>3350))
	{
		Vref = 3300;
	}
}

/*******************************************************************************
* Function Name  : ADC_Read
* Description    : Read the ADC output 
* Input          : out : u16 buffer to store data
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_Read(u16* out)
{
  uint8_t i;

  while(!(DMA_GetFlagStatus(ACC_DMA_FLAG)));
  DMA_ClearFlag(ACC_DMA_FLAG);

  for(i=0; i< (BufferSize-1); i++)
  {	
	*out=ADC_ConvertedValue[i]*Vref>>12;	// V=(AD_Value/4096)*Vref
    out++;  
  }
}

/*******************************************************************************
* Function Name  : ADC_Read_Filter
* Description    : 平均值算法
* Input          : out : u16 buffer to store data
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_Read_Filter(u16* out)
{
	uint16_t  ADC_ReadData[4];
	uint32_t  ADC_OutData[4];
	uint16_t  i, p;

	

	for(p=0; p<3; p++)
	{
		ADC_OutData[p] = 0;
	}

	for(i=0; i<16; i++)  
	{
		Delay_ms(1);
		ADC_Read(ADC_ReadData);

		for(p=0; p<3; p++)
		{
			ADC_OutData[p] += ADC_ReadData[p];
		}
	}

	for(p=0; p<3; p++)
	{
		*out = (uint16_t)(ADC_OutData[p] >> 4);	
		out++;  
	}

}


/************************************ (C) COPYRIGHT 2011 FXC *****END OF FILE****/

