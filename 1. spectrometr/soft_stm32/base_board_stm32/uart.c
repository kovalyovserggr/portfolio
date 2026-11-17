/*******************************************************************************

*******************************************************************************/
#include "General_Definition.h"
#include "CRC.h"

#define       M1                BIT28
#define       M0                BIT12
#define       RE                BIT2
#define       UE                BIT0
#define       STOP1             BIT13
#define       STOP0             BIT12
#define       TE                BIT3
#define       PCE               BIT10
#define       PS                BIT9
#define       TCIE              BIT6
#define       RXNEIE            BIT5
#define       TC                BIT6
#define       RXNE              BIT5
#define       USART1_IRQn       27
#define       USART2_IRQn       28
#define       EIE               BIT0


/***************************** змінні *****************************************/
typedef enum 
{
  Run,
  Stop,
  NameDevice,
} enumNPCommand;

u16 CRC_transmit=0;
u8 Erorrlen_3=0;
u8 Erorrlen_1=0;
u8 Erorrlen_0=0;

u8 CountTransmit1;//лічильник для реалізації передачі даних через UART
u8 lenTransmit1=0;//розмір даних, що передаються
char* DataTransmit1;//посилання на дані, які потрібно переслати чи переселаються через UART

u8 CountTransmit2;//лічильник для реалізації передачі даних через UART
u8 lenTransmit2=0;//розмір даних, що передаються
char* DataTransmit2;//посилання на дані, які потрібно переслати чи переселаються через UART

/***************************** методи *****************************************/
//
void PowerUART1(u8 Power_)
{
  if(Power_)
    {
      USART1->CR1|=TE;// увімкнути transmitter 
      USART1->CR1|=RE;// увімкнути resiver 
    }
    else   
    {
      USART1->CR1&=~TE;// вимкнути transmitter 
      USART1->CR1&=~RE;// вимкнути resiver 
    }
}

//  
void PowerUART2(u8 Power_)
{
  if(Power_)
    {
      USART2->CR1|=TE;// увімкнути transmitter 
      USART2->CR1|=RE;// увімкнути resiver 
    }
    else   
    {
      USART2->CR1&=~TE;// вимкнути transmitter 
      USART2->CR1&=~RE;// вимкнути resiver 
    }
}

//
void DirectionTR_Uart1(u8 Dir)
{
  int tempA=0;
  for(int i=0;i<1000;i++)
  tempA++;
  
  if(Dir)   
      GPIOA->ODR|=BIT11;// передавання 
    else   
      GPIOA->ODR&=~BIT11;// отримання
}

/**********************************************/
// ініціалізація uart1(швидкість 38400 біт/сек, 8 біт в пакеті, 2 стоп біт, без перевірки парності)
void init_uart1_(void)
{
    // дозвіл тактування 1
      RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
      RCC->CFGR3 &= ~RCC_CFGR3_USART1SW;
      
    //System clock (SYSCLK) selected as USART1 clock
      RCC->CFGR3 |=  RCC_CFGR3_USART1SW_0;  
    
    // задаєм 8 біт даних у пакеті
    USART1->CR1&=~M1;
    USART1->CR1|=M0;
       
    // задаєм 2 стоп біта
      USART1->CR2&=~STOP1;
      USART1->CR2&=~STOP0;
    
    // налаштування перевірки передачі пакетів даних 
      USART1->CR1|=PCE;//з перевіркою парнотсі 
      USART1->CR1&=~PS;//перевірка на парність
      
    // дозвіл переривань Тх
      USART1->CR1|=TCIE;
      
    // дозвіл переривань Rx
      USART1->CR1|=RXNEIE;
      
    // дозвіл переривань для USART1 в регістрі VIC
      NVIC_EnableIRQ(USART1_IRQn);//Дозволяємо переривання в NVIC для UART1 
    
    // вибір швидкості прийому/передачі даних
       USART1->BRR=700; // вибір швидкості прийому/передачі даних 348-115200 , 0x0829-19200, а для 9600-0x1052;
    
    // 
      PowerUART1(TRUE); 
      
    // увімкнення uart вцілому
      USART1->CR1|=UE;

   //увімкення переривань при виникненні помилок
      USART1->CR3|=BIT0;
}

