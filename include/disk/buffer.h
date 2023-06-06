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
	uint32_t block_no;
	uint64_t refcnt;
	#ifndef BLOCK_SIZE
	#define BLOCK_SIZE 512
	#endif
	uint8_t data[BLOCK_SIZE];
	int dirty;
	struct buffer* next;
	struct buffer* last;
};

#endif
