#ifndef __BOTP_H__
#define __BOTP_H__
#include "mylib.h"

#define BOTP_MAC_ADDR	0x12345678


#define BOTP_OK					0x00
#define BOTP_ERROR_FORMAT		0x01
#define BOTP_ERROR_FAMILY		0x02
#define BOTP_ERROR_VERSION		0x03
#define BOTP_ERROR_LENGTH		0x04
#define BOTP_ERROR_MSG_BUS		0x05
#define BOTP_ERROR_MSG_TYPE		0x06
#define BOTP_ERROR_SMAC_ADDR	0x07
#define BOTP_ERROR_MSG_COUNT	0x08
#define BOTP_ERROR_DMAC_ADDR	0x09
#define BOTP_ERROR_UQICK_CMD	0x0A
#define BOTP_ERROR_TYPE			0x10
#define BOTP_ERROR_STR_LENGTH	0x11
#define BOTP_ERROR_TEXT_LENGTH	0x12
#define BOTP_ERROR_DATA_LENGTH	0x13
#define BOTP_ERROR_DATA_CRC16	0x14
#define BOTP_ERROR_INDEX        0x15





#define PACK_LEN				(256)
#define PACK_DATA_LEN			(PACK_LEN - 0x18)


#define HEADER_BOTP				0x424F5450
#define HEADER					HEADER_BOTP
#define IS_HEADER(h)			(\
									HEADER_BOTP == (h) \
								)

#define FAMILY_WC				0x0000
#define FAMILY_FREE				0xffff
#define FAMILY					FAMILY_WC
#define IS_FAMILY(f)			(\
									FAMILY_WC 		== (f) 	|| \
									FAMILY_FREE 	== (f)     \
								)

#define VERSION_DEV				0x00
#define VERSION					VERSION_DEV
#define IS_VERSION(v)			(\
									VERSION_DEV 	== (v) \
								)

#define BUS_NET					0x00
#define BUS_SPI					0x01
#define BUS_UART				0x02
#define BUS_I2C					0x03
#define BUS_CAN					0x04
#define BUS_ERROR				0x0f
#define IS_BUS(b)				(\
									BUS_NET 	== (b) || \
									BUS_SPI		== (b) || \
									BUS_UART	== (b) || \
									BUS_I2C 	== (b) || \
									BUS_CAN		== (b) || \
									BUS_ERROR	== (b)    \
								)

#define MSG_TYPE_USER			0x00
#define MSG_TYPE_HEARBATE		0x01
#define MSG_TYPE_UP				0x02
#define MSG_TYPE_DOWN			0x03
#define MSG_TYPE_ASK			0x04
#define MSG_TYPE_ACK			0x05
#define MSG_TYPE_CS				0x06
#define MSG_TYPE_INT			0x07
#define MSG_TYPE_CTRL			0x08
#define MSG_TYPE_ERROR			0x0f
#define IS_MSG_TYPE(t)			(\
									MSG_TYPE_USER		== (t) || \
									MSG_TYPE_HEARBATE 	== (t) || \
									MSG_TYPE_UP			== (t) || \
									MSG_TYPE_DOWN		== (t) || \
									MSG_TYPE_ASK		== (t) || \
									MSG_TYPE_ACK		== (t) || \
									MSG_TYPE_CS			== (t) || \
									MSG_TYPE_INT		== (t) || \
									MSG_TYPE_CTRL		== (t) || \
									MSG_TYPE_ERROR		== (t)    \
								)

#define SET_MAC_ADDR(a1, a2, a3, a4)	((a1 << 24) | (a2 >> 16) | (a3 << 8) | (a4 << 0))

#define QUICK_CMD_USER			MSG_TYPE_USER
#define QUICK_CMD_TIMESTAMPS	MSG_TYPE_HEARBATE
#define QUICK_CMD_FIND			MSG_TYPE_ACK
#define QUICK_CMD_CTRL			MSG_TYPE_CTRL
#define QUICK_CMD_ERROR			MSG_TYPE_ERROR
#define IS_QUICK_CMD(c)			(\
									QUICK_CMD_USER 			== (c) || \
									QUICK_CMD_TIMESTAMPS	== (c) || \
									QUICK_CMD_FIND			== (c) || \
									QUICK_CMD_CTRL			== (c) || \
									QUICK_CMD_ERROR			== (c)    \
								)

