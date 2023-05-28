#include "../include/disk/virtio.h"
#include "../include/platform.h"
#include "../include/disk/disk.h"
#include "../include/usr/lib.h"

//ref xv6

extern struct virt_disk disk;

void Init_virtio(void) {
		printk("Initial virtio...\n");
    uint32_t status = 0;

    disk.lock.state = 0;

		printk("\tMAGIC_VALUE:0x%x\n",ADDR(MAGIC_VALUE));
    printk("\tDEVICE_VERSION:%d\n",ADDR(DEVICE_VERSION));
    printk("\tDEVICE_ID:%d\n",ADDR(DEVICE_ID));
    printk("\tVENDOR_ID:0x%x\n",ADDR(VENDOR_ID));
    if (ADDR(MAGIC_VALUE) != VIRTIO_MAGIC_VALUE || ADDR(DEVICE_VERSION) != VIRTIO_DEVICE_VERSION || ADDR(DEVICE_ID) != VIRTIO_DEVICE_ID || ADDR(VENDOR_ID) != VIRTIO_VENDER_ID) 
    {
        panic("could not find virtio disk\n");
    }

    // reset device
    ADDR(DEVICE_STATUS) = status;

    // set ACKNOWLEDGE status bit
    status |= VIRTIO_CONFIG_S_ACKNOWLEDGE;
    ADDR(DEVICE_STATUS) = status;

    // set DRIVER status bit
    status |= VIRTIO_CONFIG_S_DRIVER;
    ADDR(DEVICE_STATUS) = status;

    // negotiate features
    uint64_t features = ADDR(DEVICE_FEATURES);
    features &= ~(1 << VIRTIO_BLK_F_RO);
    features &= ~(1 << VIRTIO_BLK_F_SCSI);
    features &= ~(1 << VIRTIO_BLK_F_CONFIG_WCE);
    features &= ~(1 << VIRTIO_BLK_F_MQ);
    features &= ~(1 << VIRTIO_F_ANY_LAYOUT);
    features &= ~(1 << VIRTIO_RING_F_EVENT_IDX);
    features &= ~(1 << VIRTIO_RING_F_INDIRECT_DESC);
    ADDR(DRIVER_FEATURES) = features;

    // tell device that feature negotiation is complete.
    status |= VIRTIO_CONFIG_S_FEATURES_OK;
    ADDR(DEVICE_STATUS) = status;

    // re-read status to ensure FEATURES_OK is set.
    status = ADDR(DEVICE_STATUS);
    if (!(status & VIRTIO_CONFIG_S_FEATURES_OK))
        panic("virtio disk FEATURES_OK unset\n");

    // initialize queue 0.
    ADDR(QUEUE_SEL) = 0;

    // ensure queue 0 is not in use.
    if (ADDR(QUEUE_READY))
        panic("virtio disk should not be ready\n");

    // check maximum queue size.
    uint32_t max = ADDR(QUEUE_NUM_MAX);
    if (max == 0)
        panic("virtio disk has no queue 0\n");
    if (max < QUEUE_SIZE)
        panic("virtio disk max queue too short\n");

    // allocate and zero queue memory.
    disk.desc = (struct virtq_desc*)malloc(sizeof(struct virtq_desc));
    disk.avail = (struct virtq_avail*)malloc(sizeof(struct virtq_avail));
    disk.used = (struct virtq_used*)malloc(sizeof(struct virtq_used));
    if (!disk.desc || !disk.avail || !disk.used)
        panic("virtio disk malloc error\n");
        
    #ifndef PAGE_SIZE
    #define PAGE_SIZE 4096
    #endif
    memset(disk.desc, 0, PAGE_SIZE);
    memset(disk.avail, 0, PAGE_SIZE);
    memset(disk.used, 0, PAGE_SIZE);

    // set queue size.
    ADDR(QUEUE_NUM) = QUEUE_SIZE;

    // write physical addresses.
    ADDR(QUEUE_DESC_LOW) = (uint64_t)disk.desc;
    ADDR(QUEUE_DESC_HIGH) = (uint64_t)disk.desc >> 32;
    ADDR(QUEUE_DRIVER_LOW) = (uint64_t)disk.avail;
    ADDR(QUEUE_DRIVER_HIGH) = (uint64_t)disk.avail >> 32;
    ADDR(QUEUE_DEVICE_LOW) = (uint64_t)disk.used;
    ADDR(QUEUE_DEVICE_HIGH) = (uint64_t)disk.used >> 32;

    // queue is ready.
    ADDR(QUEUE_READY) = 0x1;

    // all NUM descriptors start out unused.
    for (int i = 0; i < QUEUE_SIZE; i++)
        disk.free[i] = 1;

    // tell device we're completely ready.
    status |= VIRTIO_CONFIG_S_DRIVER_OK;
    ADDR(DEVICE_STATUS) = status;

    // plic.c and trap.c arrange for interrupts from VIRTIO0_IRQ.
}

