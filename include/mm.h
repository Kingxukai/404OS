#ifndef _MM_H_
#define _MM_H_

#define PAGE_SIZE 4096
 
 
struct page_table_entry
{
	uint64_t index;
	uint64_t sit;
};

//存储块描述符结构
typedef struct block_desc 
{			/* 16 bytes*/
	void *block;			//该描述符对应的内存页面指针
	struct block_desc *next;	//下一个描述符指针
	void *freeptr;			//指向本块中空闲内存的指针
	uint16_t blocnt;		//引用计数
	uint16_t block_size;		//描述符对应的块大小

}*BDESC,Bdesc;

typedef struct _block_dir 
{			/* 8 bytes */
	uint32_t size;			//该存储块的大小
	struct block_desc *list;	//该存储块目录项的块描述符链表指针
}*BDIR,Bdir;



#endif
