#ifndef _LCD_DRV_H
#define _LCD_DRV_H
#include "sys.h"
#include "stdlib.h"
//////////////////////////////////////////////////////////////////////////////////	 
 
//2.4寸/2.8寸/3.5寸/4.3寸 TFT液晶驱动	  
//支持驱动IC型号包括:ILI9341/ILI9325/RM68042/RM68021/ILI9320/ILI9328/LGDP4531/LGDP4535/
//                  SPFD5408/1505/B505/C505/NT35310/NT35510等		    
//STM32F4工程-库函数版本
//淘宝店铺：http://mcudev.taobao.com
//////////////////////////////////////////////////////////////////////////////////	 	 
 
//LCD重要参数集
typedef struct
{
	u16 width;	//LCD宽度
	u16 height;	//LCD高度
	u16 id;			//LCD的ID
	u8 dir;			//横屏还是竖屏控制:0 竖屏,1 横屏
	u16 wramcmd;  //开始写gram指令
	u16 setxcmd; 	//设置X坐标指令
	u16 setycmd;  //设置Y坐标指令
} _lcd_dev;

extern _lcd_dev lcddev;  //管理LCD重要参数
extern u16 POINT_COLOR;  //默认红色;
extern u16 BACK_COLOR;	 //背景颜色,默认为白色

//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD端口定义---------------- 
#define LCD_LED	PBout(15)   //LCD背光  PB15

//LCD地址结构体
typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
}LCD_TypeDef;

//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A6作为数据命令区分线 
//注意设置时STM32内部会右移一位对其! 111 1110=0X7E	
#define LCD_BASE		((u32)(0x6C000000 | 0X0000007E))
#define TFTLCD			((LCD_TypeDef *) LCD_BASE)

//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 

#define DFT_SCAN_DIR	L2R_U2D		//默认的扫描方向


#define   BLACK                0x0000                // 黑色：    0,   0,   0 //
#define   BLUE                 0x001F                // 蓝色：    0,   0, 255 //
#define   GREEN                0x07E0                // 绿色：    0, 255,   0 //
#define   CYAN                 0x07FF                // 青色：    0, 255, 255 //
#define   RED                  0xF800                // 红色：  255,   0,   0 //
#define   MAGENTA              0xF81F                // 品红：  255,   0, 255 //
#define   YELLOW               0xFFE0                // 黄色：  255, 255, 0   //
#define   WHITE                0xFFFF                // 白色：  255, 255, 255 //
#define   NAVY                 0x000F                // 深蓝色：  0,   0, 128 //
#define   DGREEN               0x03E0                // 深绿色：  0, 128,   0 //
#define   DCYAN                0x03EF                // 深青色：  0, 128, 128 //
#define   MAROON               0x7800                // 深红色：128,   0,   0 //
#define   PURPLE               0x780F                // 紫色：  128,   0, 128 //
#define   OLIVE                0x7BE0                // 橄榄绿：128, 128,   0 //
#define   LGRAY                0xC618                // 灰白色：192, 192, 192 //
#define   DGRAY                0x7BEF                // 深灰色：128, 128, 128 //


//////////画笔颜色
////////#define WHITE         	 0xFFFF                // 白色：  255, 255, 255 //
////////#define BLACK         	 0x0000                // 黑色：    0,   0,   0 //	  
////////#define BLUE         	   0x001F                // 蓝色：    0,   0, 255 //  
////////#define BRED             0XF81F
////////#define GRED 			       0XFFE0
////////#define GBLUE            0X07FF
////////#define RED           	 0xF800                // 红色：  255,   0,   0 //
////////#define MAGENTA       	 0xF81F                // 品红：  255,   0, 255 //
////////#define GREEN         	 0x07E0                // 绿色：    0, 255,   0 //
////////#define CYAN          	 0x07FF                // 青色：    0, 255, 255 //
////////#define YELLOW        	 0xFFE0                // 黄色：  255, 255, 0   //
////////#define BROWN 			 0XBC40 //棕色
////////#define BRRED 			 0XFC07 //棕红色
////////#define GRAY  			 0X8430 //灰色

//////////GUI颜色
////////#define DARKBLUE      	 0x000F	//深蓝色
////////#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
////////#define GRAYBLUE       	 0X5458 //灰蓝色
//////////以上三色为PANEL的颜色 

////////#define LIGHTGREEN     	 0X841F //浅绿色
//////////#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
////////#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色

////////#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
////////#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

void TFTLCD_Init(void);													   	//初始化
void LCD_DisplayOn(void);													//开显示
void LCD_DisplayOff(void);													//关显示
void LCD_Clear(u16 Color);	 												//清屏
void LCD_SetCursor(u16 Xpos, u16 Ypos);										//设置光标
void LCD_DrawPoint(u16 x,u16 y);											//画点
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);								//快速画点
u16  LCD_ReadPoint(u16 x,u16 y); 											//读点 
void Draw_Circle(u16 x0,u16 y0,u8 r);										//画圆
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							//画线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   				//画矩形
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//填充单色
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);				//填充指定颜色
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						//显示一个字符
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						//显示一个数字
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//显示 数字
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);		//显示一个字符串,12/16字体

void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);		  
void LCD_Scan_Dir(u8 dir);							//设置屏扫描方向
void LCD_Display_Dir(u8 dir);						//设置屏幕显示方向
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);//设置窗口	


#endif
