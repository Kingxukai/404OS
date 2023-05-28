#ifndef _BUFFER_H__
#define _BUFFER_H__

#include "../type.h"

#define BUFFER_SIZE 512
#define BUFFER_NUM 30

struct buffer
{
	uint64_t buffer_state;
	int valid;
	int disk;
	uint32_t dev;
	uint8_t block_no;
	uint64_t refcnt;
	uint8_t data[BUFFER_SIZE];
	int dirty;
	struct buffer* next;
	struct buffer* last;
};

#endif
