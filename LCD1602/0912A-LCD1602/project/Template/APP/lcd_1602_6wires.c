/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : usart1.c
* Author             : 喜乐蒂
* Version            : V1.0
* Date               : 04/05/2009
* Description        : LCD1602驱动函数。
*******************************************************************************/

#include "config.h" 

/* If processor works on high frequency delay has to be increased, it can be 
   increased by factor 2^N by this constant                                   */
#define DELAY_2N     0

/* 8 user defined characters to be loaded into CGRAM (used for bargraph)      */
const char UserFont[8][8] = {
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
  { 0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10 },
  { 0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18 },
  { 0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C },
  { 0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E },
  { 0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F },
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }
};

/*******************************************************************************
* Delay in while loop cycles                                                   *
*   Parameter:    cnt:    number of while cycles to delay                      *
*   Return:                                                                    *
*******************************************************************************/
static void delay (int cnt);
static void delay (int cnt)
{
  cnt <<= DELAY_2N;

  while (cnt--);
}

void LCD_DATA_DIR_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);	
}

void LCD_DATA_DIR_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);	
}


/*******************************************************************************
* Function Name  : LCD_init
* Description    : LCD初始化函数
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void lcd_init(void)
{
    int i;
  	char const *p;
	
	/*********************液晶使用的I/O口初始化**************************/
    GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);   //关闭JTAG
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7
									| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*********************液晶初始化**************************/
    delay (15000);	    
    CLR_RS();
    lcd_write_4bit (0x3);                 /* Select 4-bit interface             */
    delay (4100);
 	lcd_write_4bit (0x3);
	delay (100);
	lcd_write_4bit (0x3);
	lcd_write_4bit (0x2);

	lcd_write_cmd (0x28);                 /* 2 lines, 5x8 character matrix      */
	lcd_write_cmd (0x0C);                 /* Display ctrl:Disp=ON,Curs/Blnk=OFF */
	lcd_write_cmd (0x06);                 /* Entry mode: Move right, no shift   */

	/* Load user-specific characters into CGRAM                                 */
	lcd_write_cmd(0x40);                  /* Set CGRAM address counter to 0     */
	p = &UserFont[0][0];
	for (i = 0; i < sizeof(UserFont); i++, p++)
    lcd_putchar (*p);

	lcd_write_cmd(0x80);                  /* Set DDRAM address counter to 0     */   
 
}

/*******************************************************************************
* Read status of LCD controller                                                *
*   Parameter:    none                                                         *
*   Return:       Status byte contains busy flag and address pointer           *
*******************************************************************************/
unsigned char lcd_read_status (void)
{
  uint8_t status;
  uint16_t temp_data1, temp_data2;

  LCD_DATA_DIR_IN();
  CLR_RS();
  SET_RW();
  delay(10);
  SET_EN();
  delay(10);
  temp_data1 = GPIO_ReadOutputData(GPIOA);  //读端口a输出口的数据
  temp_data1 &= 0xf0;                    	//屏蔽非数据位
  CLR_EN();
  delay(10);
  SET_EN();
  delay(10);
  temp_data2 = GPIO_ReadOutputData(GPIOA);  //读端口a输出口的数据
  temp_data2 &= 0xf0;                    	//屏蔽非数据位
  temp_data2 = temp_data2 >> 4;
  status = (uint8_t)(temp_data1 | temp_data2);
  CLR_EN();
  LCD_DATA_DIR_OUT();
  return (status);
}

/*******************************************************************************
* Wait until LCD controller busy flag is 0                                     *
*   Parameter:                                                                 *
*   Return:       Status byte of LCD controller (busy + address)               *
*******************************************************************************/
unsigned char wait_while_busy (void)
{
  unsigned char status;

  do  {
    status = lcd_read_status();
  }  while (status & 0x80);             /* Wait for busy flag                 */

  return (status);
}


/*******************************************************************************
* Write 4-bits to LCD controller                                               *
*   Parameter:    c:      command to be written                                *
*   Return:                                                                    *
*******************************************************************************/
void lcd_write_4bit (unsigned char c)
{
  u16 temp_io = 0;
    
  temp_io = GPIO_ReadOutputData(GPIOA);   //读端口B输出口的数据
  temp_io &= 0xff0f;                      //屏蔽PB4--PB7
  c = (c <<4); 					           //左移4位
  temp_io |= c;   			                //得到新数据
  GPIO_Write(GPIOA,temp_io);              //写入新数据
  
  CLR_RW();
  SET_EN();
  delay(10);
  CLR_EN();
  delay(10);
}


/*******************************************************************************
* Write command to LCD controller                                              *
*   Parameter:    c:      command to be written                                *
*   Return:                                                                    *
*******************************************************************************/
void lcd_write_cmd (unsigned char c)
{
  wait_while_busy();

  CLR_RS();
  lcd_write_4bit (c>>4);
  lcd_write_4bit (c);
}


/*******************************************************************************
* Write data to LCD controller                                                 *
*   Parameter:    c:      data to be written                                   *
*   Return:                                                                    *
*******************************************************************************/
void lcd_write_data (unsigned char c)
{
  wait_while_busy();

  SET_RS();
  lcd_write_4bit (c>>4);
  lcd_write_4bit (c);
}


/*******************************************************************************
* Print Character to current cursor position                                   *
*   Parameter:    c:      character to be printed                              *
*   Return:                                                                    *
*******************************************************************************/
void lcd_putchar (char c)
{ 
  lcd_write_data (c);
}



/*******************************************************************************
* Set cursor position on LCD display                                           *
*   Parameter:    column: column position                                      *
*                 line:   line position                                        *
*   Return:                                                                    *
*******************************************************************************/
void set_cursor (int column, int line)
{
  unsigned char address;

  address = (line * 0x40) + column;
  address = 0x80 + (address & 0x7F);
  lcd_write_cmd(address);               /* Set DDRAM address counter to 0     */
}

/*******************************************************************************
* Clear the LCD display                                                        *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/

void lcd_clear (void)
{
  lcd_write_cmd(0x01);                  /* Display clear                      */
  set_cursor (0, 0);
}


/*******************************************************************************
* Print sting to LCD display                                                   *
*   Parameter:    string: pointer to output string                             *
*   Return:                                                                    *
*******************************************************************************/

void lcd_print (char *string)
{
  while (*string)  {
    lcd_putchar (*string++);
  }
}


/*******************************************************************************
* Print a bargraph to LCD display                                              *
*   Parameter:     val:  value 0..100 %                                        *
*                  size: size of bargraph 1..16                                *
*   Return:                                                                    *
*******************************************************************************/
void lcd_bargraph (int value, int size) {
   int i;

   value = value * size / 20;            /* Display matrix 5 x 8 pixels       */
   for (i = 0; i < size; i++) {
      if (value > 5) {
         lcd_putchar (0x05);
         value -= 5;
      }
      else {
         lcd_putchar (value);
         break;
      }
   }
}


/*******************************************************************************
* Display bargraph on LCD display                                              *
*   Parameter:     pos_x: horizontal position of bargraph start                *
*                  pos_y: vertical position of bargraph                        *
*                  value: size of bargraph active field (in pixels)            *
*   Return:                                                                    *
*******************************************************************************/

void lcd_bargraphXY (int pos_x, int pos_y, int value) {
  int i;

  set_cursor (pos_x, pos_y);
  for (i = 0; i < 16; i++) 
  {
    if (value > 5)
    {
      lcd_putchar (0x05);
      value -= 5;     
  	} 
  	else 
  	{
      lcd_putchar (value);
      while (i++ < 16) lcd_putchar (0);
  	}
  }
}

/******************************************************************************/
