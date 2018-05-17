#include "WCOS_task.h"

void WCOS_TASK_Init(uint8_t TaskIndex, WCOS_TASK * CurTask, WCOS_TASK * NextTask) {
	
	assert(TaskIndex < 8);
	assert(CurTask != NULL);
	
}
