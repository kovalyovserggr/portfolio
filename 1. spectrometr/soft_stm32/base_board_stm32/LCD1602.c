/*******************************************************************************
                                 LСD1602 stm32f051

DRAM   |0x80......0x8F|......0xA8
       |              |
       |0xC0......0xCF|......0xE8


1) очистити екран і курсор у початкове положення
  0x00000001

2) курсор у початкове положення
  0x0000001-

3) напрямок здвигу курсора при введенні символа та дозвіл здвигу екрана

    0x000001DS
    D: 1-здвиг впаво, 0-здвиг вліво;
    І: 1- здвиг екрана дозволений ,0 - здвиг екрана заборонено;
  
4) напрямок здвигу курсора при введенні символа та дозвіл здвигу екрана

    0x00001DCB
    D: 1- дисплей увімкн., 0-дисплей вимкн.;
    C: 1- курсор видно ,0 - курсор не видно;
    B: 1- курсор мигає ,0 - курсор не могає;

5) рухаємо курсором чи екраном

    0x0001SR--
    S: 1- рухати екраном, 0 - рухати курсором;
    R: 1- здвиг вправо , 0 - здвиг вліво;

6) встановити розрядність шини, кількість строчок, вибір шрифта

    0x001DNF--
    D: 1- 8 адр. шина, 0- 4 адр. шина.;
    N: 1- 2 строчки ,0 - 1 строчка;
    F: 1- символ 5х7 ,0 - символ 5х10 ;
   
7 ) Встановлення адреси CGRAM куди буде записаний цифровий код символа
    0x01AAAAAA
    A: адреса в памяті CGRAM

8) Встановлення адреси DDRAM куди буде записаний цифровий код символа

    0x1AAAAAAA
    A: адреса в памяті DDRAM

*******************************************************************************/

#include "General_Definition.h"

#define   PortLED_RW    GPIOA->ODR
#define   PortLED_RS    GPIOA->ODR
#define   PortLED_E     GPIOA->ODR
#define   PortLED_D0    GPIOB->ODR
#define   PortLED_D1    GPIOB->ODR
#define   PortLED_D2    GPIOB->ODR
#define   PortLED_D3    GPIOB->ODR
#define   PortLED_D4    GPIOB->ODR
#define   PortLED_D5    GPIOB->ODR
#define   PortLED_D6    GPIOB->ODR
#define   PortLED_D7    GPIOB->ODR
#define   port_LIGHT_BACK  GPIOB->ODR

#define   BitLED_RW    BIT


#define   BitLED_RS    BIT12
#define   BitLED_E     BIT15
#define   BitLED_D0    BIT1
#define   BitLED_D1    BIT2
#define   BitLED_D2    BIT10
#define   BitLED_D3    BIT11
#define   BitLED_D4    BIT12
#define   BitLED_D5    BIT13
#define   BitLED_D6       BIT14
#define   BitLED_D7       BIT15
#define   LED_LIGHT_BACK  BIT0


u8 SetData(u8 len)
{
    DataLenLCD=len;
    counterLCD=0;
    indexDataLCD=0;
    status|=LCD_BUSY;
}

u8 To_Char(u8 digit)
{
  u8 charConversion='0';
  switch(digit)
  {
    case 0: charConversion='0'; break;
    case 1: charConversion='1'; break;
    case 2: charConversion='2'; break;
    case 3: charConversion='3'; break;
    case 4: charConversion='4'; break;
    case 5: charConversion='5'; break;
    case 6: charConversion='6'; break;
    case 7: charConversion='7'; break;
    case 8: charConversion='8'; break;
    case 9: charConversion='9'; break;
  }
  return charConversion;
}

