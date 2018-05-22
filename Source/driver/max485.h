#ifndef __MAX485_H__
#define __MAX485_H__

#include "uart.h"
#include "mylib.h"

void MAX485_Init(void);
void MAX485_WriteStr(uint8_t * str);
void MAX485_WriteHex(uint8_t * str, uint16_t len);


#endif
