#ifndef _UNISTD_H__
#define _UNISTD_H__
#include "../type.h"

uint64_t gethid();	//0
int getpid();	//1
int getppid();	//2
int fork(); //3
int execve(const char *filepath,char * const * argv,char * const * envp);//4
int exit(int error_code);	//5
int waitpid(int pid,unsigned long* stat_addr,int options);	//6
int shutdown();	//7
#endif
