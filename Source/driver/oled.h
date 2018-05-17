#ifndef __OLED_H__
#define __OLED_H__

#include "mylib.h"

#define OLED_X_MAX      16
#define OLED_Y_MAX      4

#define ASCII_SIZE_X    8
#define ASCII_SIZE_Y    16




#define OLED_CMD_SCROLL_PAGE_0          0X00    // page0   
#define OLED_CMD_SCROLL_PAGE_1          0X01    // page1   
#define OLED_CMD_SCROLL_PAGE_2          0X02    // page2   
#define OLED_CMD_SCROLL_PAGE_3          0X03    // page3   
#define OLED_CMD_SCROLL_PAGE_4          0X04    // page4   
#define OLED_CMD_SCROLL_PAGE_5          0X05    // page5   
#define OLED_CMD_SCROLL_PAGE_6          0X06    // page6   
#define OLED_CMD_SCROLL_PAGE_7          0X07    // page7

#define IS_PAGE(page)                   (\
                                            OLED_CMD_SCROLL_PAGE_0 == page || \
                                            OLED_CMD_SCROLL_PAGE_1 == page || \
                                            OLED_CMD_SCROLL_PAGE_2 == page || \
                                            OLED_CMD_SCROLL_PAGE_3 == page || \
                                            OLED_CMD_SCROLL_PAGE_4 == page || \
                                            OLED_CMD_SCROLL_PAGE_5 == page || \
                                            OLED_CMD_SCROLL_PAGE_6 == page || \
                                            OLED_CMD_SCROLL_PAGE_7 == page \
                                        )


#define OLED_CMD_SCROLL_5_FRANES        0x00    // 5 frames
#define OLED_CMD_SCROLL_64_FRANES       0x01    // 64 frames
#define OLED_CMD_SCROLL_128_FRANES      0x02    // 128 frames
#define OLED_CMD_SCROLL_256_FRANES      0x03    // 256 frames
#define OLED_CMD_SCROLL_3_FRANES        0x04    // 3 frames
#define OLED_CMD_SCROLL_4_FRANES        0x05    // 4 frames
#define OLED_CMD_SCROLL_25_FRANES       0x06    // 25 frames
#define OLED_CMD_SCROLL_2_FRANES        0x07    // 2 frames

#define IS_FRANES(Franes)               (\
                                            OLED_CMD_SCROLL_5_FRANES == Franes || \
                                            OLED_CMD_SCROLL_64_FRANES == Franes || \
                                            OLED_CMD_SCROLL_128_FRANES == Franes || \
                                            OLED_CMD_SCROLL_256_FRANES == Franes || \
                                            OLED_CMD_SCROLL_3_FRANES == Franes || \
                                            OLED_CMD_SCROLL_4_FRANES == Franes || \
                                            OLED_CMD_SCROLL_25_FRANES == Franes || \
                                            OLED_CMD_SCROLL_2_FRANES == Franes\
                                        )

#define OLED_ADDR       0x78        // 0x78 0x7A都可以
#define OLED_WRITE      OLED_ADDR
#define OLED_READ       OLED_ADDR+1

#define OLED_CMD_CONTRAST           0x81    // 设置对比度  81H xxH  对比度随着值的增加而增加
#define OLED_CMD_CONTRAST_VALUE(v)  (v) 
#define OLED_CMD_DSP_ON_RAM         0xA4    // 显示开，且恢复RAM内容
#define OLED_CMD_DSP_ON             0xA5    // 显示开，不恢复RAM内容
#define OLED_CMD_DSP_NOR            0xA6    // 正常显示
#define OLED_CMD_DSP_REV            0xA7    // 反向显示
#define OLED_CMD_SLEEP              0xAE    // 睡眠模式  暂时不知道怎么退出睡眠模式
#define OLED_CMD_SLEEP_OFF          0xAF    // 正常模式，相对于睡眠模式来说
// scroll, 滚屏功能开启之后，不可以进行RAM写
#define OLED_CMD_SCROLL_H_R         0x26    // 水平向右滚动 26H 00H 0xH 0yH 0zH  x:开始页地址(0-7) 
                                            // y:滚屏的时间间隔(0-7) z:结束页地址(0-7, z >= x)
#define OLED_CMD_SCROLL_H_L         0x27    // 水平想左滚动
#if defined OLED_CMD_SCROLL_H_R || defined OLED_CMD_SCROLL_H_L   
    #define IS_DIRECTION(d)         ((OLED_CMD_SCROLL_H_R == d) || (OLED_CMD_SCROLL_H_L == d))
#endif

#define OLED_CMD_SCROLL_V_R         0x29    // 垂直向右滚动 29H 00H 0xH 0yH 0zH iiH x:开始页地址(0-7) 
                                            // y:滚屏的时间间隔(0-7) z:结束页地址(0-7 z>=x) 
                                            // ii:垂直滚屏的位置(0-63)
#define OLED_CMD_SCROLL_V_L         0x2A    // 垂直向左滚动
#if defined OLED_CMD_SCROLL_V_R || defined OLED_CMD_SCROLL_V_L
#endif

// NOTE: 关闭滚屏功能之后，RAM数据需要重新写入
#define OLED_CMD_SCROLL_OFF         0x2E    // 关闭滚屏功能 
// 最后一个滚屏功能会被启动，之前的滚屏设置会被清除
#define OLED_CMD_SCROLL_ON          0x2F    // 开启滚屏功能

#define OLED_CMD_SCROLL_V_AREA      0xA3    // 设置垂直滚动区域 A3H xxH yyH
                                            // xx: 顶层固定行数(0-64)
                                            // yy: 底层滚定行数(0-64)
                                    
