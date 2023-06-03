#include "../include/kernel.h"
#include "../include/sched.h"
#include "../include/usr/unistd.h"
#include "../include/usr/printf.h"
#include "../include/fs/fat32_disk.h"
#include "../include/fs/fat32_mem.h"
#include "../include/fs/fs.h"
#include "../include/fs/param.h"

extern void inode_table_init();

extern struct _superblock fat32_sb;

void Init()
{
	/*other init*/
	printfYellow("user initial...\n");
	
	/*初始化结点表和根结点*/
	inode_table_init();
	fat32_fs_mount(ROOTDEV, &fat32_sb);//挂载到根结点
	current->_cwd = fat32_inode_dup(fat32_sb.root);
  
  int p1;
  
  if((p1 = fork()) == 0)
  {
  	char *argv1[] = {"getpid",0};
  	execve("/getpid",argv1,NULL);
  }
  else
  {
  	printf("here is init process\n");
  	printf("task%d has created\n",p1);
  }
  
	while(1)
	{
	
	}
	panic("unexpected step?!\n");
}
