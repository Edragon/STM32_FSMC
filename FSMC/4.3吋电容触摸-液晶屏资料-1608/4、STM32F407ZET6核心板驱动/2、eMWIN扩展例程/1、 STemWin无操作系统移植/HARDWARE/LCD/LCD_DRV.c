#include "LCD_DRV.h"
#include "FONT.h"
#include "delay.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
 
//2.4��/2.8��/3.5��/4.3�� TFTҺ������	  
//֧������IC�ͺŰ���:ILI9341/ILI9325/RM68042/RM68021/ILI9320/ILI9328/LGDP4531/LGDP4535/
//                  SPFD5408/1505/B505/C505/NT35310/NT35510��		    
//STM32F4����-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com
//////////////////////////////////////////////////////////////////////////////////	 
				 
//LCD�Ļ�����ɫ�ͱ���ɫ	  
u16 POINT_COLOR=0X0000;  //������ɫ
u16 BACK_COLOR=0XFFFF;   //������ɫ

//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;

//д�Ĵ�������
//regval:�Ĵ���ֵ
void LCD_WR_REG(vu16 regval)
{
	regval = regval; //ʹ��-O2�Ż���ʱ��,����������ʱ
	TFTLCD->LCD_REG=regval;  //д��Ҫд�ļĴ������	
}

//дLCD����
//data:Ҫд���ֵ
void LCD_WR_DATA(vu16 data)
{
	data=data;	//ʹ��-O2�Ż���ʱ��,����������ʱ
	TFTLCD->LCD_RAM=data;
}

//��LCD����
//����ֵ:������ֵ
u16 LCD_RD_DATA(void)
{
	vu16 ram;  //��ֹ���Ż�
	ram=TFTLCD->LCD_RAM;
	return ram;
}
//д�Ĵ���
//LCD_Reg:�Ĵ�����ַ
//LCD_RegValue:Ҫд�������
void LCD_WriteReg(vu16 LCD_Reg,u16 LCD_RegValue)
{
	TFTLCD->LCD_REG = LCD_Reg;  //д��Ҫд�ļĴ������
	TFTLCD->LCD_RAM = LCD_RegValue;//д������
}

//���Ĵ���
//LCD_Reg:�Ĵ�����ַ
//����ֵ:����������
u16 LCD_ReadReg(vu16 LCD_Reg)
{
	LCD_WR_REG(LCD_Reg);  //д��Ҫ��ȡ�ļĴ������
	delay_us(5);
	return LCD_RD_DATA();  //���ض�����ֵ
}

//��ʼдGRAM
void LCD_WriteRAM_Prepare(void)
{
	TFTLCD->LCD_REG=lcddev.wramcmd;
}

//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
u16 LCD_BGR2RGB(u16 c)
{
	u16 r,g,b,rgb;
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;
	rgb=(b<<11)+(g<<5)+(r<<0);
	return (rgb);
}
//��mdk -O1ʱ���Ż�ʱ��Ҫ����
//��ʱi
void opt_delay(u8 i)
{
	while(i--);
}
//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0,b=0;
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//�����˷�Χ,ֱ�ӷ���		   
	LCD_SetCursor(x,y);	
	
	LCD_WR_REG(0X2E00);	//5510 ���Ͷ�GRAMָ��

	if(TFTLCD->LCD_RAM)r=0;							//dummy Read	   
	opt_delay(2);	  
 	r=TFTLCD->LCD_RAM;  		  						//ʵ��������ɫ
	opt_delay(2);	  
	b=TFTLCD->LCD_RAM; 
	g=r&0XFF;		//����9341/5310/5510,��һ�ζ�ȡ����RG��ֵ,R��ǰ,G�ں�,��ռ8λ
	g<<=8;

  return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));//ILI9341/NT35310/NT35510��Ҫ��ʽת��һ��

}			 

//LCD������ʾ
void LCD_DisplayOn(void)
{					   

	LCD_WR_REG(0X2900);	//������ʾ

}	

//LCD�ر���ʾ
void LCD_DisplayOff(void)
{	   

  LCD_WR_REG(0X2800);	//�ر���ʾ

} 

