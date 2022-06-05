#ifndef FLASH_H
#define FLASH_H

//--------------------------------------------------------------------------------------------------------------------//
#include "stm32f4xx.h"
//#include "main.h"


//--------------------------------------------------------------------------------------------------------------------//
#define USER_FLASH_SIZE (USER_FLASH_END_ADDRESS - USER_FLASH_FIRST_PAGE_ADDRESS)
#define FLASH_KEY1               ((uint32_t)0x45670123)
#define FLASH_KEY2               ((uint32_t)0xCDEF89AB)


//--------------------------------------------------------------------------------------------------------------------//
uint32_t FlashWrite(__IO uint32_t* Address, uint32_t* Data, uint16_t DataLength);
int8_t FlashErase(uint32_t StartSector);
void FlashUnlock(void);
void FlashLock(void);

#endif /* FLASH_H */
