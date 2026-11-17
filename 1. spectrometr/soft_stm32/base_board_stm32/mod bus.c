/*******************************************************************************
                                 modbus
*******************************************************************************/

#include "General_Definition.h"
#include "uart.h"
#include "CRC.h"
#include "FleshRW.h"

#define   COUNT_CICLE                   30
#define   ADDRESS_HV                    1
#define   ADDRESS_SLIT                  2
#define   ADDRESS_DETECTOR              3

#define   HV_OK                         1
#define   HV_FAIL                       2

#define   SLIT_OK                       4  
#define   SLIT_FAIL                     5

#define   DETECTER_OK                   7
#define   DETECTER_FAIL                 8

#define   HV_SEND                       1
#define   SLIT_SEND                     2
#define   DETECTOR_SEND                 3


//
void initModBus()
{
  
}

// аналіз відповіді від пристрою
u8 auditAnswer()
{
  //tempRecivemas1;
  switch(questionL)
    {
      case HV_SEND: // відповідь на зчитування даних зі HV
            
            u16 status_=((u16)tempRecivemas1[1])<<8+tempRecivemas1[2];
            u16 Voltage_=((u16)tempRecivemas1[3])<<8+tempRecivemas1[4];
           
            
            if((!(status&NEW_ANSWER))||(hv.status&BIT0))
               return HV_FAIL;
             else
             {
               if(status_ & BIT0)
                 status |= HV_FAIL;
               
               spectr.Voltage=hv.Voltage_;
               
               return HV_OK;
             }
            break;
     
      case SLIT_SEND: // відповідь на зчитування даних зі SLIT
        
            slit.status=((u16)tempRecivemas1[3])<<8+tempRecivemas1[4];
            slit.SetX=((u16)tempRecivemas1[5])<<8+tempRecivemas1[6];
            slit.X=((u16)tempRecivemas1[7])<<8+tempRecivemas1[8];

            if((!(status&NEW_ANSWER))||(slit.status&BIT0))
               return SLIT_FAIL;
             else if(spectr.SetX!=slit.SetX)
               return SLIT_X_FAIL;
             else
             {
               spectr.X= slit.X;
               return SLIT_OK;
             }
             
            break;
     
      case DETECTOR_SEND: // відповідь на зчитування даних із DETECTOR

            if(!(status&NEW_ANSWER))
            {
               spectr.status |= DETECTOR_DATA_FAIL;
               return DETECTER_FAIL;
            }
            
            if(tempRecivemas1[3]==10)
            {
                detector.integral=((u16)tempRecivemas1[3])<<8+tempRecivemas1[4];//5
                detector.ch1=((u16)tempRecivemas1[5])<<8+tempRecivemas1[6];     //6
                detector.ch2=((u16)tempRecivemas1[7])<<8+tempRecivemas1[8];     //7
                detector.ch3=((u16)tempRecivemas1[9])<<8+tempRecivemas1[10];    //8
                detector.ch4=((u16)tempRecivemas1[11])<<8+tempRecivemas1[12];   //9
                
                if(detector.status&BIT0)
                  {
                    spectr.status |= DETECTOR_DATA_FAIL;
                    return DETECTER_FAIL;
                  }
                  else
                  {
                    spectr.status &= ~DETECTOR_DATA_FAIL;
                    //calculationSignalFromDetector(integral,ch1,ch2,ch3,ch4);
                    return DETECTER_OK;
                  }
            }
            if(tempRecivemas1[3]==26)
            {
                detector.status=((u16)tempRecivemas1[3])<<8+tempRecivemas1[4];//0
                detector.ch1=((u16)tempRecivemas1[5])<<8+tempRecivemas1[6];         //1
                detector.ch2=((u16)tempRecivemas1[7])<<8+tempRecivemas1[8];         //2
                detector.ch3=((u16)tempRecivemas1[9])<<8+tempRecivemas1[10];        //3
                detector.ch4=((u16)tempRecivemas1[11])<<8+tempRecivemas1[12];       //4
                detector.integral=((u16)tempRecivemas1[13])<<8+tempRecivemas1[14];  //5
                detector.limit1=((u16)tempRecivemas1[15])<<8+tempRecivemas1[16];    //6
                detector.limit2=((u16)tempRecivemas1[17])<<8+tempRecivemas1[18];    //7
                detector.limit3=((u16)tempRecivemas1[19])<<8+tempRecivemas1[20];    //8
                detector.limit4=((u16)tempRecivemas1[21])<<8+tempRecivemas1[22];    //9
                detector.time=((u16)tempRecivemas1[23])<<8+tempRecivemas1[24];      //10
                detector.K=((u16)tempRecivemas1[25])<<8+tempRecivemas1[26];         //11
                detector.data=((u32)tempRecivemas1[27])<<8+tempRecivemas1[28];   //12
                
                 if(detector.status&BIT0)
                  {
                    spectr.status |= DETECTOR_DATA_FAIL;
                    return DETECTER_FAIL;
                  }
                  else if(detector.limit1!=spectr.limit1)
                    return DETECTER_LIM1_FALSE;
                  else if(detector.limit2!=spectr.limit2)
                    return DETECTER_LIM2_FALSE;
                  else if(detector.limit3!=spectr.limit3)
                    return DETECTER_LIM3_FALSE;
                  else if(detector.limit4!=spectr.limit4)
                    return DETECTER_LIM4_FALSE;
                  else if(detector.time!=spectr.time)
                    return DETECTER_TIME_FALSE;
                  else if(detector.K!=spectr.K)
                    return DETECTER_K_FALSE;
                  else
                  {
                    spectr.status &= ~DETECTOR_DATA_FAIL;
                    //calculationSignalFromDetector(integral,ch1,ch2,ch3,ch4);
                    return DETECTER_OK;
                  }
                 
            }
            else
            {
                spectr.status |= DETECTOR_DATA_FAIL;
                return DETECTER_FAIL;
            }
           
            break;
    }
  
  
  return 0;
}