#define PACK_TYPE_NULL			0x00
#define PACK_TYPE_TRUE			0x01
#define PACK_TYPE_FALSE			0x02
#define PACK_TYPE_BYTE			0x03
#define PACK_TYPE_SHORT			0x04		
#define PACK_TYPE_INT			0x05
#define PACK_TYPE_LONG			0x06
#define PACK_TYPE_FLOAT			0x07
#define PACK_TYPE_DOUBLE		0x08
#define PACK_TYPE_DATE			0x09
#define PACK_TYPE_TIME			0x0A
#define PACK_TYPE_DATETIME		0x0B
#define PACK_TYPE_UUID			0x0C
#define PACK_TYPE_STRING		0x0D
#define PACK_TYPE_TEXT			0x0E
#define PACK_TYPE_OBJ			0x40
#define PACK_TYPE_OBJ_NULL		(PACK_TYPE_OBJ + 0)
#define PACK_TYPE_OBJ_NOT_NULL	(PACK_TYPE_OBJ + 1)
#define PACK_TYPE_OBJ_NULL_STR	(PACK_TYPE_OBJ + 2)
#define PACK_TYPE_OBJ_STR		(PACK_TYPE_OBJ + 3)
#define PACK_TYPE_ARRAY_SMALL	0x80				// 基本类型的小数组 长度最大为 255 
#define PACK_TYPE_ARRAY_LONG	0xA0				// 基本类型的大数组 长度最大为 65535 
#define PACK_TYPE_CLCT_NULL		0xC0				// 无类型的采集 
#define PACK_TYPE_CLCT			0xE0 				// 有类型的采集

#define IS_PACK_TYPE(t)			(\
									PACK_TYPE_NULL 				== (t) || \
									PACK_TYPE_TRUE				== (t) || \
									PACK_TYPE_FALSE				== (t) || \
									PACK_TYPE_BYTE				== (t) || \
									PACK_TYPE_SHORT				== (t) || \
									PACK_TYPE_INT				== (t) || \
									PACK_TYPE_LONG				== (t) || \
									PACK_TYPE_FLOAT				== (t) || \
									PACK_TYPE_DOUBLE			== (t) || \
									PACK_TYPE_DATE				== (t) || \
									PACK_TYPE_TIME				== (t) || \
									PACK_TYPE_DATETIME			== (t) || \
									PACK_TYPE_UUID				== (t) || \
									PACK_TYPE_STRING			== (t) || \
									PACK_TYPE_TEXT				== (t) || \
									PACK_TYPE_OBJ				== (t) || \
									PACK_TYPE_OBJ_NULL			== (t) || \
									PACK_TYPE_OBJ_NOT_NULL		== (t) || \
									PACK_TYPE_OBJ_NULL_STR		== (t) || \
									PACK_TYPE_OBJ_STR			== (t) || \
									PACK_TYPE_ARRAY_SMALL		== (t) || \
									PACK_TYPE_ARRAY_LONG		== (t) || \
									PACK_TYPE_CLCT_NULL			== (t) || \
									PACK_TYPE_CLCT				== (t)    \
								)


#define FLOAT_EQ(f1, f2) 					(((f1) - (f2)) < 0.001 && ((f2) - (f1)) < 0.001)

#define BOTP_CheckFormat(b)					((IS_HEADER((b).Header)) && (IS_VERSION((b).Version)))
#define BOTP_CheckVersionVaild(b)			(IS_VERSION((b).Version) && (VERSION >= (b).Version))
#define BOTP_CheckFamilyVaild(b)			(IS_FAMILY((b).Family))
#define BOTP_CheckBusID(b)					(IS_BUS((b).Msg.BusID))
#define BOTP_CheckMsgType(b)				(IS_BUS((b).Msg.BusID) && IS_MSG_TYPE((b).Msg.Type))
#define BOTP_CheckQuickCmd(b)				(IS_QUICK_CMD((b).QuickCmd))
#define BOTP_CheckDMacAddr(b)				((BOTP_MAC_ADDR) == BOTP_GetDMacAddr((b)))
#define BOTP_CheckCrc(b)					((b).Pack.Crc16 == CRC16_Calc((uint8_t *)(&b), (b).PackLen + 0x18))
#define BOTP_CheckPackType(p)				(IS_PACK_TYPE((p).Type))


