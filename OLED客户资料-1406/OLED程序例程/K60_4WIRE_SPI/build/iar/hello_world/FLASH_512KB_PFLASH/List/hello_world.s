///////////////////////////////////////////////////////////////////////////////
//                                                                            /
//                                                      08/Jul/2014  15:37:35 /
// IAR ANSI C/C++ Compiler V6.30.6.23336/W32 EVALUATION for ARM               /
// Copyright 1999-2012 IAR Systems AB.                                        /
//                                                                            /
//    Cpu mode     =  thumb                                                   /
//    Endian       =  little                                                  /
//    Source file  =  E:\完成设计的产品\K60资料\OLED资料                      /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\src\pr /
//                    ojects\hello_world\hello_world.c                        /
//    Command line =  "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\src\pr /
//                    ojects\hello_world\hello_world.c" -D IAR -D             /
//                    TWR_K60N512 -lCN "E:\完成设计的产品\K60资料\OLED资料    /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\FLASH_512KB_PFLASH\List\" -lB           /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\FLASH_512KB_PFLASH\List\" -o            /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\FLASH_512KB_PFLASH\Obj\" --no_cse       /
//                    --no_unroll --no_inline --no_code_motion --no_tbaa      /
//                    --no_clustering --no_scheduling --debug                 /
//                    --endian=little --cpu=Cortex-M4 -e --fpu=None           /
//                    --dlib_config C:\IAR\arm\INC\c\DLib_Config_Normal.h -I  /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\projects\hello_world\" -I  /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\common\" -I                /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\cpu\" -I                   /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\cpu\headers\" -I           /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\drivers\adc16\" -I         /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\drivers\enet\" -I          /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\drivers\pmc\" -I           /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\drivers\rtc\" -I           /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\drivers\lptmr\" -I         /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\drivers\uart\" -I          /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\drivers\mcg\" -I           /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\drivers\wdog\" -I          /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\platforms\" -I             /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\drivers\ftm\" -I           /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\drivers\SPI\" -I           /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\..\..\src\drivers\OLED\" -I          /
//                    "E:\完成设计的产品\K60资料\OLED资料                     /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\..\" -Ol --use_c++_inline               /
//    List file    =  E:\完成设计的产品\K60资料\OLED资料                      /
//                    (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\build\ /
//                    iar\hello_world\FLASH_512KB_PFLASH\List\hello_world.s   /
//                                                                            /
//                                                                            /
///////////////////////////////////////////////////////////////////////////////

        NAME hello_world

        #define SHT_PROGBITS 0x1

        EXTERN GPIOx
        EXTERN OLED_Init
        EXTERN OLED_ShowCHinese
        EXTERN OLED_ShowString
        EXTERN SPI_Init
        EXTERN gpio_init

        PUBLIC Time
        PUBLIC main

// E:\完成设计的产品\K60资料\OLED资料 (1)\OLED客户资料-1406\OLED程序例程\K60_4WIRE_SPI\src\projects\hello_world\hello_world.c
//    1 /*
//    2  * File:		hello_world.c
//    3  * Purpose:		Main process
//    4  *
//    5  */
//    6 
//    7 #include "common.h"
//    8 #include"HAL_SPI.h"
//    9 #include "SPI_FLASH.H"
//   10 #include "uart.h"
//   11 #include "sysinit.h"
//   12 #include "start.h"
//   13 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   14 unsigned long Time;
Time:
        DS8 4
//   15 /********************************************************************/

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//   16 void main (void)
//   17 {
main:
        PUSH     {R7,LR}
//   18          gpio_init  (PORTB,23,GPO,HIGH); //初始化LED1引脚
        MOVS     R3,#+1
        MOVS     R2,#+1
        MOVS     R1,#+23
        MOVS     R0,#+1
        BL       gpio_init
//   19       
//   20          gpio_init  (PORTB,22,GPO,HIGH); //初始化LED2/C引脚
        MOVS     R3,#+1
        MOVS     R2,#+1
        MOVS     R1,#+22
        MOVS     R0,#+1
        BL       gpio_init
//   21          
//   22         SPI_Init(SPI0, SPI_SCK_DIV_512, 1); //选择SPI0 100Mhz /64 = 1.5Mhz
        MOVS     R2,#+1
        MOVS     R1,#+9
        MOVS     R0,#+0
        BL       SPI_Init
//   23         
//   24         OLED_Init();			//初始化OLED      
        BL       OLED_Init
//   25   	OLED_ShowString(1,0, "0.96' OLED TEST");  
        LDR.N    R2,??main_0
        MOVS     R1,#+0
        MOVS     R0,#+1
        BL       OLED_ShowString
//   26   	OLED_ShowString(1,16,"mcudev.taobao");  
        LDR.N    R2,??main_0+0x4
        MOVS     R1,#+16
        MOVS     R0,#+1
        BL       OLED_ShowString
//   27   	//"欢迎光临");  
//   28         OLED_ShowCHinese(1,32,0);
        MOVS     R2,#+0
        MOVS     R1,#+32
        MOVS     R0,#+1
        BL       OLED_ShowCHinese
//   29          OLED_ShowCHinese(16,32,0);
        MOVS     R2,#+0
        MOVS     R1,#+32
        MOVS     R0,#+16
        BL       OLED_ShowCHinese
//   30           OLED_ShowCHinese(32,32,1);
        MOVS     R2,#+1
        MOVS     R1,#+32
        MOVS     R0,#+32
        BL       OLED_ShowCHinese
//   31            OLED_ShowCHinese(48,32,2);
        MOVS     R2,#+2
        MOVS     R1,#+32
        MOVS     R0,#+48
        BL       OLED_ShowCHinese
