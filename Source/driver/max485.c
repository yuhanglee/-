#include "max485.h"

sbit MAX485_EN = P2^7;	// 1：发送  0：接受

void Delay50us() {		//@24.000MHz
	unsigned char i, j;

	i = 2;
	j = 39;
	do
	{
		while (--j);
	} while (--i);
}


void MAX485_Init(void) {
    Uart3Init();
	MAX485_EN = 0;
}

void MAX485_WriteStr(uint8_t * str) {
	MAX485_EN = 1;
    Uart3SendStr(str);
    Delay50us();
    Delay50us();
	MAX485_EN = 0;
}

void MAX485_WriteHex(uint8_t * str, uint16_t len) {
	MAX485_EN = 1;
    Uart3SendHex(str, len);
    Delay50us();
    Delay50us();
	MAX485_EN = 0;
}
