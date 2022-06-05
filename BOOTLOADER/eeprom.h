#ifndef EEPROM_H
#define EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "flash.h"

/* Declarations and definitions ----------------------------------------------*/
#define PAGE_DATA_OFFSET                                                8
#define PAGE_DATA_SIZE                                                  8

#define UPD                                                             0x12121212
#define MAC_U                                                           0x00000002
#define MAC_D                                                           0x00000000
#define IP                                                              0xC0A80002
#define MSK                                                             0xFFFFFF00
#define GW                                                              0xC0A80001

#define VAR_NUM                                                         6

#define PAGE_0_ADDRESS                                                  0x08008000
#define PAGE_1_ADDRESS                                                  0x0800C000
#define PAGE_SIZE                                                       0x4000 //16Kb

typedef enum {
  PAGE_CLEARED = 0xFFFFFFFF,
  PAGE_ACTIVE = 0x00000000,
  PAGE_RECEIVING_DATA = 0x55555555,
} PageState;

typedef enum {
  PAGE_0 = 0,
  PAGE_1 = 1,
  PAGES_NUM = 2,
} PageIdx;

typedef enum {
  EEPROM_OK = 0,
  EEPROM_ERROR = 1,
} EepromResult;

/* Functions -----------------------------------------------------------------*/
extern EepromResult EEPROM_Init();
extern EepromResult EEPROM_Read(uint32_t varId, uint32_t *varValue);
extern EepromResult EEPROM_Write(uint32_t varId, uint32_t varValue);

#endif // #ifndef EEPROM_H
