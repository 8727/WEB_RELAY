/* Includes ------------------------------------------------------------------*/
#include "flash_if.h"

void FLASH_If_Init(void){ 
  FLASH_Unlock(); 
}

int8_t FLASH_If_Erase(uint32_t StartSector){

  /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
     be done by word */ 
 
  if (StartSector <= (uint32_t) USER_FLASH_LAST_PAGE_ADDRESS){
    FLASH_EraseSector(FLASH_Sector_4, VoltageRange_3); /* 64 Kbyte */
    FLASH_EraseSector(FLASH_Sector_5, VoltageRange_3); /* 128 Kbyte */
    FLASH_EraseSector(FLASH_Sector_6, VoltageRange_3); /* 128 Kbyte */
    FLASH_EraseSector(FLASH_Sector_7, VoltageRange_3); /* 128 Kbyte */
    FLASH_EraseSector(FLASH_Sector_8, VoltageRange_3); /* 128 Kbyte */
    FLASH_EraseSector(FLASH_Sector_9, VoltageRange_3); /* 128 Kbyte */
    FLASH_EraseSector(FLASH_Sector_10, VoltageRange_3); /* 128 Kbyte */
    FLASH_EraseSector(FLASH_Sector_11, VoltageRange_3); /* 128 Kbyte */
  }else{
    return (1);
  }
  return (0);
}

uint32_t FLASH_If_Write(__IO uint32_t* FlashAddress, uint32_t* Data ,uint16_t DataLength){
  uint32_t i = 0;

  for (i = 0; (i < DataLength) && (*FlashAddress <= (USER_FLASH_END_ADDRESS-4)); i++){
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
    if (FLASH_ProgramWord(*FlashAddress, *(uint32_t*)(Data+i)) == FLASH_COMPLETE){
     /* Check the written value */
      if (*(uint32_t*)*FlashAddress != *(uint32_t*)(Data+i)){
        /* Flash content doesn't match SRAM content */
        return(2);
      }
      /* Increment FLASH destination address */
      *FlashAddress += 4;
    }else{
      /* Error occurred while writing data in Flash memory */
      return (1);
    }
  }
  return (0);
}
