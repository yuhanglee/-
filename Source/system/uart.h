#include "mylib.h"
#include "stc8.h"


#define BRT         (65536 - FOSC / 115200 / 4)
#define BUF_MAX_LEN (256)

void UartInit(void);
void Uart1Send(char dat);
void Uart1SendStr(char *p);
void Uart1SendHex(uint8_t * buf, uint8_t len);

void Uart2Init(void);
void Uart2Send(char dat);
void Uart2SendStr(char *p);


void Uart3Init(void);
void Uart3Send(char dat);
void Uart3SendStr(char *p);

void Uart4Init(void);
void Uart4Send(char dat);
void Uart4SendStr(char *p);


