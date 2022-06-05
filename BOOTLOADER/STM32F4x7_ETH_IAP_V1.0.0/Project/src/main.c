/* Includes ------------------------------------------------------------------*/
#include "stm32f4x7_eth.h"
#include "netconf.h"
#include "main.h"
#include "tftpserver.h"
#include "httpserver.h"

/* Private typedef -----------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Private define ------------------------------------------------------------*/
#define SYSTEMTICK_PERIOD_MS  10


__IO uint32_t LocalTime = 0; /* this variable is used to create a time reference incremented by 10ms */
uint32_t timingdelay;
pFunction Jump_To_Application;
uint32_t JumpAddress;


/* Private functions ---------------------------------------------------------*/
int main(void){
  /*!< At this stage the microcontroller clock setting is already configured to 
       168 MHz, this is done through SystemInit() function which is called from
       startup file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */   

  /* Initialize Key Button mounted on STM324xG-EVAL board */       
 
  
  /* Test if Key push-button on STM324xG-EVAL Board is not pressed */
  if (0x00 != 0x00){ /* Key push-button not pressed: jump to user application */
  
    /* Check if valid stack address (RAM address) then jump to user application */
    if (((*(__IO uint32_t*)USER_FLASH_FIRST_PAGE_ADDRESS) & 0x2FFE0000 ) == 0x20000000){
      /* Jump to user application */
      JumpAddress = *(__IO uint32_t*) (USER_FLASH_FIRST_PAGE_ADDRESS + 4);
      Jump_To_Application = (pFunction) JumpAddress;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) USER_FLASH_FIRST_PAGE_ADDRESS);
      Jump_To_Application();
    }else{/* Otherwise, do nothing */

      /* do nothing */
      while(1);
    }
  }
  /* enter in IAP mode */
  else{
    
    /* configure ethernet (GPIOs, clocks, MAC, DMA) */ 
    ETH_BSP_Config();
  
    /* Initialize the LwIP stack */
    LwIP_Init();
    
#ifdef USE_IAP_HTTP
    /* Initialize the webserver module */
    IAP_httpd_init();
#endif
  
#ifdef USE_IAP_TFTP    
    /* Initialize the TFTP server */
    IAP_tftpd_init();
#endif    
    
    /* Infinite loop */
    while (1){
      /* check if any packet received */
      if (ETH_CheckFrameReceived()){ 
        /* process received ethernet packet */
        LwIP_Pkt_Handle();
      }
      /* handle periodic timers for LwIP */
      LwIP_Periodic_Handle(LocalTime);
    }
  }
}

void Delay(uint32_t nCount){
  /* Capture the current local time */
  timingdelay = LocalTime + nCount;  

  /* wait until the desired delay finish */  
  while(timingdelay > LocalTime){
  }
}

void SysTick_Handler(void){
  LocalTime += SYSTEMTICK_PERIOD_MS;
}

void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(ETH_LINK_EXTI_LINE) != RESET)
  {
    Eth_Link_ITHandler(DP83848_PHY_ADDRESS);
    /* Clear interrupt pending bit */
    EXTI_ClearITPendingBit(ETH_LINK_EXTI_LINE);
  }
}

