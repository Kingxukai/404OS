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
	u8 state;				//process state
	u64 time;				//time of existing in system
	u8 priority;
	u8 counter;
	struct reg context;
};

struct reg {
	/* ignore x0 */
	reg32 ra;
	reg32 sp;
	reg32 gp;
	reg32 tp;
	reg32 t0;
	reg32 t1;
	reg32 t2;
	reg32 s0;
	reg32 s1;
	reg32 a0;
	reg32 a1;
	reg32 a2;
	reg32 a3;
	reg32 a4;
	reg32 a5;
	reg32 a6;
	reg32 a7;
	reg32 s2;
	reg32 s3;
	reg32 s4;
	reg32 s5;
	reg32 s6;
	reg32 s7;
	reg32 s8;
	reg32 s9;
	reg32 s10;
	reg32 s11;
	reg32 t3;
	reg32 t4;
	reg32 t5;
	reg32 t6;
};

#define INIT_TASK \
{
0,\							//pid = 0
0,\	
TASK_READY,\		//state = TASK_READY
0,\							//time = 0
LOW,\						//priority = LOW
LOW,\						//counter = priority
{\
	(reg32)task0,\//point to task0
	(reg32)&task_stack[0],\
},\
}

struct PCB *task_struct[MAX_TASK];
struct PCB *current;
