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
#include "botp.h"

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

	_nop_();
	_nop_();
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
extern uint8_t wptr;
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
void SendRes(uint8_t f1, uint8_t f2, uint8_t f3) {
    uint8_t PAD_SendStr[256];
    memset(PAD_SendStr, 0, 256);
    
    sprintf(PAD_SendStr, "ff0000,%bu;00ff00,%bu;0000ff,%bu;", f1, f2, f3);
    printf("res:%s\r\n", PAD_SendStr);
    Uart3SendStr(PAD_SendStr);
    wptr = 0;
    memset(buffer, 0, 256);
}

void LED_Exp(void) {
    uint8_t f1 = 0, f2 = 0, f3 = 0;
    uint8_t key = 0, key_old = 0;
    uint8_t key_s = 1;
    uint16_t j = 10;
    float Hz = 0;
    uint16_t c = 0x20, c1;
    
    LED_F(key_s, j, 100);
    
    OLED_DisplayHanziStr(1, 0, "当前频率");
    OLED_DisplayStr(9, 1, "Hz");
    while (1) {
        key = KEY_VALUE;
        if (key != key_old) {
            key_old = key;
            switch (key) {
                case KEY_1:
                    j += 1;
                break;
                
                case KEY_2:
                    j -= 1;
                break;
                
                case KEY_3:
                    j = 10;
                break;
                
                case KEY_4:
                    if (f1 < 10) {
                        f1 = j;
                    } else if (f2 < 10) {
                        f2 = j;
                    } else if (f3 < 10) {
                        f3 = j;
                    }
                    j = 10;
                    key_s++;
                break;
            }
            c = j;
            c1 = 2;
            LED_F(key_s, j, 100);
            
            if (key_s == 4) {
                key_s = 1;
                SendRes(f1, f2, f3);
                return ;
            }
            while (c1) {
                c1--;
                OLED_DisplayChar(c1 + 6, 1, (c % 10) + '0');
                c /= 10;
            }
            OLED_Refresh_Gram();
        }
    }
}

#define bus1        BUS_UART
#define msg_type    MSG_TYPE_USER
#define saddr	    0x88888888
#define msgcount	0x25
#define daddr		0x11111111
#define qcmd		QUICK_CMD_FIND
#define plen		0x80
#define pt		    PACK_TYPE_CLCT

void main(void) {
    BOTP b;
    BOTP * pb;
	Pack_t *p = &(b.Pack);
    
	int i = 0;
	
	uint8_t index = 0;
	
    SystemInit();
    
    
    UartInit();
    DelayInit();
//    Uart3Init();
    
    EA = 1;
    LED_F(1, 40, 100);
    
    while (1) {
        
    }
    
    
//    OLED_Init();
    
        Delay500ms();
    printf("uart Init\r\n");
	
    if (1) {
        memset(&b, 0, sizeof(b));
        ((uint8_t *)(&(b.Header)))[0] = 'B';
        ((uint8_t *)(&(b.Header)))[1] = 'O';
        ((uint8_t *)(&(b.Header)))[2] = 'T';
        ((uint8_t *)(&(b.Header)))[3] = 'P';
        b.Family = 0xffff;
        b.Version = VERSION_DEV;
        b.Msg.BusID = BUS_UART;
        b.Msg.Type = MSG_TYPE_USER;
        b.SMacAddr = 0x12345678;
        b.MsgCount = 0x01;
        b.DMacAddr = BOTP_MAC_ADDR;
        b.QuickCmd = QUICK_CMD_USER;
        b.PackLen = 0x30;
        b.Pack.Crc16 = 0x1234;
        
        wc_assert(BOTP_CheckFormat(b));
        
        wc_assert(BOTP_CheckVersionVaild(b));
        wc_assert(BOTP_CheckFamilyVaild(b));
        wc_assert(BOTP_CheckBusID(b));
        wc_assert(BOTP_CheckMsgType(b));
        wc_assert(BOTP_CheckQuickCmd(b));
        wc_assert(BOTP_CheckDMacAddr(b));
        
        BOTP_SetBusID(&b, bus1);
        BOTP_SetMsgType(&b, msg_type);
        BOTP_SetSMacAddr(&b, saddr);
        BOTP_SetMsgCount(&b, msgcount);
        BOTP_SetDMacAddr(&b, daddr);
        BOTP_SetQuickCmd(&b, qcmd);
        BOTP_SetPackLength(&b, plen);
                                       
        BOTP_SetPackDataCrc16(&(b.Pack), 0x7777);
        
        wc_assert(bus1 == BOTP_GetBusID(b));
        wc_assert(msg_type == BOTP_GetMsgType(b));
        wc_assert(saddr == BOTP_GetSMacAddr(b));
        wc_assert(msgcount == BOTP_GetMsgCount(b));
        wc_assert(daddr == BOTP_GetDMacAddr(b));
        wc_assert(qcmd == BOTP_GetQuickCmd(b));
        wc_assert(plen == BOTP_GetPackLength(b));
        wc_assert(0x7777 == BOTP_GetPackDataCrc16(b.Pack));
    }
//	i = BOTP_PackDataFill(&(b.Pack));
//	BOTP_SetPackLength(&b, i);
//    printf("len;%u\r\n", i);
//	ExtDev_Init(&(device[0]));
//    
//	if (0xff == ExtDev_GetDeviceIndexByMac(b.DMacAddr)) { // 如果当前 MAC 没有在设备数组中 
//		index = ExtDev_GetDeviceIdleIndex();	 // 寻找下一个可用的设备数组索引值 
//		if (0xff != index) {	// 当前设备总线索引值是否可用 
//			ExtDev_SetMsgType(&(device[index]), b.Msg.Type);
//			ExtDev_SetBusId(&(device[index]), b.Msg.BusID);
//			ExtDev_SetMacCrc32(&(device[index]), b.DMacAddr);
//		}
//	}
//	printf("bus:%bx\r\n", device[0].Msg.BusID);
//	printf("type:%bx\r\n", device[0].Msg.Type);
//	printf("index:%bx\r\n", device[0].Index);
//	printf("mac:%lx\r\n", device[0].Mac);
//	
//	
//	
//	index = ExtDev_GetDeviceIndexByMac(b.DMacAddr);
//	printf("index:%02bx\r\n", index); 
//	
//	BOTP_SendData(&b);
//	printf("\r\n"); 
//	
//	printf("\r\n");
//	BOTP_PackExtTest(p, b.PackLen);
//	
    while (1) {
        if (wptr != rptr) {
            if (wptr > 0x1A) {
                pb = (BOTP *)buffer;
                if (wptr >= (pb->PackLen + 0x1C)) {
                    Delay_ms(10);
                    printf("ret:%bu\r\n", BOTP_Exec(pb));
                    wptr = 0;
                    for (i = 0;i < 256;i++) {
                        buffer[i] = 0x00;
                    }
                } 
                ExtDev_ClearDeviceTable();
            }
        }
    }
    
    while (1) {
        if (wptr != rptr) {
            OLED_Clear();
            LED_Exp();
        } else {
            OLED_DisplayLogo();
            OLED_Refresh_Gram();
        }
    }
}