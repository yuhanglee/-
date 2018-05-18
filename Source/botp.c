#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "botp.h"

#define BIG_ENCODE
//#define SMALL_ENCODE

static const uint16_t CRC16_TABLE[256] = {
    0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
    0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
    0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
    0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
    0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
    0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
    0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
    0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
    0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
    0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
    0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
    0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
    0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
    0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
    0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
    0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
    0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
    0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
    0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
    0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
    0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
    0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
    0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
    0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
    0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
    0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
    0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
    0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
    0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
    0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
    0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
    0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

uint16_t CRC16_Calc(char * CrcArray, uint16_t CrcLen) {
	uint16_t CrcRet = 0x0;
	
	for (;CrcLen;CrcLen--) {
		CrcRet = CRC16_TABLE[((CrcRet >> 8)  ^ *CrcArray++) & 0xff] ^ (CrcRet << 8);
	}
	
	return CrcRet & 0xffff;
}


#if defined BIG_ENCODE
void BOTP_PackGetItemData(Pack_t * p, uint8_t index, uint8_t * dat, uint8_t len) {
	uint8_t i = 0;
	
	for (i = 0;i < len;i++) {
		 dat[i] = p->Data[index++];
	}
}

void BOTP_PackAddItem(Pack_t * p, uint8_t index, uint8_t type, uint8_t * value, uint8_t len) {
	uint8_t i = 0;
	
	p->Data[index++] = type & 0xff;
	 
	for (i = 0;i < len;i++) {
		p->Data[index++] = value[i];
	}
	
}
#elif defined SMALL_ENCODE
void BOTP_PackGetItemData(Pack_t * p, uint8_t index, uint8_t * dat, uint8_t len) {
	uint8_t i = 0;
	
	for (i = 0;i < len;i++) {
		 dat[i] = p->Data[len - 1 - i + index];
	}
}
void BOTP_PackAddItem(Pack_t * p, uint8_t index, uint8_t type, uint8_t * value, uint8_t len) {
	int8_t i = 0;
	
	 
	p->Data[index++] = type & 0xff;
	
	for (i = 0;i < len;i++) {
		p->Data[index++] = value[len - 1 - i];
	}
	
}
#else
	#error "Please define encode"
#endif											

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


ExtDev device[8] = {
	{{BUS_UART, MSG_TYPE_USER},     0,  0x11111111},
	{{BUS_NET,  MSG_TYPE_USER},     0,  0x00000000},
	{{BUS_NET,  MSG_TYPE_USER},     0,  0x00000000},
	{{BUS_NET,  MSG_TYPE_USER},     0,  0x00000000},
	{{BUS_NET,  MSG_TYPE_USER},     0,  0x00000000},
	{{BUS_NET,  MSG_TYPE_USER},     0,  0x00000000},
	{{BUS_NET,  MSG_TYPE_USER},     0,  0x00000000},
	{{BUS_NET,  MSG_TYPE_USER},     0,  0x00000000},
};

ExecObjItem ExecObjArray[OBJ_LEN] = {
	0
};
void ExtDev_Init(ExtDev * Dev) {
	wc_assert(IS_EXT_DEV_ID(((Dev - device) / sizeof(device[0]))));
	
	Dev->Msg.BusID 	= BUS_ERROR;
	Dev->Msg.Type  	= MSG_TYPE_ERROR;
	Dev->Index 		= 0xff;
	Dev->Mac		= 0x00000000;
}

uint8_t ExtDev_GetBusIdleIndex(uint8_t BusId) {
	uint8_t i;
	uint8_t index = 0xff;
	
	wc_assert(IS_BUS(BusId));
	
	for (i = 0;i < (sizeof(device) / sizeof(device[0]));i++) {
		if (BusId == device[i].Msg.BusID) {
			index = device[i].Index;
		}
	}
	
	index++;
	
	return index & 0xff;
}

void ExtDev_SetBusId(ExtDev * Dev, uint8_t BusId) {
	wc_assert(IS_BUS(BusId));
	wc_assert(IS_EXT_DEV_ID((Dev - device) / sizeof(device[0])));
	
	Dev->Msg.BusID = BusId;
}

void ExtDev_SetMsgType(ExtDev * Dev, uint8_t MsgType) {
	wc_assert(IS_MSG_TYPE(MsgType));
	wc_assert(IS_EXT_DEV_ID((Dev - device) / sizeof(device[0])));
	
	Dev->Msg.Type = MsgType;
}

void ExtDev_SetMacCrc32(ExtDev * Dev, uint32_t Mac) {
	wc_assert(IS_EXT_DEV_ID((Dev - device) / sizeof(device[0])));
	
	Dev->Mac = Mac;
}
void ExtDev_SetBusIndex(ExtDev * Dev, uint8_t Index) {
	wc_assert(IS_EXT_DEV_ID((Dev - device) / sizeof(device[0])));
	
	Dev->Index = Index;
}

uint8_t ExtDev_GetBusId(ExtDev * Dev) {
	wc_assert(IS_EXT_DEV_ID((Dev - device) / sizeof(device[0])));
	
	return Dev->Msg.BusID;
}

uint8_t ExtDev_GetMsgType(ExtDev * Dev) {
	wc_assert(IS_EXT_DEV_ID((Dev - device) / sizeof(device[0])));

	return Dev->Msg.Type;
}

uint8_t ExtDev_GetDeviceIdleIndex(void) {
	uint8_t i;
	
	for (i = 0;i < (sizeof(device) / sizeof(device[0]));i++) {
		if (device[i].Mac == 0x0000000) {
			return i;
		}
	}
	
	return BOTP_ERROR_INDEX;
}

uint8_t ExtDev_GetDeviceIndexByMac(uint32_t Mac) {
	int i;
	
	for (i = 0;i < (sizeof(device) / sizeof(device[0]));i++) {
		 if (Mac == device[i].Mac) {
 			return i;
 		}
	}
	
	return BOTP_ERROR_INDEX;
}

uint8_t ExtDev_GetDeviceIndexByBusIndex(uint8_t BusId, uint8_t Index) {
	uint8_t i = 0;
	
	wc_assert(IS_BUS(BusId));
	wc_assert(IS_EXT_DEV_ID(Index));
	
	for (i = 0;i < (sizeof(device) / sizeof(device[0]));i++) {
		if ((BusId == device[i].Msg.BusID) && (Index == device[i].Index)) {
			return i;
		}
	}
	
	return BOTP_ERROR_INDEX;
} 

void ExtDev_ClearDeviceTable(void) {
    uint8_t i, j;
    
    for (i = 0;i < (sizeof(device) / sizeof(device[0]));i++) {
        if (0x00000000 != device[i].Mac) {
            for (j = i+1;j < (sizeof(device) / sizeof(device[0]));j++) {
                if (device[j].Mac == device[i].Mac) {
                    device[j].Mac = 0x00000000;
                }
            }
        }
    }
}


uint8_t ExecObjDefaultInit(ExecObjItem * Obj) {
	wc_assert(Obj);
	
	Obj->Id = 0;
	Obj->Len = 0;
	Obj->Data = 0;
	
	return 0;
}

uint8_t ExecObjInit(ExecObjItem * Obj, uint8_t Id, uint8_t Len, void * Data) {
	wc_assert(Obj);
	wc_assert(IS_OBJ_CMD(Id));
	wc_assert(Len <= 255);
	wc_assert(Data);
	
	Obj->Id = Id;
	Obj->Len = Len;
	Obj->Data = (void *)Data;
}

uint8_t ExecObj(uint8_t * DataPtr) {
	uint8_t i = 0, j;
	
	wc_assert(DataPtr);
	wc_assert(IS_OBJ_CMD(DataPtr[0]));
	
	for (i = 0;i < OBJ_LEN;i++) {
		if (DataPtr[0] == ExecObjArray[i].Id) {
			memcpy(ExecObjArray[i].Data, &(DataPtr[1]), ExecObjArray[i].Len);
			return ExecObjArray[i].Len+1;
		}
	}
	
	if (OBJ_LEN == i) {
		return 0;
	}
}

uint8_t BOTP_BusNet(BOTP botp) {
	switch (BOTP_GetMsgType(botp)) {
		case MSG_TYPE_USER:
		break;
		
		case MSG_TYPE_HEARBATE:
		break;
		
		case MSG_TYPE_CS:
		break;
		
		case MSG_TYPE_INT:
		break;
		
		case MSG_TYPE_CTRL:
		break;
		
		default:
		return BOTP_ERROR_MSG_TYPE;
	}
	
	return BOTP_OK;	
} 

uint8_t BOTP_BusUart(BOTP botp) {
	switch (BOTP_GetMsgType(botp)) {
		case MSG_TYPE_USER:
		break;
		
		case MSG_TYPE_HEARBATE:
		break;
		
		case MSG_TYPE_CS:
		break;
		
		case MSG_TYPE_INT:
		break;
		
		case MSG_TYPE_CTRL:
		break;
		
		default:
		return BOTP_ERROR_MSG_TYPE;
	}
	return BOTP_OK;	
}

uint8_t BOTP_BusSPI(BOTP botp) {
	switch (BOTP_GetMsgType(botp)) {
		case MSG_TYPE_USER:
		break;
		
		case MSG_TYPE_HEARBATE:
		break;
		
		case MSG_TYPE_CS:
		break;
		
		case MSG_TYPE_INT:
		break;
		
		case MSG_TYPE_CTRL:
		break;
		
		default:
		return BOTP_ERROR_MSG_TYPE;
	}
	return BOTP_OK;	
}

uint8_t BOTP_BusI2C(BOTP botp) {
	switch (BOTP_GetMsgType(botp)) {
		case MSG_TYPE_USER:
		break;
		
		case MSG_TYPE_HEARBATE:
		break;
		
		case MSG_TYPE_CS:
		break;
		
		case MSG_TYPE_INT:
		break;
		
		case MSG_TYPE_CTRL:
		break;
		
		default:
		return BOTP_ERROR_MSG_TYPE;
	}
	return BOTP_OK;
}

uint8_t BOTP_BusCAN(BOTP botp) {
	switch (BOTP_GetMsgType(botp)) {
		case MSG_TYPE_USER:
		break;
		
		case MSG_TYPE_HEARBATE:
		break;
		
		case MSG_TYPE_CS:
		break;
		
		case MSG_TYPE_INT:
		break;
		
		case MSG_TYPE_CTRL:
		break;
		
		default:
		return BOTP_ERROR_MSG_TYPE;
	}
	return BOTP_OK;
}

void BOTP_Init(BOTP * botp) {
	memset(botp, 0, sizeof(BOTP));
	botp->Header 			= HEADER;
	botp->Family			= FAMILY;
	botp->Version			= VERSION;
	botp->SMacAddr			= BOTP_MAC_ADDR;
	botp->MsgCount			= 0x0000;
	botp->DMacAddr			= BOTP_MAC_ADDR;
}

uint8_t BOTP_Exec(BOTP * botp) {
	uint8_t index = 0x00;
	// 无效的格式 
	if (0 == BOTP_CheckFormat(*botp)) {
		return BOTP_ERROR_FORMAT;
	}
	// 无效的协议 
	if (0 == BOTP_CheckFamilyVaild(*botp)) {
		return BOTP_ERROR_FAMILY;
	}
	
	// 目标地址和本机地址不一致 
	if (0 == BOTP_CheckDMacAddr(*botp)) {
		index = ExtDev_GetDeviceIndexByMac(botp->DMacAddr);
        if (BOTP_ERROR_INDEX != index) { // 可以在设备表中找到设备
            botp->Msg.BusID = device[index].Msg.BusID;
            botp->MsgCount = device[index].Msg.Type;
            // BOTP_PackExtTest(&(botp->Pack), botp->PackLen);
            return BOTP_SendData(botp);
        } else {
            index = ExtDev_GetDeviceIdleIndex(); // 获取空闲设备索引
            if (BOTP_ERROR_INDEX != index) {    // 正常获取
                ExtDev_SetBusId(&(device[index]), botp->Msg.BusID);
                ExtDev_SetMsgType(&(device[index]), botp->Msg.Type);
                ExtDev_SetBusIndex(&(device[index]), ExtDev_GetBusIdleIndex(botp->Msg.BusID));
                ExtDev_SetMacCrc32(&(device[index]), botp->SMacAddr); 
                return BOTP_OK;
            } else {
                printf("idle device index error\r\n");
                return BOTP_ERROR_INDEX;
            }
            printf("idle device index error\r\n");
        }
		return BOTP_ERROR_DMAC_ADDR;
	} else { // 进行本机解析
		 if (0 == BOTP_PackExtTest(&(botp->Pack), botp->PackLen)) {
			printf("ext ok\r\n");
		} else {
			printf("ext error\r\n");
		}
	}
	
//	// 数据校验不对 
//	if (0 == BOTP_CheckCrc(*botp)) {
//		return BOTP_ERROR_DATA_CRC16;
//	} 
//	
//	switch (BOTP_GetBusID(*botp)) {
//		case BUS_NET:
//			BOTP_BusNet(*botp);
//		break;
//		
//		case BUS_SPI:
//			BOTP_BusSPI(*botp);
//		break;
//		
//		case BUS_UART:
//			BOTP_BusUart(*botp);
//		break;
//		
//		case BUS_I2C:
//			BOTP_BusI2C(*botp);
//		break;
//		
//		case BUS_CAN:
//			BOTP_BusCAN(*botp);
//		break;
//		
//		default:
//		return BOTP_ERROR_MSG_BUS; 
//	}
    
   
	
    return BOTP_OK;	
}

uint16_t BOTP_PackDataFill(Pack_t * p) {
	int i = 0;
	uint32_t data_i;
	float data_f;
	double data_d; 
	uint8_t data_ch[16] = {
		0x1,
		0x2,
		0x3,
		0x4,
		0x5,
		0x6,
		0x7,
		0x8,
		0x9,
		0xa,
		0xb,
		0xc,
		0xd,
		0xe,
		0xf,
		0x0,
	};
	
	
	BOTP_ObjToNull(p, i); i+=1;
	BOTP_ObjToBool(p, i, i % 2); i+=1;
	BOTP_ObjToBool(p, i, i % 2); i+=1;
	data_i = 0x12345678;
	data_f = 0.22;
	data_d = 0.24;
	
	BOTP_ObjToByte(p, i, &data_i); i+=2;
	BOTP_ObjToShort(p, i, &data_i); i+=3;
	BOTP_ObjToInt(p, i, &data_i); i+=5;
	BOTP_ObjToLong(p, i, &data_i); i+=9;
	BOTP_ObjToFloat(p, i, &data_f); i+=5;
	BOTP_ObjToDouble(p, i, &data_d); i+=9;
	BOTP_ObjToDate(p, i, data_ch); i+=4;
	BOTP_ObjToTime(p, i, data_ch); i+=4;
	BOTP_ObjToDateTime(p, i, data_ch); i+=7;
	BOTP_ObjToUuid(p, i, data_ch); i+=17;
	BOTP_ObjToBool(p, i, i % 2); i+=1;
	BOTP_ObjToDate(p, i, data_ch); i+=4;
		
	printf("%bu\r\n", i);
	return i;
} 

uint8_t BOTP_PackExtTest(Pack_t * p, uint16_t len) {
	uint16_t i = 0, u_8 = 0;
	uint16_t item_len = 0;
	uint8_t ret = 0x00;
	char res[16];
	
	do {
		switch (p->Data[i]) {
			case PACK_TYPE_NULL:
				printf("NULL\r\n");
				item_len = 1;
			break;
			
			case PACK_TYPE_TRUE:
			case PACK_TYPE_FALSE:
				printf("%bx\r\n", BOTP_BoolToObj(p, i));
				item_len = 1;
			break;
			
			case PACK_TYPE_BYTE:
				BOTP_ByteToObj(p, i+1, res);
				printf("byte:\t%bx\r\n", *((uint8_t *)(res)));
				item_len = 2;
			break;
			case PACK_TYPE_SHORT:
				BOTP_ShortToObj(p, i+1, res);
				printf("short:\t%x\r\n", *((uint16_t *)(res)));
				item_len = 3;
			break;
			case PACK_TYPE_INT:
				BOTP_IntToObj(p, i+1, res);
				printf("int:\t%lx\r\n", *((uint32_t *)(res)));
				item_len = 5;
			break;
			case PACK_TYPE_LONG:
				BOTP_LongToObj(p, i+1, res);
				printf("long:\t%lx\r\n", *((uint32_t *)(res)));
				item_len = 9;
			break;
			case PACK_TYPE_FLOAT:
				BOTP_FloatToObj(p, i+1, res);
				printf("float:\t%f\r\n", *((float *)(res)));
				item_len = 5;
			break;
			case PACK_TYPE_DOUBLE:
				BOTP_DoubleToObj(p, i+1, res);
				printf("double:\t%f\r\n", *((double *)(res)));
				item_len = 9;
			break;
			case PACK_TYPE_DATE:
				BOTP_DateToObj(p, i+1, res);
				printf("date:");
				item_len = 4;
				for (u_8 = 0;u_8 < 3;u_8++) {
					printf("%bx ", res[u_8]);
				}
				printf("\r\n");
			break;
			case PACK_TYPE_TIME:
				BOTP_TimeToObj(p, i+1, res);
				printf("time:");
				item_len = 4;
				for (u_8 = 0;u_8 < 3;u_8++) {
					printf("%bx ", res[u_8]);
				}
				printf("\r\n");
			break;
			case PACK_TYPE_DATETIME:
				BOTP_DateTimeToObj(p, i+1, res);
				printf("datetime:");
				item_len = 7;
				for (u_8 = 0;u_8 < 6;u_8++) {
					printf("%bx ", res[u_8]);
				}
				printf("\r\n");
			break;
			case PACK_TYPE_UUID:
				BOTP_UuidToObj(p, i+1, res);
				printf("uuid:");
				item_len = 17;
				for (u_8 = 0;u_8 < 16;u_8++) {
					printf("%bx ", res[u_8]);
				}
				printf("\r\n");
			break;
			
			case PACK_TYPE_OBJ_NOT_NULL:
				item_len = ExecObj((uint8_t *)(&(p->Data[i+1]))) + 1;
			break;
			
			default:
				printf("cmd default: %bx\r\n", p->Data[i]);
			break;
		}
		i += item_len;
		len -= item_len;
		item_len = 0;
        if ((int)len < 0) {
            ret = 0xff;
			break;
        }
	} while (len);
    printf("end%x\r\n", len);
	return ret;
}

uint8_t BOTP_SendData(BOTP * b) {
	uint8_t busId = b->Msg.BusID;
	uint8_t msgType = b->Msg.Type;
	uint16_t i;
	
	wc_assert(IS_BUS(busId));
	wc_assert(IS_MSG_TYPE(msgType));
	
	switch (busId) {
		case BUS_UART:
			switch (msgType) {
				case MSG_TYPE_USER:
					for (i = 0;i < 0x1A;i++) {
						if ((i & 0x00ff) == 0) {
							printf("\r\n");
						}
						printf("%02bx ", ((uint8_t *)(b))[i]);
					}
					if (b->PackLen != 0) {
						for (;i < (b->PackLen + 0x1C);i++) {
							if ((i & 0x00ff) == 0) {
								printf("\n");
							}
							printf("%02bx ", ((uint8_t *)(b))[i]);
						}
					}
				break;
				default:
					printf("msgType:%02bx\r\n", msgType);
                    return BOTP_ERROR_TYPE;
				break;
			}
		break;
		
		default:
			printf("busId:%02bx\r\n", busId);
            return BOTP_ERROR_MSG_BUS;
        break;
	}
    
    return BOTP_OK;
}

