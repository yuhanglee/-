#include "led.h"
#include "wc_string.h"
#include "string.h"
#include "stdio.h"
#include "timer.h"

LEDItem LED;
static void Delay10us(void) {		//@24.000MHz
	unsigned char i;

	i = 78;
	while (--i);
}
static void Delay100us(void) {		//@24.000MHz
	unsigned char i, j;

	i = 4;
	j = 27;
	do
	{
		while (--j);
	} while (--i);
}
void LED_Init(void) {
    LED_R_RESET();
    LED_G_RESET();
    LED_B_RESET();
}
void LED_PWM(uint8_t num, uint8_t c) {
    uint8_t i, j;
    
    for (i = 0;i < 100;i++) {
        if (i < c) {
           LED_B_SET();
//            switch (num) {
//                case LED_B:
//                    LED_B_SET();
//                break;
//                
//                case LED_G:
//                    LED_G_SET();
//                break;
//                
//                case LED_R:
//                    LED_R_SET();
//                break;
//            }
        } else {
                    LED_B_RESET();
//            switch (num) {
//                case LED_B:
//                    LED_B_RESET();
//                break;
//                
//                case LED_G:
//                    LED_G_RESET();
//                break;
//                
//                case LED_R:
//                    LED_R_RESET();
//                break;
//            }
        }
        Delay10us();
    }
}
uint16_t fre = 0;
uint8_t color = 1;
void LED_F(uint8_t num, uint16_t f, uint8_t c) {
    uint16_t i;
    uint8_t j;
    fre = 10000 / f;
    color = num;
    
    printf("cur: %bu %f Hz\r\n", num, 1000.0 / fre * 10);
    
//    for (i = 0;i < f;i++) {
//        if (i < f/2) {
//                    LED_B_RESET();
////            LED_PWM(num, c);
//        } else {
//                    LED_B_SET();
////            switch (num) {
////                case LED_B:
////                    LED_B_RESET();
////                break;
////                
////                case LED_G:
////                    LED_G_RESET();
////                break;
////                
////                case LED_R:
////                    LED_R_RESET();
////                break;
////            }
//            //while (!IS_TIME_OUT_1MS(e_TimTest, 1000));
//        }
//        Delay100us();
//    }
}


void LED_ColorToStr(uint8_t r, uint8_t g, uint8_t b, uint8_t *str) {
    wc_assert(str != NULL);
    
    //sprintf(str, "%02bx%02bx%02bx", r, g, b);
}

