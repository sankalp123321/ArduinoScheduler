#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#define WAITING 1
#define RUNNING 2
#define READY 3
#define IDLE 4

enum {
	TASK_STATUS_FAIL = 0,
	TASK_STATUS_PASS,
	TASK_ALREADY_STARTED,
	TASK_ALREADY_STOPPED,
	NULL_FUNCTION_POINTER,
	TASK_COUNT_EXCEEDED_ERROR
};

#define MAX_ALLOWABLE_TASKS 20

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef unsigned char SchedulerTaskID;

typedef struct {
	SchedulerTaskID taskID;
	u32 timer;
	void (*taskCallback)();
	u32 burstTime;
	u8 taskState;
}TaskControlBlock;

void Scheduler_TicksCounter();
u8 Scheduler_AddTask(SchedulerTaskID taskID, u32 timer, void(*fp)());
u8 Scheduler_StartTask(SchedulerTaskID taskID);
u8 Scheduler_StopTask(SchedulerTaskID taskID);
void Scheduler_Init();
void Scheduler_Dispacther();
void Scheduler_MainLoop();

#endif