/*******************************************************************************
                                 Flesh stm32f030
*******************************************************************************/

#include "General_Definition.h"

///////////////////////////////////////////////////////
#define FLASH_KEY1                         ((uint32_t)0x45670123)
#define FLASH_KEY2                         ((uint32_t)0xCDEF89AB)
#define FLASH_PAGE                          ((uint8_t)0x1E)
///////////////////////////////////////////////////////

u32 flash_ready(void) {
    return !(FLASH->SR & FLASH_SR_BSY);
}

//Затераємо сторінку
void flash_erase_page(u32 address) {
        FLASH->CR|= FLASH_CR_PER;
        FLASH->AR = address;
        FLASH->CR|= FLASH_CR_STRT;
        while(!flash_ready())
                ;
        FLASH->CR&= ~FLASH_CR_PER;
}

//розблоковуємо
void flash_unlock(void) {
          FLASH->KEYR = FLASH_KEY1;
          FLASH->KEYR = FLASH_KEY2;
}

//блокувати флеш
void flash_lock() {
        FLASH->CR |= FLASH_CR_LOCK;
}

//запис у флеш
void flash_write(u32 address,u32 data) {

        FLASH->CR |= FLASH_CR_PG;
        while(!flash_ready())
          ;
        *(__IO u16*) address = (u16)data;
        while(!flash_ready())
          ;
        address+=2;
        data>>=16;
        *(__IO u16*) address = (u16)data;
        while(!flash_ready())
          ;
        FLASH->CR &= ~(FLASH_CR_PG);

}

//зчитування флеш
u32 flash_read(u32 address) {
  //u32 address_ = FLASH_BASE + 30 * 1024;//30 - сторінка флеша(старт адреса нульової стор-0х8000000),одна сторінка 1 кБ
        return (*(__IO u32*) address);
}

//запис двойне слово у флеш (мінімальний розмір даних це сторінка що зкладається з двойних слів)
void flash_write_word(u32 word){
        u32 wr_data = word;
        u32 st_address = FLASH_BASE + FLASH_PAGE * 1024;

        flash_unlock();
        flash_erase_page(st_address);
        flash_lock();

        flash_unlock();
        for(int i=0;i<1024;i+=4)
                flash_write(st_address+i,wr_data);
        flash_lock(); 
}

// Записати дані у флеш
void SaveToFlesh()
{
      u32 address = FLASH_BASE + 30 * 1024;//30 - сторінка флеша(старт адреса нульової стор-0х8000000),одна сторінка 1 кБ

      flash_unlock();
      flash_erase_page(address);
      flash_lock();

      flash_unlock();
      for(int i=0;i<1024;i+=4)//
      {
        
        if(i<(50*4)) //- двойних слів
             flash_write(address+i,bufferFromFlesh[i/4]);
          else
             flash_write(address+i,0xFFFFFFFF);
      }
      flash_lock(); 
}

// Зчитати дані з флеш
void ReadFromFlesh()
{ 
  u32 address_=FLASH_BASE + 30 * 1024;
  for(int i=0;i<50;i++)
    bufferFromFlesh[i]=flash_read(address_+i*4);
}
             