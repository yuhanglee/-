
#include "mylib.h"
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void Delay_us(unsigned int us);

void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void IIC_Send_Byte(unsigned char IIC_Byte);
void IIC_Ack(void);
void IIC_NAck(void);
u8 IIC_Wait_Ack(void);
u8 IIC_Read_Byte(u8 ack);