//   32             OLED_ShowCHinese(64,32,3);
        MOVS     R2,#+3
        MOVS     R1,#+32
        MOVS     R0,#+64
        BL       OLED_ShowCHinese
//   33              OLED_ShowCHinese(80,32,4);
        MOVS     R2,#+4
        MOVS     R1,#+32
        MOVS     R0,#+80
        BL       OLED_ShowCHinese
//   34              OLED_ShowCHinese(96,32,0);
        MOVS     R2,#+0
        MOVS     R1,#+32
        MOVS     R0,#+96
        BL       OLED_ShowCHinese
//   35              OLED_ShowCHinese(112,32,0);
        MOVS     R2,#+0
        MOVS     R1,#+32
        MOVS     R0,#+112
        BL       OLED_ShowCHinese
//   36              
//   37         
//   38         
//   39         OLED_ShowString(1,48,"         2014-05");    
        LDR.N    R2,??main_0+0x8
        MOVS     R1,#+48
        MOVS     R0,#+1
        BL       OLED_ShowString
        B.N      ??main_1
//   40 
//   41         
//   42 	while(1)
//   43 	{
//   44 	
//   45           GPIO_SET(PORTB,23,0);//LED灯
//   46           
//   47          for(Time=0;Time<0xfffff;Time++);//延时
//   48           
//   49           GPIO_SET(PORTB,23,1);
//   50           
//   51          for(Time=0;Time<0xfffff;Time++);//延时
//   52            
//   53           GPIO_SET(PORTB,22,0);//LED灯
//   54           
//   55         for(Time=0;Time<0xfffff;Time++);//延时
??main_2:
        LDR.N    R0,??main_0+0xC
        LDR      R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.N    R1,??main_0+0xC
        STR      R0,[R1, #+0]
??main_3:
        LDR.N    R0,??main_0+0xC
        LDR      R0,[R0, #+0]
        LDR.N    R1,??main_0+0x10  ;; 0xfffff
        CMP      R0,R1
        BCC.N    ??main_2
//   56     
//   57           GPIO_SET(PORTB,22,1);
        LDR.N    R0,??main_0+0x14
        LDR      R0,[R0, #+4]
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x400000
        LDR.N    R1,??main_0+0x14
        LDR      R1,[R1, #+4]
        STR      R0,[R1, #+0]
??main_1:
        LDR.N    R0,??main_0+0x14
        LDR      R0,[R0, #+4]
        LDR      R0,[R0, #+0]
        BICS     R0,R0,#0x800000
        LDR.N    R1,??main_0+0x14
        LDR      R1,[R1, #+4]
        STR      R0,[R1, #+0]
        LDR.N    R0,??main_0+0xC
        MOVS     R1,#+0
        STR      R1,[R0, #+0]
        B.N      ??main_4
??main_5:
        LDR.N    R0,??main_0+0xC
        LDR      R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.N    R1,??main_0+0xC
        STR      R0,[R1, #+0]
??main_4:
        LDR.N    R0,??main_0+0xC
        LDR      R0,[R0, #+0]
        LDR.N    R1,??main_0+0x10  ;; 0xfffff
        CMP      R0,R1
        BCC.N    ??main_5
        LDR.N    R0,??main_0+0x14
        LDR      R0,[R0, #+4]
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x800000
        LDR.N    R1,??main_0+0x14
        LDR      R1,[R1, #+4]
        STR      R0,[R1, #+0]
        LDR.N    R0,??main_0+0xC
        MOVS     R1,#+0
        STR      R1,[R0, #+0]
        B.N      ??main_6
??main_7:
        LDR.N    R0,??main_0+0xC
        LDR      R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.N    R1,??main_0+0xC
        STR      R0,[R1, #+0]
??main_6:
        LDR.N    R0,??main_0+0xC
        LDR      R0,[R0, #+0]
        LDR.N    R1,??main_0+0x10  ;; 0xfffff
        CMP      R0,R1
        BCC.N    ??main_7
        LDR.N    R0,??main_0+0x14
        LDR      R0,[R0, #+4]
        LDR      R0,[R0, #+0]
        BICS     R0,R0,#0x400000
        LDR.N    R1,??main_0+0x14
        LDR      R1,[R1, #+4]
        STR      R0,[R1, #+0]
        LDR.N    R0,??main_0+0xC
        MOVS     R1,#+0
        STR      R1,[R0, #+0]
        B.N      ??main_3
        DATA
??main_0:
        DC32     `?<Constant "0.96\\' OLED TEST">`
        DC32     `?<Constant "mcudev.taobao">`
        DC32     `?<Constant "         2014-05">`
        DC32     Time
        DC32     0xfffff
        DC32     GPIOx
//   58          
//   59           
//   60           
//   61 	} 
//   62 }

        SECTION `.iar_vfe_header`:DATA:REORDER:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
`?<Constant "0.96\\' OLED TEST">`:
        DATA
        DC8 "0.96' OLED TEST"

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
`?<Constant "mcudev.taobao">`:
        DATA
        DC8 "mcudev.taobao"
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
`?<Constant "         2014-05">`:
        DATA
        DC8 "         2014-05"
        DC8 0, 0, 0

        END
//   63 
//   64 
//   65 
//   66 
//   67 
//   68 
//   69 
//   70 
//   71 /********************************************************************/
// 
//   4 bytes in section .bss
//  52 bytes in section .rodata
// 324 bytes in section .text
// 
// 324 bytes of CODE  memory
//  52 bytes of CONST memory
//   4 bytes of DATA  memory
//
//Errors: none
//Warnings: none
