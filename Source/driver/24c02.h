#include "iic.h"
#include "mylib.h"


#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  

//?a�����?��1��?��?��?24c02��??����??����?EE_TYPE?aAT24C02
#define EE_TYPE AT24C02

u8 AT24CXX_ReadOneByte(u16 ReadAddr);							//???����??��?����?��???��??��
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite);		//???����??��D�䨨?��???��??��
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len);//???����??��?a��?D�䨨????��3��?����?��y?Y
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len);					//???����??��?a��??����????��3��?����y?Y
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);	//�䨮???����??��?a��?D�䨨????��3��?����?��y?Y
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);   	//�䨮???����??��?a��??��3????��3��?����?��y?Y

u8 AT24CXX_Check(void);  //?��2��?��?t

