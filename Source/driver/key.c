#include "key.h"
#include "timer.h"

uint8_t KEY_Scan(void) {
    if (KEY_VALUE != 0x0f) {
        IS_TIME_OUT_1MS(e_TimTest, 20);
        if (KEY_VALUE != 0x0f) {
            return KEY_VALUE;
        }
        return 0;
    }
    
    return 0;
}