#define BOTP_PackLength(b)					((b).PackLen + 0x18)


#define BOTP_SetBusID(b, id)				((b)->Msg.BusID = (id))
#define BOTP_SetMsgType(b, type)			((b)->Msg.Type = (type))
#define BOTP_SetSMacAddr(b, addr)			((b)->SMacAddr = (addr))
#define BOTP_SetMsgCount(b, count)			((b)->MsgCount = (count))
#define BOTP_SetDMacAddr(b, addr)			((b)->DMacAddr = (addr))
#define BOTP_SetQuickCmd(b, cmd)			((b)->QuickCmd = (cmd))
#define BOTP_SetPackLength(b, length)		((b)->PackLen = (length))
#define BOTP_SetPackDataCrc16(b, crc)		((*(uint16_t *)(&((b).Pack[(b).PackLen]))  ) =  (crc))

#define BOTP_SetPackType(p, type)			((p)->Type = (type))
#define BOTP_SetPackStringLength(p, l)		((p)->StrLen = (l))
#define BOTP_SetPackTextLength(p, l)		((p)->TextLen = (l))

#define BOTP_GetBusID(b)					((b).Msg.BusID)
#define BOTP_GetMsgType(b)					((b).Msg.Type)
#define BOTP_GetSMacAddr(b)					((b).SMacAddr)
#define BOTP_GetMsgCount(b)					((b).MsgCount)
#define BOTP_GetDMacAddr(b) 				((b).DMacAddr)
#define BOTP_GetQuickCmd(b)					((b).QuickCmd)
#define BOTP_GetPackDataCrc16(b)			(*((uint16_t *)(&(b).Pack.Data[(b).PackLen])))
#define BOTP_GetPackLength(b)				((b).PackLen)
#define BOTP_GetPackType(p)					((p).Type)
#define BOTP_GetPackStringLength(p)			((p).StrLen)
#define BOTP_GetPackTextLength(p)			((p).TextLen)

#define IS_EXT_DEV_ID(id)					( \
												((id) >= 0) && \
												((id) <= 7) \
											) 
	
	
#define EXEC_OBJ_CMD_LED					0x51				// LED 光融合实验结构体
#define EXEC_OBJ_CMD_LED_RET				0x52				// LED 光融合实验结果


#define IS_OBJ_CMD(id)						( \
												(EXEC_OBJ_CMD_LED 				== (id)) || \
												(EXEC_OBJ_CMD_LED_RET			== (id)) \
											)	






#define BOTP_PackAddZore(p, index, type)			do { \
														BOTP_PackAddItem(p, index, type, (uint8_t *)(0), 0); \
													} while (0)


#define BOTP_PackAddByte(p, index, type, byte)		do { \
														BOTP_PackAddItem(p, index, type, (uint8_t *)(byte), 1); \
													} while (0)

#define BOTP_PackAddWord(p, index, type, word)		do { \
														BOTP_PackAddItem(p, index, type, (uint8_t *)(word), 2); \
													} while (0)
													
#define BOTP_PackAddInt(p, index, type, int)		do { \
														BOTP_PackAddItem(p, index, type, (uint8_t *)(int), 4); \
													} while (0)


#define BOTP_PackAddLong(p, index, type, long)		do { \
														BOTP_PackAddItem(p, index, type, (uint8_t *)(long), 8); \
													} while (0)
													
#define BOTP_PackAddDate(p, index, type, date)		do { \
														BOTP_PackAddItem(p, index, type, (uint8_t *)(date), 3); \
													} while (0)
#define BOTP_PackAddTime(p, index, type, time)		do { \
														BOTP_PackAddItem(p, index, type, (uint8_t *)(time), 3); \
													} while (0)
													
#define BOTP_PackAddDateTime(p, index, type, datetime)	do { \
															BOTP_PackAddItem(p, index, type, (uint8_t *)(datetime), 6); \
														} while (0)
													
#define BOTP_PackAddUuid(p, index, type, uuid)		do { \
														BOTP_PackAddItem(p, index, type, (uint8_t *)(uuid), 16); \
													} while (0) 
													
