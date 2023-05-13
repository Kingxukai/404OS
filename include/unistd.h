#ifndef _UNISTD_H__
#define _UNISTD_H__
#include "type.h"

uint64_t gethid();	//0
pid_t getpid();	//1
pid_t getppid();	//2
pid_t fork(); //3
int execve(const char *filepath,char * const * argv,char * const * envp);//4
pid_t exit();	//5
pid_t waitpid(pid_t pid,uint64_t* stat_addr,int options);	//6
#endif
