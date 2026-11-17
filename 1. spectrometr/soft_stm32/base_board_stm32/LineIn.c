/*******************************************************************************
                                 LineIn stm32f030
*******************************************************************************/

#include "General_Definition.h"
#include "uart.h"
#include "CRC.h"
#include "FleshRW.h"

#define   COUNT_CICLE                   30
#define   ADDRESS_HV                    1
#define   ADDRESS_SLIT                  3
#define   ADDRESS_DETECTOR              2

#define   HV_OK                         1
#define   HV_FAIL                       2

#define   SLIT_OK                       4  
#define   SLIT_FAIL                     5

#define   DETECTER_OK                   7
#define   DETECTER_FAIL                 8

#define   HV_SEND                       1
#define   SLIT_SEND                     3
#define   DETECTOR_SEND                 2

u16 counterErrorHV = 0;
u16 counterErrorSlit = 0;
u16 counterErrorDetector = 0;
///
void initLineIn()
{
 
}

// аналіз відповіді від пристрою
void auditAnswer()
{
  u16 status_=0;
  switch(tempRecivemas1[0])
    {
      case HV_SEND: // відповідь на зчитування даних зі HV
            if(!(status & NEW_ANSWER))
            {
              if(counterErrorHV > 10)
                spectr.status |= HV_FAIL;
              else
                counterErrorHV++;
              
             return;
            }
            else if(counterErrorHV>1)
              counterErrorHV--;
            
            status_=((((u16)tempRecivemas1[1])<<8)+((u16)tempRecivemas1[2]));
            spectr.Voltage =((((u16)tempRecivemas1[3])<<8)+((u16)tempRecivemas1[4]));
            
            if( status_ & BIT0)
               spectr.status |= HV_FAIL;
             else
              spectr.status &= ~HV_FAIL;
             
            break;
     
      case SLIT_SEND: // відповідь на зчитування даних зі SLIT
        
           if(!(status & NEW_ANSWER))
            {
              if(counterErrorSlit > 10)
                spectr.status |= SLIT_FAIL;
              else
                counterErrorSlit++;
              
             return;
            }
            else if(counterErrorSlit>1)
              counterErrorSlit--;
            
            status_=((((u16)tempRecivemas1[1])<<8)+((u16)tempRecivemas1[2]));
            spectr.X =((((u16)tempRecivemas1[3])<<8)+((u16)tempRecivemas1[4]));
            
            if( status_ & BIT0)
               spectr.status |= SLIT_FAIL;
             else
                spectr.status &= ~SLIT_FAIL;
             
            break;
      case DETECTOR_SEND: // відповідь на зчитування даних із DETECTOR
             if(!(status & NEW_ANSWER))
            {
              if(counterErrorDetector > 10)
                spectr.status |= DETECTOR_FAIL;
              else
                counterErrorDetector++;
              
             return;
            }
            else if(counterErrorDetector>1)
              counterErrorSlit--;
            
            u16 Ifeu = calculationSignalFromDetector(); 
            u16 Kabb = ABB();

            status_=((u16)tempRecivemas1[1])<<8+tempRecivemas1[2];                              //1
            u16 integral_ = (((u16)tempRecivemas1[3])<<8)+(u16)(tempRecivemas1[4]);             //2
            u32 ch1_ =(((u16)tempRecivemas1[5])<<24)+((u16)(tempRecivemas1[6])<<16) + (u32)((((u32)tempRecivemas1[7])<<8)+(((u32)tempRecivemas1[8])));        //4
            u32 ch2_ =(((u16)tempRecivemas1[9])<<24)+((u16)(tempRecivemas1[10])<<16) + (u32)((((u32)tempRecivemas1[11])<<8)+(((u32)tempRecivemas1[12])));           //6
            u32 ch3_ =(((u16)tempRecivemas1[13])<<24)+((u16)(tempRecivemas1[14])<<16) + (u32)((((u32)tempRecivemas1[15])<<8)+(((u32)tempRecivemas1[16])));       //8
            u32 ch4_ =(((u16)tempRecivemas1[17])<<24)+((u16)(tempRecivemas1[18])<<16) + (u32)((((u32)tempRecivemas1[19])<<8)+(((u32)tempRecivemas1[20])));         //10
            
            spectr.integral = (u16)((Ifeu*Kabb*integral_)/1000);
            spectr.ch1 = ((ch1_));
            spectr.ch2 = ((ch2_));
            spectr.ch3 = ((ch3_));
            spectr.ch4 = ((ch4_));
            
            u16 crc_=((u16)tempRecivemas1[21])<<8+tempRecivemas1[22];    //1
             
            if(status_ & BIT0)
                spectr.status |= DETECTOR_FAIL;
              else
                spectr.status &= ~DETECTOR_FAIL;
              
            break;
    }
}

