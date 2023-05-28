#ifndef _VIRTIO_H__
#define _VIRTIO_H__

#include "../type.h"

#define QUEUE_SIZE 8

#define VIRTIO_CONFIG_S_ACKNOWLEDGE 1
#define VIRTIO_CONFIG_S_DRIVER 2
#define VIRTIO_CONFIG_S_DRIVER_OK 4
#define VIRTIO_CONFIG_S_FEATURES_OK 8

#define VIRTIO_BLK_F_RO 5          /* Disk is read-only */
#define VIRTIO_BLK_F_SCSI 7        /* Supports scsi command passthru */
#define VIRTIO_BLK_F_CONFIG_WCE 11 /* Writeback mode available in config */
#define VIRTIO_BLK_F_MQ 12         /* support more than one vq */
#define VIRTIO_F_ANY_LAYOUT 27
#define VIRTIO_RING_F_INDIRECT_DESC 28
#define VIRTIO_RING_F_EVENT_IDX 29

#define VIRTQ_DESC_F_NEXT 1	/*this marks a buffer as continuing via the next field*/
#define VIRTQ_DESC_F_WRITE 2	/*this marks a buffer as device write-only(otherwise read-only)*/
#define VIRTQ_DESC_F_INDIRECT 4	/*this means the buffer contains a list of buffer descriptors*/

#define VIRTIO_MAGIC_VALUE 0x74726976
#define VIRTIO_DEVICE_VERSION 2
#define VIRTIO_DEVICE_ID 2
#define VIRTIO_VENDER_ID 0x554d4551

struct virtq_desc
{
	/*address (guest-physical)*/
	uint64_t addr;
	/*length*/
	uint32_t len;
	
	uint16_t flags;/*this flags as indicated above*/
	uint16_t next;/*next field enable if flags & VIRTQ_DESC_F_NEXT */
};

	#define VIRTQ_AVAIL_F_NO_INTERRUPT 1	
struct virtq_avail
{
	uint16_t flags;
	uint16_t idx;
	uint16_t ring[QUEUE_SIZE];
	uint16_t unused;
};

#define VIRTIO_BLK_T_IN 0  // read the disk
#define VIRTIO_BLK_T_OUT 1 // write the disk

struct virtq_used_elem/*uint32_t is used for ids for padding reasons*/
{
	uint32_t id;/*index of start of used descriptor chain*/
	uint32_t len;/*total length of the descriptor chain which was used*/
};

#define VIRTQ_USED_F_NO_NOTIFT 1
struct virtq_used
{
	uint16_t flags;
	uint16_t idx;
	struct virtq_used_elem ring[QUEUE_SIZE];
};

struct virtio_blk_req
{
	uint32_t type;
	uint32_t reserved;
	uint64_t sector;
};

void virtio_disk_interrupt_handler();

#endif
