#ifndef _SYS_H__
#define _SYS_H__

#include "type.h"

extern int sys_gethid();		//just like syscall format in linux

sys_func sys_call_table[] = {//sys_func defined in include/type.h
sys_gethid									//0
};

#endif