//викликається циклічно
void line()
{
  countRecive1=0;
  if(status & WRITE_LINES)
    return;

  auditAnswer(&ReciveLine[0]);
    
    if(talkingAddress < 4)
        talkingAddress++;
      else 
        talkingAddress=1;

    index=0;
    // TX pack
    switch(talkingAddress)
    {
      case ADDRESS_HV:
          // address
          TransmiteLine[index++]=talkingAddress;// address

          // set voltage H
          TransmiteLine[index++]=(u8)(spectr.SetVoltage>>8);
          // set voltage L
          TransmiteLine[index++]=spectr.SetVoltage;
          
          crc_temp=crc16_ANSI(TransmiteLine,index,0xFFFF); // обрахунок crc
          TransmiteLine[index++]=(u8)(crc_temp);           // crc L
          TransmiteLine[index++]=(u8)(crc_temp>>8);        // crc H

          SendData_Uart1(TransmiteLine,index);             // відправка
        break;
    case ADDRESS_DETECTOR:
          // address
          TransmiteLine[index++]=talkingAddress;// address
          
          // time 
          TransmiteLine[index++]=(u8)(spectr.time>>8);  // address start register H max=127
          TransmiteLine[index++]=(u8)(spectr.time);  // address start register L
          
          // K
          TransmiteLine[index++]=(u8)(spectr.K>>8);  // data H
          TransmiteLine[index++]=(u8)spectr.K;       // data L
          
          // limit1
          TransmiteLine[index++]=(u8)(spectr.limit1>>8);  // data H
          TransmiteLine[index++]=(u8)spectr.limit1;       // data L
          // limit2
          TransmiteLine[index++]=(u8)(spectr.limit2>>8);  // data H
          TransmiteLine[index++]=(u8)spectr.limit2;       // data L
          // limit3
          TransmiteLine[index++]=(u8)(spectr.limit3>>8);  // data H
          TransmiteLine[index++]=(u8)spectr.limit3;       // data L
          
          // limit4
          TransmiteLine[index++]=(u8)(spectr.limit4>>8);  // data H
          TransmiteLine[index++]=(u8)spectr.limit4;       // data L
         
          crc_temp=crc16_ANSI(TransmiteLine,index,0xFFFF); // обрахунок crc
          TransmiteLine[index++]=(u8)(crc_temp);           // crc L
          TransmiteLine[index++]=(u8)(crc_temp>>8);        // crc H

          SendData_Uart1(TransmiteLine,index);             // відправка
        break;
      case ADDRESS_SLIT:
           // address
          TransmiteLine[index++]=talkingAddress;// address

          // set X H
          TransmiteLine[index++]=(u8)(spectr.SetX>>8);
          // set X L
          TransmiteLine[index++]=spectr.SetX;
          
          crc_temp=crc16_ANSI(TransmiteLine,index,0xFFFF); // обрахунок crc
          TransmiteLine[index++]=(u8)(crc_temp);           // crc L
          TransmiteLine[index++]=(u8)(crc_temp>>8);        // crc H

          SendData_Uart1(TransmiteLine,index);             // відправка
        break;
     case 4:
          // address
          TransmiteLine[index++]=2;// address
          
          // time 
          TransmiteLine[index++]=spectr.time;  // address start register H max=127
          TransmiteLine[index++]=spectr.time;  // address start register L
          
          // K
          TransmiteLine[index++]=(u8)(spectr.K>>8);  // data H
          TransmiteLine[index++]=(u8)spectr.K;       // data L
          
          // limit1
          TransmiteLine[index++]=(u8)(spectr.limit1>>8);  // data H
          TransmiteLine[index++]=(u8)spectr.limit1;       // data L
          // limit2
          TransmiteLine[index++]=(u8)(spectr.limit2>>8);  // data H
          TransmiteLine[index++]=(u8)spectr.limit2;       // data L
          // limit3
          TransmiteLine[index++]=(u8)(spectr.limit3>>8);  // data H
          TransmiteLine[index++]=(u8)spectr.limit3;       // data L
          
          // limit4
          TransmiteLine[index++]=(u8)(spectr.limit4>>8);  // data H
          TransmiteLine[index++]=(u8)spectr.limit4;       // data L
         
          crc_temp=crc16_ANSI(TransmiteLine,index,0xFFFF); // обрахунок crc
          TransmiteLine[index++]=(u8)(crc_temp);           // crc L
          TransmiteLine[index++]=(u8)(crc_temp>>8);        // crc H

          SendData_Uart1(TransmiteLine,index);             // відправка
        break;
      
      default:
        
        break;
    }
    
}



