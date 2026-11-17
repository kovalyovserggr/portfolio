/*******************************************************************************
                                 Timers stm32f030
*******************************************************************************/

#include "General_Definition.h"
#include "uart.h"
#include "CRC.h"
#include "FleshRW.h"

#define         TIM3_IRQn                       16
#define         TIM1_BRK_UP_TRG_COM_IRQn        13
#define         TIM1_CC_IRQn                    14
#define         TIM15_IRQn                      20
#define         TIM14_IRQn                      19 
#define         TIM17_IRQn                      22 

/******************************************************************************/
//ініціалізація протоколу логіки організації обміну даними в лінії 
void initProtocolB()
{ 
  ReadFromFlesh();//зчитати стан системи до вимкнення з флеш 
    
  for(int i=0;i<16;i++)
    {
      leds[i].Address=i;
      leds[i].Speed=speedChangeDimm;//
      leds[i].correct=(u16)(bufferFromFleshDimming[i]>>16);//записати з флеш
      leds[i].Dim=(u16)(bufferFromFleshDimming[i]); 
      if(i==15)
        leds[i].Address=31;
    }
    
   if(bufferFromFleshDimming[16]&AUTO_CONTROL_LED)
      status|=AUTO_CONTROL_LED;
     else
      status&=~AUTO_CONTROL_LED;
}


// викликається циклічно
void protokol_B_step()
{
 

}
