#ifndef _DISK_H__
#define _DISK_H__

#include "buffer.h"
#include "virtio.h"
#include "../lock.h"

#define BLOCK_SIZE 512

#define disk_rw(buf,rw) virtio_disk_rw(buf,rw)

typedef struct virtq_desc q_desc;
typedef struct virtq_avail q_avail;
typedef struct virtq_used q_used;
typedef struct virtq_used_elem q_used_elem;
typedef struct virtq_blk_config q_blk_config;
typedef struct virtio_blk_req q_blk_req;

struct virt_disk
{
	q_desc* desc;
	q_avail* avail;
	q_used* used;
	
	uint8_t free[QUEUE_SIZE];
	uint16_t used_idx;
	
	struct
	{
		struct buffer* buf;
		uint8_t status;
	}info[QUEUE_SIZE];
	
	q_blk_req ops[QUEUE_SIZE];
	
	struct spin_lock lock;
};

void Init_virtio();
void Init_buffer(void);

#endif