#define BOTP_ObjToNull(p, 	index)				BOTP_PackAddZore(p, index, PACK_TYPE_NULL)
#define BOTP_ObjToTrue(p, 	index)				BOTP_PackAddZore(p, index, PACK_TYPE_TRUE)
#define BOTP_ObjToFalse(p, 	index)				BOTP_PackAddZore(p, index, PACK_TYPE_FALSE)
#define BOTP_ObjToBool(p, 	index, value)		BOTP_PackAddZore(p, index, ((value)?0x01:0x02))
#define BOTP_ObjToByte(p, 	index, value)		BOTP_PackAddByte(p, index, PACK_TYPE_BYTE, 		value)
#define BOTP_ObjToShort(p, 	index, value)		BOTP_PackAddWord(p, index, PACK_TYPE_SHORT, 	value)
#define BOTP_ObjToInt(p,	index, value)		BOTP_PackAddInt( p, index, PACK_TYPE_INT,		value)
#define BOTP_ObjToLong(p,  	index, value)		BOTP_PackAddLong(p, index, PACK_TYPE_LONG,		value)
#define BOTP_ObjToFloat(p, 	index, value)		BOTP_PackAddInt( p, index, PACK_TYPE_FLOAT,		value)
#define BOTP_ObjToDouble(p,	index, value)		BOTP_PackAddLong(p, index, PACK_TYPE_DOUBLE,	value)
#define BOTP_ObjToDate(p,   index, value)		BOTP_PackAddDate(p, index, PACK_TYPE_DATE, 		value) 
#define BOTP_ObjToTime(p,   index, value)		BOTP_PackAddTime(p, index, PACK_TYPE_TIME, 		value) 
#define BOTP_ObjToDateTime(p,index, value)		BOTP_PackAddDateTime(p, index, PACK_TYPE_DATETIME,	value) 
#define BOTP_ObjToUuid(p,	index, value)		BOTP_PackAddUuid(p, index, PACK_TYPE_UUID,		value) 

#define BOTP_ObjToObjNotNull(p, index, type, value, len)    do { \
                                                                BOTP_PackAddItem(p, index, PACK_TYPE_OBJ_NOT_NULL, (uint8_t *)0, 0); \
                                                                BOTP_PackAddItem(p, index, type, (uint8_t *)(value), len); \
                                                            } while (0) 
        
#define BOTP_PackGetItemType(p, index)				((p)->Data[(index)])

#define BOTP_PackGetZore(p, index)					((p)->Data[(index)])

#define BOTP_PackGetByte(p, index, byte)			do { \
														BOTP_PackGetItemData(p, index, (uint8_t *)(byte), 1); \
													} while (0)

#define BOTP_PackGetWord(p, index, word)			do { \
														BOTP_PackGetItemData(p, index, (uint8_t *)(word), 2); \
													} while (0)
													
#define BOTP_PackGetInt(p, index, int)				do { \
														BOTP_PackGetItemData(p, index, (uint8_t *)(int), 4); \
													} while (0)


#define BOTP_PackGetLong(p, index, long)			do { \
														BOTP_PackGetItemData(p, index, (uint8_t *)(long), 8); \
													} while (0)
													
#define BOTP_PackGetDate(p, index, date)			do { \
														BOTP_PackGetItemData(p, index, (uint8_t *)(date), 3); \
													} while (0)
#define BOTP_PackGetTime(p, index, time)			do { \
														BOTP_PackGetItemData(p, index, (uint8_t *)(time), 3); \
													} while (0)
													
#define BOTP_PackGetDateTime(p, index, datetime)	do { \
															BOTP_PackGetItemData(p, index, (uint8_t *)(datetime), 6); \
														} while (0)
													
#define BOTP_PackGetUuid(p, index, uuid)			do { \
														BOTP_PackGetItemData(p, index, (uint8_t *)(uuid), 16); \
													} while (0) 
													
