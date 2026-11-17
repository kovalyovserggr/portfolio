/*******************************************************************************

*******************************************************************************/
#include "General_Definition.h"

#define TO_PRES_LEFT               BIT5
#define TO_PRES_RIGHT              BIT4
#define TO_PRES_UP                 BIT7
#define TO_PRES_DOWN               BIT6

#define IN_BUTTON_RIGHT            GPIOA->IDR
#define IN_BUTTON_LEFT             GPIOA->IDR
#define IN_BUTTON_UP               GPIOA->IDR
#define IN_BUTTON_DOWN             GPIOA->IDR

/*

  0) Run ______________________________________________________________________ 22) L = 371.1 нм
  2) Chanel_1 _________ 10) Lim1= 100,0 %__________16) Lim1= 100,0 %            23) Val =  100,0 %
  3) Chanel_2 _________ 11) Lim2= 100,0 %__________17) Lim1= 100,0 %            24) CH1: 1000000000
  4) Chanel_3 _________ 12) Lim3= 100,0 %__________18) Lim1= 100,0 %            25) CH2: 1000000000
  5) Chanel_4 _________ 13) Lim4= 100,0 %__________19) Lim1= 100,0 %            26) CH3: 1000000000
  6) Amplifire_________ 14) K= 10000 ______________20) K= 10000                 27) CH4: 1000000000
  7) Voltage  _________ 15) Voltage= 2100 V _______21) Voltage= 2100 V          28) CH1-2: 1000000000
                                                                                29) CH2-3: 1000000000
                                                                                30) CH3-4: 1000000000      
*/

/******************************************************************************/
//метод налаштування тактування
void initButtons(void)
{

}

void Buttons(void)
{

  if(ledCounter >100){
    ledCounter=0;
    GPIOA->ODR ^= BIT1;
  } else
  {
        ledCounter++;
  }
   // left
    if(!(IN_BUTTON_LEFT&TO_PRES_LEFT)) // "left"-A4
        {
          
          if(buttonDownL==timeClick)
                menu(0,0);
          if(buttonDownL<timeMultiClick) 
              buttonDownL++;
            else
              {
                menu(0,1);
                buttonDownL=timeClick+1;
              }
        }
      else
        buttonDownL=0;

    // right
    if(!(IN_BUTTON_RIGHT&TO_PRES_RIGHT))// "right"-A6
        {
          
          if(buttonDownR==timeClick) 
               menu(1,0);
          
          if(buttonDownR<timeMultiClick) 
              buttonDownR++;
            else
              {
                 menu(1,1);
                buttonDownR=timeClick+1;
              }
        }
      else
        buttonDownR=0;

    // up
    if(!(IN_BUTTON_UP&TO_PRES_UP))// "up"-A7
        {
          
          if(buttonDownU==timeClick)  
             menu(2,0);
          
          if(buttonDownU<timeMultiClick)  
              buttonDownU++;
          else
            {
              if(accelerationUp<250)accelerationUp++;
               menu(2,1);
              buttonDownU=timeClick+1;
            }
        }
      else
      {
        if(buttonDownU) 
          {
            
          }         
          
        buttonDownU=0;
        accelerationUp=0;
        
      }

    // down
    if(!(IN_BUTTON_DOWN&TO_PRES_DOWN))// "Down"-A0
      {
        if(buttonDownD==timeClick) 
           menu(3,0);
        if(buttonDownD<timeMultiClick) 
            buttonDownD++;
          else
            {
              if(accelerationDwn<250)accelerationDwn++;
               menu(3,1);
              buttonDownD=timeClick+1;
            }
      }
    else
      {
         if(buttonDownD) 
           {
             
           }
         buttonDownD=0;
         accelerationDwn=0;
      }
    
    if(!(status&LCD_BUSY))
    {
      if(countUpdate>300)
        {
         menu(5,0);
          countUpdate=0;
        }
        else
          countUpdate++;
          
    }
    // для прискорення зміни значень при тривалому утримуванню кнопки
    if((accelerationUp>10)||(accelerationDwn>10))
        timeMultiClick=50;
     else
        timeMultiClick=150;
}


