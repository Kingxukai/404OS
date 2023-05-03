#ifndef _SCHED_H__
#define _SCHED_H__

#include "platform.h"
#include "kernel.h"
#include "type.h"

#define TASK_CREATE 0		//process state value
#define TASK_RUNNING 1
#define TASK_READY 2
#define TASK_WAIT 3
#define TASK_STOP 4

#define TOP 3	//priority value
#define MID 2
#define LOW 1

#define MAX_TASK 64
#define STACK_SIZE 1024

void schedule();
pid_t do_exit();
void Init_sched();
extern void task0();

struct task_struct *TASK[MAX_TASK];
struct task_struct *current;
uint16_t task_stack[MAX_TASK][STACK_SIZE];

extern pid_t NEW_PID;

struct reg {
	reg64_t ra;
	reg64_t sp;
	reg64_t gp;
	reg64_t tp;
	reg64_t t0;
	reg64_t t1;
	reg64_t t2;
	reg64_t s0;
	reg64_t s1;
	reg64_t a0;
	reg64_t a1;
	reg64_t a2;
	reg64_t a3;
	reg64_t a4;
	reg64_t a5;
	reg64_t a6;
	reg64_t a7;
	reg64_t s2;
	reg64_t s3;
	reg64_t s4;
	reg64_t s5;
	reg64_t s6;
	reg64_t s7;
	reg64_t s8;
	reg64_t s9;
	reg64_t s10;
	reg64_t s11;
	reg64_t t3;
	reg64_t t4;
	reg64_t t5;
	reg64_t t6;
	
	reg64_t epc;//to save the pc the task can switch to
};

struct task_struct
{
	pid_t pid;				//process id
	pid_t father_pid;	
	int16_t state;				//process state
	uint64_t start_time;	//start time
	uint64_t time;				//time of existing in system
	int16_t priority;
	int16_t counter;
	bool in_Queue;				//if in queue or not
	int8_t order;				//the order of queue
	struct reg context;
};

#define INIT_TASK \
{ \
/*pid*/									   0, \
/*father pid*/    				 0, \
/*state*/			    				 TASK_READY, \
/*start time*/    				 0, \
/*running time*/  				 0, \
/*priority*/	    				 LOW, \
/*counter*/		    				 LOW, \
/*in_Queue*/							 0, \
/*order*/                  0, \
/*register initialization*/{ \
/*return address of function*/0, \
/*task stack pointer*/				(reg64_t)&task_stack[0][STACK_SIZE-1], \
/*remain 31+1-2*/							0,0,0,0,0,0,0, \
/*=30 registers*/							0,0,0,0,0,0,0, \
															0,0,0,0,0,0,0, \
															0,0,0,0,0,0,0, \
															0, \
/*return address of task*/		(reg64_t)task0 \
		  										 } \
}

struct Queue
{
	pid_t pid;
	struct task_struct* task;
	struct Queue *next;
};

struct Queue_head
{
	struct Queue *next;
};

#define COUNTER(order) (2 + 6 * order)				//counter of each qeueu

#endif
