#include "stc8.h"
#include "mylib.h"
#include "intrins.h"
#include "uart.h"
#include "wc_string.h"
#include "command.h"
#include "string.h"
#include "24c02.h"
#include "oled.h"
#include "max485.h"
#include "timer.h"
#include "gt20.h"
#include "led.h"
#include "key.h"
#include "WDT.h"
#include "botp.h"
#include "crc.h"

LEDItem LEDRes[4];
static void Delay_ms(uint16_t Del_1ms) {
	uint8_t j;
    
	while (Del_1ms--) {	
		for (j  =0;j < 123;j++) {
        
        }
	}
}

static void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
extern uint16_t wptr;
extern uint8_t rptr;
extern char buffer[];

void SystemInit(void) {
    SCON    = 0x00;
    S2CON   = 0x00;
    S3CON   = 0x00;
    S4CON   = 0x00;
    
    AUXR    = 0x00;
    AUXR2   = 0x00;
}

void DelayInit(void) {
    Timer t3;
    
    t3.Type = TIMER_TYPE_TIMER;
	t3.Mode = TIMER_Mode_0;
	t3.FreqDiv = TIMER_FREQ_DIV_1;
	t3.Count = 10;
    Timer3_Init(&t3);
}

void LED_Exp(uint32_t Color, uint32_t Freq, uint8_t Count) {
	switch (Color) {
		case 0xff0000:		// RED
			LED_F(3, (Freq >> 20) & 0x3ff, 100);
		break;
		
		case 0x00ff00:		// GREND
			LED_F(2, (Freq >> 10) & 0x3ff, 100);
		break;
		
		case 0x0000ff:		// BLUE
			LED_F(1, (Freq >> 0) & 0x3ff, 100);
		break;
		
		default:
			LED_F(0, 0, 100); // 停止闪烁
		break;
	}
					
}


#define TASK_LED			0x00
void RunTask(void) {
	uint8_t i = 0;
    uint16_t index = 0;
    BOTP b;
	uint8_t c = 0;
	uint16_t crc16 = 0x0000;
    
	for (i = 0;i < 1;i++) {
		switch (i) {
			case TASK_LED:
				if (((LED.Color >> 24) & 0xff) == 0x00) { // LED 有数据传输过来
					LED_Exp(LED.Color & 0x00ffffff, LED.Freq & 0x3fffffff, (LED.Freq >> 30) & 0x03);
					// 赋值给结果数组
                    LEDRes[(LED.Freq >> 30) & 0x03].Color = LED.Color;
                    LEDRes[(LED.Freq >> 30) & 0x03].Freq  = LED.Freq & 0x3fffffff;
                    // 清掉标志
                    LED.Color |= 0xff000000;
				} else if (((LED.Color >> 24) & 0xff) == 0x01) { // LED 返回结果，返回结果，利用LED的结构体，进行返回
                    // 初始化BOTP协议
                    BOTP_Init(&b, BOTP_MAC_ADDR, device[0].Mac);
                    // 填充结果数组
                    for (c = 0;c < 4;c++) {
                        if (LEDRes[c].Color != 0) {
							BOTP_PackAddZore(&(b.Pack), index, EXEC_OBJ_CMD_LED_RET);
							BOTP_ObjToObjNotNull(&(b.Pack), index+1, EXEC_OBJ_CMD_LED_RET, (uint8_t *)(&(LEDRes[c])), sizeof(LEDRes[0]));
                            index += (sizeof(LEDRes[0]) + 2);
                        }
                    }
                    // 设置长度
                    BOTP_SetPackLength(&b, index);
					crc16 = CRC_16((uint8_t *)(&(b.Pack), index));
					// 设置crc校验
 					BOTP_SetPackDataCrc16(b, crc16);
                    b.Msg.BusID = device[0].Msg.BusID;
                    b.Msg.Type = device[0].Msg.Type;
                    BOTP_SendData(&b);
                    // 停止闪烁
                    LED_Exp(0, 0, 0);
					
                    // 清掉标志
                    LED.Color |= 0xff000000;
                    // 清空数组
                    memset(LEDRes, 0, sizeof(LEDRes));
                }
			break;
		}
	}
}

void main(void) {
    BOTP * pb;
    
	uint16_t i = 0, j;
	uint8_t index = 0;

	WDT_Init(WDT_PS_256);
    SystemInit();
    
    LED_Init();
    UartInit();
    MAX485_Init();
    DelayInit();
	
	memset(LEDRes, 0, sizeof(LEDRes));
    EA = 1;
	
	Delay500ms();
    print_debug("uart Init\r\n");
    wptr = 0;
    
		
	ExecObjInit(&(ExecObjArray[0]),		// 外部obj 
				EXEC_OBJ_CMD_LED, 		// id
				sizeof(LEDItem), 		// len
				(void *)(&LED));		// data
	
	print_debug("led:%bx\r\n", sizeof(LEDItem));
/*
	while (1) {
		if (wptr != 0) {
			if (wptr > 0x1A) {
				pb = (BOTP *)buffer;
				if (wptr >= (pb->PackLen + 0x1C)) {
					Delay_ms(10);
					for (i = 0;i < wptr;i++) {
						printf("%02bx ", buffer[i]);
					}
					printf("\r\n");
					wptr = 0;
				}
			}
		}
	}
	*/
    while (1) {
        if (wptr != rptr) {
			if (wptr > 0x1A) {
                pb = (BOTP *)buffer;
                if (wptr >= (pb->PackLen + 0x1C)) {
                    Delay_ms(10);
                    print_debug("ret:%bu\r\n", BOTP_Exec(pb));
                    for (i = 0;i < 256;i++) {
                        buffer[i] = 0x00;
                    }
					wptr = 0;
                } 
                ExtDev_ClearDeviceTable();
            }
        }
		
		RunTask();
		WDT_ReloadCount();	// 鍠傜嫍
    }
}