#include "../include/unistd.h"
#include "../include/printf.h"
#include "../include/lib.h"
typedef struct _node {
	struct node_ *next;
	char ch;
	int in;
	long lo;
	short sh;
}*NODE,Node;

void task2()
{
	printf("task%d running\n",getpid());
	exit();
}

void task3()
{
	int t = 5;
	while(t--)
	{
		printf("task%d running\n",getpid());
	}
	exit();
}

void task4()
{
	printf("test\n");
	NODE node = (NODE)malloc(sizeof(struct _node));
	node->next = node;
	node->sh = 10;
	node->ch = 't';
	node->in = 1;
	node->lo = 1000000000000;
	printf("short:%d ptr:%x \n",node->sh,node->next);
	printf("int:%d char:%c long:%ld \n",node->in,node->ch,node->lo);
	free(node);
	printf("after short:%d ptr:%x \n",node->sh,node->next);
	printf("int:%d char:%c long:%ld \n",node->in,node->ch,node->lo);
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
	while(1)
	{
	
	}
}

void task1()
{
	pid_t pid2,pid3,pid4;
	if((pid2 = fork()) == 0)
	{
		execve(task2,NULL,NULL);
	}
	else if((pid3 = fork()) == 0)
	{
		execve(task3,NULL,NULL);
	}
	else if((pid4 = fork()) == 0)
	{
		execve(task4,NULL,NULL);
	}
	else
	{
		printf("task%d has created\n",pid2);
		printf("task%d has created\n",pid3);
		printf("task%d has created\n",pid4);
		//wait();
		printf("here is father process\n");
		printf("task%d is running\n",getpid());
	}
	while(1)
	{
	
	}
}
