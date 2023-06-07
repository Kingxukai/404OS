#include "../include/usr/unistd.h"
#include "../include/usr/printf.h"
#include "../include/usr/lib.h"
#include "../include/macro.h"

int test_getpid(int argc,char* argv[])
{
	TEST_START(__func__);
  int pid = getpid();
  assert(pid >= 0);
  printf("getpid success.\npid = %d\n", pid);
  TEST_END(__func__);
	return 0;
}

int test_getppid()
{
	TEST_START(__func__);
  pid_t ppid = getppid();
  if(ppid > 0) printf("  getppid success. ppid : %d\n", ppid);
  else printf("  getppid error.\n");
  TEST_END(__func__);
	return 0;
}

int test_fork()
{
	TEST_START(__func__);
    int cpid, wstatus;
    cpid = fork();
    assert(cpid != -1);
    if(cpid > 0){
	wait(&wstatus);
	printf("  parent process. wstatus:%d\n", wstatus);
    }else{
	printf("  child process.\n");
	exit(0);
    }
 	TEST_END(__func__);
	return 0;
}