//���ù��λ��
//Xpos:������
//Ypos:������
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	 

		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(Xpos>>8); 
		LCD_WR_REG(lcddev.setxcmd+1); 
		LCD_WR_DATA(Xpos&0XFF);	 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(Ypos>>8); 
		LCD_WR_REG(lcddev.setycmd+1); 
		LCD_WR_DATA(Ypos&0XFF);		
	
} 	
//����LCD���Զ�ɨ�跽��
//ע��:�����������ܻ��ܵ��˺������õ�Ӱ��(������9341/6804����������),
//����,һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.
//dir:0~7,����8������(���嶨���lcd.h)
//9320/9325/9328/4531/4535/1505/b505/5408/9341/5310/5510��IC�Ѿ�ʵ�ʲ���	   	   
void LCD_Scan_Dir(u8 dir)
{
	u16 regval=0;
	u16 dirreg=0;
	u16 temp;  
	
		if(lcddev.dir==1)//����ʱ
		{			   
			switch(dir)//����ת��
			{
				case 0:dir=6;break;
				case 1:dir=7;break;
				case 2:dir=4;break;
				case 3:dir=5;break;
				case 4:dir=1;break;
				case 5:dir=0;break;
				case 6:dir=3;break;
				case 7:dir=2;break;	     
			}
		}

		switch(dir)
		{
			case L2R_U2D://������,���ϵ���
				regval|=(0<<7)|(0<<6)|(0<<5); 
				break;
			case L2R_D2U://������,���µ���
				regval|=(1<<7)|(0<<6)|(0<<5); 
				break;
			case R2L_U2D://���ҵ���,���ϵ���
				regval|=(0<<7)|(1<<6)|(0<<5); 
				break;
			case R2L_D2U://���ҵ���,���µ���
				regval|=(1<<7)|(1<<6)|(0<<5); 
				break;	 
			case U2D_L2R://���ϵ���,������
				regval|=(0<<7)|(0<<6)|(1<<5); 
				break;
			case U2D_R2L://���ϵ���,���ҵ���
				regval|=(0<<7)|(1<<6)|(1<<5); 
				break;
			case D2U_L2R://���µ���,������
				regval|=(1<<7)|(0<<6)|(1<<5); 
				break;
			case D2U_R2L://���µ���,���ҵ���
				regval|=(1<<7)|(1<<6)|(1<<5); 
				break;	 
		}
			
		dirreg=0X3600;
		
		
		LCD_WriteReg(dirreg,regval);
		
 		if((regval&0X20)||lcddev.dir==1)
		{
			if(lcddev.width<lcddev.height)//����X,Y
			{
				temp=lcddev.width;
				lcddev.width=lcddev.height;
				lcddev.height=temp;
 			}
		}else  
		{
			if(lcddev.width>lcddev.height)//����X,Y
			{
				temp=lcddev.width;
				lcddev.width=lcddev.height;
				lcddev.height=temp;
 			}
		}  

			LCD_WR_REG(lcddev.setxcmd);LCD_WR_DATA(0); 
			LCD_WR_REG(lcddev.setxcmd+1);LCD_WR_DATA(0); 
			LCD_WR_REG(lcddev.setxcmd+2);LCD_WR_DATA((lcddev.width-1)>>8); 
			LCD_WR_REG(lcddev.setxcmd+3);LCD_WR_DATA((lcddev.width-1)&0XFF); 
			LCD_WR_REG(lcddev.setycmd);LCD_WR_DATA(0); 
			LCD_WR_REG(lcddev.setycmd+1);LCD_WR_DATA(0); 
			LCD_WR_REG(lcddev.setycmd+2);LCD_WR_DATA((lcddev.height-1)>>8); 
			LCD_WR_REG(lcddev.setycmd+3);LCD_WR_DATA((lcddev.height-1)&0XFF);

}   

//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);  //���ù��
	LCD_WriteRAM_Prepare();  //��ʼд��GRAM
	TFTLCD->LCD_RAM=POINT_COLOR;
}

//���ٻ���
//x,y:����
//color:��ɫ
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{	   

		LCD_WR_REG(lcddev.setxcmd);LCD_WR_DATA(x>>8);  
		LCD_WR_REG(lcddev.setxcmd+1);LCD_WR_DATA(x&0XFF);	  
		LCD_WR_REG(lcddev.setycmd);LCD_WR_DATA(y>>8);  
		LCD_WR_REG(lcddev.setycmd+1);LCD_WR_DATA(y&0XFF); 
				 
	TFTLCD->LCD_REG=lcddev.wramcmd; 
	TFTLCD->LCD_RAM=color; 
	
}	 

//����LCD��ʾ����
//dir:0 ����;1,����
void LCD_Display_Dir(u8 dir)
{
	if(dir==0) //����
	{
		  lcddev.dir=0;	//����
			lcddev.wramcmd=0X2C00;
	 		lcddev.setxcmd=0X2A00;
			lcddev.setycmd=0X2B00; 
			lcddev.width=480;
			lcddev.height=800;

	}else  //����
	{
			lcddev.dir=1;	//����

			lcddev.wramcmd=0X2C00;
	 		lcddev.setxcmd=0X2A00;
			lcddev.setycmd=0X2B00; 
			lcddev.width=800;
			lcddev.height=480;

	}
	
	LCD_Scan_Dir(DFT_SCAN_DIR);  //Ĭ��ɨ�跽��	
}

//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height.
//68042,����ʱ��֧�ִ�������!! 
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
{   

	width=sx+width-1;
	height=sy+height-1;

		LCD_WR_REG(lcddev.setxcmd);LCD_WR_DATA(sx>>8);  
		LCD_WR_REG(lcddev.setxcmd+1);LCD_WR_DATA(sx&0XFF);	  
		LCD_WR_REG(lcddev.setxcmd+2);LCD_WR_DATA(width>>8);   
		LCD_WR_REG(lcddev.setxcmd+3);LCD_WR_DATA(width&0XFF);   
		LCD_WR_REG(lcddev.setycmd);LCD_WR_DATA(sy>>8);   
		LCD_WR_REG(lcddev.setycmd+1);LCD_WR_DATA(sy&0XFF);  
		LCD_WR_REG(lcddev.setycmd+2);LCD_WR_DATA(height>>8);   
		LCD_WR_REG(lcddev.setycmd+3);LCD_WR_DATA(height&0XFF);  
	
} 

