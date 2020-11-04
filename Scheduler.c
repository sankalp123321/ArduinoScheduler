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

u8 Scheduler_AddTask(SchedulerTaskID &taskID, void(*fp)())
{
	u8 newTaskIDCounter = 0;
	if (IS_VALID_TASK(taskID)) return TASK_STATUS_FAIL;
	if (fp == NULL) return NULL_FUNCTION_POINTER;

	while (newTaskIDCounter < MAX_ALLOWABLE_TASKS)
	{
		if (tcb[newTaskIDCounter].taskCallback == NULL) 
		{
			tcb[newTaskIDCounter].taskID = newTaskIDCounter;
			tcb[newTaskIDCounter].taskCallback = fp;
			tcb[newTaskIDCounter].taskState = WAITING;
			taskID = newTaskIDCounter;
			return TASK_STATUS_PASS;
		}
		newTaskIDCounter++;
	}
	return TASK_COUNT_EXCEEDED_ERROR;
}

u8 Scheduler_StartTask(SchedulerTaskID taskID, u32 timer)
{
	if (IS_VALID_TASK(taskID)) return TASK_STATUS_FAIL;
	if (timer < 0) return TASK_STATUS_FAIL;
	cli();
	if (tcb[taskID].taskID == taskID)
	{
		if (tcb[taskID].taskID == RUNNING)
		{
			sei();
			return TASK_ALREADY_STARTED;
		}
		tcb[taskID].taskState = RUNNING;
		tcb[taskID].timer = timer;
	}
	sei();
	return TASK_STATUS_PASS;
}

u8 Scheduler_StopTask(SchedulerTaskID taskID)
{
	u8 taskItr = 0;
	if (IS_VALID_TASK(taskID)) return TASK_STATUS_FAIL;

	cli();
	if (tcb[taskID].taskID == taskID)
	{
		if (tcb[taskID].taskID == RUNNING)
		{
			sei();
			return TASK_ALREADY_STOPPED;
		}
		tcb[taskID].taskState = IDLE;
	}
	sei();
	return TASK_STATUS_PASS;
}

void Scheduler_MainLoop()
{
	for (;;)
	{

	}
}

void Scheduler_Dispacther(SchedulerTaskID task)
{
	tcb[task].taskCallback();
}

void Scheduler_Init()
{
	gRegisteredTaskCounter = 0;
	gTickCounter = 0;
	memset(&tcb, 0, sizeof(TaskControlBlock));
}
