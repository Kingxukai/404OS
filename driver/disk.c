#include "../include/disk/buffer.h"
#include "../include/disk/disk.h"
#include "../include/disk/virtio.h"
#include "../include/lock.h"

struct virt_disk disk;

static struct
{
	struct spin_lock lock;
	struct buffer buf[BUFFER_NUM];
}buffer_cache;

#define READ 0
#define WRITE 1

void Init_buffer(void)
{
	printk("Initial buffer...\n");
	struct buffer* buf;
	for(buf = &buffer_cache.buf; buf < &buffer_cache.buf[BUFFER_NUM - 1]; buf++)
	{
		buf->buffer_state = 0;
		buf->valid = 0;
		buf->disk = 0;
		buf->dev = 0;
		buf->block_no = 0;
		buf->refcnt = 0;
		buf->dirty = 0;
	}
}

struct buffer* buffer_get(uint8_t dev, uint8_t block_no)
{
	spin_lock(&buffer_cache.lock);
	
	struct buffer* buf;
	
	for(buf = &buffer_cache.buf; buf < &buffer_cache.buf[BUFFER_NUM - 1]; buf++)
	{
		if(buf->dev == dev && buf->block_no == block_no)
		{	
			buf->refcnt++;
			spin_unlock(&buffer_cache.lock);
			return buf;
		}
	}
	
	for(buf = &buffer_cache.buf[BUFFER_NUM - 1]; buf >= &buffer_cache.buf[0]; buf--)
	{
		if(buf->refcnt == 0)
		{
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

struct buffer* buffer_read(uint8_t dev, uint8_t block_no)
{
	struct buffer* buf = buffer_get(dev,block_no);
	if(!buf->valid)
	{
		disk_rw(buf, READ);
		buf->valid = 1;
		buf->dirty = 0;
	}
	return buf;
}

void buffer_write(struct buffer* buf)
{
	buf->dirty = 1;
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
