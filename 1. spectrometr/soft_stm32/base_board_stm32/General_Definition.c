/*******************************************************************************

*******************************************************************************/
#include "stm32f0xx.h"

#define         REG_1(A)        BIT##A
#define         REG_2(A,B)      A##B
#define         REGS(Register,NamePort) REG_2(Register,NamePort)
#define         TRUE            1
#define         FALSE           0
#define         BIT0            0x1    
#define         BIT1            0x2
#define         BIT2            0x4
#define         BIT3            0x8
#define         BIT4            0x10    
#define         BIT5            0x20
#define         BIT6            0x40
#define         BIT7            0x80
#define         BIT8            0x100    
#define         BIT9            0x200
#define         BIT10           0x400
#define         BIT11           0x800
#define         BIT12           0x1000    
#define         BIT13           0x2000
#define         BIT14           0x4000
#define         BIT15           0x8000
#define         BIT16           0x10000
#define         BIT17           0x20000

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

u16 masConfigXW[40]; //
u16 masConfigWI_FEU[40];
u16 masConfigWF[20];

typedef struct{
u16 status;
u16 SetWave;
u16 Wave;
u16 temperatura;
u16 counterOn;
u16 Kgray;
u16 SetVoltage;
u16 Voltage;
u16 data1;
u16 SetX;
u16 X;
u16 K;          //11
u32 ch1;        //1
u32 ch2;        //2
u32 ch3;        //3
u32 ch4;        //4
u16 integral;   //5
u16 limit1;     //6
u16 limit2;     //7
u16 limit3;     //8
u16 limit4;     //9
u16 time;       //10
u32 control;    //12
u32 forWave;    //14
#define         DETECTOR_DATA_FAIL      BIT3
#define         HV_DATA_FAIL            BIT4
#define         SLIT_DATA_FAIL          BIT5
#define         SLIT_AUTO               BIT6
}Spectrometr;

Spectrometr spectr;

typedef struct{
u16 status;
u16 SetVoltage;
u16 Voltage;
u16 data1;
u16 data2;
u16 countError;
}HV_device;

HV_device hv;

typedef struct{
u16 status;
u16 SetX;
u16 X;
u16 countError;
// status
#define  ERROR_SLIT     BIT0
#define  AUTO_MODE      BIT1
}Slit_device;

Slit_device slit;
u16 index=0;

typedef struct{
u16 status;     //0
u16 time;       //10
u32 ch1;        //1
u32 ch2;        //2
u32 ch3;        //3
u32 ch4;        //4
u16 integral;   //5
u16 limit1;     //6
u16 limit2;     //7
u16 limit3;     //8
u16 limit4;     //9
u16 countError; //13
u32 K;          //11
u32 data;       //12
}detector_device;

detector_device detector;
        
//натиснення на кнопку
const u8 timeClick=5; // час натиснення кнопки після якого вважається виникнення події її натиснення
u8 timeMultiClick=150; // час тривалого натиснення кнопки після чого подія натиснення виконується автоматично
u32 status=0;
u8 counterForCalculationSlit=0;


//LCD
u8 menuLCD=0;
u16 DataLCD[100];
u8 DataLenLCD=3;
u8 counterLCD=0;
u8 indexDataLCD=0;
u32 countOFFLCD=0;
u8 stringLCD1[20];
u8 stringLCD2[20];
u16 countUpDateLCD=0;
u16 limCountUpDateLCD=300;
u16 limitTimeOffLCD=7000;

//Button
u8 buttonUP=1,buttonDOWN=1,buttonLEFT=1,buttonRIGHT=1;
u8 buttonDownL=0, buttonDownU=0, buttonDownR=0, buttonDownD=0;
u8 accelerationUp=0;
u8 accelerationDwn=0;

u16 temp_crc=0, crc_temp=0;
u16 typeSourseDetector=0;

//UART
u8 TransmiteLine[100];
u8 ReciveLine[100];
u8 tempRecivemas1[100];
u8 countRecive1=0;
u8 LenRecive1=20;
u16 ReceiveCRC1=0;
u16 temp_crc1=0;
u16 temp_crc11=0;
u8 buf1=0; 
u8 questionL=0;

u8 TransmiteCOMP[200];
u8 ReciveCOMP[200];
u8 tempRecivemas2[100];
u8 countRecive2=0;
u8 LenRecive2=20;
u16 ReceiveCRC2=0;
u16 temp_crc2=0;
u16 temp_crc21=0;
u8 buf2=0; 
u16 numberRegLine=0;

u16 errorCount =0;

//scaner
u16 motorStep=1;
u16 motorStepDir=1;
u16 motorStepCount=0;
u16 setMotorStep=0;

//connection
u16 counterErrorConnect=0;
u16 countStep=0;

u16 talkingAddress=0;
u16 maxCountAddress=0;

u8 countBackFromWriteLine=0;

u8 ledCounter=0;

u16 countUpdate=0;
//буфер для збереження у флеш
u32 bufferFromFlesh[]={0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
                        0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
                        0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
                        0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
                        0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF};


