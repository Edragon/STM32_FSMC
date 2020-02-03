#include "touch.h"
#include "LCD_DRV.h"
#include "delay.h"
#include "stdlib.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////////////////	 
 
//电容触摸屏驱动代码	   
//STM32F4工程-库函数版本
//淘宝店铺：http://mcudev.taobao.com								   
//////////////////////////////////////////////////////////////////////////////////

													//通讯端口配置		
#define			CLR_SCL()			GPIO_ResetBits(GPIOB, GPIO_Pin_0)
   
#define			SET_SCL()			GPIO_SetBits(GPIOB, GPIO_Pin_0)

#define			CLR_SDA()			GPIO_ResetBits(GPIOF, GPIO_Pin_11)

#define			SET_SDA()			GPIO_SetBits(GPIOF, GPIO_Pin_11)

#define			READ_SDA()		  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_11) 


//*************************************************
//函数名称 : void Touch_GPIO_Config(void)  
//功能描述 : 设置触屏的IIC引脚,用软件模拟的方法实现IIC功能
//输入参数 : 
//输出参数 : 
//返回值   : 
//*************************************************
void Touch_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

/*************************IIC**************************************/

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOF, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;  //PB0  
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;  //输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;  //上拉输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11; //PF11
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;  //输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;  //上拉输出
	GPIO_Init(GPIOF, &GPIO_InitStructure);
 

  GPIO_SetBits(GPIOB, GPIO_Pin_0);  //设置为高输出

  GPIO_SetBits(GPIOF, GPIO_Pin_11); //设置为高输出
	
//	I2C1_Stop();
}


/****************************************************************************

                      模拟IIC程序

**************************************************************************/

void SDA_Out(void)
	
	{
	  
  
	  GPIO_InitTypeDef GPIO_InitStructure;
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	    //初始化SDA
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	  //推挽输出
		GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;    //推挽输出
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOF, &GPIO_InitStructure); 
	
	}


 void SDA_In(void)
	{

    GPIO_InitTypeDef GPIO_InitStructure;
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	    //初始化SDA
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	  //浮空输入
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOF, &GPIO_InitStructure); 
	
	}