//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ILI93XXҺ��,�������������ǻ���ILI9320��!!!
//�������ͺŵ�����оƬ��û�в���! 
void TFTLCD_Init(void)
{ 	
	vu32 i=0;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef FSMC_ReadWriteTimingStructure;
		
	 //ʹ��PB,PD,PG,PF,PE
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG,ENABLE);
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE); //ʹ��FSMCʱ��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;  
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;  //�������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);  //��ʼ��PB15����
	
	//PD0,1,4,5,8,9,10,14,15�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; //�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure); 
	
	//PE7,8,9,10,11,12,13,14,15�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOE,&GPIO_InitStructure);  
	
	//PF12�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init(GPIOF,&GPIO_InitStructure); 
	
	//PG12�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init(GPIOG,&GPIO_InitStructure); 
	
	//GPIOD���Ÿ���
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);  //PD0 AF12
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);  //PD1 AF12
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);  //PD4 AF12
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC);  //PD5 AF12
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC);  //PD8 AF12
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);  //PD9 AF12
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);  //PD10 AF12
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);  //PD14 AF12
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);  //PD15 AF12
	
	//GPIOE���Ÿ���
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);  //PE7 AF12
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);  //PE8 AF12
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);  //PE9 AF12
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);  //PE10 AF12
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);  //PE11 AF12
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);  //PE12 AF12
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);  //PE13 AF12
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);  //PE14 AF12
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);  //PE15 AF12
	
	//GPIOF���Ÿ���
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource12,GPIO_AF_FSMC);  //PE15 AF12		
	//GPIOG���Ÿ���
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource12,GPIO_AF_FSMC);  //PE15 AF12
	
	//FSMC��ʱ����ƼĴ���
	FSMC_ReadWriteTimingStructure.FSMC_AddressSetupTime = 0x08; //��ַ����ʱ�� 16��HCLK =16X(1/168M)=96ns
	FSMC_ReadWriteTimingStructure.FSMC_AddressHoldTime = 0x00;  //��ַ����ʱ��ģʽAδ�õ� 
	FSMC_ReadWriteTimingStructure.FSMC_DataSetupTime = 0x0F;    //���ݱ���ʱ��Ϊ25��HCLK 25x(1/168M)=150ns
	FSMC_ReadWriteTimingStructure.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_ReadWriteTimingStructure.FSMC_CLKDivision = 0x00;
	FSMC_ReadWriteTimingStructure.FSMC_DataLatency = 0x00;
	FSMC_ReadWriteTimingStructure.FSMC_AccessMode = FSMC_AccessMode_A; //ģʽA
	
	
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;  //NOR/SRAM��Bank4
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; //������������
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;   //
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;  //16λ���ݿ��
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable; //�Ƿ�ʹ��ͻ������,����ͬ��ͻ���洢����Ч,�˴�δ�õ�
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;//�Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ�
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low; //�ȴ��źŵļ���,����ͻ��ģʽ����������
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;  //�Ƿ�ʹ�ܻ�·ͻ��ģʽ,�˴�δ�õ�
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState; //�洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable; //�洢��дʹ��
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   //�ȴ�ʹ��λ,�˴�δ�õ�
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; //��дʹ�ò�ͬ��ʱ��
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  //�첽�����ڼ�ĵȴ��ź�
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_ReadWriteTimingStructure;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_ReadWriteTimingStructure; //дʱ��
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //FSMC��ʼ��
	
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4,ENABLE);  //ʹ��NOR/SRAM����
			 
 	delay_ms(50); // delay 50 ms 
 	LCD_WriteReg(0x0000,0x0001);
	delay_ms(50); // delay 50 ms 
  lcddev.id = LCD_ReadReg(0x0000); 


//	LCD_WR_REG(0XDA00);	
//	lcddev.id=LCD_RD_DATA();//����0X00	 
//	LCD_WR_REG(0XDB00);	
//	lcddev.id=LCD_RD_DATA();//����0X80
//	lcddev.id<<=8;	
//	LCD_WR_REG(0XDC00);	
//	lcddev.id|=LCD_RD_DATA();//����0X00	

//	if(lcddev.id==0x8200)lcddev.id=0x5510;//NT35510���ص�ID��8000H,Ϊ��������,����ǿ������Ϊ5510
//printf("LCD ID:%x\r\n",lcddev.id); //��ӡLCD ID  

	
	
	
	//ENABLE PAGE 1
LCD_WR_REG(0xF000);LCD_WR_DATA(0x55);
LCD_WR_REG(0xF001);LCD_WR_DATA(0xAA);
LCD_WR_REG(0xF002);LCD_WR_DATA(0x52);
LCD_WR_REG(0xF003);LCD_WR_DATA(0x08);
LCD_WR_REG(0xF004);LCD_WR_DATA(0x01);

