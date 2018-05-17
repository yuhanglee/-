#ifndef __MYLIB_H__
#define __MYLIB_H__

#include "stdio.h"
#include "stc8.h"

#define DEBUG

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned long   uint32_t;
typedef char            int8_t;
typedef short           int16_t;
typedef long            int32_t;
typedef uint8_t         u8;
typedef uint16_t        u16;
typedef uint32_t        u32;
typedef int8_t          s8;
typedef int16_t         s16;
typedef int32_t         s32;


#define FALSE   0
#define TRUE    1

#define LOW     0
#define HIGH    1

#define low     0
#define high    1




#ifdef DEBUG
    #define wc_assert(n)    \
    do {\
        if (!(n)) {\
            if (__LINE__ > 255) { \
                printf("%s %u\n", __FILE__, __LINE__);\
            } else { \
                printf("%s %bu\n", __FILE__, __LINE__);\
            } \
            while (1);\
        }\
    } while(0)
#else
    #define wc_assert(n)    
#endif




#define FOSC        (24000000UL) // 内部晶振为24MHz，如果需要使用外部的11.0592MHz，则需要对硬件做一些改动
//#define FOSC        (11059200UL) // 内部晶振为24MHz，如果需要使用外部的11.0592MHz，则需要对硬件做一些改动



#define CLEAR_FLAG(flag, num)           (AUXINTIF &= !(##flag##num##IF))


/* GPIO 定义 */
typedef enum {
    GPIO_Mode_QB_Port = 0,      // 双向输出
    GPIO_Mode_Out_PP,           // 推挽输出
    GPIO_Mode_Input,            // 高阻输入
    GPIO_Mode_OD_PP,            // 开漏输出
}GPIO_Mode_Type;

#define GPIO_Mode(gpio, pin, mode)         \
do {\
    ##gpio##M0 &= ~(((1) & 0x1) << pin);\
    ##gpio##M0 |= (((mode) & 0x1) << pin);\
    ##gpio##M1 &= ~(((1) & 0x1) << pin);\
    ##gpio##M1 |= (((mode >> 1) & 0x1) << pin);\
}while (0) 


#define GPIO_SetPin(gpio, pin)          ((gpio) |= (1 << (pin)))
#define GPIO_ResetPin(gpio, pin)        ((gpio) &= (~(1 << (pin))))


#define PU_Set(gpio, pin)               ((##gpio##PU) |= (1 << (pin)))
#define PU_Reset(gpio, pin)             ((##gpio##PU) &= (~(1 << (pin))))

#define NCS_Set(gpio, pin)              ((##gpio##NCS) |= (1 << (pin)))
#define NCS_Reset(gpio, pin)            ((##gpio##NCS) &= (~(` << (pin))))

/* 外部中断 */
#define INT_01_ENABLE(num)              (EX##num = 1)
#define INT_01_DISABLE(num)             (EX##num = 0) 

#define INT_234_ENABLE(num)             (INTCLKO |= EX##num)
#define INT_234_DISABLE(num)            (INTCLKO &= ~(EX##num))

#define CLEAR_INT_234_FLAG(num)         CLEAR_FLAG(INT, num)

#define INT0_PRI(num)                   do { \
                                            IP &= ~(PX0);\
                                            IP |= ((num & 0x01) << 0);\
                                            IPH &= ~(PX0H);\
                                            IPH |= ((num >> 1) & 0x01) << 0;\
                                        } while (0)

#define INT1_PRI(num)                   do { \
                                            IP &= ~(PX1);\
                                            IP |= ((num & 0x01) << 2);\
                                            IPH &= ~(PX1H);\
                                            IPH |= ((num >> 1) & 0x01) << 2;\
                                        } while (0)

#define INT4_PRI(num)                   do {\
                                            IP2 &= ~(PX4);\
                                            IP2 |= ((num & 0x01) << 4);\
                                            IP2H &= ~(PX4H);\
                                            IP2H |= ((num >> 1) & 0x01) << 4;\
                                        } while (0)


