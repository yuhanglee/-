#ifndef __GT20_H__
#define __GT20_H__

#include "mylib.h"


sbit GT20_CS = P0^6;
sbit GT20_MOSI = P5^3;
sbit GT20_MISO = P5^2;
sbit GT20_SCLK = P0^7;

#define __CPOL__ 0
#define __CPHA__ 0

void GT20_ReadChar(uint32_t addr, unsigned char len, unsigned char * arr);
uint32_t GT20FontAddr(uint8_t MSB,uint8_t LSB);
#endif