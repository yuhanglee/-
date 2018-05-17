#ifndef __LED_H__
#define __LED_H__
#include "mylib.h"


#define LED1_SET()          GPIO_SetPin(P6, 0)
#define LED1_RESET()        GPIO_ResetPin(P6, 0)

#define LED2_SET()          GPIO_SetPin(P6, 1)
#define LED2_RESET()        GPIO_ResetPin(P6, 1)

#define LED3_SET()          GPIO_SetPin(P6, 2)
#define LED3_RESET()        GPIO_ResetPin(P6, 2)

#define LED4_SET()          GPIO_SetPin(P6, 7)
#define LED4_RESET()        GPIO_ResetPin(P6, 7)

#define LED5_SET()          GPIO_SetPin(P7, 0)
#define LED5_RESET()        GPIO_ResetPin(P7, 0)

#define LED6_SET()          GPIO_SetPin(P7, 1)
#define LED6_RESET()        GPIO_ResetPin(P7, 1)


#define LED_B_SET()         LED1_SET()
#define LED_B_RESET()       LED1_RESET()

#define LED_G_SET()         LED2_SET()
#define LED_G_RESET()       LED2_RESET()

#define LED_R_SET()         LED3_SET()
#define LED_R_RESET()       LED3_RESET()

#define LED_B               1
#define LED_G               2
#define LED_R               3

extern uint16_t fre;
extern uint8_t color;
void LED_ColorToStr(uint8_t r, uint8_t g, uint8_t b, uint8_t *str);
void LED_PWM(uint8_t num, uint8_t c);
void LED_F(uint8_t num, uint16_t f, uint8_t c);
void LED_Init(void);
#endif
