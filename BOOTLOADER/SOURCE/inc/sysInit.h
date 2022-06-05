#ifndef SYSINIT_H
#define SYSINIT_H

//--------------------------------------------------------------------------------------------------------------------//
#include "stm32f4xx.h"
#include "eeprom.h"
//#include "lan87xx.h"
//#include "string.h"




//--------------------------------------------------------------------------------------------------------------------//
#define true                            0x01
#define false                           0x00
  
#if (INFO == true || WEB_BOOT_DEBUG == true)
  #define ACTIVE_SWO
#endif

#if defined ACTIVE_SWO
  #include "stdio.h"
  #define ITM_Port8(n)                  (*((volatile unsigned char *)(0xE0000000+4*n)))
  #define ITM_Port32(n)                 (*((volatile unsigned long *)(0xE0000000+4*n)))
  #define DEMCR                         (*((volatile unsigned long *)(0xE000EDFC)))
  #define TRCENA                        0x01000000
#endif

//--------------------------------------------------------------------------------------------------------------------//
#define BUILD_YEAR (__DATE__[7] == '?' ? 1900 : (((__DATE__[7] - '0') * 1000 ) + (__DATE__[8] - '0') * 100 + (__DATE__[9] - '0') * 10 + __DATE__[10] - '0'))
#define BUILD_MONTH (__DATE__ [2] == '?' ? 1 : __DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 1 : 6) : __DATE__ [2] == 'b' ? 2 : __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 3 : 4) \
        : __DATE__ [2] == 'y' ? 5 : __DATE__ [2] == 'l' ? 7 : __DATE__ [2] == 'g' ? 8 : __DATE__ [2] == 'p' ? 9 : __DATE__ [2] == 't' ? 10 : __DATE__ [2] == 'v' ? 11 : 12)
#define BUILD_DAY (__DATE__[4] == '?' ? 1 : ((__DATE__[4] == ' ' ? 0 : ((__DATE__[4] - '0') * 10)) + __DATE__[5] - '0'))
#define BUILD_TIME_H (__TIME__[0] == '?' ? 1 : ((__TIME__[0] == ' ' ? 0 : ((__TIME__[0] - '0') * 10)) + __TIME__[1] - '0'))
#define BUILD_TIME_M (__TIME__[3] == '?' ? 1 : ((__TIME__[3] - '0') * 10 + __TIME__[4] - '0'))
#define BUILD_TIME_S (__TIME__[6] == '?' ? 1 : ((__TIME__[6] - '0') * 10 + __TIME__[7] - '0'))

//--------------------------------------------------------------------------------------------------------------------//
extern uint32_t upTime;

//--------------------------------------------------------------------------------------------------------------------//
void Sysinit(void);
void DelayMs(uint32_t ms);
#endif /* SYSINIT_H */
