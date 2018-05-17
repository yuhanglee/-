#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "mylib.h"

#define CMD_STR_MAX_LEN         40
typedef enum {
    cmd_Error = -3,
    cmd_EpmRead = -2,
    cmd_EpmWrite = -1,
    cmd_Ping = 0,
    cmd_LcdOff,
    cmd_LcdOn,
} cmd_code;


typedef enum {
    cmd_ErrorCmdCode = -2,
    cmd_ErrorFormat = -1,
    cmd_OK = 0,
} cmd_status;


#define USER_NOR  0x01
#define USER_DEV  0x02

typedef struct cmd {
    char str[CMD_STR_MAX_LEN];
    char user;                  // 该命令的权限
    uint16_t hash;              // hash:  16bit
    char len;                   // len < CMD_STR_MAX_LEN
    cmd_code  _code;
} cmd;




cmd_code        cmd_check(char * cmd_str);
cmd_status      cmd_exec(cmd_code cmd_e);

#endif