#define BOTP_NullToObj(p, 	index)				BOTP_PackGetZore(p, index)
#define BOTP_BoolToObj(p, 	index)				BOTP_PackGetZore(p, index)
#define BOTP_ByteToObj(p, 	index, value)		BOTP_PackGetByte(p, index,	value)
#define BOTP_ShortToObj(p, 	index, value)		BOTP_PackGetWord(p, index, 	value)
#define BOTP_IntToObj(p,	index, value)		BOTP_PackGetInt( p, index,	value)
#define BOTP_LongToObj(p,  	index, value)		BOTP_PackGetLong(p, index,	value)
#define BOTP_FloatToObj(p, 	index, value)		BOTP_PackGetInt( p, index,	value)
#define BOTP_DoubleToObj(p,	index, value)		BOTP_PackGetLong(p, index,	value)
#define BOTP_DateToObj(p,   index, value)		BOTP_PackGetDate(p, index,	value) 
#define BOTP_TimeToObj(p,   index, value)		BOTP_PackGetTime(p, index,	value) 
#define BOTP_DateTimeToObj(p,index, value)		BOTP_PackGetDateTime(p, index,	value) 
#define BOTP_UuidToObj(p,	index, value)		BOTP_PackGetUuid(p, index,	value) 







typedef struct {
	uint8_t 	Data[PACK_DATA_LEN + 2];
} Pack_t;

struct _msg{
	uint8_t BusID:4;
	uint8_t Type:4; 
};

typedef struct {
	uint32_t	 	Header; 		// "BOTP"
	uint16_t 		Family;			// ushort 类型  	0x0000 微畅    0xffff 自由协议
	uint8_t 		Version;		// 版本			 	0x00   开发版本
	struct _msg		Msg;			// 消息类型 
	uint32_t 		SMacAddr;		// 从设备mac地址 
 	uint32_t 		MsgCount;		// 消息计数
 	uint32_t 		DMacAddr;		// 目标设备mac地址  供中继使用
	uint32_t 		QuickCmd;		// 快速指令
	uint16_t 		PackLen;		// 数据长度
	Pack_t 	 		Pack;
} BOTP;



typedef struct {
	struct _msg	Msg; 		// 当前设备消息类型  参考 BOTP 的消息类型
	uint8_t 	Index;		// 当前设备占用资源索引值 
	uint32_t 	Mac;		// 当前设备 MAC 地址(CRC32) 
} ExtDev;

extern ExtDev device[];
typedef struct {
    uint8_t     CE;         // CE 引脚状态，每个设备占1bit，共1*8=8bits
    uint8_t     USE;        // USE 引脚状态，每个设备占1bit，共1*8=8bits
    uint8_t     INT;        // INT 引脚状态，每个设备占1bit，共1*8=8bits
    uint32_t    ADDR;       // ADDR 每个设备占3bits，共3*8=24bits
    uint32_t    BUS;        // 总线协议，每个设备占 3bits ，共 3*8=24 bits
} ExtDevInfo;

#define OBJ_LEN				8
typedef struct {
	uint8_t Id;				// 执行obj的唯一标识
	uint8_t Len;			// Obj的长度，用于获取数据
	void *  Data;			// 数据的指针
} ExecObjItem;
extern ExecObjItem ExecObjArray[];


uint16_t BOTP_PackDataFill(Pack_t * p);
void BOTP_Init(BOTP * botp, uint32_t SrcMacAddr, uint32_t DecMacAddr);
uint8_t BOTP_PackExtTest(Pack_t * p, uint16_t len);
uint8_t BOTP_Exec(BOTP * botp);

void ExtDev_ClearDeviceTable(void);
void ExtDev_Init(ExtDev * Dev);
void ExtDev_SetBusId(ExtDev * Dev, uint8_t BusId);
void ExtDev_SetMsgType(ExtDev * Dev, uint8_t MsgType);
void ExtDev_SetMacCrc32(ExtDev * Dev, uint32_t Mac);
void ExtDev_SetBusIndex(ExtDev * Dev, uint8_t Index);
uint8_t ExtDev_GetBusId(ExtDev * Dev);
uint8_t ExtDev_GetMsgType(ExtDev * Dev);
uint8_t ExtDev_GetDeviceIdleIndex(void);
uint8_t ExtDev_GetDeviceIndexByMac(uint32_t Mac);
uint8_t ExtDev_GetDeviceIndexByBusIndex(uint8_t BusId, uint8_t Index);
uint8_t BOTP_SendData(BOTP * b);

uint8_t ExecObjInit(ExecObjItem * Obj, uint8_t Id, uint8_t Len, void * Data);


void BOTP_PackGetItemData(Pack_t * p, uint8_t index, uint8_t * dat, uint8_t len);
void BOTP_PackAddItem(Pack_t * p, uint8_t index, uint8_t type, uint8_t * value, uint8_t len);

#endif