#define OLED_CMD_SET_LOW_ADDR(addr)     (addr & 0x0f)                   // 页模式下设置列起始地址低位
#define OLED_CMD_SET_HIGH_ADDR(addr)    (((addr >> 4) & 0x0f) | 0x20)   // 页模式下设置列起始地址高位

#define OLED_CMD_MEMORY_MODE            0x20    // 设置内存模式  20H 0xH   x:模式选择(0-2)
#define OLED_CMD_MEMORY_MODE_H_ADDR     0x00    // 水平地址模式
#define OLED_CMD_MEMORY_MODE_V_ADDR     0x01    // 垂直地址模式
#define OLED_CMD_MEMORY_MODE_P_ADDR     0x02    // 页地址模式

#define OLED_CMD_SET_COLUMN_ADDR        0x21    // 设置列地址    21H xxH yyH xx: 开始地址(0-127) yy:结束地址(0-127)
#define OLED_CMD_SET_PAGE_ADDR          0x22    // 设置页地址    22H xxH yyH xx: 开始地址(0-7) yy:结束地址(0-7)
#define OLED_CMD_SET_PAGE_START_ADDR(a) (0xB0 | a)  // 设置页开始地址作为页地址模式

#define OLED_CMD_SET_DISPLAY_START_LINE(line)           (0x40 | line)
#define OLED_CMD_SET_SEG_NOR            0xA0    // 列地址0映射到seg0
#define OLED_CMD_SET_SEG_RE_MAP         0xA1    // 列地址127映射到seg0，即左右镜像

#define OLED_CMD_MUX_RATIO              0xA8    // 设置复用率 A8H xxH xx:复用率(16-64)
#define OLED_CMD_MUX_RATIO_VALUE(v)     (v)     // 设置复用率的值

#define OLED_CMD_COM_OUT_SCAN_DIR_NOR   0xC0    // 扫描方式从com0-comN
#define OLED_CMD_COM_OUT_SCAN_DIR_REMAP 0xC8    // 扫描方式从comN-com0 上下镜像

#define OLED_CMD_SET_DSP_OFFSET          0xD3    // 设置垂直偏移量 D3H xxH  xx: 垂直偏移量(0-63)
#define OLED_CMD_SET_DSP_OFFSET_VALUE(v) (v)
#define OLED_CMD_SET_COM_PINS           0xDA    // 设置列引脚硬件配置 DAH x2H    x: 模式选择(0x00-0x0f)
#define OLED_CMD_SET_COM_PINS_SEQU      0x00    // 顺序引脚配置
#define OLED_CMD_SET_COM_PINS_ALTER     0x10    // 替代引脚配置
#define OLED_CMD_SET_COM_PINS_RL_NOR    0x00    // 关闭左右映射
#define OLED_CMD_SET_COM_PINS_RL_REMAP  0x20    // 开启左右映射
#define OLED_CMD_SET_COM_PINS_VALUE(v)  ((v) | 0x02)  // 模式配置值

#define OLED_CMD_SET_DIV_OSC_FREQ       0xD5    // 设置时钟和DCLK分频系数
#define OLED_CMD_SET_DIV_VALUE(v)       (v)     // 分频系数
#define OLED_CMD_SET_OSC_FREQ_VALUE(v)  ((v) << 4)// 时钟频率
#define OLED_CMD_SET_DIV_OSC_FREQ_VALUE(v)  (v)

#define OLED_CMD_SET_PRE_CHARGE_PERIOD              0xD9    // 设置预充电周期
#define OLED_CMD_SET_PRE_CHARGE_PERIOD_1_VALUE(v)   (v)
#define OLED_CMD_SET_PRE_CHARGE_PERIOD_2_VALUE(v)   ((v) << 4)
#define OLED_CMD_SET_PRE_CHARGE_PERIOD_VALUE(v)     (v)

#define OLED_CMD_SET_VCOMH_DESELECT_LEVEL           0xDB    // 设置VCOMH反压值
#define OLED_CMD_SET_VCOMH_DESELECT_LEVEL_0_65_VCC  0x00    // ~0.65*Vcc
#define OLED_CMD_SET_VCOMH_DESELECT_LEVEL_0_77_VCC  0x20    // ~0.77*Vcc
#define OLED_CMD_SET_VCOMH_DESELECT_LEVEL_0_83_VCC  0x30    // ~0.83*Vcc

#define OLED_CMD_NOP                    0xE3    // 无操作

#define OLED_CMD_SET_CHARGE_PUMP        0x8D    // 电荷泵设置    8DH 1xH x:0 关闭  4:开启
#define OLED_CMD_SET_CHARGE_PUMP_ON     0x14    // 开启
#define OLED_CMD_SET_CHARGE_PUMP_OFF    0x10    // 关闭









#define OLED_ScrollLeft(StartPage, EndPage, Franes)   \
            OLED_Scroll(OLED_CMD_SCROLL_H_L, StartPage, EndPage, Franes)
#define OLED_ScrollRight(StartPage, EndPage, Franes)   \
            OLED_Scroll(OLED_CMD_SCROLL_H_R, StartPage, EndPage, Franes)





void OLED_Init(void);
void OLED_Refresh_Gram(void);
void OLED_Clear(void);
void OLED_DisplayChar(uint8_t x, uint8_t y, uint8_t ch);
void OLED_DisplayStr(uint8_t x, uint8_t y, uint8_t * str);
void OLED_Scroll(uint8_t Direction, uint8_t StartPage, uint8_t EndPage, uint8_t Franes);
void OLED_ScrollUp(uint8_t StartPage, uint8_t EndPage, uint8_t Franes);
void OLED_DisplayIcon(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t * ch, uint16_t len);
void OLED_DisplayHanziStr(u8 x, u8 y, char * disStr);
void OLED_DisplayLogo(void);
#endif
