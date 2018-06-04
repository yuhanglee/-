#include "led.h"
#include "wc_string.h"
#include "string.h"
#include "stdio.h"
#include "timer.h"

LEDItem LED;

void LED_Init(void) {
     LED_R_RESET();
    LED_G_RESET();
    LED_B_RESET();
}
uint16_t fre = 0;
uint8_t color = 1;
void LED_F(uint8_t num, uint16_t f, uint8_t c) {
    uint16_t i;
    uint8_t j;
    fre = 10000 / f;
    color = num;
}
