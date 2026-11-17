/*******************************************************************************
                                 Timers stm32f030
*******************************************************************************/

#include "General_Definition.h"
#include "uart.h"
#include "CRC.h"
#include "FleshRW.h"

typedef struct {
u8 two;
u8 three;
}one;

one *first;

/******************************************************************************/

//ініціалізація протоколу логіки організації обміну даними в лінії 
void initComp()
{ 
  
}

// викликається циклічно
void Comp()
{
   if(status & DATAFROMPC)//аналіз даних отриманих від компа
    {
      counterErrorConnect = 0;
      status &= ~DATAFROMPC; 
      
       switch(tempRecivemas2[0])
       {
         case 2: //читати феу
           
              TransmiteCOMP[0]=2;
              TransmiteCOMP[1]=1;  
              for (int i = 0; i < 20; i++)
              {
                TransmiteCOMP[i * 4 + 2]=(u8) masConfigWI_FEU[i];
                TransmiteCOMP[i * 4 + 3]=(u8)(((u16)masConfigWI_FEU[i])>>8);  
                TransmiteCOMP[i * 4 + 4]=(u8) masConfigWI_FEU[i+20];
                TransmiteCOMP[i * 4 + 5]=(u8)(((u16)masConfigWI_FEU[i+20])>>8);  
              }
                
              temp_crc=crc16_ANSI(TransmiteCOMP,82,0xFFFF); // обрахунок crc
              TransmiteCOMP[82]=(u8) (temp_crc >> 8); // crc H
              TransmiteCOMP[83]=(u8) (temp_crc);    // crc L

              SendData_Uart2(TransmiteCOMP,84);  
              break;
         case 3://читати сканер
              TransmiteCOMP[0]=3;
              TransmiteCOMP[1]=1;  
              for (int i = 0; i < 20; i++)
              {
                TransmiteCOMP[i * 4 + 2]=(u8) masConfigXW[i];
                TransmiteCOMP[i * 4 + 3]=(u8)(((u16)masConfigXW[i])>>8);  
                TransmiteCOMP[i * 4 + 4]=(u8) masConfigXW[i+20];
                TransmiteCOMP[i * 4 + 5]=(u8)(((u16)masConfigXW[i+20])>>8);  
              }
                
              temp_crc=crc16_ANSI(TransmiteCOMP,82,0xFFFF); // обрахунок crc
              TransmiteCOMP[82]=(u8) (temp_crc >> 8); // crc H
              TransmiteCOMP[83]=(u8) (temp_crc);    // crc L

              SendData_Uart2(TransmiteCOMP,84); 
              break;
         case 4:// читати щілину
              TransmiteCOMP[0]=4;
              TransmiteCOMP[1]=1;  
              for (int i = 0; i < 10; i++)
              {
                TransmiteCOMP[i * 3 + 2]=(u8) masConfigWF[i];
                TransmiteCOMP[i * 3 + 3]=(u8)(((u16)masConfigWF[i])>>8);  
                TransmiteCOMP[i * 3 + 4]=(u8) masConfigWF[i+10]; 
              }
                
              temp_crc=crc16_ANSI(TransmiteCOMP,32,0xFFFF); // обрахунок crc
              TransmiteCOMP[32]=(u8) (temp_crc >> 8); // crc H
              TransmiteCOMP[33]=(u8) (temp_crc);    // crc L

              SendData_Uart2(TransmiteCOMP,34);
              break;
         case 5:// запис даних
             
              /*
               (timeCounting >> 8),         //21
               (timeCounting  & 0x00FF),    //22
               (control  >> 8),             //23
               (control  & 0x00FF),         //24
              */
                
              spectr.SetWave=(((u16)tempRecivemas2[3])<<8)+(u16)tempRecivemas2[4];
              if(spectr.SetWave<3500)
                spectr.SetWave=3500;
              if(spectr.SetWave>7500)
                spectr.SetWave=7500;

              spectr.limit1=(((u16)tempRecivemas2[5])<<8)+(u16)tempRecivemas2[6];
              spectr.limit2=(((u16)tempRecivemas2[7])<<8)+(u16)tempRecivemas2[8];
              spectr.limit3=(((u16)tempRecivemas2[9])<<8)+(u16)tempRecivemas2[10];
              spectr.limit4=(((u16)tempRecivemas2[11])<<8)+(u16)tempRecivemas2[12];
              
              //voltage
              spectr.SetVoltage=(((u16)tempRecivemas2[13])<<8)+(u16)tempRecivemas2[14]; 

              //amplifier
              spectr.K=(((u16)tempRecivemas2[17])<<8)+(u16)tempRecivemas2[18];
              
              //time
              spectr.time =(((u16)tempRecivemas2[19])<<8)+(u16)tempRecivemas2[20];
              
              if(spectr.time < 20)
                TIM15->ARR=1000 * spectr.time;
               else
                 TIM15->ARR=20000;
                
              /*
              if(spectr.time >= 30)
              {
                 TIM15->ARR=1200; // (4 посилки на 160 мс 3 кроків двигуна)32 мс період між посилками з даними, 40 мс на крок
              }else if(spectr.time >= 20)
              {
                 TIM15->ARR=1300; // (4 посилки на 160 мс 6 кроків двигуна)32 мс період між посилками з даними, 27 мс на крок
              }else if(spectr.time >= 10)
              {
                 TIM15->ARR=1300; // (4 посилки на 150 мс 12 кроків двигуна) 32 мс період між посилками з даними, 14 мс на крок
              }else if(spectr.time >= 5)
              {
                 TIM15->ARR=900; // (6 посилок на 160 мс 23 кроків двигуна) 25 мс період між посилками з даними, 7,2 мс на крок
              }else if(spectr.time >= 2)
              {
                 TIM15->ARR=500;  // (10 посилок на 160 мс 53 кроків двигуна) 14 мс період між посилками з даними, 2,8 мс на крок 
              }else if(spectr.time == 1)
              {
                 TIM15->ARR=300;// (14 посилок на 150 мс 109 кроків двигуна) 10 мс період між посилками з даними, 1,4 мс на крок
              }
              */
              //температура випромінюваного тіла
              spectr.temperatura =(((u16)tempRecivemas2[25])<<8)+(u16)tempRecivemas2[26];
              
              //коефіцієнт сірості 
              spectr.Kgray=(((u16)tempRecivemas2[27])<<8)+(u16)tempRecivemas2[28];

              //вказівка на здійснення ручного чи автоматичного керування щілиною 
              u16 control=(((u16)tempRecivemas2[23])<<8)+(u16)tempRecivemas2[24];
              if(control&BIT0)
                spectr.status |= SLIT_AUTO;
              else
                spectr.status &= ~SLIT_AUTO;
              
              //Focus
              if(!(spectr.status&SLIT_AUTO))
              {
                spectr.SetX =(((u16)tempRecivemas2[15])<<8)+(u16)tempRecivemas2[16];
                if(spectr.SetX<0)
                  spectr.SetX=0;
                if(spectr.SetX>110)
                  spectr.SetX=110;
              } 
              break;
         case 6: //записати графік для феу
             
              for (int i = 0; i < 20; i++)
              {
                  masConfigWI_FEU[i]=(u16)(((u16)tempRecivemas2[i * 4 + 2])+(((u16)tempRecivemas2[i * 4 + 3])<<8));  // довжина хвилі
                  masConfigWI_FEU[i+20]=((u16)tempRecivemas2[i * 4 + 4])+((((u16)tempRecivemas2[i * 4 + 5])<<8));  // чутливість  
              }
              saveLines();
              
              TransmiteCOMP[0]=6;
              TransmiteCOMP[1]=1;
              TransmiteCOMP[2]=0;
              temp_crc=crc16_ANSI(TransmiteCOMP,3,0xFFFF); // обрахунок crc
              TransmiteCOMP[3]=(u8) (temp_crc >> 8); // crc H
              TransmiteCOMP[4]=(u8) (temp_crc);    // crc L
              
              SendData_Uart2(TransmiteCOMP,5);  
              

              break;
         case 7:// записати графік для сканера
              for (int i = 0; i < 20; i++)
              {
                  masConfigXW[i]=((u16)tempRecivemas2[i * 4 + 2])+(((u16)tempRecivemas2[i * 4 + 3])<<8);  // координата
                  masConfigXW[i+20]=((u16)tempRecivemas2[i * 4 + 4])+(((u16)tempRecivemas2[i * 4 + 5])<<8);  // довжина хвилі  
              }
              saveLines();
              
              TransmiteCOMP[0]=7;
              TransmiteCOMP[1]=1;
              TransmiteCOMP[2]=0;
              temp_crc=crc16_ANSI(TransmiteCOMP,3,0xFFFF); // обрахунок crc
              TransmiteCOMP[3]=(u8) (temp_crc >> 8); // crc H
              TransmiteCOMP[4]=(u8) (temp_crc);    // crc L
              
              SendData_Uart2(TransmiteCOMP,5);  
              
              break; 
         case 8: // записати графік для щілини
              for (int i = 0; i < 10; i++)
              {
                  masConfigWF[i]=((u16)tempRecivemas2[i * 3 + 2])+(((u16)tempRecivemas2[i * 3 + 3])<<8);  // жовжина хвилі
                  masConfigWF[i+10]=(u16)tempRecivemas2[i * 3 + 4];  // фокусна відстань 
              }
              saveLines();

              TransmiteCOMP[0]=8;
              TransmiteCOMP[1]=1;
              TransmiteCOMP[2]=0;
              temp_crc=crc16_ANSI(TransmiteCOMP,3,0xFFFF); // обрахунок crc
              TransmiteCOMP[3]=(u8) (temp_crc >> 8); // crc H
              TransmiteCOMP[4]=(u8) (temp_crc);    // crc L
              SendData_Uart2(TransmiteCOMP,5);  
              break;
      }

        if(countBackFromWriteLine>100)
        {
          if(status & WRITE_LINES)
              status &= ~WRITE_LINES;
          countBackFromWriteLine=0;
        }
        else
          countBackFromWriteLine++;
      
   }
   else
   {  
      
    if(counterErrorConnect > 1000)
      {
         if( menuLCD == 111)
             menu(7,0);//перехід в початкове меню
         
         status &= ~IS_CONNECT;
         counterErrorConnect=0;
      }
      else
       counterErrorConnect++;
     
   }
   
   if(status & RECIVE_HI)
   { 
      status &=  ~RECIVE_HI;
      status |= IS_CONNECT;
      counterErrorConnect=0;
      menu(6,0);//перехід в початкове меню
      SendData_Uart2("and you!",8);
   }
   
}