#define INT01_FALL(num)                 (IT##num = 1)
#define INT01_FALL_RIS(num)             (IT##num = 0)
                                        
#define INT234_FALL(num)                (INTCLKO |= EX##num)
#define INT234_FALL_RIS(num)            (INTCLKO &= ~(EX##num))

#define INT0_FALL()                     INT01_FALL(0)
#define INT0_FALL_RIS()                 INT01_FALL_RIS(0)
                                        
#define INT1_FALL()                     INT01_FALL(1)
#define INT1_FALL_RIS()                 INT01_FALL_RIS(1)
                                        
#define INT2_FALL()                     INT234_FALL(2)
#define INT2_FALL_RIS()                 INT234_FALL_RIS(2)

#define INT3_FALL()                     INT234_FALL(3)
#define INT3_FALL_RIS()                 INT234_FALL_RIS(3)

#define INT4_FALL()                     INT234_FALL(4)
#define INT4_FALL_RIS()                 INT234_FALL_RIS(4)

/* 定时器定义 */
/* TCON */
#define TCON_Set(mask)                  (TCON &= ~(mask);TCON |= (mask))

/* TLx & THx */
#define TIMER_T(l, num, count)          (T##l##num = (count))

#define TIMER0_TL(count)                (TIMER_T(L, 0, (count)))
#define TIMER0_TH(count)                (TIMER_T(H, 0, (count)))

#define TIMER1_TL(count)                (TIMER_T(L, 1, (count)))
#define TIMER1_TH(count)                (TIMER_T(H, 1, (count)))

#define TIMER2_TL(count)                (TIMER_T(L, 2, (count)))
#define TIMER2_TH(count)                (TIMER_T(H, 2, (count)))

#define TIMER3_TL(count)                (TIMER_T(L, 3, (count)))
#define TIMER3_TH(count)                (TIMER_T(H, 3, (count)))

#define TIMER4_TL(count)                (TIMER_T(L, 4, (count)))
#define TIMER4_TH(count)                (TIMER_T(H, 4, (count)))

/* ETx */

#define TIMER0_ENABLE()                 (ET0 = 1)
#define TIMER0_DISABLE()                (ET0 = 0)

#define TIMER1_ENABLE()                 (ET1 = 1)
#define TIMER1_DISABLE()                (ET1 = 0)

#define TIMER2_ENABLE()                 (IE2 |= ET2)
#define TIMER2_DISABLE()                (IE2 &= ~ET2)

#define TIMER3_ENABLE()                 (IE2 |= ET3)
#define TIMER3_DISABLE()                (IE2 &= ~ET3)

#define TIMER4_ENABLE()                 (IE2 |= ET4)
#define TIMER4_DISABLE()                (IE2 &= ~ET4)

/* TRx */
#define TIMER0_RUN()                    TR0 = 1
#define TIMER0_STOP()                   TR0 = 0
    
#define TIMER1_RUN()                    TR1 = 1
#define TIMER1_STOP()                   TR1 = 0

#define TIMER2_RUN()                    AUXR |= T2R
#define TIMER2_STOP()                   AUXR &= ~(T2R)

#define TIMER3_RUN()                    T4T3M |= T3R        
#define TIMER3_STOP()                   T4T3M &= ~(T3R)

#define TIMER4_RUN()                    T4T3M |= (T4R)
#define TIMER4_STOP()                   T4T3M &= ~(T4R)

/* T0_CT 如果想恢复定时器功能，需要将复位寄存器，重新初始化 */
#define TIMER01_COUNT(x)                TMOD |= T##x##_CT
#define TIMER01_GET_COUNT(x)			(TMOD & (~(T##x##_CT)))

#define TIMER0_COUNT()                  TIMER01_COUNT(0)
#define TIMER1_COUNT()                  TIMER01_COUNT(1)

#define TIMER0_GET_COUNT()				TIMER01_GET_COUNT(0)
#define TIMER1_GET_COUNT()				TIMER01_GET_COUNT(1)

#define TIMER2_COUNT()                  AUXR |= T2_CT
#define TIMER2_GET_COUNT()				(AUXR & T2_CT)