//GAMMA SETING  RED
LCD_WR_REG(0xD100);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD101);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD102);LCD_WR_DATA(0x1b);
LCD_WR_REG(0xD103);LCD_WR_DATA(0x44);
LCD_WR_REG(0xD104);LCD_WR_DATA(0x62);
LCD_WR_REG(0xD105);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD106);LCD_WR_DATA(0x7b);
LCD_WR_REG(0xD107);LCD_WR_DATA(0xa1);
LCD_WR_REG(0xD108);LCD_WR_DATA(0xc0);
LCD_WR_REG(0xD109);LCD_WR_DATA(0xee);
LCD_WR_REG(0xD10A);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD10B);LCD_WR_DATA(0x10);
LCD_WR_REG(0xD10C);LCD_WR_DATA(0x2c);
LCD_WR_REG(0xD10D);LCD_WR_DATA(0x43);
LCD_WR_REG(0xD10E);LCD_WR_DATA(0x57);
LCD_WR_REG(0xD10F);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD110);LCD_WR_DATA(0x68);
LCD_WR_REG(0xD111);LCD_WR_DATA(0x78);
LCD_WR_REG(0xD112);LCD_WR_DATA(0x87);
LCD_WR_REG(0xD113);LCD_WR_DATA(0x94);
LCD_WR_REG(0xD114);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD115);LCD_WR_DATA(0xa0);
LCD_WR_REG(0xD116);LCD_WR_DATA(0xac);
LCD_WR_REG(0xD117);LCD_WR_DATA(0xb6);
LCD_WR_REG(0xD118);LCD_WR_DATA(0xc1);
LCD_WR_REG(0xD119);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD11A);LCD_WR_DATA(0xcb);
LCD_WR_REG(0xD11B);LCD_WR_DATA(0xcd);
LCD_WR_REG(0xD11C);LCD_WR_DATA(0xd6);
LCD_WR_REG(0xD11D);LCD_WR_DATA(0xdf);
LCD_WR_REG(0xD11E);LCD_WR_DATA(0x95);
LCD_WR_REG(0xD11F);LCD_WR_DATA(0xe8);
LCD_WR_REG(0xD120);LCD_WR_DATA(0xf1);
LCD_WR_REG(0xD121);LCD_WR_DATA(0xfa);
LCD_WR_REG(0xD122);LCD_WR_DATA(0x02);
LCD_WR_REG(0xD123);LCD_WR_DATA(0xaa);
LCD_WR_REG(0xD124);LCD_WR_DATA(0x0b);
LCD_WR_REG(0xD125);LCD_WR_DATA(0x13);
LCD_WR_REG(0xD126);LCD_WR_DATA(0x1d);
LCD_WR_REG(0xD127);LCD_WR_DATA(0x26);
LCD_WR_REG(0xD128);LCD_WR_DATA(0xaa);
LCD_WR_REG(0xD129);LCD_WR_DATA(0x30);
LCD_WR_REG(0xD12A);LCD_WR_DATA(0x3c);
LCD_WR_REG(0xD12B);LCD_WR_DATA(0x4A);
LCD_WR_REG(0xD12C);LCD_WR_DATA(0x63);
LCD_WR_REG(0xD12D);LCD_WR_DATA(0xea);
LCD_WR_REG(0xD12E);LCD_WR_DATA(0x79);
LCD_WR_REG(0xD12F);LCD_WR_DATA(0xa6);
LCD_WR_REG(0xD130);LCD_WR_DATA(0xd0);
LCD_WR_REG(0xD131);LCD_WR_DATA(0x20);
LCD_WR_REG(0xD132);LCD_WR_DATA(0x0f);
LCD_WR_REG(0xD133);LCD_WR_DATA(0x8e);
LCD_WR_REG(0xD134);LCD_WR_DATA(0xff);
//GAMMA SETING GREEN
LCD_WR_REG(0xD200);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD201);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD202);LCD_WR_DATA(0x1b);
LCD_WR_REG(0xD203);LCD_WR_DATA(0x44);
LCD_WR_REG(0xD204);LCD_WR_DATA(0x62);
LCD_WR_REG(0xD205);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD206);LCD_WR_DATA(0x7b);
LCD_WR_REG(0xD207);LCD_WR_DATA(0xa1);
LCD_WR_REG(0xD208);LCD_WR_DATA(0xc0);
LCD_WR_REG(0xD209);LCD_WR_DATA(0xee);
LCD_WR_REG(0xD20A);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD20B);LCD_WR_DATA(0x10);
LCD_WR_REG(0xD20C);LCD_WR_DATA(0x2c);
LCD_WR_REG(0xD20D);LCD_WR_DATA(0x43);
LCD_WR_REG(0xD20E);LCD_WR_DATA(0x57);
LCD_WR_REG(0xD20F);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD210);LCD_WR_DATA(0x68);
LCD_WR_REG(0xD211);LCD_WR_DATA(0x78);
LCD_WR_REG(0xD212);LCD_WR_DATA(0x87);
LCD_WR_REG(0xD213);LCD_WR_DATA(0x94);
LCD_WR_REG(0xD214);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD215);LCD_WR_DATA(0xa0);
LCD_WR_REG(0xD216);LCD_WR_DATA(0xac);
LCD_WR_REG(0xD217);LCD_WR_DATA(0xb6);
LCD_WR_REG(0xD218);LCD_WR_DATA(0xc1);
LCD_WR_REG(0xD219);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD21A);LCD_WR_DATA(0xcb);
LCD_WR_REG(0xD21B);LCD_WR_DATA(0xcd);
LCD_WR_REG(0xD21C);LCD_WR_DATA(0xd6);
LCD_WR_REG(0xD21D);LCD_WR_DATA(0xdf);
LCD_WR_REG(0xD21E);LCD_WR_DATA(0x95);
LCD_WR_REG(0xD21F);LCD_WR_DATA(0xe8);
LCD_WR_REG(0xD220);LCD_WR_DATA(0xf1);
LCD_WR_REG(0xD221);LCD_WR_DATA(0xfa);
LCD_WR_REG(0xD222);LCD_WR_DATA(0x02);
LCD_WR_REG(0xD223);LCD_WR_DATA(0xaa);
LCD_WR_REG(0xD224);LCD_WR_DATA(0x0b);
LCD_WR_REG(0xD225);LCD_WR_DATA(0x13);
LCD_WR_REG(0xD226);LCD_WR_DATA(0x1d);
LCD_WR_REG(0xD227);LCD_WR_DATA(0x26);
LCD_WR_REG(0xD228);LCD_WR_DATA(0xaa);
LCD_WR_REG(0xD229);LCD_WR_DATA(0x30);
LCD_WR_REG(0xD22A);LCD_WR_DATA(0x3c);
LCD_WR_REG(0xD22B);LCD_WR_DATA(0x4a);
LCD_WR_REG(0xD22C);LCD_WR_DATA(0x63);
LCD_WR_REG(0xD22D);LCD_WR_DATA(0xea);
LCD_WR_REG(0xD22E);LCD_WR_DATA(0x79);
LCD_WR_REG(0xD22F);LCD_WR_DATA(0xa6);
LCD_WR_REG(0xD230);LCD_WR_DATA(0xd0);
LCD_WR_REG(0xD231);LCD_WR_DATA(0x20);
LCD_WR_REG(0xD232);LCD_WR_DATA(0x0f);
LCD_WR_REG(0xD233);LCD_WR_DATA(0x8e);
LCD_WR_REG(0xD234);LCD_WR_DATA(0xff);

