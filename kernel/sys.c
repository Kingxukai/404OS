#include "../include/sys.h"
#include "../include/sched.h"
#include "../include/asm/riscv64.h"
#include "../include/type.h"
#include "../include/errno.h"
#include "../include/usr/lib.h"
#include "../include/usr/unistd.h"
#include "../include/platform.h"
#include "../include/fs/fat32_disk.h"
#include "../include/fs/elf.h"

void do_syscall(struct reg *context)										//syscall executing function
{
	reg64_t sys_num = context->a7;
	sys_func fn;
	fn = (sys_func)sys_call_table[sys_num];
	context->a0 = (*fn)(context->a0,context->a1,context->a2,context->a3,context->a4,context->a5);
}

uint64_t sys_gethid()	
{
	return r_tp();
}

pid_t sys_getpid()
{
	return current->pid;
}

pid_t sys_getppid()
{
	return current->father_pid;
}

pid_t sys_fork()
{
	if( find_new_id() >= MAX_TASK )
	{	
		panic("No free PCB_id to request!\n");
	}
	
	return copy_process();
}

int sys_execve(const char *filepath,char * const * argv,char * const * envp)
{
	struct task_struct *p = current;
	struct inode* ip;
	struct elfhdr elf;
	struct proghdr p_header;
	if( (ip = name_to_i(filepath)) == NULL)
	{
		return -1;
	}
	
	fat32_inode_lock(ip);
	
	if (fat32_inode_read(ip, 0, (uint64_t)&elf, 0, sizeof(elf)) != sizeof(elf))
     goto bad;

  if (elf.magic != ELF_MAGIC)
     goto bad;
  
	#define MAX_PROG_HEADERS 64 // 预先设置一个足够大的程序头部数量上限

	uint32_t** allocated_mems = (uint32_t **)malloc(MAX_PROG_HEADERS * sizeof(uint32_t *));
	if (allocated_mems == NULL)
	{
		  goto bad;
	}

	int allocated_count = 0;
	// Load program into memory.
	for (int i = 0, off = elf.ph_off; i < elf.ph_num; i++, off += sizeof(p_header))
	{
		  if (fat32_inode_read(ip, 0, (uint64_t)&p_header, off, sizeof(p_header)) != sizeof(p_header))
		      goto bad;
		  if (p_header.type != ELF_PROG_LOAD)
		      continue;
		  if (p_header.memsz < p_header.filesz)
		      goto bad;
		  if (p_header.vaddr + p_header.memsz < p_header.vaddr)
		      goto bad;
		  if (p_header.vaddr % PAGE_SIZE != 0)
		      goto bad;
		      
		  // Allocate memory using malloc.
		  uint32_t* allocated_mem = (uint32_t *)malloc(p_header.memsz);
		  if (allocated_mem == NULL)
		      goto bad;

		  // Read data from ELF file into allocated memory.
		  if (fat32_inode_read(ip, 0, (uint64_t)allocated_mem, p_header.off, p_header.filesz) != p_header.filesz) 
		  {
		      free(allocated_mem);
		      goto bad;
		  }

		  // Zero out the remaining memory.
		  if (p_header.memsz - p_header.filesz > 0) 
		  {
		      memset((uint8_t *)allocated_mem + p_header.filesz, 0, p_header.memsz - p_header.filesz);
		  }

		  allocated_mems[allocated_count++] = allocated_mem;
		  if (allocated_count >= MAX_PROG_HEADERS)
			{
					panic("huge size of elf,which can't load temporially!!\n");
			}
	}

  
  fat32_inode_unlock_put(ip);
  ip = NULL;
	
	elf.entry = (uint32_t)allocated_mems;

	
	if(argv[0])
	{
		p->context.ra = (reg64_t)exit;//make it over while exit current process
		p->context.sp = (reg64_t)&task_stack[p->pcb_id][STACK_SIZE-1];	
		p->context.gp = 0;
		p->context.tp = 0;
		p->context.t0 = 0;
		p->context.t1 = 0;
		p->context.t2 = 0;
		p->context.s0 = 0;
		p->context.s1 = 0;
		p->context.a0 = (reg64_t)(sizeof(argv) / sizeof(char*));	//transfer the arg to filepath/process and sizeof(argv) is argc
		p->context.a1 = (reg64_t)argv;
		p->context.a2 = 0;
		p->context.a3 = 0;
		p->context.a4 = 0;
		p->context.a5 = 0;
		p->context.a6 = 0;
		p->context.a7 = 0;
		p->context.s2 = 0;
		p->context.s3 = 0;
		p->context.s4 = 0;
		p->context.s5 = 0;
		p->context.s6 = 0;
		p->context.s7 = 0;
		p->context.s8 = 0;
		p->context.s9 = 0;
		p->context.s10 = 0;
		p->context.s11 = 0;
		p->context.t3 = 0;
		p->context.t4 = 0;
		p->context.t5 = 0;
		p->context.t6 = 0;
		p->context.epc = (reg64_t)elf.entry;
		p->context.temp = 0;	
		switch_to(0, &(p->context));
	}
	else
		goto bad;
bad:
	if(ip)
		fat32_inode_unlock_put(ip);
	return -1;
			
}

pid_t sys_exit(int error_code)
{
	return do_exit(error_code);
}

pid_t sys_waitpid(pid_t pid,uint64_t* stat_addr,int options)
{
	bool flag;
	struct task_struct **p;
	int i;
	repeat:
		p = &TASK[MAX_TASK];
		i = MAX_TASK;
		flag = 0;
		while(--i)
		{
			if(!*--p || *p == current)continue;
			if((*p)->father_pid != current->pid)continue;
			if(pid > 0)
			{
				if(pid != (*p)->pid)continue;
				if((*p)->state == TASK_ZOMBINE)
				{
					current->time += (*p)->time;
					release(*p);
					return (*p)->pid;
				}
				else if((*p)->state == TASK_STOP)
				{
					return (*p)->pid;
				}
				else flag = 1;
			}
		}
		if(flag)
		{
			current->state = TASK_WAIT;
			current->in_Queue = 0;
			
			schedule();
			
			if(!(current->signal &= (~SIG_CHLD)))
				goto repeat;
			else
				{
					return -EINTR;
				}
		}
	return -ECHILD;
}

int sys_shutdown()
{
	ADDR(SYS_CTL_ADDR) = SYS_CTL(SYS_PASS);
}