void To_string(u32 number1,u8 mode1,u32 number2,u8 mode2)
{            
 
  //stringLCD
  switch(mode1)
  {
      case 0:
          stringLCD1[4]=To_Char((u8)(number1%10));
          stringLCD1[3]=',';
          stringLCD1[2]=To_Char((u8)((number1%100)/10));
          stringLCD1[1]=To_Char((u8)((number1%1000)/100));
          stringLCD1[0]=To_Char((u8)((number1%10000)/1000));
          if(stringLCD1[0]=='0')
            stringLCD1[0]=' ';
          if((stringLCD1[1]=='0')&&(stringLCD1[0]==' '))
            stringLCD1[1]=' ';
          break;
       case 1:
          stringLCD1[9]=To_Char((u8)(number1%10));
          stringLCD1[8]=',';
          stringLCD1[7]=To_Char((u8)((number1%100)/10));
          stringLCD1[6]=To_Char((u8)((number1%1000)/100));
          stringLCD1[5]=To_Char((u8)((number1%10000)/1000));
          if(stringLCD1[5]=='0')
            stringLCD1[5]=' ';
          if((stringLCD1[6]=='0')&&(stringLCD1[5]==' '))
            stringLCD1[6]=' ';
          break;
        
       case 2:
          stringLCD1[6]=To_Char((u8)(number1%10));
          stringLCD1[5]=To_Char((u8)((number1%100)/10));
          stringLCD1[4]=To_Char((u8)((number1%1000)/100));
          stringLCD1[3]=To_Char((u8)((number1%10000)/1000));
          stringLCD1[2]=To_Char((u8)((number1%100000)/10000));
          stringLCD1[1]=To_Char((u8)((number1%1000000)/100000));
          stringLCD1[0]=To_Char((u8)((number1%10000000)/1000000));
          break;
       case 3:
          stringLCD1[13]=To_Char((u8)(number1%10));
          stringLCD1[12]=To_Char((u8)((number1%100)/10));
          stringLCD1[11]=To_Char((u8)((number1%1000)/100));
          stringLCD1[10]=To_Char((u8)((number1%10000)/1000));
          break;
      
        case 5:
          stringLCD1[12]=To_Char((u8)(number1%10));
          stringLCD1[11]=',';
          stringLCD1[10]=To_Char((u8)((number1%100)/10));
          stringLCD1[9]=To_Char((u8)((number1%1000)/100));
          break;
        case 6:
          stringLCD1[3]=To_Char((u8)(number1%10));
          stringLCD1[2]=',';
          stringLCD1[1]=To_Char((u8)((number1%100)/10));
          stringLCD1[0]=To_Char((u8)((number1%1000)/100));
          break;
        case 7:
          stringLCD1[15]=To_Char((u8)number1);
          break;
        case 9:
          stringLCD1[11]=To_Char((u8)(number1%10));
          stringLCD1[10]=To_Char((u8)((number1%100)/10));
          stringLCD1[9]=To_Char((u8)((number1%1000)/100));
          stringLCD1[8]=To_Char((u8)((number1%10000)/1000));
          stringLCD1[7]=To_Char((u8)((number1%100000)/10000));
          stringLCD1[6]=To_Char((u8)((number1%1000000)/100000));
          stringLCD1[5]=To_Char((u8)((number1%10000000)/1000000));
          break;
        case 10:
          stringLCD1[11]=To_Char((u8)(number1%10));
          stringLCD1[10]=To_Char((u8)((number1%100)/10));
          stringLCD1[9]=To_Char((u8)((number1%1000)/100));
          stringLCD1[8]=To_Char((u8)((number1%10000)/1000));
          stringLCD1[7]=To_Char((u8)((number1%100000)/10000));
          stringLCD1[6]=To_Char((u8)((number1%1000000)/100000));
          stringLCD1[5]=To_Char((u8)((number1%10000000)/1000000));
          break;
  }
  
 switch(mode2)
  { 
     case 0:
        stringLCD2[9]=To_Char((u8)(number2%10));
        stringLCD2[8]=To_Char((u8)((number2%100)/10));
        stringLCD2[7]=To_Char((u8)((number2%1000)/100));
        stringLCD2[6]=To_Char((u8)((number2%10000)/1000));
        stringLCD2[5]=To_Char((u8)((number2%100000)/10000));
        stringLCD2[4]=To_Char((u8)((number2%1000000)/100000));
        break;
    case 1:
        stringLCD2[12]=To_Char((u8)(number2%10));
        stringLCD2[11]=To_Char((u8)((number2%100)/10));
        stringLCD2[10]=To_Char((u8)((number2%1000)/100));
        stringLCD2[9]=To_Char((u8)((number2%10000)/1000));
        break;
    case 3:
        stringLCD2[5]=To_Char((u8)(number2%10));
        stringLCD2[4]=To_Char((u8)((number2%100)/10));
        stringLCD2[3]=To_Char((u8)((number2%1000)/100));
        stringLCD2[2]=To_Char((u8)((number2%10000)/1000));
        stringLCD2[1]=To_Char((u8)((number2%100000)/10000));
        stringLCD2[0]=To_Char((u8)((number2%1000000)/100000));
        break;
    case 4:
        stringLCD2[3]=To_Char((u8)(number2%10));
        stringLCD2[2]=To_Char((u8)((number2%100)/10));
        stringLCD2[1]=To_Char((u8)((number2%1000)/100));
        stringLCD2[0]=To_Char((u8)((number2%10000)/1000));
        break;
    case 5:
        if(spectr.status&HV_FAIL)
           {
              stringLCD2[15]='o';
              stringLCD2[14]='n';
           }
           else
           {
              stringLCD2[15]='k';
              stringLCD2[14]='o';
           }
      
        stringLCD2[4]=To_Char((u8)(number2%10));
        stringLCD2[3]=To_Char((u8)((number2%100)/10));
        stringLCD2[2]=To_Char((u8)((number2%1000)/100));
        stringLCD2[1]=To_Char((u8)((number2%10000)/1000));
        break;
    case 6:
        stringLCD2[4]=To_Char((u8)(number2%10));
        stringLCD2[3]=',';
        stringLCD2[2]=To_Char((u8)((number2%100)/10));
        stringLCD2[1]=To_Char((u8)((number2%1000)/100));
        break;
     case 7:
        stringLCD2[3]=To_Char((u8)(number2%10));
        stringLCD2[2]=To_Char((u8)((number2%100)/10));
        stringLCD2[1]=To_Char((u8)((number2%1000)/100));
        stringLCD2[0]=To_Char((u8)((number2%10000)/1000));
        break;
     case 8:
       
       if(spectr.status&DETECTOR_FAIL)
       {
          stringLCD2[15]='o';
          stringLCD2[14]='n';
       }
       else
       {
          stringLCD2[15]='k';
          stringLCD2[14]='o';
       }
       
        stringLCD2[5]=' ';
        stringLCD2[4]=To_Char((u8)((number2%10)));
        stringLCD2[3]=To_Char((u8)((number2%100)/10));
        stringLCD2[2]=',';
        stringLCD2[1]=To_Char((u8)((number2%1000)/100));
        break;
   
  }
  
}

