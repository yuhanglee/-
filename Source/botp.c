#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "botp.h"
#include "uart.h"
#include "crc.h"
#include "max485.h"

#define BIG_ENCODE
//#define SMALL_ENCODE



#if defined BIG_ENCODE
void BOTP_PackGetItemData(Pack_t * p, uint8_t index, uint8_t * dat, uint8_t len) {
	uint8_t i = 0;
	
    if (dat != 0) {
        for (i = 0;i < len;i++) {
             dat[i] = p->Data[index++];
        }
    }
}

void BOTP_PackAddItem(Pack_t * p, uint8_t index, uint8_t type, uint8_t * value, uint8_t len) {
	uint8_t i = 0;
	
	p->Data[index++] = type & 0xff;
	 
    if (value != 0) {
        for (i = 0;i < len;i++) {
            p->Data[index++] = value[i];
        }
    }
	
}
#elif defined SMALL_ENCODE
void BOTP_PackGetItemData(Pack_t * p, uint8_t index, uint8_t * dat, uint8_t len) {
	uint8_t i = 0;
	
    if (dat != 0) {
        for (i = 0;i < len;i++) {
             dat[i] = p->Data[len - 1 - i + index];
        }
    }
}
void BOTP_PackAddItem(Pack_t * p, uint8_t index, uint8_t type, uint8_t * value, uint8_t len) {
	int8_t i = 0;
	
	 
	p->Data[index++] = type & 0xff;
	
    if (value != 0) {
        for (i = 0;i < len;i++) {
            p->Data[index++] = value[len - 1 - i];
        }
    }
}
#else
	#error "Please define encode"
#endif											

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

void BOTP_Init(BOTP * botp, uint32_t SrcMacAddr, uint32_t DecMacAddr) {
	memset(botp, 0, sizeof(BOTP));
	botp->Header 			= HEADER;
	botp->Family			= FAMILY;
	botp->Version			= VERSION;
	botp->SMacAddr			= SrcMacAddr;
	botp->MsgCount			= 0x0000;
	botp->DMacAddr			= DecMacAddr;
}

uint8_t BOTP_Exec(BOTP * botp) {
	uint8_t index = 0x00;
	// 无效的格式 
	if (0 == BOTP_CheckFormat(*botp)) {
        print_error("format;%lx version;%lx\r\n", botp->Header, botp->Version);
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
            botp->Msg.Type = device[index].Msg.Type;
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
                print_error("idle device index error\r\n");
                return BOTP_ERROR_INDEX;
            }
            print_error("idle device index error\r\n");
        }
		return BOTP_ERROR_DMAC_ADDR;
	} else { // 进行本机解析
			print_debug("crc %04X\r\n", CRC_16((uint8_t *)(&(botp->Pack)), botp->PackLen));
			print_debug("crc %04X\r\n", BOTP_GetPackDataCrc16(*botp));
		if (BOTP_GetPackDataCrc16(*botp) == CRC_16((uint8_t *)(&(botp->Pack)), botp->PackLen)) {
			print_debug("crc ok\r\n");
		 	return BOTP_PackExtTest(&(botp->Pack), botp->PackLen);
		} else {
			print_debug("crc error\r\n");
			return BOTP_ERROR_DATA_CRC16;
		}
	}
	  
	
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
		
	print_debug("%bu\r\n", i);
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
				print_debug("NULL\r\n");
				item_len = 1;
			break;
			
			case PACK_TYPE_TRUE:
			case PACK_TYPE_FALSE:
				print_debug("%bx\r\n", BOTP_BoolToObj(p, i));
				item_len = 1;
			break;
			
			case PACK_TYPE_BYTE:
				BOTP_ByteToObj(p, i+1, res);
				print_debug("byte:\t%bx\r\n", *((uint8_t *)(res)));
				item_len = 2;
			break;
			case PACK_TYPE_SHORT:
				BOTP_ShortToObj(p, i+1, res);
				print_debug("short:\t%x\r\n", *((uint16_t *)(res)));
				item_len = 3;
			break;
			case PACK_TYPE_INT:
				BOTP_IntToObj(p, i+1, res);
				print_debug("int:\t%lx\r\n", *((uint32_t *)(res)));
				item_len = 5;
			break;
			case PACK_TYPE_LONG:
				BOTP_LongToObj(p, i+1, res);
				print_debug("long:\t%lx\r\n", *((uint32_t *)(res)));
				item_len = 9;
			break;
			case PACK_TYPE_FLOAT:
				BOTP_FloatToObj(p, i+1, res);
				print_debug("float:\t%f\r\n", *((float *)(res)));
				item_len = 5;
			break;
			case PACK_TYPE_DOUBLE:
				BOTP_DoubleToObj(p, i+1, res);
				print_debug("double:\t%f\r\n", *((double *)(res)));
				item_len = 9;
			break;
			case PACK_TYPE_DATE:
				BOTP_DateToObj(p, i+1, res);
				print_debug("date:");
				item_len = 4;
				for (u_8 = 0;u_8 < 3;u_8++) {
					print_debug("%bx ", res[u_8]);
				}
				print_debug("\r\n");
			break;
			case PACK_TYPE_TIME:
				BOTP_TimeToObj(p, i+1, res);
				print_debug("time:");
				item_len = 4;
				for (u_8 = 0;u_8 < 3;u_8++) {
					print_debug("%bx ", res[u_8]);
				}
				print_debug("\r\n");
			break;
			case PACK_TYPE_DATETIME:
				BOTP_DateTimeToObj(p, i+1, res);
				print_debug("datetime:");
				item_len = 7;
				for (u_8 = 0;u_8 < 6;u_8++) {
					print_debug("%bx ", res[u_8]);
				}
				print_debug("\r\n");
			break;
			case PACK_TYPE_UUID:
				BOTP_UuidToObj(p, i+1, res);
				print_debug("uuid:");
				item_len = 17;
				for (u_8 = 0;u_8 < 16;u_8++) {
					print_debug("%bx ", res[u_8]);
				}
				print_debug("\r\n");
			break;
			
			case PACK_TYPE_OBJ_NOT_NULL:
				item_len = ExecObj((uint8_t *)(&(p->Data[i+1]))) + 1;
			break;
			
			default:
				print_debug("cmd default: %bx\r\n", p->Data[i]);
                item_len = 1;
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
    print_debug("end%x\r\n", len);
	return ret;
}

uint8_t BOTP_SendData(BOTP * b) {
	uint8_t busId = b->Msg.BusID;
	uint8_t msgType = b->Msg.Type;
    uint8_t Index = ExtDev_GetDeviceIndexByMac(b->DMacAddr);
	uint16_t i;
	
	wc_assert(IS_BUS(busId));
	wc_assert(IS_MSG_TYPE(msgType));
	print_debug("b->DMacAddr:%lx\r\n", b->DMacAddr);
    for (i = 0;i < BOTP_GetPackLength(*b) + 0x1C;i++) {
        printf("%02bx ", ((uint8_t *)b)[i]);
    }
	switch (busId) {
		case BUS_UART:
			switch (device[Index].Index) {
				case 0:
                    MAX485_WriteHex((uint8_t *)b, BOTP_GetPackLength(*b) + 0x1C);
					print_debug("dev index:%02bx\r\n", Index);
				break;
                
				default:
					print_error("Uart index:%02bx\r\n", Index);
                    return BOTP_ERROR_MSG_BUS;
				break;
			}
		break;
		
		default:
			print_error("busId:%02bx\r\n", busId);
            return BOTP_ERROR_MSG_BUS;
        break;
	}
    
    return BOTP_OK;
}

