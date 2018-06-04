#ifndef __WCOS_TYPEDEF_H__
#define __WCOS_TYPEDEF_H__

/*
 * 本文件是进行OS系统的类型定义
 */


#include "WCOS_config.h"

typedef unsigned char   		uint8_t;
typedef unsigned short  		uint16_t;
typedef unsigned long   		uint32_t;
typedef char            		int8_t;
typedef short           		int16_t;
typedef long            		int32_t;
typedef uint8_t         		u8;
typedef uint16_t        		u16;
typedef uint32_t        		u32;
typedef int8_t          		s8;
typedef int16_t         		s16;
typedef int32_t         		s32;

typedef u8              		bool;

typedef uint8_t         		size_t;

#ifdef DEBUG
    #define assert(t) \
    do {\
        if (!(t)) {\
            if (__LINE__ > 255) { \
                print_error("%s %u\n", __FILE__, __LINE__);\
            } else { \
                print_error("%s %bu\n", __FILE__, __LINE__);\
            } \
            while (1);\
        }\
    } while(0)
#else
    #define assert(t)
#endif


    
#ifndef false   
    #define false       		((bool)0)
#endif
    
#ifndef true
    #define true        		((bool)1)
#endif

#ifndef BOOL
    #define BOOL        		bool
#endif
    

#ifndef FALSE   
    #define FALSE       		((BOOL)0)
#endif
    
#ifndef TRUE
    #define TRUE        		((BOOL)1)
#endif

    
#ifdef YES
    #undef YES
#endif
    
#define YES             		(1)

#ifdef NO
    #undef NO
#endif

#define NO              		(0)

#ifndef WCOS_OK
	#define WCOS_OK				(1)
#endif

#ifndef WCOS_NOK
	#define WCOS_NOK			(0)
#endif

#ifndef WCOS_FAIL
	#define WCOS_FAIL			(-1)
#endif




#endif