//Увімкнути/вимкнути підсвітку 
void BackLightLCD(u8 on_off)
{
  if(on_off){
    countOFFLCD=0;
    status|=LCD_LIGHT;
    port_LIGHT_BACK |= LED_LIGHT_BACK;
  }
  else{
    countOFFLCD=0;
    status&=~LCD_LIGHT;
    port_LIGHT_BACK &=~ LED_LIGHT_BACK;
  }
} 

void initLCD(void)
{
  //ініціалізація LCD1602
  /*
  1. Команда №6 — 0x30 – встановити режим 8 біт
  2. Команда №6 — 0x28 – встановити режим 4 біти
  3. Команда №4 — 0x08 – вимкнути дисплей
  4. Команда №1 — 0x01 – зкинути дисплей
  5. Команда №3 — 0x06 – задати здвижку курсора вправо при записі символа
  6. Команда №4 — 0x0C – увімкнути дисплей
  */
  
  //засвітити екран
  countOFFLCD=0;
  BackLightLCD(1);
  status&LCD_LIGHT;
  
  DataLCD[0]=0x08;
  DataLCD[1]=0x01;
  DataLCD[2]=0x3C;
  DataLCD[3]=0x0C;
  
  // запис двох символів
  DataLCD[4]=0x000+0x40+0x00;
  DataLCD[5]=0x100+0x00;
  DataLCD[6]=0x100+0x04;
  DataLCD[7]=0x100+0x00;
  DataLCD[8]=0x100+0x04;
  DataLCD[9]=0x100+0x04;
  DataLCD[10]=0x100+0x04;
  DataLCD[11]=0x100+0x04;
  DataLCD[12]=0x100+0x00;
  DataLCD[13]=0x100+0x00;
  DataLCD[14]=0x100+0x10;
  DataLCD[15]=0x100+0x18;
  DataLCD[16]=0x100+0x1C;
  DataLCD[17]=0x100+0x1E;
  DataLCD[18]=0x100+0x1C;
  DataLCD[19]=0x100+0x18;
  DataLCD[20]=0x100+0x10;
  DataLCD[21]=0x000+0x80+0x00;
  DataLCD[22]=0x000+0x01;
  
  // виведення символів
  DataLCD[23]=0x100+' ';
  DataLCD[24]=0x100+'I';
  DataLCD[25]=0x100+' ';
  DataLCD[26]=0x100+'=';
  DataLCD[27]=0x100+' ';
  DataLCD[28]=0x100+'1';
  DataLCD[29]=0x100+'0';
  DataLCD[30]=0x100+'0';
  DataLCD[31]=0x100+',';
  DataLCD[32]=0x100+'0';
  DataLCD[33]=0x100+' ';
  DataLCD[34]=0x100+'%';
  DataLCD[35]=0x100+' ';
  DataLCD[36]=0x100+' ';
  DataLCD[37]=0x100+' ';
  DataLCD[38]=0x100+' ';
  DataLCD[39]=0x100+' ';
  DataLCD[40]=0x100+' ';
  DataLCD[41]=0x000+0x80+0x29;
  DataLCD[42]=0x100+'<';
  DataLCD[43]=0x100+'W';
  DataLCD[44]=0x100+'a';
  DataLCD[45]=0x100+'v';
  DataLCD[46]=0x100+'e';
  DataLCD[47]=0x100+' ';
  DataLCD[48]=0x100+'=';
  DataLCD[49]=0x100+' ';
  DataLCD[50]=0x100+'0';
  DataLCD[51]=0x100+'0';
  DataLCD[52]=0x100+'0';
  DataLCD[53]=0x100+'0';
  DataLCD[54]=0x100+' ';
  DataLCD[55]=0x100+'A';
  DataLCD[56]=0x100+'>';
  DataLCD[57]=0x100+' ';
  
  SetData(58);
}
 