// ініціалізація uart2(швидкість 38400 біт/сек, 8 біт в пакеті, 2 стоп біт, без перевірки парності)
void init_uart2_(void)
{
    // дозвіл тактування 1
      RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
      RCC->CFGR3 &= ~RCC_CFGR3_USART2SW;
      
    //System clock (SYSCLK) selected as USART2 clock
      RCC->CFGR3 |=  RCC_CFGR3_USART2SW_0;  
    
    // задаєм 8 біт даних у пакеті
      USART2->CR1&=~(M1+M0);
      
    // задаєм 2 стоп біта
      USART2->CR2|=STOP1;
      USART2->CR2|=STOP0;
    
    // налаштування передачі пакетів даних без перевірки парнотсі 
      USART2->CR1&=~PCE;
      
    // дозвіл переривань Тх
      USART2->CR1|=TCIE;
      
    // дозвіл переривань Rx
      USART2->CR1|=RXNEIE;
      
    // дозвіл переривань для USART1 в регістрі VIC
      NVIC_EnableIRQ(USART2_IRQn);//Дозволяємо переривання в NVIC для UART1 
    
    // вибір швидкості прийому/передачі даних
       USART2->BRR=346; //115200 вибір швидкості прийому/передачі даних
    
    // 
      PowerUART2(TRUE); 
      
    // увімкнення uart вцілому
      USART2->CR1|=UE;

   //увімкення переривань при виникненні помилок
      USART2->CR3|=BIT0;
}

/***************************************/
// відправити дані в порт
u8 SendData_Uart1(u8* newComand,u8 Len)
{
  USART1->CR1&=~RXNEIE;// дозвіл переривань Rx зкинуто
  DirectionTR_Uart1(1);
  for(int i=0;i<1200;i++)
   {} 
  //DirectionTR_Uart1(1);
  TIM14->CNT=0;
  lenTransmit1=Len;
  CountTransmit1=0;
  DataTransmit1=newComand;
  USART1->TDR=newComand[CountTransmit1];
  return 0;
}

// відправити дані в порт
u8 SendData_Uart2(u8* newComand,u8 Len)
{
  for(int i=0;i<1200;i++)
   {}
  
  lenTransmit2=Len;
  CountTransmit2=0;
  DataTransmit2=newComand;
  USART2->TDR=newComand[CountTransmit2];
  return 0;
}

/***********************************************/
void USART1_IRQHandler(void)// переривання від uart LINE
{
    TIM14->CNT=0;
    //прапор зпустошення Tx зкидається автоматично при запису у регістр USART1->TDR даних
    if(USART1->ISR&TC)
      {
        CountTransmit1++;
        
        if(lenTransmit1>CountTransmit1)
          USART1->TDR=DataTransmit1[CountTransmit1];
        else
        {
          countRecive1=0;
          LenRecive1=17;
          DirectionTR_Uart1(0);
          USART1->CR1|=RXNEIE;// дозвіл переривань Rx зкинуто
        }
        
         //зкидання прапора переривання зпустошення буфера
        USART1->ICR|=TC;
        
        //----------------------------------------------------------------------
      }else if(USART1->ISR&RXNE)// прапор наявності вхідних даних зкидається автоматично при зчитувані даних з USART1->RDR 
      {
        newByte:
        ReciveLine[countRecive1]=USART1->RDR;

        if(countRecive1==0)
        {
          switch(ReciveLine[0])
          {
		case 1:
              		LenRecive1=6;
			break;
		case 2:
              		LenRecive1=22;
			break;
		case 3:
              		LenRecive1=6;
			break;
          }
        }
        
        if(countRecive1==LenRecive1)
          {
            
            if(ReciveLine[0]==2)
              ReciveLine[0]=2;
              
              
            temp_crc=((u16)(ReciveLine[LenRecive1]<<8)&0xFF00)+(u16)ReciveLine[LenRecive1-1];
            temp_crc1=crc16_ANSI(ReciveLine,LenRecive1-1,0xFFFF);
            if(temp_crc==temp_crc1) // обрахунок crc
            {
                for(int i=0;i<27;i++)
                  tempRecivemas1[i]=ReciveLine[i];
              
                status|=NEW_ANSWER;
            }
          }
       
        if(countRecive1>LenRecive1)
          {
              countRecive1=0;
              LenRecive1=17;
          }
          else
            countRecive1++;
        
        if(USART1->ISR&RXNE)
          goto newByte;
       //---------------------------------------------------------------------- 
      }else if(USART1->ISR&BIT3) //подія - помилка переповнення
      {
        USART1->ICR|=BIT3;
      }else if(USART1->ISR&BIT1)//подія - помилка в перевірці кадру 
      {
       
        USART1->ICR|=BIT1;
      }else if(USART1->ISR&BIT0)//подія - помилка в перевірці парності 
      {
        USART1->ICR|=BIT0;
      }
    
      USART1->ICR=65535;
}

