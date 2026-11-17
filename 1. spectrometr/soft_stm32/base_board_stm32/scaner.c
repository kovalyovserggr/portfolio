/*******************************************************************************

*******************************************************************************/
#include "General_Definition.h"


/******************************************************************************/
//метод налаштуванн€ тактуванн€
void initScaner(void)
{
  spectr.SetWave=3500;
  spectr.K=100;
  spectr.time=1;
  status &= ~CORDINATE_IS_TRUE;
}

void Scaner(void)
{
  //обрахунок заданого положенн€ щ≥лини
  if(counterForCalculationSlit>100)
  { 
    spectr.SetX = X_Calculation(spectr.Wave);
    counterForCalculationSlit=0;  
  }
  else
    counterForCalculationSlit++;
  
  
    countStep++;
    if(countStep>=spectr.time){
      
     // GPIOB->ODR^=BIT9;
     
      if(status&CORDINATE_IS_TRUE)
          {
            if(!(GPIOB->IDR&BIT7))//замкнути ключ дос€гненн€ сканером к≥нц€ 7500
              motorStepCount=0;
            
            if(!(GPIOB->IDR&BIT8))//замкнути ключ дос€гненн€ сканером к≥нц€ 3500
            {
              motorStepCount=20000;
            }
            
            setMotorStep=Position(spectr.SetWave);
            
            if(motorStepCount==setMotorStep){
            
              if(spectr.status & LAST_WAVE_CALCULATION)
                {
                  spectr.status &= ~LAST_WAVE_CALCULATION;
                  spectr.Wave = wave_Calculation(motorStepCount);
                }
              
              GPIOB->ODR&=~BIT3; 
              GPIOB->ODR&=~BIT6; 
              GPIOB->ODR&=~BIT4; 
              GPIOB->ODR&=~BIT5;
              
              return;
            }else if(motorStepCount<setMotorStep)
              {
                motorStepCount++;
                motorStepDir=1;
                //GPIOA->ODR^=BIT1;
              }
              else
              {
                motorStepCount--;
                motorStepDir=0;
                //GPIOA->ODR^=BIT1;
              }
            
            //при умов≥ р≥вност≥ заданоњ та реальноњ координати це прапорець дозволить ще раз обрахувати довжину хвил≥
            spectr.status |=LAST_WAVE_CALCULATION;
            spectr.Wave = wave_Calculation(motorStepCount);
          }
          else
          {
             if(!(GPIOB->IDR&BIT7))
              status|=CORDINATE_IS_TRUE;

            motorStepDir=0;
          } 
          
          if(motorStepDir)
          {
            motorStep++;
            if(motorStep==8)
              motorStep=0;
          }
          else
          {
            if(motorStep==0)
              motorStep=8; 
            motorStep--;
          }
          
          switch(motorStep)
          {
            case 0: GPIOB->ODR|=BIT3; GPIOB->ODR&=~BIT6; GPIOB->ODR&=~BIT4; GPIOB->ODR&=~BIT5;  break;
             case 1: GPIOB->ODR|=BIT5; GPIOB->ODR|=BIT3;  GPIOB->ODR&=~BIT4; GPIOB->ODR&=~BIT6;  break;
            case 2: GPIOB->ODR|=BIT5; GPIOB->ODR&=~BIT3;  GPIOB->ODR&=~BIT4; GPIOB->ODR&=~BIT6;  break;
             case 3: GPIOB->ODR|=BIT5; GPIOB->ODR&=~BIT3;  GPIOB->ODR&=~BIT4; GPIOB->ODR|=BIT6;  break;
            case 4: GPIOB->ODR|=BIT6; GPIOB->ODR&=~BIT4; GPIOB->ODR&=~BIT5; GPIOB->ODR&=~BIT3;   break;
             case 5: GPIOB->ODR&=~BIT5; GPIOB->ODR&=~BIT3;  GPIOB->ODR|=BIT4; GPIOB->ODR|=BIT6;  break;
            case 6: GPIOB->ODR|=BIT4; GPIOB->ODR&=~BIT3; GPIOB->ODR&=~BIT5;  GPIOB->ODR&=~BIT6;  break;
             case 7: GPIOB->ODR&=~BIT5; GPIOB->ODR|=BIT3;  GPIOB->ODR|=BIT4; GPIOB->ODR&=~BIT6;  break;
            default: break;
          }
        countStep=0;
    }    
}

