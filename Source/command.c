#include "command.h"
#include "mylib.h"
#include "wc_string.h"

#define CMDSTR_SIZE     (sizeof(CMDSTR) / sizeof(CMDSTR[0]))
#define SIZE(b)         (sizeof(b))

static code cmd CMDSTR[] = {
    {"EPM READ",    USER_DEV, 0x3eac, 8, cmd_EpmRead},
    {"EPM WRITE",   USER_DEV, 0x116a, 9, cmd_EpmWrite},
    {"LCD OFF",     USER_NOR, 0x1106, 7, cmd_LcdOff},
    {"LCD ON",      USER_NOR, 0x5987, 6, cmd_LcdOn},
    {"PING",        USER_NOR, 0xAD1A, 4, cmd_Ping},
}; 


uint16_t hash_calc(char * str, uint8_t len) {
    uint16_t hash = 0;
    uint8_t i = 0;
    uint8_t step = (len >> 3) + 1;
        
    for (i = 0;i < len;i += step) {
        hash = hash ^ ((hash << 5) + (hash >> 2) + (unsigned char)(str[i]));
    }
    printf("hash:%04x\r\n", hash);
    return hash;
}

void cmd_init(cmd * CmdArray, uint8_t len) {
    int8_t i;
    uint8_t CmdStrLen;
    
    for (i = 0;i < len;++i) {
        CmdStrLen = str_len(CmdArray[i].str);
        CmdArray[i].len = CmdStrLen;
        CmdArray[i].hash = hash_calc(CmdArray[i].str, CmdStrLen);
    }
}

cmd_code cmd_check(char * cmd_str) {
    int8_t i;
    uint16_t hash;
    
    wc_assert(cmd_str != 0);
    hash = hash_calc(cmd_str, str_len(cmd_str));
    for (i = 0;i < CMDSTR_SIZE;++i) {
        if (CMDSTR[i].hash == hash) {
            return (cmd_code)(CMDSTR[i]._code);
        }
    }
    
    return (cmd_code)(cmd_Error);
}

cmd_status cmd_exec(cmd_code cmd_e) {
    cmd_status ret = cmd_ErrorFormat;
    switch (cmd_e) {
        case cmd_Error:
            printf("cmd code error\r\n");
            break;
        
        case cmd_LcdOff:
            printf("LCD of\rf\n");
            break;
        
        case cmd_LcdOn:
            printf("LCD on\r\n");
            break;
        
        case cmd_Ping:
            printf("OK\r\n");
            ret = cmd_OK;
            break;
        
        case cmd_EpmRead:
            printf("eeprom read test\r\n");
            break;
        
        case cmd_EpmWrite:
            printf("eeprom write test\r\n");
            break;
        
        default:
            printf("Format error\r\n");
    }
        
    return ret;
}
