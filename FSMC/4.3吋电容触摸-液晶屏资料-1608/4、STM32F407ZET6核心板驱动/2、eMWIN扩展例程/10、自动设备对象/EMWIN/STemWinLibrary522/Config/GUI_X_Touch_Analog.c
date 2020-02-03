/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2012  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.16 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_TOUCH_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/
#include "GUI.h"
#include "touch.h"
#include "LCD_DRV.h"


void GUI_TOUCH_X_ActivateX(void) 
{
 // XPT2046_WriteCMD(0x90);
}


void GUI_TOUCH_X_ActivateY(void)
{
  //XPT2046_WriteCMD(0xd0);
}



u8 a,buf[10];

volatile static u16 touchX=0,touchY=0,lastY=0;

int  GUI_TOUCH_X_MeasureX(void) 
{

	FT6206_Read_Reg((uint8_t*)&buf, 7);

	if ((buf[2]&0x0f) == 1)
	{
		touchY = (s16)(buf[5] & 0x0F)<<8 | (s16)buf[6];
		touchX = (s16)(buf[3] & 0x0F)<<8 | (s16)buf[4];
		if(touchY==0)
			touchX=0;	
		
			if(touchX >479 ) touchX =479;
			//else if(touchX < 0) touchX=0;
		
			if(touchY > 799) touchY = 799;
			//else if(touchY < 0) touchY = 0;
		
	}
	else
	{
		touchY =0;
		touchX =0;		
	}
	
	return touchX;
	
}


int  GUI_TOUCH_X_MeasureY(void) 
{	
	
		return touchY;
	
}

