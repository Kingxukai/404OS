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
    disk.desc = (struct virtq_desc*)malloc(4096);
    disk.avail = (struct virtq_avail*)malloc(4096);
    disk.used = (struct virtq_used*)malloc(4096);
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
	// wakeup(&disk.free[0]);
	//sema_signal(&disk.sem_disk);
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

static int alloc_desc()//返回一个整型变量，表示一个描述符的编号
{
	for(int i = 0;i < QUEUE_SIZE;i++)
	{//free[]:该数组用于记录磁盘上每个描述符的使用状态
		if(disk.free[i])//从磁盘中空闲的描述符中查找一个可用于分配的描述符
		{
			disk.free[i] = 0;
			return i;
		}
	}
	return -1;
}

static bool alloc_descs(int *index)
{
	for(int i = 0;i < 3;i++)//尝试三次分配描述符
	{
		index[i] = alloc_desc();//调用另一个函数 alloc_desc 来获取新的描述符编号。
		if(index[i] == -1)//如果 alloc_desc 返回 0 ，说明没有可用的描述符了
		{
			for(int j = 0;j < i;j++)
			{
				free_desc(index[j]);//调用函数 free_desc 来释放已经分配的描述符。
			}
			return 1;
		}
	}
	return 0;
}

void virtio_disk_rw(struct buffer* buf, bool rw)
{
	uint64_t sector = buf->block_no * (BLOCK_SIZE / BUFFER_SIZE);//计算出需要读写的数据所在的扇区的编号
	
	spin_lock(&disk.lock);
	int index[3];//为 virtio 接口的请求、数据、和状态描述符分配三个描述符，并将它们的索引存储在 index 数组中
	while(alloc_descs(index))//0：得到了三个连续的描述符 1：没有得到三个连续的描述符
	{
		spin_unlock(&disk.lock);/*
		睡眠，放弃处理机直到被唤醒--------pending resolution-----------
		spin_lock(&disk.lock);*/
	}
	/*设置 virtio 接口请求描述符中的操作类型、保留位和扇区号。*/
	struct virtio_blk_req* req_buf = &disk.ops[index[0]];
	
	req_buf->type = (rw?VIRTIO_BLK_T_OUT:VIRTIO_BLK_T_IN);//当 rw 为1时，表示需要向磁盘写数据，这时操作类型被设置为 VIRTIO_BLK_T_OUT；否则，表示需要从磁盘读取数据，操作类型被设置为 VIRTIO_BLK_T_IN。
	req_buf->reserved = 0;
	req_buf->sector = sector;
	
	/*设置 virtio 接口请求描述符的虚拟地址、描述符大小、标记位和链表指向下一个描述符的指针。这里将第一个请求描述符连到第二个数据描述符上。*/
	disk.desc[index[0]].addr = (uint64_t)req_buf;
	disk.desc[index[0]].len = sizeof(struct virtio_blk_req);
	disk.desc[index[0]].flags = VIRTQ_DESC_F_NEXT;
	disk.desc[index[0]].next = index[1];
	
	/*设置 virtio 接口数据传输描述符的虚拟地址、描述符大小、标记位和链表指向下一个描述符的指针。这里将第二个数据描述符连到第三个状态描述符上。*/
	disk.desc[index[1]].addr = (uint64_t)buf->data;
	disk.desc[index[1]].len = BLOCK_SIZE;
	disk.desc[index[1]].flags = (rw?0:VIRTQ_DESC_F_WRITE) | VIRTQ_DESC_F_NEXT;//根据 rw 参数确定设备读取 buffer 还是向 buffer 写入数据。
	disk.desc[index[1]].next = index[2];
	
	/*设置 virtio 接口状态描述符的虚拟地址、描述符大小、标记位和链表指向下一个描述符的指针。*/
	disk.info[index[0]].status = 0xff;//这里使用了一个作为请求描述符信息的 status 变量，当 virtio 设备成功完成读写操作时，会在此处写入值 0。
	disk.desc[index[2]].addr = (uint64_t)&disk.info[index[0]].status;
	disk.desc[index[2]].len = 1;
	disk.desc[index[2]].flags = VIRTQ_DESC_F_WRITE;
	disk.desc[index[2]].next = 0;
	
	/*将要读写的缓存块数据对应的 buffer 结构体记录到 virtio 接口请求描述符信息的结构体中。*/
	buf->disk = 1;
	disk.info[index[0]].buf = buf;
	
	/*将分配的请求描述符的下标存放到可用描述符环形队列中，同步内存中的修改。*/
	disk.avail->ring[disk.avail->idx % QUEUE_SIZE] = index[0];
	
	__sync_synchronize();
	
	disk.avail->idx++;//增加可用描述符环形队列的下标
	
	__sync_synchronize();//再次使用这个函数来确保所有对缓存的修改都已经被刷新到内存中
	
	spin_unlock(&disk.lock);
	
	ADDR(QUEUE_NOTIFY) = 0;//向设备发送一个中断通知，告诉它已经有新的可用描述符了
	
	while(buf->disk)//等待设备处理完这个请求，并将 buf->disk 设置为 0 来表示请求已经完成
	{
		if(get_mode())
		{
			sleep();
		}
		/*睡眠，放弃处理机直到被唤醒--------pending resolution-----------
		spin_lock(&disk.lock);*/
	}
	spin_lock(&disk.lock);
	disk.info[index[0]].buf = 0;//清除设备信息描述符中的请求缓存区指针
	free_chain(index[0]);//将此次请求的描述符和其它相关的描述符放回到 free 链表中，以备后续的使用
	
	spin_unlock(&disk.lock);
}

void virtio_disk_interrupt_handler()
{
	spin_lock(&disk.lock);
	
	ADDR(INTERRUPT_ACK) = ADDR(INTERRUPT_STATUS) & 0X3;
	__sync_synchronize();
	
	while(disk.used_idx != disk.used->idx)
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
	wakeup();
	spin_unlock(&disk.lock);
}
