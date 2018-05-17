#include "stc8.h"
#include "24c02.h"

/*******************************************************************************
* o¡¥ ¨ºy ??         : AT24CXX_ReadOneByte
* o¡¥¨ºy1|?¨¹		   : ?¨²AT24CXX???¡§¦Ì??¡¤?¨¢3?¨°???¨ºy?Y
* ¨º?    ¨¨?         : ReadAddr:?a¨º??¨¢¨ºy¦Ì?¦Ì??¡¤ 
* ¨º?    3?         : ?¨¢¦Ì?¦Ì?¨ºy?Y
*******************************************************************************/
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //¡¤¡é?¨ªD¡ä?¨¹¨¢?
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//¡¤¡é?¨ª??¦Ì??¡¤	    
	}
	else 
	{
		IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //¡¤¡é?¨ª?¡Â?t¦Ì??¡¤0XA0,D¡ä¨ºy?Y
	} 	   
	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //¡¤¡é?¨ª¦Ì¨ª¦Ì??¡¤
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //??¨¨??¨®¨º??¡ê¨º?			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//2¨²¨¦¨²¨°???¨ª¡ê?1¨¬??t	    
	return temp;
}

/*******************************************************************************
* o¡¥ ¨ºy ??         : AT24CXX_WriteOneByte
* o¡¥¨ºy1|?¨¹		   : ?¨²AT24CXX???¡§¦Ì??¡¤D¡ä¨¨?¨°???¨ºy?Y
* ¨º?    ¨¨?         : WriteAddr  :D¡ä¨¨?¨ºy?Y¦Ì???¦Ì?¦Ì??¡¤ 
					 DataToWrite:¨°aD¡ä¨¨?¦Ì?¨ºy?Y
* ¨º?    3?         : ?T
*******************************************************************************/
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //¡¤¡é?¨ªD¡ä?¨¹¨¢?
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//¡¤¡é?¨ª??¦Ì??¡¤	  
	}
	else 
	{
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //¡¤¡é?¨ª?¡Â?t¦Ì??¡¤0XA0,D¡ä¨ºy?Y
	} 	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //¡¤¡é?¨ª¦Ì¨ª¦Ì??¡¤
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //¡¤¡é?¨ª¡Á??¨²							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//2¨²¨¦¨²¨°???¨ª¡ê?1¨¬??t 
}

/*******************************************************************************
* o¡¥ ¨ºy ??         : AT24CXX_WriteLenByte
* o¡¥¨ºy1|?¨¹		   : ?¨²AT24CXX¨¤???¦Ì????¡§¦Ì??¡¤?a¨º?D¡ä¨¨?3¡è?¨¨?aLen¦Ì?¨ºy?Y
					 ¨®?¨®¨²D¡ä¨¨?16bit?¨°??32bit¦Ì?¨ºy?Y
* ¨º?    ¨¨?         : WriteAddr  :D¡ä¨¨?¨ºy?Y¦Ì???¦Ì?¦Ì??¡¤ 
					 DataToWrite:¨°aD¡ä¨¨?¦Ì?¨ºy?Y
					 Len        :¨°aD¡ä¨¨?¨ºy?Y¦Ì?3¡è?¨¨2,4
* ¨º?    3?         : ?T
*******************************************************************************/
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

/*******************************************************************************
* o¡¥ ¨ºy ??         : AT24CXX_ReadLenByte
* o¡¥¨ºy1|?¨¹		   : ?¨²AT24CXX¨¤???¦Ì????¡§¦Ì??¡¤?a¨º??¨¢3?3¡è?¨¨?aLen¦Ì?¨ºy?Y
					 ¨®?¨®¨²?¨¢3?16bit?¨°??32bit¦Ì?¨ºy?Y
* ¨º?    ¨¨?         : ReadAddr   :?a¨º??¨¢3?¦Ì?¦Ì??¡¤ 
					 Len        :¨°a?¨¢3?¨ºy?Y¦Ì?3¡è?¨¨2,4
* ¨º?    3?         : ?¨¢¨¨?¦Ì?¨ºy?Y
*******************************************************************************/
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}

/*******************************************************************************
* o¡¥ ¨ºy ??         : AT24CXX_Check
* o¡¥¨ºy1|?¨¹		   : ?¨¬2¨¦AT24CXX¨º?¡¤??y3¡ê
* ¨º?    ¨¨?         : ?T
* ¨º?    3?         : 1:?¨¬2a¨º¡ì¡ã¨¹¡ê?0:?¨¬2a3¨¦1|
*******************************************************************************/
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_ReadOneByte(0);//¡À¨¹?a??¡ä??a?¨²??D¡äAT24CXX	
    printf("%bd\n", temp);
	if(temp == 0x36)return 0;		   
	else//??3y¦Ì¨²¨°?¡ä?3?¨º??¡¥¦Ì??¨¦??
	{
		AT24CXX_WriteOneByte(0,0X36);
	    temp = AT24CXX_ReadOneByte(0);	  
		if(temp == 0X36)return 0;
	}
	return 1;											  
}

/*******************************************************************************
* o¡¥ ¨ºy ??         : AT24CXX_Read
* o¡¥¨ºy1|?¨¹		   : ?¨²AT24CXX¨¤???¦Ì????¡§¦Ì??¡¤?a¨º??¨¢3????¡§??¨ºy¦Ì?¨ºy?Y
* ¨º?    ¨¨?         : ReadAddr :?a¨º??¨¢3?¦Ì?¦Ì??¡¤ ??24c02?a0~255
					 pBuffer  :¨ºy?Y¨ºy¡Á¨¦¨º¡Á¦Ì??¡¤
					 NumToRead:¨°a?¨¢3?¨ºy?Y¦Ì???¨ºy
* ¨º?    3?         : ?T
*******************************************************************************/
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
} 

/*******************************************************************************
* o¡¥ ¨ºy ??         : AT24CXX_Write
* o¡¥¨ºy1|?¨¹		   : ?¨²AT24CXX¨¤???¦Ì????¡§¦Ì??¡¤?a¨º?D¡ä¨¨????¡§??¨ºy¦Ì?¨ºy?Y
* ¨º?    ¨¨?         : WriteAddr :?a¨º?D¡ä¨¨?¦Ì?¦Ì??¡¤ ??24c02?a0~255
					 pBuffer  :¨ºy?Y¨ºy¡Á¨¦¨º¡Á¦Ì??¡¤
					 NumToRead:¨°a?¨¢3?¨ºy?Y¦Ì???¨ºy
* ¨º?    3?         : ?T
*******************************************************************************/
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}


