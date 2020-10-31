#include "Scheduler.h"
#include <stdio.h>
#include <stdlib.h>

static u8 gRegisteredTaskCounter = 0;
static u8 gTickCounter = 0;
TaskControlBlock tcb[MAX_ALLOWABLE_TASKS];

void Scheduler_TicksCounter()
{
	gTickCounter++;
}

u8 Scheduler_AddTask(SchedulerTaskID taskID, u32 timer, void(*fp)())
{
	if (taskID < 0 && taskID >= 20) return 0;
	if (timer < 0) return;

	tcb[gRegisteredTaskCounter].taskID = taskID;
	tcb[gRegisteredTaskCounter].taskCallback = fp;
	tcb[gRegisteredTaskCounter].timer = timer;
	tcb[gRegisteredTaskCounter].taskState = WAITING;
	gRegisteredTaskCounter++;
	return 0;
}

u8 Scheduler_StartTask(SchedulerTaskID taskID)
{
	u8 taskItr = 0;
	for (taskItr = 0; taskItr < MAX_ALLOWABLE_TASKS; taskItr++)
	{
		if (tcb[taskItr].taskID == taskID)
		{
			tcb[taskItr].taskState = READY;
		}
	}
	return 0;
}

u8 Scheduler_StopTask(SchedulerTaskID taskID)
{
	u8 taskItr = 0;
	for (taskItr = 0; taskItr < MAX_ALLOWABLE_TASKS; taskItr++)
	{
		if (tcb[taskItr].taskID == taskID)
		{
			tcb[taskItr].taskState = IDLE;
		}
	}
	return 0;
}

void Scheduler_Run()
{
	while (1)
	{

	}
}

void Scheduler_Init()
{
	gRegisteredTaskCounter = 0;
	gTickCounter = 0;
	memset(tcb, 0, sizeof(TaskControlBlock));
}
