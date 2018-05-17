#ifndef __TIMER_H__
#define __TIMER_H__

#include "mylib.h"




enum {
	Timer1 = 1,
	Timer2 = 2,
	Timer3 = 3,
	Timer4 = 4,
	Timer5 = 5,
};

#define IS_TIMER(timer)					(\
											Timer1 == (timer) || \
											Timer2 == (timer) || \
											Timer3 == (timer) || \
											Timer4 == (timer) || \
											Timer5 == (timer)    \
										)

typedef enum {
	TIMER_Mode_0 = 0,
	TIMER_Mode_1 = 1,
	TIMER_Mode_2 = 2,
	TIMER_Mode_3 = 3,
} TimerMode;	

#define IS_TIMER_MODE(mode)				(\
											TIMER_Mode_0 == (mode) || \
											TIMER_Mode_1 == (mode) || \
											TIMER_Mode_2 == (mode) || \
											TIMER_Mode_3 == (mode)    \
										)

typedef enum {
	TIMER_TYPE_TIMER = 0,
	TIMER_TYPE_COUNT = 1,
} TimerType;							
#define IS_TIMER_TYPE(type)				(\
											TIMER_TYPE_TIMER == (type) || \
											TIMER_TYPE_COUNT == (type)    \
										)

typedef enum {
	TIMER_FREQ_DIV_12 = 0,
	TIMER_FREQ_DIV_1 = 1,
} TimerFreqDiv;					

#define IS_TIMER_FREQ_DIV(div)			(\
											TIMER_FREQ_DIV_1  == (div) || \
											TIMER_FREQ_DIV_12 == (div)    \
										)						
	
#define IS_TIMER_COUNT(count)			(\
											0     <= (count) || \
											65535 >= (count)    \
										)
typedef struct {
    TimerType  Type;
    TimerMode  Mode;
    uint8_t  FreqDiv;
    uint16_t Count;
} Timer;

#define CALC_COUNT(f, t, n)				(t)?(0xFFFF - FOSC / n):(0xFFFF - FOSC / 12 / n)

enum {
	e_TimTest = 0,
	e_TimMax,
};
extern uint16_t TimerDelayArray[];
#define IS_TIME_OUT_1MS(index, count)	(\
											TimerDelayArray[(index)] >= (count) ? \
											(TimerDelayArray[(index)] = 0) == 0 : \
											0 \
										)



extern uint16_t t3_1;
void Timer2_Init(uint16_t count);
void Timer3_Init(Timer * tim);

#endif