/*
  // Зчитування даних 
  masTransmitModBus[0]=(u8)address; //address for talkinf
  masTransmitModBus[1]=3;                                        // number command
  masTransmitModBus[2]=0x00;                                     // start address registr H
  masTransmitModBus[3]=0x00;                                     // start address registr L
  masTransmitModBus[4]=0x00;                                     // count register max=127
  masTransmitModBus[5]=0x05;                                     // count register
  crc_temp=crc16_ANSI(masTransmitModBus,6,0xFFFF);               // обрахунок crc
  masTransmitModBus[6]=(u8)(crc_temp);                           // crc L
  masTransmitModBus[7]=(u8)(crc_temp>>8);                        // crc H
  SendData_Uart2(masTransmitModBus,8);                           // відправка        

  // Відповідь на зчитування даних 
  masTransmitModBus[0]=(u8)address; //address for talkinf
  masTransmitModBus[1]=3;                                        // number command
  masTransmitModBus[2]=0x00;                                     // number byte
  masTransmitModBus[3]=data1;                                    // data1 H
  masTransmitModBus[4]=data1;                                    // data1 L
  ...
  masTransmitModBus[N+2]=dataN;                                  // dataN H
  masTransmitModBus[N+2]=dataN;                                  // dataN L
  crc_temp=crc16_ANSI(masTransmitModBus,6,0xFFFF);               // обрахунок crc
  masTransmitModBus[6]=(u8)(crc_temp);                           // crc L
  masTransmitModBus[7]=(u8)(crc_temp>>8);                        // crc H
  SendData_Uart2(masTransmitModBus,8);                           // відправка        

  // Запис 
  masTransmitModBus[0]=Address;                              // address for talkinf
  masTransmitModBus[1]=6;                                    // number command
  masTransmitModBus[2]=0x00;                                 // address registr H max=127
  masTransmitModBus[3]=address_reg;                          // address registr L
  masTransmitModBus[4]=(u8)data;                             // data H
  masTransmitModBus[5]=(u8)dfta;                             // data L
  crc_temp=crc16_ANSI(masTransmitModBus,6,0xFFFF);           // обрахунок crc
  masTransmitModBus[6]=(u8)(crc_temp);                       // crc L
  masTransmitModBus[7]=(u8)(crc_temp>>8);                    // crc H
  SendData_Uart2(masTransmitModBus,8);                       // відправка
 
  // Відповідь на запис 
  masTransmitModBus[0]=Address;                              // address for talkinf
  masTransmitModBus[1]=6;                                    // number command
  masTransmitModBus[2]=0x00;                                 // address registr H max=127
  masTransmitModBus[3]=address_reg;                          // address registr L
  masTransmitModBus[4]=(u8)data;                             // data H
  masTransmitModBus[5]=(u8)dfta;                             // data L
  crc_temp=crc16_ANSI(masTransmitModBus,6,0xFFFF);           // обрахунок crc
  masTransmitModBus[6]=(u8)(crc_temp);                       // crc L
  masTransmitModBus[7]=(u8)(crc_temp>>8);                    // crc H
  SendData_Uart2(masTransmitModBus,8);                       // відправка

*/