const unsigned char cucBit2[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

void DelayIntr(unsigned char Time_CLK)
	{
	  
	  unsigned short Time;
	  while(Time_CLK--)
	  {
	     for(Time=0;Time<9;Time++)__NOP();
	   } 
	    	
	}

void I2C1_Start(void)
{
	
	SDA_Out();
	
	SET_SDA();
	SET_SCL();
	DelayIntr(4);
	CLR_SDA();							
	DelayIntr(4);
	CLR_SCL();		
}

void I2C1_Stop(void)
{
	SDA_Out();
	CLR_SCL();
    CLR_SDA(); 
    DelayIntr(4);
	SET_SCL();
	DelayIntr(4);
	SET_SDA();	
}


unsigned char I2C1_WaitAck(void)
{
	unsigned long ucErrTime2 = 0xfffff;	
	
	unsigned char SDA_Indata;
		
	   SDA_In();//DDRM_DDRM4=0;  //数据接收方向切换----接收
	          
	   SET_SDA();

     DelayIntr(1);

	   SET_SCL();

	   DelayIntr(1);

	   SDA_Indata=READ_SDA(); 
	         
       while(SDA_Indata==1)
         {
             SDA_Indata=READ_SDA();
						 DelayIntr(1);
						 ucErrTime2--; 

             if (ucErrTime2 == 0) 
                 {
										 I2C1_Stop();
                     return (1);

                 }
          }


       CLR_SCL();
       return (0);
}

void SendAck2(void)
{
	CLR_SCL();

	SDA_Out();

    CLR_SDA();

	DelayIntr(2);

	SET_SCL();

  	DelayIntr(2);

  	CLR_SCL();	
}

void SendNotAck2(void)
{
	CLR_SCL(); 

	SDA_Out();

    SET_SDA();

  	DelayIntr(2);

 	SET_SCL();

  	DelayIntr(2);

  	CLR_SCL();	
}


void I2C1_Send_Byte(unsigned char ucData2)
{
	unsigned char IIC_i;

	SDA_Out();//设置为输出

	CLR_SCL();

	for (IIC_i=0;IIC_i<8;IIC_i++)
	{
		
	
		if ( (ucData2 & cucBit2[IIC_i]) != 0)
		      {
		       	SET_SDA();
	       	}
		else
		      {
		        CLR_SDA();
		      }


		DelayIntr(2);

		SET_SCL();

		DelayIntr(2);
		
		CLR_SCL();

		DelayIntr(2);
		
				
	};

}

//读1个字节，ack=1时，发送ACK，ack=0，发送nACK  
unsigned char I2C1_Read_Byte(unsigned char ACK)
{
	unsigned char ucData2 = 0x00;
	unsigned char IIC_i;
	
	SDA_In();//数据接收方向切换----接收

	SET_SDA();

	for (IIC_i=0;IIC_i<8;IIC_i++)
	{
			
		CLR_SCL();
		DelayIntr(2);
		SET_SCL();
		//SDA_In();//DDRM_DDRM4=0;	 //数据接收方向切换----接收
		
		if (READ_SDA())
		{
			ucData2 |= cucBit2[IIC_i];
		}
		DelayIntr(1);
				  
	};
	
	if(!ACK)
	{
	    SendNotAck2();
	}
	else SendAck2();//发送应答
	//SDA_Out();//DDRM_DDRM4=1;	   //数据接收方向切换----接收
	
	
	return ucData2;
}










/****************************************************************************************
																	电容屏 FT6336芯片驱动

***************************************************************************************/
typedef struct
{
	uint16_t cx1; //CTP_X1
	uint16_t cy1; //CTP_Y1
	uint16_t cx2; //CTP_X2
	uint16_t cy2; //CTP_Y2
}CTP_Stru;

CTP_Stru	CTP_Dat;

typedef struct 
{
	uint8_t packet_id;
	uint8_t xh_yh;
	uint8_t xl;
	uint8_t yl;
	uint8_t dxh_dyh;
	uint8_t dxl;
	uint8_t dyl;
  uint8_t checksum;
}TpdTouchData;

//static uint8_t FT6206_Write_Reg(uint8_t startaddr,uint8_t *pbuf,uint32_t len)
//{
//	__IO uint16_t i = 0,j = 0;
//	
//	I2C1_Start();
//	//I2C1_Send_Byte(FT6206_ADDR);
//	do
//	{
//		I2C1_Send_Byte(FT6206_ADDR);

//		if(++i >= 1000)	//Time Out
//		{
//			I2C1_Stop();
//			return 1;
//		}
//	}while(I2C1_WaitAck());	//Read Ack
//	
//	i = 0;
//	do
//	{
//		I2C1_Send_Byte(startaddr);	//Send Sub Address
//		if(++i >= 1000)	//Time Out
//		{
//			I2C1_Stop();
//			return 1;
//		}
//	}while(I2C1_WaitAck());	//Read Ack
//	for(i=0; i<len; i++)
//	{
//		j=0;
//		do
//		{
//			I2C1_Send_Byte(pbuf[i]);
//			
//			if(++j >= 1000)	//Time Out
//			{
//				I2C1_Stop();
//				return 1;
//			}
//		}while(I2C1_WaitAck());	//Read Ack
//	}
//	I2C1_Stop();
//	return 0;
//}


u8 FT6206_Read_Reg1(u8 RegIndex)
{
	unsigned char receive=0;

	I2C1_Start();
	I2C1_Send_Byte(FT6206_ADDR);
	I2C1_WaitAck();
	I2C1_Send_Byte(RegIndex);
	I2C1_WaitAck();
	
	I2C1_Start();
	I2C1_Send_Byte(FT6206_ADDR+1);
	I2C1_WaitAck();	
	receive=I2C1_Read_Byte(0);
	I2C1_Stop();	 
	return receive;
}

void FT6206_Write_Reg1(u8 RegIndex,u8 data)
{
	I2C1_Start();
	I2C1_Send_Byte(FT6206_ADDR);
	I2C1_WaitAck();
	I2C1_Send_Byte(RegIndex);
	I2C1_WaitAck();
	
	I2C1_Send_Byte(data);
	I2C1_WaitAck();	

	I2C1_Stop();	 
}


void FT6206_Read_RegN(u8 *pbuf,u8 len)
{
	u8 i;
	I2C1_Start();
	I2C1_Send_Byte(FT6206_ADDR+1);
	I2C1_WaitAck();	
	
	for(i=0;i<len;i++)
	{
		if(i==(len-1))  *(pbuf+i)=I2C1_Read_Byte(0);
		else            *(pbuf+i)=I2C1_Read_Byte(1);
	}		
	I2C1_Stop();
}

uint8_t FT6206_Read_Reg(uint8_t *pbuf,uint32_t len)
{
	
	int8_t i=0;

	I2C1_Start();
	I2C1_Send_Byte(FT6206_ADDR);
	I2C1_WaitAck();	
	
	I2C1_Send_Byte(0);
	I2C1_WaitAck();	
  I2C1_Stop();
  
	I2C1_Start();
	I2C1_Send_Byte(FT6206_ADDR+1);
	I2C1_WaitAck();	
	
	for(i=0;i<len;i++)
	{
		if(i==(len-1))  *(pbuf+i)=I2C1_Read_Byte(0);
		else            *(pbuf+i)=I2C1_Read_Byte(1);
	}		
	I2C1_Stop();
  
	return 0;
}


///*******************************************************************************
//* Function Name  : FT6206_Read_Reg
//* Description    : Read The FT6206
//* Parameter      : startaddr: First address
//*				   pbuf: The Pointer Point to a buffer
//				   len: The length of the read Data 
//* Return         : 1:Fail; 0:Success
//*******************************************************************************/
//uint8_t FT6206_Read_Reg0(uint8_t startaddr,uint8_t *pbuf,uint32_t len)
//{
//	__IO uint16_t i = 0;
//	
//	I2C1_Start();
//	//I2C1_Send_Byte(FT6206_ADDR);	//Send Slave Address for Write

//	do
//	{
//		I2C1_Send_Byte(FT6206_ADDR);	//Send Slave Address for Write
//		if(++i>100)
//		{
//			I2C1_Stop();
//			return 1;
//		}
//	}while(I2C1_WaitAck());	//Read Ack
/////////////////////////////////////////////////////	
//	i = 0;		
//	do
//	{	
//		I2C1_Send_Byte(startaddr);	//Send Slave Address for Read
//		if(++i > 100)	//Time Out
//		{
//			I2C1_Stop();
//			return 1;
//		}
//			
//	}while(I2C1_WaitAck());//Read Ack
/////////////////////////////////////////////////////
//	I2C1_Start();
//	i = 0;		
//	do
//	{	
//		I2C1_Send_Byte(FT6206_ADDR | 0x01);	//Send Slave Address for Read
//			
//		if(++i >= 100)	//Time Out
//		{
//			I2C1_Stop();
//			return 1;
//		}
//			
//	}while(I2C1_WaitAck());//Read Ack
//	
//	//len-1 Data
//	for(i=0; i<len-1; i++)
//	{
//		pbuf[i] = I2C1_Read_Byte(1);	//读取1个字节
//		I2C1_Ack();	 //Ack
//	}

//	pbuf[i] = I2C1_Read_Byte(0);	//Read the last Byte
//	I2C1_NoAck(); // NoAck
//		
//	I2C1_Stop();	 

//	return 0;	 
//}

//static uint8_t CheckSum(uint8_t *buf)
//{
//	__IO uint8_t i;
//	__IO uint16_t sum = 0;

//	for(i=0;i<7;i++)
//	{
//		sum += buf[i];		
//	}

//	sum &= 0xff;
//	sum = 0x0100-sum;
//	sum &= 0xff;

//	return (sum == buf[7]);
//}

/*******************************************************************************
* Function Name  : FT6206_Read_Data
* Description    : Read The FT6206
* Parameter      : startaddr: First address
*				   pbuf: The Pointer Point to a buffer
				   len: The length of the read Data 
* Return         : 1:Fail; 0:Success
*******************************************************************************/

//uint8_t CTP_Read(uint8_t flag)
//{
//	__IO uint16_t DCX = 0,DCY = 0;
//	
//	TpdTouchData TpdTouchData;

//	//memset((uint8_t*)&TpdTouchData,0,sizeof(TpdTouchData));

//	//Read the FT6206

//	
//	if(FT6206_Read_Reg((uint8_t*)&TpdTouchData, sizeof(TpdTouchData)))
//	{
////		printf("FT6206 Read Fail!\r\n");
//		return 0;
//	}
//	
//	//Check The ID of FT6206
//	if(TpdTouchData.packet_id != 0x52)	
//	{
////		printf("The ID of FT6206 is False!\r\n");
//		return 0;	
//	}		
//	
//	//CheckSum
//	if(!CheckSum((uint8_t*)(&TpdTouchData)))
//	{
////		printf("Checksum is False!\r\n");
//		return 0;
//	}
//	
//	//The Key Of TP		
//	if(TpdTouchData.xh_yh == 0xff && TpdTouchData.xl == 0xff
//		&& TpdTouchData.yl == 0xff && TpdTouchData.dxh_dyh == 0xff && TpdTouchData.dyl == 0xff)
//	{
//		/*switch(TpdTouchData.dxl)
//		{
//			case 0:	return 0;
//			case 1: printf("R-KEY\r\n"); break;	 //Right Key
//			case 2: printf("M-KEY\r\n"); break;	 //Middle Key
//			case 4: printf("L-KEY\r\n"); break;	 //Left Key
//			default:;
//		}*/		
//	}
//	else 
//	{
//		//The First Touch Point
//		CTP_Dat.cx1 = (TpdTouchData.xh_yh&0xf0)<<4 | TpdTouchData.xl;
//		CTP_Dat.cy1 = (TpdTouchData.xh_yh&0x0f)<<8 | TpdTouchData.yl;

//		//The Second Touch Point
//		if(TpdTouchData.dxh_dyh != 0 || TpdTouchData.dxl != 0 || TpdTouchData.dyl != 0)
//		{	
//			DCX = (TpdTouchData.dxh_dyh&0xf0)<<4 | TpdTouchData.dxl;
//			DCY = (TpdTouchData.dxh_dyh&0x0f)<<8 | TpdTouchData.dyl;

//			DCX <<= 4;
//			DCX >>= 4;
//			DCY <<= 4;
//			DCY >>= 4;

//			if(DCX >= 2048)
//				DCX -= 4096;
//			if(DCY >= 2048)
//				DCY -= 4096;

//			CTP_Dat.cx2 = CTP_Dat.cx1 + DCX;
//			CTP_Dat.cy2 = CTP_Dat.cy1 + DCY;
//		}		
//	}

//	if(CTP_Dat.cx1 == 0 && CTP_Dat.cy1 == 0 && CTP_Dat.cx2 == 0 && CTP_Dat.cy2 == 0)
//	{
//		return 0;
//	}
//	
////	if(flag)
////	{	
////		printf("#CP%04d,%04d!%04d,%04d;%04d,%04d\r\n",0,0,CTP_Dat.cx1,CTP_Dat.cy1,CTP_Dat.cx2,CTP_Dat.cy2);
////		memset((uint8_t*)&CTP_Dat, 0, sizeof(CTP_Dat));
////	}
//	return 1;
//}




//触摸屏初始化
//返回值:0,没有进行校准
//			 1,进行过校准
u8 TP_Init(void)
{

		//OTT2001A_Init();
	
	 Touch_GPIO_Config(); 
	
//		tp_dev.scan = CTP_Read; //扫描函数指向电容触摸屏扫描函数
//		tp_dev.touchtype |= 0X80; //电容屏
//		tp_dev.touchtype |= lcddev.dir&0x01;//横屏还是竖屏
		return 0;



}
	
