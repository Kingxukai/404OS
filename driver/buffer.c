#include "../include/disk/buffer.h"
#include "../include/disk/disk.h"
#include "../include/disk/virtio.h"
#include "../include/lock.h"

//ref xv6

struct virt_disk disk;

static struct
{
	struct spin_lock lock;
	struct buffer buf[BUFFER_NUM];
	struct buffer* head;
}buffer_cache;

#define READ 0
#define WRITE 1

void Init_buffer(void)
{
	printk("Initial buffer...\n");
	struct buffer* buf;
	struct buffer* last_buf = buffer_cache.head = &buffer_cache.buf[0];
	last_buf->last = NULL;
	for(buf = &buffer_cache.buf[1]; buf <= &buffer_cache.buf[BUFFER_NUM - 1]; last_buf = buf, buf++)
	{
		last_buf->next = buf;
		buf->last = last_buf;
		buf->next = NULL;
	}
}

static struct buffer* bget(uint8_t dev, uint8_t block_no)
{
	spin_lock(&buffer_cache.lock);
	
	struct buffer* buf;
	
	for(buf = &buffer_cache.buf; buf < &buffer_cache.buf[BUFFER_NUM - 1]; buf++)//遍历整个块缓存，寻找给定设备和块号相应的块。
	{
		if(buf->dev == dev && buf->block_no == block_no)//如果找到了相应块，则将该块的引用计数加 1，并使用 spin_unlock() 解锁块缓存锁，返回该块的指针。
		{	
			buf->refcnt++;
			spin_unlock(&buffer_cache.lock);
			return buf;
		}
	}
	
	for(buf = &buffer_cache.buf[BUFFER_NUM - 1]; buf >= &buffer_cache.buf[0]; buf--)//如果在块缓存中找不到相应块，则再次遍历整个块缓存
	{
		if(buf->refcnt == 0)//寻找引用计数为 0 的块
		{//将该块的设备、块号、有效性等属性设置为给定的设备、块号、无效（valid=0），将引用计数设置为 1，并使用 spin_unlock() 解锁块缓存锁，返回该块的指针。
			buf->dev = dev;
			buf->block_no = block_no;
			buf->valid = 0;
			buf->refcnt++;
			spin_unlock(&buffer_cache.lock);
			return buf;
		}
	}
	panic("no free buffer to get\n");
}

struct buffer* bread(uint8_t dev, uint8_t block_no)
{
	struct buffer* buf = bget(dev,block_no);//调用buffer_get()来获取一个struct buffer*的指针
	if(!buf->valid)//如果该块是新获取的
	{
		disk_rw(buf, READ);//从磁盘中读入该块
		buf->valid = 1;
		buf->dirty = 0;
	}
	return buf;
}

void bwrite(struct buffer* buf)
{
	buf->dirty = 1;
}

void brelse(struct buffer* buf) {
    // if (!holdingsleep(&b->lock))
    //     panic("brelse");
    if (buf->dirty == 1) //buf的数据是脏数据，需要写回磁盘
    {
        virtio_disk_rw(buf, WRITE);
        buf->dirty = 0;//现在不是脏数据了
    }
    
    spin_lock(&buffer_cache.lock);
    
    if(buf->refcnt == 0)
    {
    	/*从LRU链表中删除该buf*/
    	struct buffer* temp = buf->last;
    	temp->next = buf->next;
    	
    	/*加入链表头，可能再次被使用*/
    	struct buffer* head = buffer_cache.head;
    	head->last = buf;//buf<-head
    	buf->next = head;//buf->head
    	head = buf;//head = buf
    	head->last = NULL;//NULL<-head
    }

    spin_unlock(&buffer_cache.lock);
}

int bpin(struct buffer *buf)
{
    int ret = buf->refcnt;
    return ret;
}

int bunpin(struct buffer *buf) {
    int ret = buf->refcnt;
    return ret;
}
