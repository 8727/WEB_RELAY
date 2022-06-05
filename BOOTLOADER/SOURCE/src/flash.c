#include "flash.h"




void Flash_EraseSector(uint8_t tSector)
{
  while(FLASH->SR & FLASH_SR_BSY);
  FLASH->CR = FLASH_CR_SER | FLASH_CR_PSIZE_1 | ((tSector & 0x1f) << 3);
  FLASH->CR |= FLASH_CR_STRT;
  while(FLASH->SR & FLASH_SR_BSY);
}
//void FLASH_EraseSector(uint32_t FLASH_Sector, uint8_t VoltageRange)
{
  uint32_t tmp_psize = 0x0;

  tmp_psize = FLASH_PSIZE_WORD;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation();
  
  if(status == FLASH_COMPLETE)
  { 
    /* if the previous operation is completed, proceed to erase the sector */
    FLASH->CR &= CR_PSIZE_MASK;
    FLASH->CR |= tmp_psize;
    FLASH->CR &= SECTOR_MASK;
    FLASH->CR |= FLASH_CR_SER | FLASH_Sector;
    FLASH->CR |= FLASH_CR_STRT;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();
    
    /* if the erase operation is completed, disable the SER Bit */
    FLASH->CR &= (~FLASH_CR_SER);
    FLASH->CR &= SECTOR_MASK; 
  }
}

//int8_t FlashErase(uint32_t StartSector){
//  if(StartSector <= (uint32_t) USER_FLASH_LAST_PAGE_ADDRESS){
//    FLASH_EraseSector(FLASH_Sector_4, VoltageRange_3); /* 64 Kbyte */
//    FLASH_EraseSector(FLASH_Sector_5, VoltageRange_3); /* 128 Kbyte */
//    FLASH_EraseSector(FLASH_Sector_6, VoltageRange_3); /* 128 Kbyte */
//    FLASH_EraseSector(FLASH_Sector_7, VoltageRange_3); /* 128 Kbyte */
//    FLASH_EraseSector(FLASH_Sector_8, VoltageRange_3); /* 128 Kbyte */
//    FLASH_EraseSector(FLASH_Sector_9, VoltageRange_3); /* 128 Kbyte */
//    FLASH_EraseSector(FLASH_Sector_10, VoltageRange_3); /* 128 Kbyte */
//    FLASH_EraseSector(FLASH_Sector_11, VoltageRange_3); /* 128 Kbyte */
//  }else{
//    return(true);
//  }
//  return(false);
//}
///**
//  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
//  * @note   After writing data buffer, the flash content is checked.
//  * @param  FlashAddress: start address for writing data buffer
//  * @param  Data: pointer on data buffer
//  * @param  DataLength: length of data buffer (unit is 32-bit word)   
//  * @retval 0: Data successfully written to Flash memory
//  *         1: Error occurred while writing data in Flash memory
//  *         2: Written Data in flash memory is different from expected one
//  */
//uint32_t FlashWrite(__IO uint32_t* FlashAddress, uint32_t* Data ,uint16_t DataLength){
//  uint32_t i = 0;

//  for (i = 0; (i < DataLength) && (*FlashAddress <= (USER_FLASH_END_ADDRESS-4)); i++){
//    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
//       be done by word */ 
//    if (FLASH_ProgramWord(*FlashAddress, *(uint32_t*)(Data+i)) == FLASH_COMPLETE){
//     /* Check the written value */
//      if (*(uint32_t*)*FlashAddress != *(uint32_t*)(Data+i)){
//        /* Flash content doesn't match SRAM content */
//        return(2);
//      }
//      /* Increment FLASH destination address */
//      *FlashAddress += 4;
//    }else{
//      /* Error occurred while writing data in Flash memory */
//      return (1);
//    }
//  }
//  return (0);
//}

//FLASH_Status FlashProgramDoubleWord(uint32_t Address, uint64_t Data)
//{
//  FLASH_Status status = FLASH_COMPLETE;
//  /* Check the parameters */
//  assert_param(IS_FLASH_ADDRESS(Address));
//  /* Wait for last operation to be completed */
//  status = FLASH_WaitForLastOperation();
//  if(status == FLASH_COMPLETE){
//    /* if the previous operation is completed, proceed to program the new data */
//    FLASH->CR &= CR_PSIZE_MASK;
//    FLASH->CR |= FLASH_PSIZE_DOUBLE_WORD;
//    FLASH->CR |= FLASH_CR_PG;
//    *(__IO uint64_t*)Address = Data;
//    /* Wait for last operation to be completed */
//    status = FLASH_WaitForLastOperation();
//    /* if the program operation is completed, disable the PG Bit */
//    FLASH->CR &= (~FLASH_CR_PG);
//  }
//  /* Return the Program Status */
//  return status;
//}

void FlashUnlock(void){
  if((FLASH->CR & FLASH_CR_LOCK) != RESET){
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
  }
}

void FlashLock(void){
  FLASH->CR |= FLASH_CR_LOCK;
}