//GAMMA SETING BLUE
LCD_WR_REG(0xD300);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD301);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD302);LCD_WR_DATA(0x1b);
LCD_WR_REG(0xD303);LCD_WR_DATA(0x44);
LCD_WR_REG(0xD304);LCD_WR_DATA(0x62);
LCD_WR_REG(0xD305);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD306);LCD_WR_DATA(0x7b);
LCD_WR_REG(0xD307);LCD_WR_DATA(0xa1);
LCD_WR_REG(0xD308);LCD_WR_DATA(0xc0);
LCD_WR_REG(0xD309);LCD_WR_DATA(0xee);
LCD_WR_REG(0xD30A);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD30B);LCD_WR_DATA(0x10);
LCD_WR_REG(0xD30C);LCD_WR_DATA(0x2c);
LCD_WR_REG(0xD30D);LCD_WR_DATA(0x43);
LCD_WR_REG(0xD30E);LCD_WR_DATA(0x57);
LCD_WR_REG(0xD30F);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD310);LCD_WR_DATA(0x68);
LCD_WR_REG(0xD311);LCD_WR_DATA(0x78);
LCD_WR_REG(0xD312);LCD_WR_DATA(0x87);
LCD_WR_REG(0xD313);LCD_WR_DATA(0x94);
LCD_WR_REG(0xD314);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD315);LCD_WR_DATA(0xa0);
LCD_WR_REG(0xD316);LCD_WR_DATA(0xac);
LCD_WR_REG(0xD317);LCD_WR_DATA(0xb6);
LCD_WR_REG(0xD318);LCD_WR_DATA(0xc1);
LCD_WR_REG(0xD319);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD31A);LCD_WR_DATA(0xcb);
LCD_WR_REG(0xD31B);LCD_WR_DATA(0xcd);
LCD_WR_REG(0xD31C);LCD_WR_DATA(0xd6);
LCD_WR_REG(0xD31D);LCD_WR_DATA(0xdf);
LCD_WR_REG(0xD31E);LCD_WR_DATA(0x95);
LCD_WR_REG(0xD31F);LCD_WR_DATA(0xe8);
LCD_WR_REG(0xD320);LCD_WR_DATA(0xf1);
LCD_WR_REG(0xD321);LCD_WR_DATA(0xfa);
LCD_WR_REG(0xD322);LCD_WR_DATA(0x02);
LCD_WR_REG(0xD323);LCD_WR_DATA(0xaa);
LCD_WR_REG(0xD324);LCD_WR_DATA(0x0b);
LCD_WR_REG(0xD325);LCD_WR_DATA(0x13);
LCD_WR_REG(0xD326);LCD_WR_DATA(0x1d);
LCD_WR_REG(0xD327);LCD_WR_DATA(0x26);
LCD_WR_REG(0xD328);LCD_WR_DATA(0xaa);
LCD_WR_REG(0xD329);LCD_WR_DATA(0x30);
LCD_WR_REG(0xD32A);LCD_WR_DATA(0x3c);
LCD_WR_REG(0xD32B);LCD_WR_DATA(0x4A);
LCD_WR_REG(0xD32C);LCD_WR_DATA(0x63);
LCD_WR_REG(0xD32D);LCD_WR_DATA(0xea);
LCD_WR_REG(0xD32E);LCD_WR_DATA(0x79);
LCD_WR_REG(0xD32F);LCD_WR_DATA(0xa6);
LCD_WR_REG(0xD330);LCD_WR_DATA(0xd0);
LCD_WR_REG(0xD331);LCD_WR_DATA(0x20);
LCD_WR_REG(0xD332);LCD_WR_DATA(0x0f);
LCD_WR_REG(0xD333);LCD_WR_DATA(0x8e);
LCD_WR_REG(0xD334);LCD_WR_DATA(0xff);


