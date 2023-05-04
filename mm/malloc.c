#include "../include/kernel.h"

 Bdir block_dir[] = {
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
BDESC free_block_desc = NULL;


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
/*
* 内存分配函数，参数size--请求分配的内存块长度
*/
void* _malloc_(uint32_t length) 
{
	 BDIR bdir = block_dir;
	 BDESC bdesc;
	void *retval; 
	/*
	*检索block_dir查找合适大小的内存块描述块列表
	*/
	
	for( bdir = block_dir ;  bdir->size ; bdir) 
				if( bdir->size >= length) 
					break;
	//若检索不到合适大小的块,则输出错误,并暂停程序
	if(!bdir->size) {
		printf("malloc called with a Unsatisfied requirements : (%d)! \n",length);

		panic("malloc : bad arg");

	}
	//在块链表中检索合适的空闲块
	for( bdesc = bdir->list; bdesc; bdesc = bdesc->next ) 
			if(bdesc->freeptr) 
				break;
	if(!bdesc) {
		char *cp;
		int i;
		/*
		*若free_block_desc为空表示第一次调用程序,则初始化free_block_desc
		*此时free_bloc_desc指向空块描述符
		*/
		if(!free_block_desc) 
			Init_block_desc();
		//取free_block_desc指向的空描述符,并让free_block_desc指向下一个空闲描述符
		bdesc = free_block_desc;
		free_block_desc = bdesc->next;
		/*
			初始化该块描述符,置引用数为0,块的大小对应块目录的大小.申请一空闲页
			令描述符中的page指向该页面,freeptr也指向页面首地址,此时为全空闲
		*/
		bdesc->blocnt = 0;
		bdesc->block_size = bdir->size;
		bdesc->block  = bdesc->freeptr = (void*)(cp  =  (char *)page_alloc(1));
		if(!cp) {
			panic("out of memory in malloc ");
		}
		/*
			在该空闲内存页中建立空闲内存对象链表
			以块目录大小为对象长度，对该内存页进行划分，并设置每个对象开始的前四个字节为指向下一个对象的指针
		*/
		for( i = PAGE_SIZE/bdesc->block_size; i > 1; i --) {
			* ((char**) cp) = cp + bdir->size;
			cp += bdir->size;
		}
		/*
			令最后一个对象指向空，让描述符的下一个指针指向链表首，链表指向描述符首地址
			将描述符链入到block链表中
		*/
		*((char**) cp) = NULL;
		bdesc->next = bdir->list;
		bdir->list = bdesc;
	}
	/*
		令返回的指针retval指向空闲对象，并令描述符的空闲指针指向空闲对象的内部的下一个空闲对象
		描述符引用加1
	*/
	retval = (void*)bdesc->freeptr;
	bdesc->freeptr = *( (void**) retval);
	bdesc->blocnt++;
	return retval;
}

void _free(unsigned long address) 
{

	
}

void _free_block_(unsigned long address) {
	return ;
}
