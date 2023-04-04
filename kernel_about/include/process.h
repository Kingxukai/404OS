#define TASK_CREATE 0		//process state value
#define TASK_RUNNING 1
#define TASK_READY 2
#define TASK_WAIT 3
#define TASK_STOP 4

#define TOP 3	//priority value
#define MID 2
#define LOW 1

#define MAX_TASK 1024	* 8

struct PCB
{
	u16 pid;				//process id
	uc16 father_id;	
	u8 state;				//process state
	u64 time;				//time of existing in system
	u8 priority;
	u8 counter;
};

#define INIT_TASK \
{
0,\							//pid = 0
0,\	
TASK_READY,\		//state = TASK_READY
0,\							//time = 0
LOW,\						//priority = LOW
LOW,\						//counter = priority
}

struct PCB *task_struct[MAX_TASK];
struct PCB *current;
