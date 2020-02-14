/*
 * File:		io.c
 * Purpose:		Serial Input/Output routines
 *
 * Notes:       TERMINAL_PORT defined in <board>.h
 */

#include "common.h"
#include "uart.h"



volatile struct GPIO_MemMap *GPIOx[5] = {PTA_BASE_PTR, PTB_BASE_PTR, PTC_BASE_PTR, PTD_BASE_PTR, PTE_BASE_PTR}; //�������ָ�����鱣�� GPIOx �ĵ�ַ
volatile struct PORT_MemMap *PORTX[5] = {PORTA_BASE_PTR, PORTB_BASE_PTR, PORTC_BASE_PTR, PORTD_BASE_PTR, PORTE_BASE_PTR};

/*************************************************************************
*
*  �������ƣ�gpio_init
*  ����˵������ʼ��gpio
*  ����˵����PORTx       �˿ںţ�PORTA,PORTB,PORTC,PORTD,PORTE��
*            n           �˿�����
*            IO          ���ŷ���,0=����,1=���
*            data        �����ʼ״̬,0=�͵�ƽ,1=�ߵ�ƽ ����������Ч��
*  �������أ���
*  �޸�ʱ�䣺2012-1-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void gpio_init (PORTx portx, u8 n, GPIO_CFG cfg, u8 data)
{
    ASSERT( (n < 32u)  && (data < 2u) );           //ʹ�ö��Լ�����롢��ƽ �Ƿ�Ϊ1bit

    //ѡ���ܽ� PORTx_PCRx ��ÿ���˿ڶ��и��Ĵ��� PORTx_PCRx
    PORT_PCR_REG(PORTX[portx], n) = (0 | PORT_PCR_MUX(1) | cfg);

    //�˿ڷ���������뻹�����
    if( ( (cfg & 0x01) == GPI) || (cfg == GPI_UP) ||     (cfg == GPI_UP_PF)      )
        //   ���λΪ0������   ||   ��������ģʽ  ||   ��������������Դ�˲���
    {
        GPIO_PDDR_REG(GPIOx[portx]) &= ~(1 << n);  //���ö˿ڷ���Ϊ����
    }
    else
    {
        GPIO_PDDR_REG(GPIOx[portx]) |= (1 << n);    //���ö˿ڷ���Ϊ���
        if(data == 1)//output
        {
            GPIO_SET(portx, n, 1);                  //�Զ˿�������ƣ����Ϊ1
        }
        else
        {
            GPIO_SET(portx, n, 0);                  //�Զ˿�������ƣ����Ϊ0
        }
    }
}

/*************************************************************************
*
*  �������ƣ�gpio_set
*  ����˵������������״̬
*  ����˵����PORTx       �˿ںţ�PORTA,PORTB,PORTC,PORTD,PORTE��
*            n           �˿�����
*            data        �����ʼ״̬,0=�͵�ƽ,1=�ߵ�ƽ
*  �������أ���
*  �޸�ʱ�䣺2012-1-16   �Ѳ���
*  ��    ע��
*************************************************************************/
void gpio_set (PORTx portx, u8 n, u8 data)
{
    ASSERT( (n < 32u)  && (data < 2u) );           //ʹ�ö��Լ�����롢��ƽ �Ƿ�Ϊ1bit

    if(data == 1)               //���
        GPIO_SET(portx, n, 1);  //GPIO_PDOR_REG(PORTx) |= (1<<n);
    else
        GPIO_SET(portx, n, 0);  //GPIO_PDOR_REG(PORTx) &= ~(1<<n);
}

/*************************************************************************
*
*  �������ƣ�gpio_turn
*  ����˵������ת����״̬
*  ����˵����PORTx       �˿ںţ�PORTA,PORTB,PORTC,PORTD,PORTE��
*            n           �˿�����
*  �������أ���
*  �޸�ʱ�䣺2012-1-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void gpio_turn (PORTx portx, u8 n)
{
    ASSERT( n < 32u );           //ʹ�ö��Լ�����ź�
    GPIO_TURN(portx, n);
}

/*************************************************************************
*
*  �������ƣ�gpio_get
*  ����˵������ȡ��������״̬
*  ����˵����PORTx       �˿ںţ�PORTA,PORTB,PORTC,PORTD,PORTE��
*            n           �˿�����
*  �������أ���
*  �޸�ʱ�䣺2012-1-15   �Ѳ���
*  ��    ע��
*************************************************************************/
u8 gpio_get(PORTx portx, u8 n)          //��ȡ����״̬
{
    ASSERT( n < 32u );                  //ʹ�ö��Լ�����ź�
    return GPIO_Get(portx, n);
}




/********************************************************************/
char
in_char (void)
{
	return uart_getchar(TERM_PORT);
}
/********************************************************************/
void
out_char (char ch)
{
	uart_putchar(TERM_PORT, ch);
}
/********************************************************************/
int
char_present (void)
{
	return uart_getchar_present(TERM_PORT);
}
/********************************************************************/