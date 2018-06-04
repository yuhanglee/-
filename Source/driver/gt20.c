#include "stdio.h"
#include "gt20.h"

static void Delay_us(unsigned int us) {
    int i = 100;
    (void)us;
    for (;i;i--);
}

uint32_t GT20FontAddr(uint8_t MSB, uint8_t LSB) {
    uint32_t temp=(MSB-0xB0)*94+LSB-0xA1;
    uint32_t BaseAdd=0,Address;
    if(MSB == 0xA9 && LSB >=0xA1) {
        Address = (282 + (LSB - 0xA1))*32+BaseAdd;
    } else if (MSB >=0xA1 && MSB <= 0xA3 && LSB >=0xA1) {
        Address =( (MSB - 0xA1) * 94 + (LSB - 0xA1))*32+ BaseAdd;  
    } else if (MSB >=0xB0 && MSB <= 0xF7 && LSB >=0xA1) {
        Address = (846+temp)*32+ BaseAdd;
    }
 
	return Address;
}

void SPI_SendChar(long int ch) {
    unsigned char i;
    
# if __CPOL__ == 0 && __CPHA__ == 0
    for (i = 0;i < 8;i++) {
        if (ch & 0x80)
            GT20_MOSI = 1;
        else 
            GT20_MOSI = 0;
        GT20_SCLK = 1;
        Delay_us(1);
        GT20_SCLK = 0;
        Delay_us(1);
        ch <<= 1;
    }
    GT20_SCLK = 0;
    Delay_us(1);
# elif __CPOL__ == 0 && __CPHA__ == 1
    GT20_SCLK = 0;
    Delay_us(1);
    for (i = 0;i < 8;i++) {
        GT20_SCLK = 1;
        Delay_us(1);
        if (ch & 0x80)
            GT20_MOSI = 1;
        else 
            GT20_MOSI = 0;
        GT20_SCLK = 0;
        Delay_us(1);
        ch <<= 1;
    }
# elif __CPOL__ == 1 && __CPHA__ == 0
    for (i = 0;i < 8;i++) {
        GT20_SCLK = 1;
        Delay_us(1);
        if (ch & 0x80)
            GT20_MOSI = 1;
        else 
            GT20_MOSI = 0;
        GT20_SCLK = 0;
        Delay_us(1);
        ch <<= 1;
    }
    GT20_SCLK = 1;
    Delay_us(1);
# elif __CPOL__ == 1 && __CPHA__ == 1
    GT20_SCLK = 1;
    Delay_us(1);
    for (i = 0;i < 8;i++) {
        GT20_SCLK = 1;
        Delay_us(1);
        if (ch & 0x80)
            GT20_MOSI = 1;
        else 
            GT20_MOSI = 0;
        GT20_SCLK = 0;
        Delay_us(1);
        ch <<= 1;
    }
# else
    #error "cuowu"
# endif
}

unsigned char SPI_RecvChar(void) {
    unsigned char res = 0;
    unsigned char i;
# if __CPOL__ == 0 && __CPHA__ == 0
    for (i = 0;i < 8;i++) {
        res <<= 1;
        GT20_SCLK = 1;
        Delay_us(1);
        if (GT20_MISO)
            res |= 0x01;
        GT20_SCLK = 0;
        Delay_us(1);
    }

# elif __CPOL__ == 0 && __CPHA__ == 1
    for (i = 0;i < 8;i++) {
        res <<= 1;
        GT20_SCLK = 1;
        Delay_us(1);
        if (GT20_MISO)
            res |= 0x01;
        GT20_SCLK = 0;
        Delay_us(1);
    }
    GT20_SCLK = 0;
    Delay_us(1);
# elif __CPOL__ == 1 && __CPHA__ == 0
    for (i = 0;i < 8;i++) {
        res <<= 1;
        GT20_SCLK = 1;
        Delay_us(1);
        if (GT20_MISO)
            res |= 0x01;
        GT20_SCLK = 0;
        Delay_us(1);
    }
    GT20_SCLK = 1;
    Delay_us(1);
# elif __CPOL__ == 1 && __CPHA__ == 1
    GT20_SCLK = 0;
    Delay_us(1);
    for (i = 0;i < 8;i++) {
        res <<= 1;
        GT20_SCLK = 0;
        Delay_us(1);
        if (GT20_MISO)
            res |= 0x01;
        GT20_SCLK = 1;
        Delay_us(1);
    }
    GT20_SCLK = 1;
    Delay_us(1);
# else
    #error "cuowu"
#endif
    return res;
}

void GT20_ReadChar(uint32_t addr, uint8_t len, uint8_t * arr) {
    uint8_t i = 0;
    //print_debug("%bx %lx %lx %lx\n", 0x0b, (addr >> 16) & 0xff, (addr >> 8) & 0xff, addr & 0xff);
    
    GT20_SCLK = 0;
    GT20_CS = 0;
    
 
    SPI_SendChar(0x0b);
    SPI_SendChar((addr >> 16) & 0xff);
    SPI_SendChar((addr >> 8) & 0xff);
    SPI_SendChar(addr & 0xff);
    SPI_SendChar(00);
    for (i = 0;i < len;i++) {
        arr[i] = (uint8_t)SPI_RecvChar();
    }
    
    GT20_CS = 1;
    
    GT20_SCLK = 0;
}