void question(u8 Address, u8 isRead,u8 startReg,u16 data)
{
  if(isRead)
      {
        if(Address<ADDRESS_HV)
            questionL=HV_READ;
          else if(Address==ADDRESS_SLIT)
            questionL=SLIT_READ;
          else
            questionL=DETECTOR_READ;
      }
    else
      {
        if(Address<ADDRESS_HV)
            questionL=HV_WRITE;
          else if(Address==ADDRESS_SLIT)
            questionL=SLIT_WRITE;
          else
            questionL=DETECTOR_WRITE;
      }
  
    u8 index=0;
    
    // address
    TransmiteLine[index++]=Address;// address

    // number command
    if(isRead){
      TransmiteLine[index++]=3;// read
    }
    else{
      TransmiteLine[index++]=6;// write
    }
    
    // start register 
    TransmiteLine[index++]=0;         // address start register H max=127
    TransmiteLine[index++]=startReg;  // address start register L
    
    // data or len read
    TransmiteLine[index++]=(u8)(data>>8);  // data H
    TransmiteLine[index++]=(u8)data;       // data L
    
    crc_temp=crc16_ANSI(TransmiteLine,index,0xFFFF); // обрахунок crc
    TransmiteLine[index++]=(u8)(crc_temp);           // crc L
    TransmiteLine[index++]=(u8)(crc_temp>>8);        // crc H

    SendData_Uart1(TransmiteLine,index);             // відправка
}

//викликається циклічно
void modBus()
{

  switch(auditAnswer(&ReciveLine[0]))
    {
      
  if(talkingAddress<(COUNT_CICLE+2))
      talkingAddress++;
    else 
      talkingAddress=1;

  
  // TX pack
  switch(talkingAddress)
    {
      case ADDRESS_HV:
          question(ADDRESS_HV,READ,START_READ_REG_HV,COUNT_READ_REG_HV);
        break;
      case ADDRESS_SLIT:
          question(ADDRESS_SLIT,READ,START_READ_REG_SLIT,COUNT_READ_REG_SLIT);
        break;
      case ADDRESS_DETECTOR:
          question(ADDRESS_DETECTOR,READ,START_READ_REG_DETECTOR,COUNT_READ_REG_DETECTOR);
        break;
      default:
          question(ADDRESS_DETECTOR,READ,START_READ_REG_DETECTOR_M,COUNT_READ_REG_DETECTOR_M);
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
