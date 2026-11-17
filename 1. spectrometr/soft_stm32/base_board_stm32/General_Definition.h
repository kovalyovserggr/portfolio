/*******************************************************************************

*******************************************************************************/

#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

#define         BIT0                    0x1    
#define         BIT1                    0x2
#define         BIT2                    0x4
#define         BIT3                    0x8
#define         BIT4                    0x10    
#define         BIT5                    0x20
#define         BIT6                    0x40
#define         BIT7                    0x80
#define         BIT8                    0x100    
#define         BIT9                    0x200
#define         BIT10                   0x400
#define         BIT11                   0x800
#define         BIT12                   0x1000    
#define         BIT13                   0x2000
#define         BIT14                   0x4000
#define         BIT15                   0x8000
#define         BIT16                   0x10000    
#define         BIT17                   0x20000
#define         BIT18                   0x40000
#define         BIT19                   0x80000
#define         BIT20                   0x100000    
#define         BIT21                   0x200000
#define         BIT22                   0x400000
#define         BIT23                   0x800000
#define         BIT24                   0x1000000    
#define         BIT25                   0x2000000
#define         BIT26                   0x4000000
#define         BIT27                   0x8000000
#define         BIT28                   0x10000000    
#define         BIT29                   0x20000000
#define         BIT30                   0x40000000
#define         BIT31                   0x80000000

#define         MAX_LEN_TRANSMIT        50 //
#define         MAX_LEN_RECIVE          50 //


#define         TRUE                    1
#define         FALSE                   0
#define         MAX_LEN_DATA_PACK       20 //максимальний розмір масиву даних де зберігаються значення вимірювань для точок пристрою

// status
#define         LCD_BUSY                BIT0 // LCD зайнятий виконує команди
#define         LCD_CURSOR_UP           BIT1 // готовність до відправки експериментальних даних
#define         BUTTON_UP               BIT2 // прапор отриманні MASTER пакету
#define         BUTTON_DOWN             BIT3 // прапор вказує драйверу I2C, що потрібно примінити нові межі вимірювання гіроскопу
#define         BUTTON_LEFT             BIT4 // прапор помилка при зчитування експериментальних даних
#define         BUTTON_RIGHT            BIT5 // прапор початку зчитування експериментальних даних, якщо 0 - непотрібно починати зчитувати дані
#define         LCD_LIGHT               BIT6 // LCCD екран світиться
#define         DATAFROMPC              BIT9
#define         RECIVE_HI               BIT10
#define         CORDINATE_IS_TRUE       BIT11
#define         IS_CONNECT              BIT12
#define         NEW_ANSWER              BIT13
#define         LAST_WAVE_CALCULATION   BIT14 //при умові рівності заданої та реальної координати це прапорець дозволить ще раз обрахувати довжину хвилі
#define         WRITE_LINES             BIT16 
//******************************Timers define***********************************
typedef uint8_t u8;
typedef uint16_t u16;         
typedef uint32_t u32;

extern u16 masConfigXW[40];     //графік залежності довжини хвилі від координати від 0 до 19 значення координат і від 20 до 39 відповідні довжини хвиль у анкстремах
extern u16 masConfigWI_FEU[40]; //графік залежності чутливості ФЕУ від довжини хвилі від 0 до 19 значення довжини хвиль і від 20 до 39 відповідні значення чутливаості ФЕУ (у діапазоні від 0 до 100,0 % з кроком 0,1%)
extern u16 masConfigWF[20];     //графік залежності фокусу вихідної щілини від довжини хвилі, від 0 до 9 значення довжини хвиль і від 10 до 19 відповідні значення Фокусу (у діапазоні від 0 до 11мм з кроком 0,1мм)

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
#define         DETECTOR_FAIL           BIT3
#define         HV_FAIL                 BIT4
#define         SLIT_FAIL               BIT5
#define         SLIT_AUTO               BIT6
}Spectrometr;

extern Spectrometr spectr;



//натиснення кнопки
extern const u8 timeClick; // час натиснення кнопки після якого вважається виникнення події її натиснення
extern u8 timeMultiClick; // час тривалого натиснення кнопки після чого подія натиснення виконується автоматично
extern u8 counterForCalculationSlit;

extern u32 status;
extern u16 index;
//LCD
extern u16 countOFFLCD;
extern u16 limitTimeOffLCD;
extern u16 limCountUpDateLCD;
extern u8 menuLCD;
extern u8 stringLCD1[20];
extern u8 stringLCD2[20];
extern u16 countUpDateLCD;
extern u16 DataLCD[100];
extern u8 DataLenLCD;
extern u8 counterLCD;
extern u8 indexDataLCD;

extern u16 temp_crc, crc_temp;
extern u16 typeSourseDetector;
extern u16 errorCount;
//UART
extern u8 TransmiteLine[100];
extern u8 ReciveLine[100];
extern u8 tempRecivemas1[100];
extern u8 countRecive1;
extern u8 LenRecive1;
extern u16 ReceiveCRC1;
extern u16 temp_crc1;
extern u16 temp_crc11;
extern u8 buf1; 
extern u8 questionL;

extern u8 TransmiteCOMP[200];
extern u8 ReciveCOMP[200];
extern u8 tempRecivemas2[100];
extern u8 countRecive2;
extern u8 LenRecive2;
extern u16 ReceiveCRC2;
extern u16 temp_crc2;
extern u16 temp_crc21;
extern u8 buf2; 
extern u16 numberRegLine;

//Button
extern u8 buttonDownL,buttonDownU, buttonDownR, buttonDownD;
extern u8 buttonUP,buttonDOWN,buttonLEFT,buttonRIGHT;
extern u8 accelerationUp;
extern u8 accelerationDwn;

//буфер для збереження у флеш
extern u32 bufferFromFlesh[50];

//scaner
extern  u16 motorStep;
extern  u16 motorStepDir;
extern  u16 motorStepCount;
extern  u16 setMotorStep;

//connection
extern u16 counterErrorConnect;

//ModBus
extern u16 talkingAddress;
extern u16 maxCountAddress;

extern u16 countStep;
extern u8 countBackFromWriteLine;
extern u16 countUpdate;

extern u8 ledCounter;