//GAMMA SETING  RED
LCD_WR_REG(0xD400);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD401);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD402);LCD_WR_DATA(0x1b);
LCD_WR_REG(0xD403);LCD_WR_DATA(0x44);
LCD_WR_REG(0xD404);LCD_WR_DATA(0x62);
LCD_WR_REG(0xD405);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD406);LCD_WR_DATA(0x7b);
LCD_WR_REG(0xD407);LCD_WR_DATA(0xa1);
LCD_WR_REG(0xD408);LCD_WR_DATA(0xc0);
LCD_WR_REG(0xD409);LCD_WR_DATA(0xee);
LCD_WR_REG(0xD40A);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD40B);LCD_WR_DATA(0x10);
LCD_WR_REG(0xD40C);LCD_WR_DATA(0x2c);
LCD_WR_REG(0xD40D);LCD_WR_DATA(0x43);
LCD_WR_REG(0xD40E);LCD_WR_DATA(0x57);
LCD_WR_REG(0xD40F);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD410);LCD_WR_DATA(0x68);
LCD_WR_REG(0xD411);LCD_WR_DATA(0x78);
LCD_WR_REG(0xD412);LCD_WR_DATA(0x87);
LCD_WR_REG(0xD413);LCD_WR_DATA(0x94);
LCD_WR_REG(0xD414);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD415);LCD_WR_DATA(0xa0);
LCD_WR_REG(0xD416);LCD_WR_DATA(0xac);
LCD_WR_REG(0xD417);LCD_WR_DATA(0xb6);
LCD_WR_REG(0xD418);LCD_WR_DATA(0xc1);
LCD_WR_REG(0xD419);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD41A);LCD_WR_DATA(0xcb);
LCD_WR_REG(0xD41B);LCD_WR_DATA(0xcd);
LCD_WR_REG(0xD41C);LCD_WR_DATA(0xd6);
LCD_WR_REG(0xD41D);LCD_WR_DATA(0xdf);
LCD_WR_REG(0xD41E);LCD_WR_DATA(0x95);
LCD_WR_REG(0xD41F);LCD_WR_DATA(0xe8);
LCD_WR_REG(0xD420);LCD_WR_DATA(0xf1);
LCD_WR_REG(0xD421);LCD_WR_DATA(0xfa);
LCD_WR_REG(0xD422);LCD_WR_DATA(0x02);
LCD_WR_REG(0xD423);LCD_WR_DATA(0xaa);
LCD_WR_REG(0xD424);LCD_WR_DATA(0x0b);
LCD_WR_REG(0xD425);LCD_WR_DATA(0x13);
LCD_WR_REG(0xD426);LCD_WR_DATA(0x1d);
LCD_WR_REG(0xD427);LCD_WR_DATA(0x26);
LCD_WR_REG(0xD428);LCD_WR_DATA(0xaa);
LCD_WR_REG(0xD429);LCD_WR_DATA(0x30);
LCD_WR_REG(0xD42A);LCD_WR_DATA(0x3c);
LCD_WR_REG(0xD42B);LCD_WR_DATA(0x4A);
LCD_WR_REG(0xD42C);LCD_WR_DATA(0x63);
LCD_WR_REG(0xD42D);LCD_WR_DATA(0xea);
LCD_WR_REG(0xD42E);LCD_WR_DATA(0x79);
LCD_WR_REG(0xD42F);LCD_WR_DATA(0xa6);
LCD_WR_REG(0xD430);LCD_WR_DATA(0xd0);
LCD_WR_REG(0xD431);LCD_WR_DATA(0x20);
LCD_WR_REG(0xD432);LCD_WR_DATA(0x0f);
LCD_WR_REG(0xD433);LCD_WR_DATA(0x8e);
LCD_WR_REG(0xD434);LCD_WR_DATA(0xff);

//GAMMA SETING GREEN
LCD_WR_REG(0xD500);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD501);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD502);LCD_WR_DATA(0x1b);
LCD_WR_REG(0xD503);LCD_WR_DATA(0x44);
LCD_WR_REG(0xD504);LCD_WR_DATA(0x62);
LCD_WR_REG(0xD505);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD506);LCD_WR_DATA(0x7b);
LCD_WR_REG(0xD507);LCD_WR_DATA(0xa1);
LCD_WR_REG(0xD508);LCD_WR_DATA(0xc0);
LCD_WR_REG(0xD509);LCD_WR_DATA(0xee);
LCD_WR_REG(0xD50A);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD50B);LCD_WR_DATA(0x10);
LCD_WR_REG(0xD50C);LCD_WR_DATA(0x2c);
LCD_WR_REG(0xD50D);LCD_WR_DATA(0x43);
LCD_WR_REG(0xD50E);LCD_WR_DATA(0x57);
LCD_WR_REG(0xD50F);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD510);LCD_WR_DATA(0x68);
LCD_WR_REG(0xD511);LCD_WR_DATA(0x78);
LCD_WR_REG(0xD512);LCD_WR_DATA(0x87);
LCD_WR_REG(0xD513);LCD_WR_DATA(0x94);
LCD_WR_REG(0xD514);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD515);LCD_WR_DATA(0xa0);
LCD_WR_REG(0xD516);LCD_WR_DATA(0xac);
LCD_WR_REG(0xD517);LCD_WR_DATA(0xb6);
LCD_WR_REG(0xD518);LCD_WR_DATA(0xc1);
LCD_WR_REG(0xD519);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD51A);LCD_WR_DATA(0xcb);
LCD_WR_REG(0xD51B);LCD_WR_DATA(0xcd);
LCD_WR_REG(0xD51C);LCD_WR_DATA(0xd6);
LCD_WR_REG(0xD51D);LCD_WR_DATA(0xdf);
LCD_WR_REG(0xD51E);LCD_WR_DATA(0x95);
LCD_WR_REG(0xD51F);LCD_WR_DATA(0xe8);
LCD_WR_REG(0xD520);LCD_WR_DATA(0xf1);
LCD_WR_REG(0xD521);LCD_WR_DATA(0xfa);
LCD_WR_REG(0xD522);LCD_WR_DATA(0x02);
LCD_WR_REG(0xD523);LCD_WR_DATA(0xaa);
LCD_WR_REG(0xD524);LCD_WR_DATA(0x0b);
LCD_WR_REG(0xD525);LCD_WR_DATA(0x13);
LCD_WR_REG(0xD526);LCD_WR_DATA(0x1d);
LCD_WR_REG(0xD527);LCD_WR_DATA(0x26);
LCD_WR_REG(0xD528);LCD_WR_DATA(0xaa);
LCD_WR_REG(0xD529);LCD_WR_DATA(0x30);
LCD_WR_REG(0xD52A);LCD_WR_DATA(0x3c);
LCD_WR_REG(0xD52B);LCD_WR_DATA(0x4a);
LCD_WR_REG(0xD52C);LCD_WR_DATA(0x63);
LCD_WR_REG(0xD52D);LCD_WR_DATA(0xea);
LCD_WR_REG(0xD52E);LCD_WR_DATA(0x79);
LCD_WR_REG(0xD52F);LCD_WR_DATA(0xa6);
LCD_WR_REG(0xD530);LCD_WR_DATA(0xd0);
LCD_WR_REG(0xD531);LCD_WR_DATA(0x20);
LCD_WR_REG(0xD532);LCD_WR_DATA(0x0f);
LCD_WR_REG(0xD533);LCD_WR_DATA(0x8e);
LCD_WR_REG(0xD534);LCD_WR_DATA(0xff);

