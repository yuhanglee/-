#include "delay.h"


void Delay_ms(uint16_t Del_1ms) {
	uint8_t i, j;
    
	while (Del_1ms--) {	
		i = 32;
		j = 40;
		do
		{
			while (--j);
		} while (--i);
	}
}

void Delay500ms(void) {		//@24MHz 
	unsigned char i, j, k;

	i = 61;
	j = 225;
	k = 62;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


