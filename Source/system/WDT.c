#include "WDT.h"
void WDT_ReloadCount(void) {
	WDT_CONTR	|= CLR_WDT;	// 看门狗定时器清零
}


void WDT_Init(uint16_t c) {
	WDT_CONTR 	= 0x00;


	WDT_CONTR	|= IDL_WDT;	// IDLE 模式下继续计数

	/*
	 *	                12*32768*2^(WDT_PS+1)
     * 看门狗溢出时间 = ---------------------  ms
     *                           SysClk
	 */
	WDT_CONTR 	|= c;		// 分频系数 WDT_PS
	
	WDT_CONTR  	|= EN_WDT;	// 启动看门狗
}