void writeLCD(u8 start1,u8* row1,u8 len1,u8 start2,u8* row2,u8 len2,u8 isClear,u8 triangleIndex)
{
    u8 index=0;
    u8 indexRow1=0;
    u8 indexRow2=0;

    if(isClear)
        DataLCD[index++]=0x000+0x01;// переведення курсора в нульове положення і очищуємо екран
      else
        DataLCD[index++]=0x000+0x02;// переведення курсора в нульове положення

    for(int i=0;i<20;i++)
      {
          if(i==triangleIndex)
          {
                DataLCD[index++]=0x080+triangleIndex;// переміщення курсора на позицію triangleIndex
                DataLCD[index++]=0x100+0x01; // запис стрілочки
          }
          else  if((i>=start1)&&(i<(start1+len1)))
          {
            if(i==start1)
              {
                 indexRow1=0;
                 DataLCD[index++]=0x080+start1;// переміщення курсора на позицію start1
              }

            DataLCD[index++]=0x100+row1[indexRow1];

          } else if((i>=(start1+len1))&&(isClear))
            DataLCD[index++]=0x100+' ';
          indexRow1++;
     }
   
    triangleIndex-=16; 
   
    for(int i=0;i<20;i++)
      {
          if(i==triangleIndex)
          {
                DataLCD[index++]=0x080+0x28+triangleIndex;// переміщення курсора на позицію triangleIndex
                DataLCD[index++]=0x100+0x01; // запис стрілочки
          }
          else  if((i>=start2)&&(i<(start2+len2)))
          {
            if(i==start2)
              {
                 indexRow2=0;
                 DataLCD[index++]=0x080+0x28+start2;// переміщення курсора на позицію start1
              }

            DataLCD[index++]=0x100+row2[indexRow2];

          } else if((i>=(start2+len2))&&(isClear))
            DataLCD[index++]=0x100+' ';
          indexRow2++;
     }
   
    SetData(index);
}