//GAMMA SETING BLUE
LCD_WR_REG(0xD600);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD601);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD602);LCD_WR_DATA(0x1b);
LCD_WR_REG(0xD603);LCD_WR_DATA(0x44);
LCD_WR_REG(0xD604);LCD_WR_DATA(0x62);
LCD_WR_REG(0xD605);LCD_WR_DATA(0x00);
LCD_WR_REG(0xD606);LCD_WR_DATA(0x7b);
LCD_WR_REG(0xD607);LCD_WR_DATA(0xa1);
LCD_WR_REG(0xD608);LCD_WR_DATA(0xc0);
LCD_WR_REG(0xD609);LCD_WR_DATA(0xee);
LCD_WR_REG(0xD60A);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD60B);LCD_WR_DATA(0x10);
LCD_WR_REG(0xD60C);LCD_WR_DATA(0x2c);
LCD_WR_REG(0xD60D);LCD_WR_DATA(0x43);
LCD_WR_REG(0xD60E);LCD_WR_DATA(0x57);
LCD_WR_REG(0xD60F);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD610);LCD_WR_DATA(0x68);
LCD_WR_REG(0xD611);LCD_WR_DATA(0x78);
LCD_WR_REG(0xD612);LCD_WR_DATA(0x87);
LCD_WR_REG(0xD613);LCD_WR_DATA(0x94);
LCD_WR_REG(0xD614);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD615);LCD_WR_DATA(0xa0);
LCD_WR_REG(0xD616);LCD_WR_DATA(0xac);
LCD_WR_REG(0xD617);LCD_WR_DATA(0xb6);
LCD_WR_REG(0xD618);LCD_WR_DATA(0xc1);
LCD_WR_REG(0xD619);LCD_WR_DATA(0x55);
LCD_WR_REG(0xD61A);LCD_WR_DATA(0xcb);
LCD_WR_REG(0xD61B);LCD_WR_DATA(0xcd);
LCD_WR_REG(0xD61C);LCD_WR_DATA(0xd6);
LCD_WR_REG(0xD61D);LCD_WR_DATA(0xdf);
LCD_WR_REG(0xD61E);LCD_WR_DATA(0x95);
LCD_WR_REG(0xD61F);LCD_WR_DATA(0xe8);
LCD_WR_REG(0xD620);LCD_WR_DATA(0xf1);
LCD_WR_REG(0xD621);LCD_WR_DATA(0xfa);
LCD_WR_REG(0xD622);LCD_WR_DATA(0x02);
LCD_WR_REG(0xD623);LCD_WR_DATA(0xaa);
LCD_WR_REG(0xD624);LCD_WR_DATA(0x0b);
LCD_WR_REG(0xD625);LCD_WR_DATA(0x13);
LCD_WR_REG(0xD626);LCD_WR_DATA(0x1d);
LCD_WR_REG(0xD627);LCD_WR_DATA(0x26);
LCD_WR_REG(0xD628);LCD_WR_DATA(0xaa);
LCD_WR_REG(0xD629);LCD_WR_DATA(0x30);
LCD_WR_REG(0xD62A);LCD_WR_DATA(0x3c);
LCD_WR_REG(0xD62B);LCD_WR_DATA(0x4A);
LCD_WR_REG(0xD62C);LCD_WR_DATA(0x63);
LCD_WR_REG(0xD62D);LCD_WR_DATA(0xea);
LCD_WR_REG(0xD62E);LCD_WR_DATA(0x79);
LCD_WR_REG(0xD62F);LCD_WR_DATA(0xa6);
LCD_WR_REG(0xD630);LCD_WR_DATA(0xd0);
LCD_WR_REG(0xD631);LCD_WR_DATA(0x20);
LCD_WR_REG(0xD632);LCD_WR_DATA(0x0f);
LCD_WR_REG(0xD633);LCD_WR_DATA(0x8e);
LCD_WR_REG(0xD634);LCD_WR_DATA(0xff);

//AVDD VOLTAGE SETTING
LCD_WR_REG(0xB000);LCD_WR_DATA(0x05);
LCD_WR_REG(0xB001);LCD_WR_DATA(0x05);
LCD_WR_REG(0xB002);LCD_WR_DATA(0x05);
//AVEE VOLTAGE SETTING
LCD_WR_REG(0xB100);LCD_WR_DATA(0x05);
LCD_WR_REG(0xB101);LCD_WR_DATA(0x05);
LCD_WR_REG(0xB102);LCD_WR_DATA(0x05);

