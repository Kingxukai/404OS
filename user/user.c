#include "../include/unistd.h"
#include "../include/printf.h"

typedef struct _node {
	int *next;
	char ch;
	int in;
	long lo;
	short sh;
}*NODE,Node;

void task1()
{
	printf("task%d running\n",getpid());
	exit();
}

void task2()
{
	int t = 5;
	while(t--)
	{
		printf("task%d running\n",getpid());
	}
	exit();
}

void task3()
{
	printf("test\n");
	NODE node = (NODE)malloc(sizeof(struct _node));
	node->next = NULL;
	node->sh = 10;
	node->ch = 't';
	node->in = 1;
	node->lo = 1000000000000;
	printf("int:%d char:%c long:%ld short:%d ptsr:%p\n",node->in,node->ch,node->lo,node->sh,node->next);
	int *a = (int*) malloc(sizeof(int));
	*a = 100;
	printf("the int type index is : %d\n",*a);
	char *b = (char*)malloc(sizeof(char));
	*b = 'a';
	printf("the int type index is : %c\n",*b);
	long *c = (long*)malloc(sizeof(long));
	*c = 1000000000000;
	printf("the int type index is : %ld\n",*c);
	void *d = malloc(sizeof(void));
	//*d = 10; 
	short *e = (short*)malloc(sizeof(short));
	*e = 10;
	printf("the int type index is : %d\n",*e);
	
	
	printf("task0 create\n");
	printf("task0 running\n");
	pid_t pid1,pid2;
	if((pid1 = fork()) == 0)
	{
		execve(task1,NULL,NULL);
	}
	else if((pid2 = fork()) == 0)
	{
		execve(task2,NULL,NULL);
	}
	else
	{
		printf("here is father task\n");
		printf("task%d create\n",pid1);
		printf("task%d create\n",pid2);
	}

	printf("task%d running\n",getpid());
	wait();
	printf("task%d running\n",getpid());
}