void driveLCD(void)
{

  if((counterLCD%2)==0)
        {
          PortLED_E|=BitLED_E;//наростаючий фронт тактування
          //0-bit
          if(DataLCD[indexDataLCD]&BIT0)
            PortLED_D0|=BitLED_D0;
          else
            PortLED_D0&=~BitLED_D0;
          //1-bit
          if(DataLCD[indexDataLCD]&BIT1)
            PortLED_D1|=BitLED_D1;
          else
            PortLED_D1&=~BitLED_D1;
          //2-bit
          if(DataLCD[indexDataLCD]&BIT2)
            PortLED_D2|=BitLED_D2;
          else
            PortLED_D2&=~BitLED_D2;
          //3-bit
          if(DataLCD[indexDataLCD]&BIT3)
            PortLED_D3|=BitLED_D3;
          else
            PortLED_D3&=~BitLED_D3;
          //4-bit
          if(DataLCD[indexDataLCD]&BIT4)
            PortLED_D4|=BitLED_D4;
          else
            PortLED_D4&=~BitLED_D4;
          //5-bit
          if(DataLCD[indexDataLCD]&BIT5)
            PortLED_D5|=BitLED_D5;
          else
            PortLED_D5&=~BitLED_D5;
          //6-bit
          if(DataLCD[indexDataLCD]&BIT6)
            PortLED_D6|=BitLED_D6;
          else
            PortLED_D6&=~BitLED_D6;
          //7-bit
          if(DataLCD[indexDataLCD]&BIT7)
            PortLED_D7|=BitLED_D7;
          else
            PortLED_D7&=~BitLED_D7;
          
          if(DataLCD[indexDataLCD]&BIT8)
            PortLED_RS|=BitLED_RS;
          else
            PortLED_RS&=~BitLED_RS;
        }               
       else
        {
          PortLED_E &= ~BitLED_E;// спадаючий фронт тактування
         
          /*GPIOB->ODR&=~BIT1;
          GPIOA->ODR&=~BIT12;
          GPIOA->ODR&=~BIT11;
          GPIOA->ODR&=~BIT8;
          GPIOB->ODR&=~BIT15;
          GPIOB->ODR&=~BIT14;
          GPIOB->ODR&=~BIT13;
          GPIOB->ODR&=~BIT12;*/
          indexDataLCD++;
        }
    
    counterLCD++;
    if(!(indexDataLCD < DataLenLCD))
      status &= ~LCD_BUSY;
}

void LCD(void){
  
        // оновлення LCD
        if(status&LCD_BUSY)// триває оновлення зображення LCD
          driveLCD(); //обновлення зображення LCD    
        
        if(countUpDateLCD > limCountUpDateLCD){
          
          if(status&LCD_LIGHT)
              countOFFLCD++; 

            if(countOFFLCD>limitTimeOffLCD)
            {
              BackLightLCD(0);
              
              for(int i=0;i<16;i++)
                bufferFromFlesh[i]=0; 
              bufferFromFlesh[16]=status;
              //SaveToFlesh();//записати стан системи у флеш
            }
          
          countUpDateLCD=0;
        }
        countUpDateLCD++;
}
