/******************************************************************************/
void USART2_IRQHandler(void)// переривання від uart  КОМП
{
    TIM15->CNT=0;
    TIM17->CNT=0;
    
    //прапор зпустошення Tx зкидається автоматично при запису у регістр USART2->TDR даних
    if(USART2->ISR&TC)
      { 
        CountTransmit2++;
        if(lenTransmit2>CountTransmit2)
          USART2->TDR=DataTransmit2[CountTransmit2];
        else
        {
          if(status & WRITE_LINES)
            status &= ~WRITE_LINES;
          LenRecive2=100;
        }
         //зкидання прапора переривання зпустошення буфера
        
        //зкидання прапора переривання зпустошення буфера
        USART2->ICR|=TC;
        //----------------------------------------------------------------------
      }else if(USART2->ISR&RXNE)// прапор наявності вхідних даних зкидається автоматично при зчитувані даних з USART2->RDR 
      {
          startRecive2:
          buf2=USART2->RDR;
          
          ReciveCOMP[countRecive2]=buf2;
          errorCount=0;
        
          if(countRecive2 == 0)
          {
            switch(ReciveCOMP[0])
            {
             case 1://нормальний обмін
                LenRecive2=4;
              break;
             case 2: //читати феу
               LenRecive2=4;
              break;
             case 3://читати сканер
               LenRecive2=4;
              break;
             case 4:// читати щілину
               LenRecive2=4;
              break;
             case 5:// читати щілину
               LenRecive2=30;
              break;
             case 6: //записати графік для феу
               LenRecive2=83;
               countBackFromWriteLine=0;
               status |= WRITE_LINES;
              break;
             case 7:// записати графік лдя сканера
               LenRecive2=83;
               countBackFromWriteLine=0;
               status |= WRITE_LINES;
              break; 
             case 8: // записати графік для щілини
               LenRecive2=33;
               countBackFromWriteLine=0;
               status |= WRITE_LINES;
              break;
             case 10: // записати графік для щілини
               LenRecive2=10;
               break;
             case 11:
                  LenRecive2=4; 
              break;
             case 'H': // вітання
               LenRecive2=6;
              break;
            default:
              countRecive2=0;
              break;
            }
          }
          else if(countRecive2==LenRecive2)
          {
              if(ReciveCOMP[0]=='H')
              {
                if((ReciveCOMP[1]=='i')&&
                      (ReciveCOMP[2]==' ')&&
                        (ReciveCOMP[3]=='y')&&
                          (ReciveCOMP[4]=='o')&&
                            (ReciveCOMP[5]=='u')&&
                              (ReciveCOMP[6]=='!'))
                  {
                    status |= RECIVE_HI;
                    
                    return;
                  }  
              }
              else
              {
                 u16 resultCRC = crc16_ANSI(ReciveCOMP,LenRecive2-1,0xFFFF);
                 if(((u16)ReciveCOMP[LenRecive2]+((u16)(ReciveCOMP[LenRecive2-1]<<8)&0xFF00)) == resultCRC)
                 {
                      for(int i = 0 ; i < 90; i++ )
                        tempRecivemas2[i]=ReciveCOMP[i];
                      
                      status|=DATAFROMPC;//наявний пакет даних від компютера
                 }
                }
              
              countRecive2=0;
              return;
          }
          
          if(countRecive2>LenRecive2)
            {
              countRecive2=0;
              LenRecive2=10;
              return;
            }
             else
               countRecive2++;
          
          if(USART2->ISR&RXNE)
            goto startRecive2;
           
      //---------------------------------------------------------------------- 
      }else if(USART2->ISR&BIT3) //подія - помилка переповнення
      {
        
        USART2->ICR|=BIT3;
      }else if(USART2->ISR&BIT1)//подія - помилка в перевірці кадру 
      {
       
        USART2->ICR|=BIT1;
      }else if(USART2->ISR&BIT0)//подія - помилка в перевірці парності 
      {
       
        USART2->ICR|=BIT0;
      }
     USART2->ICR=65535;
}

/*
Прерывания от UART’а могут генерироваться по факту наступления одного из событий:

USART_IT_CTS: Прерывание по изменению состояния CTS
USART_IT_LBD: LIN Break detection interrupt.
USART_IT_TXE: Прерывание по опустошению регистра передачи
USART_IT_TC: Прерывание по окончанию передачи.
USART_IT_RXNE: Прерывание по факту приема данных.
USART_IT_IDLE: Idle line detection interrupt.
USART_IT_PE: Прерывание по факту ошибки четности.
USART_IT_ERR: Прерывание по факту ошибки (Frame error, noise error, overrun error).
*/