//AVDD Boosting
LCD_WR_REG(0xB600);LCD_WR_DATA(0x34);
LCD_WR_REG(0xB601);LCD_WR_DATA(0x34);
LCD_WR_REG(0xB603);LCD_WR_DATA(0x34);
//AVEE Boosting
LCD_WR_REG(0xB700);LCD_WR_DATA(0x24);
LCD_WR_REG(0xB701);LCD_WR_DATA(0x24);
LCD_WR_REG(0xB702);LCD_WR_DATA(0x24);
//VCL Boosting
LCD_WR_REG(0xB800);LCD_WR_DATA(0x24);
LCD_WR_REG(0xB801);LCD_WR_DATA(0x24);
LCD_WR_REG(0xB802);LCD_WR_DATA(0x24);
//VGLX VOLTAGE SETTING
LCD_WR_REG(0xBA00);LCD_WR_DATA(0x14);
LCD_WR_REG(0xBA01);LCD_WR_DATA(0x14);
LCD_WR_REG(0xBA02);LCD_WR_DATA(0x14);
//VCL Boosting
LCD_WR_REG(0xB900);LCD_WR_DATA(0x24);
LCD_WR_REG(0xB901);LCD_WR_DATA(0x24);
LCD_WR_REG(0xB902);LCD_WR_DATA(0x24);
//Gamma Voltage
LCD_WR_REG(0xBc00);LCD_WR_DATA(0x00);
LCD_WR_REG(0xBc01);LCD_WR_DATA(0xa0);//vgmp=5.0
LCD_WR_REG(0xBc02);LCD_WR_DATA(0x00);
LCD_WR_REG(0xBd00);LCD_WR_DATA(0x00);
LCD_WR_REG(0xBd01);LCD_WR_DATA(0xa0);//vgmn=5.0
LCD_WR_REG(0xBd02);LCD_WR_DATA(0x00);
//VCOM Setting
LCD_WR_REG(0xBe01);LCD_WR_DATA(0x3d);//3
//ENABLE PAGE 0
LCD_WR_REG(0xF000);LCD_WR_DATA(0x55);
LCD_WR_REG(0xF001);LCD_WR_DATA(0xAA);
LCD_WR_REG(0xF002);LCD_WR_DATA(0x52);
LCD_WR_REG(0xF003);LCD_WR_DATA(0x08);
LCD_WR_REG(0xF004);LCD_WR_DATA(0x00);
//Vivid Color Function Control
LCD_WR_REG(0xB400);LCD_WR_DATA(0x10);
//Z-INVERSION
LCD_WR_REG(0xBC00);LCD_WR_DATA(0x05);
LCD_WR_REG(0xBC01);LCD_WR_DATA(0x05);
LCD_WR_REG(0xBC02);LCD_WR_DATA(0x05);

//*************** add on 20111021**********************//
LCD_WR_REG(0xB700);LCD_WR_DATA(0x22);//GATE EQ CONTROL
LCD_WR_REG(0xB701);LCD_WR_DATA(0x22);//GATE EQ CONTROL

LCD_WR_REG(0xC80B);LCD_WR_DATA(0x2A);//DISPLAY TIMING CONTROL
LCD_WR_REG(0xC80C);LCD_WR_DATA(0x2A);//DISPLAY TIMING CONTROL
LCD_WR_REG(0xC80F);LCD_WR_DATA(0x2A);//DISPLAY TIMING CONTROL
LCD_WR_REG(0xC810);LCD_WR_DATA(0x2A);//DISPLAY TIMING CONTROL
//*************** add on 20111021**********************//
//PWM_ENH_OE =1
LCD_WR_REG(0xd000);LCD_WR_DATA(0x01);
//DM_SEL =1
LCD_WR_REG(0xb300);LCD_WR_DATA(0x10);
//VBPDA=07h
LCD_WR_REG(0xBd02);LCD_WR_DATA(0x07);
//VBPDb=07h
LCD_WR_REG(0xBe02);LCD_WR_DATA(0x07);
//VBPDc=07h
LCD_WR_REG(0xBf02);LCD_WR_DATA(0x07);
//ENABLE PAGE 2
LCD_WR_REG(0xF000);LCD_WR_DATA(0x55);
LCD_WR_REG(0xF001);LCD_WR_DATA(0xAA);
LCD_WR_REG(0xF002);LCD_WR_DATA(0x52);
LCD_WR_REG(0xF003);LCD_WR_DATA(0x08);
LCD_WR_REG(0xF004);LCD_WR_DATA(0x02);
//SDREG0 =0
LCD_WR_REG(0xc301);LCD_WR_DATA(0xa9);
//DS=14
LCD_WR_REG(0xfe01);LCD_WR_DATA(0x94);
//OSC =60h
LCD_WR_REG(0xf600);LCD_WR_DATA(0x60);
//TE ON
LCD_WR_REG(0x3500);LCD_WR_DATA(0x00);
//SLEEP OUT 
LCD_WR_REG(0x1100);


delay_ms(120);
//DISPLY ON
LCD_WR_REG(0x2900);

delay_ms(100);
	
LCD_WR_REG(0x3A00); LCD_WR_DATA(0x55);

LCD_WR_REG(0x3600); LCD_WR_DATA(0xA8);
	
	
	LCD_Display_Dir(1);		 	//ʹ�ú���
	LCD_LED=0;					//�͵�ƽ  ��������
	LCD_Clear(WHITE);
	
	
}  

//��������
//color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 			//�õ��ܵ���

	LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
	LCD_WriteRAM_Prepare();     		//��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		TFTLCD->LCD_RAM=color;	
	}
}  
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
//	u16 temp;

		xlen=ex-sx+1;	 
		for(i=sy;i<=ey;i++)
		{
		 	LCD_SetCursor(sx,i);      				//���ù��λ�� 
			LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	  
			for(j=0;j<xlen;j++)TFTLCD->LCD_RAM=color;	//��ʾ��ɫ 	    
		}
		 
}  
//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 			//�õ����Ŀ��
	height=ey-sy+1;			//�߶�
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)TFTLCD->LCD_RAM=color[i*width+j];//д������ 
	}		  
}  
//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  
//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
	//���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=asc2_1608[num][t];	//����1608����
		else if(size==24)temp=asc2_2412[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(x>=lcddev.width)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev.width)return;	//��������
				break;
			}
		}  	 
	}  	    	   	 	  
}   
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 
//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}
