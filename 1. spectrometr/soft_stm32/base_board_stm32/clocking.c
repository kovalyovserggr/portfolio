/*******************************************************************************

*******************************************************************************/
#include "General_Definition.h"

//CR
#define         HSI_ON_MY       BIT0  // увімкнення HSI
#define         HSI_RDY_MY      BIT1  // готовнівсть HSI (модуль працює)
#define         HSE_ON_MY       BIT16 // увімкення HSE
#define         HSE_RDY_MY      BIT17 // готовність HSE (модуль працює)
#define         HSE_BYP_MY      BIT18 // увімкнути в обхід HSE
#define         CSS_ON_MY       BIT19 // детектор CSS (детект. роб. зовн. такт.)
#define         PLL_ON_MY       BIT24 // увімкення PLL
#define         PLL_RDY_MY      BIT25 // готовність Pll (модуль працює)

//CFGR
#define         MOV_SWS_MY              0x02  // превірка джерел. татування сист. 
#define         MOV_HPRE_MY             0x04  // дільник між SYSCLK і HCLK
#define         MOV_PPRE_MY             0x08  // 
#define         MOV_PLL_SRC_MY          0x0F  // зміщ. для виб. вхідн. такт. PLL
#define         MOVE_PLL_MUL_MY         0x012 //
#define         MOVE_MCO_MY             0x18  //
#define         PLL_NO_DIV2_MY          BIT31 //

/******************************************************************************/
//налаштування тактування
void clocking_init(void)
{
      //Вмикаємо зовнішній генератор
      //RCC->CR|=HSE_ON_MY;
      /**/RCC->CR|=HSI_ON_MY;    
  
      //Очікуємо запуску HSI
      /**/while(!(RCC->CR&HSI_RDY_MY));
      
      //Вимикаємо PLL
      RCC->CR&=~PLL_ON_MY; 
      
      //вибираємо тактування системної шини від PLL
      RCC->CFGR|=BIT1;
      
      //вибираємо дільнка на 1 для тактування AHB (24 Мгц) від PLL
      //RCC->CFGR&=~(BIT3+BIT2+BIT1+BIT0)<<MOV_HPRE_MY;
      
      //вибираємо дільнка на 2 для тактування APB(12 МГЦ) від AHB
      //RCC->CFGR&=~(BIT2+BIT1+BIT0)<<MOV_PPRE_MY;
      
      //вибираємо джерело тактування входу PLL від HSI через дільник 
      //RCC->CFGR&=~BIT1<<MOV_PLL_SRC_MY;
      
      //вибираємо дільник на 1 частоти від HSE для тактування входу PLL 
        // RCC->CFGR|=BIT1<<MOV_PLL_SRC_MY;
      
      RCC->CFGR2=0;
      
      //вибираємо множник на частоту HSI/2 для виводу результату на вихід PLL
      RCC->CFGR|=((BIT3)<<MOVE_PLL_MUL_MY);
        
      //вибираємо подачу на MCO від PLL 
      RCC->CFGR|=BIT24+BIT25+BIT26;
      
      //дільник тактування, що подається на MCO рівний 1 
      RCC->CFGR&=~(BIT28+BIT29+BIT30);
      
      //тактування від PLL не ділиться на 2 при виводі на MCO
      RCC->CFGR&=~BIT31;
      
      //вмикаємо PLL
      RCC->CR|=PLL_ON_MY;
      
      /* RCC->CIR - регістр для дозволу, перевірки та зкидання переривань, що 
                    виникають ванслідок подій з різними модулями системи такту-
                    вання контролера*/
      
      /*APB1RSTR і APB2RSTR - регістри  для зкидання переферійних модулів*/
      
      /* AHBENR  і APB1ENR і  APB2ENR - регістри для увімкнення тактування пери-
      ферійних пристроїв*/
      
      /*CFGR3 - регістр для вибору джерела тактування периферійних пристроїв*/
      
      
      //очікуємо запуску PLL
      while(!(RCC->CR&PLL_RDY_MY));
      
      //перевіряємо джерело тактування для SYSCLK (необхідно, щоб було PLL)
      while(!((RCC->CFGR&(BIT1<<MOV_SWS_MY))&&(!(RCC->CFGR&(BIT0<<MOV_SWS_MY)))));
}