static void free_desc(int i)
{
	if(i > QUEUE_SIZE)
		panic("free descriptor overflow\n");
	if(disk.free[i])
		panic("free descriptor error\n");
	disk.desc[i].addr = 0;
	disk.desc[i].len = 0;
	disk.desc[i].flags = 0;
	disk.desc[i].next = 0;
	disk.free[i] = 1;
}

static void free_chain(int i)
{
	while(1)
	{
		int flag = disk.desc[i].flags;
		int next = disk.desc[i].next;
		free_desc(i);
		if(flag & VIRTQ_DESC_F_NEXT)
			i  = next;
		else
			return;
	}
}

static int alloc_desc()
{
	for(int i = 0;i < QUEUE_SIZE;i++)
	{
		if(disk.free[i])
		{
			disk.free[i] = 0;
			return i;
		}
	}
	return 0;
}

static bool alloc_descs(int *index)
{
	for(int i = 0;i < 3;i++)
	{
		index[i] = alloc_desc();
		if(!index[i])
		{
			for(int j = 0;j < i;j++)
			{
				free_desc(index[j]);
			}
			return 1;
		}
	}
	return 0;
}

void virtio_disk_rw(struct buffer* buf, bool rw)
{
	uint64_t sector = buf->block_no * (BUFFER_SIZE / BLOCK_SIZE);
	
	spin_lock(&disk.lock);
	int index[3];
	while(alloc_descs(index))
	{
		spin_unlock(&disk.lock);
		/*...*/
		spin_lock(&disk.lock);
	}
	
	struct virtio_blk_req* req_buf = &disk.ops[index[0]];
	
	req_buf->type = (rw?VIRTIO_BLK_T_OUT:VIRTIO_BLK_T_IN);
	req_buf->reserved = 0;
	req_buf->sector = sector;
	
	disk.desc[index[0]].addr = (uint64_t)req_buf;
	disk.desc[index[0]].len = sizeof(struct virtio_blk_req);
	disk.desc[index[0]].flags = VIRTQ_DESC_F_NEXT;
	disk.desc[index[0]].next = index[1];
	
	disk.desc[index[1]].addr = (uint64_t)buf->data;
	disk.desc[index[1]].len = BUFFER_SIZE;
	disk.desc[index[1]].flags = (rw?0:VIRTQ_DESC_F_WRITE) | VIRTQ_DESC_F_NEXT;
	disk.desc[index[1]].next = index[2];
	
	disk.info[index[0]].status = 0xff;
	disk.desc[index[2]].addr = (uint64_t)&disk.info[index[0]].status;
	disk.desc[index[2]].len = 1;
	disk.desc[index[2]].flags = VIRTQ_DESC_F_WRITE;
	disk.desc[index[2]].next = 0;
	
	buf->disk = 1;
	disk.info[index[0]].buf = buf;
	
	disk.avail->ring[disk.avail->idx % QUEUE_SIZE] = index[0];
	
	__sync_synchronize();
	
	disk.avail->idx++;
	
	__sync_synchronize();
	
	ADDR(QUEUE_NOTIFY) = 0;
	
	while(buf->disk)
	{
		spin_unlock(&disk.lock);
		/*...*/
		spin_lock(&disk.lock);
	}
	disk.info[index[0]].buf = 0;
	free_chain(index[0]);
}

void virtio_disk_interrupt_handler()
{
	spin_lock(&disk.lock);
	
	ADDR(INTERRUPT_ACK) = ADDR(INTERRUPT_STATUS) & 0X3;
	__sync_synchronize();
	
	while(disk.used_idx != disk.used_idx)
	{
		__sync_synchronize();
		int id = disk.used->ring[disk.used_idx % QUEUE_SIZE].id;
		
		if(disk.info[id].status != 0)
		{
			panic("disk interrupt status\n");
		}
		
		struct buffer* buf = disk.info[id].buf;
		buf->disk = 0;
		
		disk.used_idx++;
	}
	spin_unlock(&disk.lock);
}
