#ifndef __MAIN_H
#define __MAIN_H

//--------------------------------------------------------------------------------------------------------------------//
#include "stm32f4xx.h"
#include "sysInit.h"

//--------------------------------------------------------------------------------------------------------------------//
#define USER_FLASH_FIRST_PAGE_ADDRESS 0x08008000 /* Only as example see comment */
#define USER_FLASH_LAST_PAGE_ADDRESS  0x080E0000
#define USER_FLASH_END_ADDRESS        0x080FFFFF  
   
/* UserID and Password definition *********************************************/
#define USERID       "root"
#define PASSWORD     "root"
#define LOGIN_SIZE   (15+ sizeof(USERID) + sizeof(PASSWORD))

/* MAC Address definition *****************************************************/
#define MAC_ADDR0   0
#define MAC_ADDR1   0
#define MAC_ADDR2   0
#define MAC_ADDR3   0 
#define MAC_ADDR4   0
#define MAC_ADDR5   2
 
/* Static IP Address definition ***********************************************/
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   0
#define IP_ADDR3   10
   
/* NETMASK definition *********************************************************/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/* Gateway Address definition *************************************************/
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   0
#define GW_ADDR3   1  

//--------------------------------------------------------------------------------------------------------------------//

  
//--------------------------------------------------------------------------------------------------------------------//


#endif /* __MAIN_H */
