#ifndef _PARAM_H__
#define _PARAM_H__

#define NCPU 3                    // maximum number of CPUs
#define NOFILE 128                // open files per process
#define NFILE 100                 // open files per system
#define NINODE 50                 // maximum number of active i-nodes
#define NDEV 10                   // maximum major device number
#define ROOTDEV 1                 // device number of file system root disk
#define MAXARG 32                 // max exec arguments
#define MAXENV 32                 // max exec environment arguments
#define MAXOPBLOCKS 10            // max # of blocks any FS op writes
#define LOGSIZE (MAXOPBLOCKS * 3) // max data blocks in on-disk log
#define NBUF (MAXOPBLOCKS * 3)    // size of disk block cache
#define FSSIZE 2000               // size of file system in blocks
#define MAXPATH 128               // maximum file path name

typedef unsigned short WORD;
typedef unsigned int DWORD;

// remember return to fat32_file.h
struct devsw {
    int (*read)(int, uint64_t, int);
    int (*write)(int, uint64_t, int);
};

extern struct devsw devsw[];

// // in xv6
// #define MAXPATH 128 // maximum file path name
#endif // __PARAM_H__
