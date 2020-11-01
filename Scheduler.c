#include "Scheduler.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

static u8 gRegisteredTaskCounter = 0;
static u8 gTickCounter = 0;
TaskControlBlock tcb[MAX_ALLOWABLE_TASKS];

#define IS_VALID_TASK(a)((taskID < 0) && (taskID > MAX_ALLOWABLE_TASKS))

void Scheduler_TicksCounter()
{
	gTickCounter++;
}

u8 Scheduler_AddTask(SchedulerTaskID taskID, void(*fp)())
{
	if (IS_VALID_TASK(taskID)) return TASK_STATUS_FAIL;
	if (fp == NULL) return NULL_FUNCTION_POINTER;

	tcb[gRegisteredTaskCounter].taskID = taskID;
	tcb[gRegisteredTaskCounter].taskCallback = fp;
	tcb[gRegisteredTaskCounter].taskState = WAITING;
	gRegisteredTaskCounter++;
	return TASK_STATUS_PASS;
}

u8 Scheduler_StartTask(SchedulerTaskID taskID, u32 timer)
{
	u8 taskItr = 0;
	if (IS_VALID_TASK(taskID)) return TASK_STATUS_FAIL;
	if (timer < 0) return TASK_STATUS_FAIL;
	cli();
	for (taskItr = 0; taskItr < MAX_ALLOWABLE_TASKS; taskItr++)
	{
		if (tcb[taskItr].taskID == taskID)
		{
			if (tcb[taskItr].taskID == RUNNING)
			{
				sei();
				return TASK_ALREADY_STARTED;
			}
			tcb[taskItr].taskState = RUNNING;
			tcb[taskItr].timer = timer;
		}
	}
	sei();
	return TASK_STATUS_PASS;
}

u8 Scheduler_StopTask(SchedulerTaskID taskID)
{
	u8 taskItr = 0;
	if (IS_VALID_TASK(taskID)) return TASK_STATUS_FAIL;

	cli();
	for (taskItr = 0; taskItr < MAX_ALLOWABLE_TASKS; taskItr++)
	{
		if (tcb[taskItr].taskID == taskID)
		{
			if (tcb[taskItr].taskID == RUNNING)
			{
				sei();
				return TASK_ALREADY_STOPPED;
			}
			tcb[taskItr].taskState = IDLE;
		}
	}
	sei();
	return TASK_STATUS_PASS;
}

void Scheduler_Dispacther()
{
	while (1)
	{
		if (gTickCounter == 0)
		{

		}
	}
}

void Scheduler_Init()
{
	gRegisteredTaskCounter = 0;
	gTickCounter = 0;
	memset(&tcb, 0, sizeof(TaskControlBlock));
}
