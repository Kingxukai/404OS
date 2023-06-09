#ifndef _TYPE_H__
#define _TYPE_H__

typedef unsigned char uint8_t;			//data 8bit
typedef unsigned short uint16_t;		//data 16bit
typedef unsigned int uint32_t;			//data 32bit
typedef unsigned long uint64_t;		//data 64bit

typedef char int8_t;			//data 8bit
typedef short int16_t;		//data 16bit
typedef int int32_t;			//data 32bit
typedef long int64_t;		//data 64bit

typedef uint8_t reg8_t; 							//register 8bit
typedef uint16_t reg16_t;					//register 16bit
typedef uint32_t reg32_t;							//register 32bit
typedef uint64_t reg64_t;						 //register 64bit

typedef int pid_t;						//pid type

typedef _Bool bool;								//bool type

typedef reg64_t (*sys_func)();				//sys_call function

typedef uint32_t sigset_t;				//32bit siganl bit map

typedef int64_t ssize_t;

typedef long time_t;

#ifndef NULL
#define NULL (void *)(0)
#endif

#endif
