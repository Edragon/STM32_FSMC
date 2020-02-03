/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name			: usart_printf.c
* Author			: 晓晓
* Version			: V1.0
* Date				: 2009.7.27
* Description		: printf 串口函数
*******************************************************************************/

#include "config.h"
#include <stdio.h>

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/*******************************************************************************
* Function Name  : UART1_Configuration
* Description    : Configures the uart1 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART1_Configuration(void)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE); //打开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  
  
	// Configure USART1_Tx as alternate function push-pull 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Configure USART1_Rx as input floating 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
	/* Configure the USART1*/ 
	USART_Init(USART1, &USART_InitStructure);  
    
	/* Enable the USART1 */
	USART_Cmd(USART1, ENABLE);  
}


/*******************************************************************************
* Function Name  : Retargets the C library printf function to the USART.
* Description    : printf a char to the uart.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

/*******************************************************************************
* Function Name  : Uart1_PutChar
* Description    : printf a char to the uart.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Uart1_PutChar(u8 ch)
{
	/* Write a character to the USART */
	USART_SendData(USART1, (u8) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
	{
	}	
}


/*******************************************************************************
* Function Name  : USART_Scanf_Cmd
* Description    : Gets Char values from the hyperterminal.
* Input          : None
* Output         : None
* Return         : Length
*******************************************************************************/
void USART_Scanf_Cmd(char * str)
{	
    uint8_t index = 0;    
    while(1) 
    {
        /* Loop until RXNE = 1 */
        while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {}        
		str[index++] = (USART_ReceiveData(USART1));	    
    	if((str[index - 1] == 13) || (index >= 32) )//回车
	    {  
	        return;
        }
    }
}


