#include "../include/kernel.h"

struct page_table_entry
{
	uint64_t index;
	uint64_t sit;
};
//存储块描述符结构
struct block_desc 
{			/* 16 bytes*/
	void *block;			//该描述符对应的内存页面指针
	struct block_desc *next;	//下一个描述符指针
	void *freeptr;			//指向本块中空闲内存的指针
	uint16_t blocnt;		//引用计数
	uint16_t block_size;		//描述符对应的块大小

};

void _free_block_(unsigned long address) {
	
}

struct _block_dir 
{			/* 8 bytes */
	uint32_t size;			//该存储块的大小
	struct block_desc *list;	//该存储块目录项的块描述符链表指针
};

struct _block_dir bolck_dir[] = {
	{ 8, (struct block_desc *) 0},		// 8 字节长度的内存块链表
	{ 16, (struct block_desc *) 0},		// 16 字节长度的内存块链表
	{ 32, (struct block_desc *) 0},		// 32 字节长度的内存块链表
	{ 64, (struct block_desc *) 0},		// 64 字节长度的内存块链表
	{ 128, (struct block_desc *) 0},	// 128 字节长度的内存块链表
	{ 256, (struct block_desc *) 0},	// 256 字节长度的内存块链表
	{ 512, (struct block_desc *) 0},	// 512 字节长度的内存块链表
	{ 1024, (struct block_desc *) 0},	// 1024 字节长度的内存块链表
	{ 2048, (struct block_desc *) 0},	// 2048 字节长度的内存块链表
	{ 4096, (struct block_desc *) 0},	// 4096 字节长度的内存块链表
	{ 0, (struct block_desc *) 0},		// 队列末尾标记
};
/*
* 这是含有空闲描述符内存块的链表
*/
struct block_desc *free_block_desc = NULL;


/*
* 初始化内存块列表
* 建立空闲块描述符链表，并让free_block_desc 指向第一个空闲块描述符
*/
void Init_block_desc () 
{
	printf("Init block_desc for malloc\n");
	struct block_desc *bdesc,*first;
	int i;
	
	first = bdesc = (struct block_desc *) page_alloc(1);
	if(!bdesc) {
		panic("Out of bolck_buket_desc[]!");
	}
	for( i = PAGE_SIZE/sizeof(struct block_desc); i > 1; i--) {
			bdesc->next = bdesc +  1;
			bdesc = bdesc->next;
	}
/*
*	进行最后处理，为了避免alloc_page无法调用，而子程序被调用引起竞争条件
*/
	bdesc->next = free_block_desc;
	free_block_desc = first;
}

void* _malloc_(int size) 
{
	
	return NULL;
}

void _free(unsigned long address) 
{

	
}
