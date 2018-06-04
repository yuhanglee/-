#ifndef __WCOS_CONFIG_H__
#define __WCOS_CONFIG_H__

/*
 * 本文件是进行OS的基本设置
 */


//#define DEBUG

#ifdef DEBUG
    #define DEBUG_PRINT                                 // 定义调试输出
#endif


#define PLOTFORM_FREQ           (24000000UL)            // MCU的频率

#endif
