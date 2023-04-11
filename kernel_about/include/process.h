#ifndef _PROCESS_H__
#define _PROCESS_H__

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

struct PCB
{
	u16 pid;				//process id
	uc16 father_id;	
	u16 state;				//process state
	u64 start_time;	//start time
	u64 time;				//time of existing in system
	u16 priority;
	u16 counter;
	struct reg context;
};

struct reg {
	reg64 ra;
	reg64 sp;
	reg64 gp;
	reg64 tp;
	reg64 t0;
	reg64 t1;
	reg64 t2;
	reg64 s0;
	reg64 s1;
	reg64 a0;
	reg64 a1;
	reg64 a2;
	reg64 a3;
	reg64 a4;
	reg64 a5;
	reg64 a6;
	reg64 a7;
	reg64 s2;
	reg64 s3;
	reg64 s4;
	reg64 s5;
	reg64 s6;
	reg64 s7;
	reg64 s8;
	reg64 s9;
	reg64 s10;
	reg64 s11;
	reg64 t3;
	reg64 t4;
	reg64 t5;
	reg64 t6;
};

#define INIT_TASK \
{
0,\							//pid = 0
0,\	
TASK_READY,\		//state = TASK_READY
jiffies,\
0,\							//time = 0
LOW,\						//priority = LOW
LOW,\						//counter = priority
{\
	(reg64)task0,\//point to task0
	(reg64)&task_stack[0],\
},\
}

struct PCB *task_struct[MAX_TASK];
struct PCB *current;

#endif
