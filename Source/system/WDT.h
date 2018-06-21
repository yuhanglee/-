#ifndef __WDT_H__
#define __WDT_H__

#include "mylib.h"

#define WDT_PS_2	0x00
#define WDT_PS_4	0x01
#define WDT_PS_8	0x02
#define WDT_PS_16	0x03
#define WDT_PS_32	0x04
#define WDT_PS_64	0x05
#define WDT_PS_128	0x06
#define WDT_PS_256	0x07	

void WDT_ReloadCount(void);
void WDT_Init(uint16_t c);

#endif
