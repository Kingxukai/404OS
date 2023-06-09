#include "../include/kernel.h"
#include "../include/sched.h"
#include "../include/usr/unistd.h"
#include "../include/usr/printf.h"
#include "../include/fs/fat32_disk.h"
#include "../include/fs/fat32_mem.h"
#include "../include/fs/fs.h"
#include "../include/fs/param.h"
#include "../include/fs/stat.h"

extern int test_getpid();
extern int test_getppid();
extern int test_fork();

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
  
  //fat32_inode_create("/getpid",T_FILE, 1,2);
  
  int n = 3;
  int pid[n];
  
	if((pid[0] = fork()) == 0)
  {
  	char *argv[] = {test_fork, NULL};
  	if(execve(NULL, argv, NULL) == -1 )
  	{
  		printfRed("error in execving %s\n",argv[0]);
  	};
  }
  else if((pid[1] = fork()) == 0)
  {
  	char *argv[] = {test_getppid, NULL};
  	if(execve(NULL, argv, NULL) == -1 )
  	{
  		printfRed("error in execving %s\n",argv[0]);
  	};
  }
  else if((pid[2] = fork()) == 0)
  {
  	char *argv[] = {test_getpid, NULL};
  	if(execve(NULL, argv, NULL) == -1 )
  	{
  		printfRed("error in execving %s\n",argv[0]);
  	};
  }
  else
  {
  	printf("here is init process\n");
  	for(int i = 0;i < n;i++)
  	{
  		printf("task%d has created\n",pid[i]);
  	}
  	int error = 0;
  	waitpid(pid[0],NULL,0);
  	waitpid(pid[1],NULL,0);
  	waitpid(pid[2],NULL,0);
  	waitpid(5,NULL,0);
  	
  	shutdown();//must shutdown while travel all test watchpoint
  }
  
	while(1)
	{
	
	}
	panic("unexpected step?!\n");
}