#define TIMER34_COUNT(x)                T4T3M |= (T##x##_CT)
#define TIMER34_GET_COUNT(x)			(T4T3M & (T##x##_CT))

#define TIMER3_COUNT()                  TIMER34_COUNT(3)
#define TIMER4_COUNT()                  TIMER34_COUNT(4)

#define TIMER3_GET_COUNT()				TIMER34_GET_COUNT(3)
#define TIMER4_GET_COUNT()				TIMER34_GET_COUNT(4)
/* MODE 模式共分为4种，需要看手册 */
#define TIMER01_MODE(x, num)            do {\
                                            TMOD = ((num) & 0x01) ? \
												TMOD | (T##x##_M0) : \
												TMOD & ~(T##x##_M0);\
											TMOD = (((num) >> 1) & 0x1) ? \
												TMOD | (T##x##_M1) : \
												TMOD & ~(T##x##_M1);\
                                        } while (0)

#define TIMER0_MODE(num)                TIMER01_MODE(0, num)
#define TIMER1_MODE(num)                TIMER01_MODE(1, num)

/* 是否分频 分频只能是12分频 */                                        
#define TIMER012_FREQ_ENABLE(n)         AUXR &= ~(T##n##x12)   
#define TIMER012_FREQ_DISABLE(n)        AUXR |= T##n##x12
                                        
#define TIMER34_FREQ_ENABLE(n)          T4T3M &= ~(T##n##x12)
#define TIMER34_FREQ_DISABLE(n)         T4T3M |= T##n##x12

/* 读取是否分频，计算重载值时，需要读取 */
#define TIMER012_FREQ(n)                (AUXR & T##n##x12)

#define TIMER34_FREQ(n)                (T4T3M & T##n##x12)            

                                        
#define TIMER0_FREQ_ENABLE()            TIMER012_FREQ_ENABLE(0)
#define TIMER0_FREQ_DISABLE()           TIMER012_FREQ_DISABLE(0)
                                        
#define TIMER1_FREQ_ENABLE()            TIMER012_FREQ_ENABLE(1)
#define TIMER1_FREQ_DISABLE()           TIMER012_FREQ_DISABLE(1)

#define TIMER2_FREQ_ENABLE()            TIMER012_FREQ_ENABLE(2)
#define TIMER2_FREQ_DISABLE()           TIMER012_FREQ_DISABLE(2)

#define TIMER3_FREQ_ENABLE()            TIMER34_FREQ_ENABLE(3)
#define TIMER3_FREQ_DISABLE()           TIMER34_FREQ_DISABLE(3)

#define TIMER4_FREQ_ENABLE()            TIMER34_FREQ_ENABLE(4)
#define TIMER4_FREQ_DISABLE()           TIMER34_FREQ_DISABLE(4)

#define TIMER0_FREQ()                   TIMER012_FREQ(0)
#define TIMER1_FREQ()                   TIMER012_FREQ(1)
#define TIMER2_FREQ()                   TIMER012_FREQ(2)

#define TIMER3_FREQ()                   TIMER34_FREQ(3)
#define TIMER4_FREQ()                   TIMER34_FREQ(4)

/* 定时器输出 */
#define TIMER012_OUT_ENABLE(x)          INTCLKO |= T##x##CLKO
#define TIMER012_OUT_DISABLE(x)         INTCLKO &= ~(T##x##CLKO)

#define TIMER0_OUT_ENABLE()             TIMER012_OUT_ENABLE(0)
#define TIMER1_OUT_ENABLE()             TIMER012_OUT_ENABLE(1)
#define TIMER2_OUT_ENABLE()             TIMER012_OUT_ENABLE(2)

#define TIMER0_OUT_DISABLE(x)           TIMER012_OUT_DISABLE(0)
#define TIMER1_OUT_DISABLE(x)           TIMER012_OUT_DISABLE(1)
#define TIMER2_OUT_DISABLE(x)           TIMER012_OUT_DISABLE(2)


#endif
