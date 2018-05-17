#ifndef __WCOS_PRINT_H__
#define __WCOS_PRINT_H__

#include "WCOS_print.h"

#define WC_ERR_LEVEL       0

#define WC_WARN_LEVEL      (WC_ERR_LEVEL + 1)

#define WC_INFO_LEVEL      (WC_WARN_LEVEL + 1)

#define WC_DEBUG_LEVEL     (WC_INFO_LEVEL + 1)



#define PRINT_LEVEL         WC_ERR_LEVEL


#ifdef DEBUG_PRINT
    #ifdef PRINT_LEVEL <= WC_ERR_LEVEL
        #define print_error(str)            printf("[*] error:\t%s\r\n", str)
    #endif
    
    #ifdef PRINT_LEVEL <= WC_INFO_LEVEL
        #define print_info(str)             printf("[+] info:\t%s\r\n", str)
    #endif
    
    #ifdef PRINT_LEVEL <= WC_WARN_LEVEL
        #define print_warn(str)             printf("[-] warning:\t%s\r\n", str);
    #endif
    
    #ifdef PRINT_LEVEL <= WC_DEBUG_LEVEL
        #define print_debug(str)            printf("[-] debug:\t%s\r\n", str);
    #endif
#endif


#endif
