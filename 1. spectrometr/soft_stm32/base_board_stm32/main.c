/*****************************************************
програма - "Ball_01" 
дата 20.11.19
розробник - Ковальов С.Г. 
*****************************************************/
#include "General_Definition.h"
#include "timers_.h"
#include "ports_.h"
#include "clocking.h"
#include "ACP.h"
#include "uart.h"
#include "stm32f0xx.h"
#include "Math.h"
#include "LCD1602.h"
#include "LineIn.h"
#include "Menu.h"
#include "CRC.h"
#include "FleshRW.h"
#include "scaner.h"
#include "mod bus.h"
#include "Buttons.h"
#include "PC.h"
#include "dataLineConfig.h"
/******************************************************************************/


//основна функція
int main()
{ 
    #warning потрібно заблокувати прошивку !!!

    status=0;
    
    //вимкнути перивання глобально
    __disable_irq (); 

    //методи налаштування контролера
    {   
        //налаштування тактування
        clocking_init();

        //
        initLines();
        
        //налаштування порту А
        ports_init();

        //налаштування таймера1
        init_timer1_();
        
        //налаштування таймера3
        init_timer3_();
        
        //налаштування таймера14
        init_timer14_();
        
        //налаштування таймера14
        init_timer15_();
        
        //налаштування таймера16 
        init_timer16_();
         
        //налаштування таймера17 
        init_timer17_();
        
        //налаштування АЦП
        //init_ACP_();
        
        //налаштування UART1
        init_uart1_(); // Line
        
        //налаштування UART2  
        init_uart2_(); // Комп
        
        //налаштування UART2  
        initLCD();
        
        //налаштування сканера
        initScaner();
          
        //ініціалізація протоколу "B"
        initLineIn();
        
        //Buttons
        initButtons();
        
        //Копмютер
        initComp();
    }
    
    //увімкнути перивання глобально
   __enable_irq();

  spectr.SetWave=3600;

  while(1)
  {   
   
    //таймер 1,33 мс  
    if(TIM17->SR&BIT0) 
    {
      Comp(); //Computer
      countRecive2=0;
      TIM17->SR&=~BIT0;//зкидання прапора переривань таймера Т1
    }
    //
    if(!(status & WRITE_LINES))
    {
    
      //таймер 2,58 мс  
      if(TIM15->SR&BIT0) 
      { 
        if(!(status & WRITE_LINES))
        {
            countBackFromWriteLine=0;
            TransmiteCOMP[0]=1;
            TransmiteCOMP[1]=1;
            TransmiteCOMP[2]=14;
            TransmiteCOMP[3]=(u8)((spectr.status >> 8) & 0x00FF);
            TransmiteCOMP[4]=(u8) (spectr.status & 0x00FF);
            TransmiteCOMP[5]=(u8)((spectr.X >> 8) & 0x00FF);
            TransmiteCOMP[6]=(u8) (spectr.X & 0x00FF);
            TransmiteCOMP[7]=(u8)((spectr.Voltage >> 8) & 0x00FF);
            TransmiteCOMP[8]=(u8) (spectr.Voltage & 0x00FF);
            TransmiteCOMP[9]=(u8)((spectr.integral >> 8) & 0x00FF);
            TransmiteCOMP[10]=(u8)(spectr.integral & 0x00FF);
            TransmiteCOMP[11]=(u8)((spectr.ch1 >> 24) & 0x00FF);
            TransmiteCOMP[12]=(u8)((spectr.ch1 >> 16) & 0x00FF);
            TransmiteCOMP[13]=(u8)((spectr.ch1 >> 8) & 0x00FF);
            TransmiteCOMP[14]=(u8) (spectr.ch1 & 0x00FF);
            TransmiteCOMP[15]=(u8)((spectr.ch2 >> 24) & 0x00FF);
            TransmiteCOMP[16]=(u8)((spectr.ch2 >> 16) & 0x00FF);
            TransmiteCOMP[17]=(u8)((spectr.ch2 >> 8) & 0x00FF);
            TransmiteCOMP[18]=(u8) (spectr.ch2&0x00FF);
            TransmiteCOMP[19]=(u8)((spectr.ch3 >> 24) &0x00FF);
            TransmiteCOMP[20]=(u8)((spectr.ch3 >> 16) &  0x00FF);
            TransmiteCOMP[21]=(u8)((spectr.ch3 >> 8) & 0x00FF);
            TransmiteCOMP[22]=(u8) (spectr.ch3 & 0x00FF);
            TransmiteCOMP[23]=(u8)((spectr.ch4 >> 24) & 0x00FF);
            TransmiteCOMP[24]=(u8)((spectr.ch4 >> 16) & 0x00FF);
            TransmiteCOMP[25]=(u8)((spectr.ch4 >> 8) & 0x00FF);
            TransmiteCOMP[26]=(u8) (spectr.ch4 & 0x00FF);
            TransmiteCOMP[27]=(u8) 0;
            TransmiteCOMP[28]=(u8) 0;
            TransmiteCOMP[29]=(u8)((spectr.Wave >> 8) & 0x00FF);
            TransmiteCOMP[30]=(u8) (spectr.Wave & 0x00FF);

            temp_crc=crc16_ANSI(TransmiteCOMP,31,0xFFFF); // обрахунок crc
            TransmiteCOMP[31]=(u8) (temp_crc >> 8); // crc H
            TransmiteCOMP[32]=(u8) (temp_crc);    // crc L

            SendData_Uart2(TransmiteCOMP,33);
        }
         TIM15->SR&=~BIT0;//зкидання прапора переривань таймера Т1
      }
      
      //таймер 9,80 мс
      if(TIM1->SR&BIT0)
        {
          Buttons();  //Butoons
          TIM1->SR&=~BIT0;//зкидання прапора переривань таймера Т1     
        }

        //таймер 1,0 мс  
        if(TIM3->SR&BIT0) 
        {
          LCD();
          TIM3->SR&=~BIT0;//зкидання прапора переривань таймера Т1
        }
      
       //таймер 2,58 мс  
        if(TIM14->SR&BIT0) 
        { 
          line(); //Line
          TIM14->SR&=~BIT0;//зкидання прапора переривань таймера Т1
        }
      
        //таймер 1,00 мс  
        if(TIM16->SR&BIT0) 
        { 
          Scaner();//Scaner 
          TIM16->SR&=~BIT0;//зкидання прапора переривань таймера Т1
        }
    }
    else
      TIM16->SR&=~BIT0;//зкидання прапора переривань таймера Т1
      
  }
}

/******************************************************************************/
