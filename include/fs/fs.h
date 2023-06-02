#ifndef _FS_H__
#define _FS_H__

#include "../type.h"
#include "param.h"
#include "../lock.h"
#include "fat32_mem.h"

struct kstat;
extern struct ftable _ftable;

#define TODO() 0

typedef enum { FD_NONE,
               FD_PIPE,
               FD_INODE,
               FD_DEVICE } type_t;

union file_type {
    struct pipe *f_pipe;    // FD_PIPE
    struct inode *f_inode; // FDINODE and FD_DEVICE
};

typedef enum {
    FAT32=1,
    EXT2,
} fs_t;

struct _superblock {
    //struct semaphore sem; /* binary semaphore */
    uint8_t s_dev;          // device number

    uint32_t s_blocksize;       // 逻辑块的数量
    uint32_t sectors_per_block; // 每个逻辑块的扇区个数
    uint32_t cluster_size;        // size of a cluster

    // uint32_t s_blocksize_bits;
    uint32_t n_sectors;   // Number of sectors
    uint32_t sector_size; // size of a sector

    struct super_operations *s_op;//一个指向指向超级块操作（super_operations）的指针，表示文件系统可以支持的操作集合
    struct inode *s_mount;//一个指向挂载点的 inode 对象
    struct inode *root;//一个指向超级块关联的跟节点的 inode 对象。

    union {
        struct fat32_sb_info fat32_sb_info;
        // struct xv6fs_sb_info xv6fs_sb;
        // void *generic_sbp;
    };
};

// abstarct everything in memory
struct file {
    type_t f_type;
    uint16_t f_mode;
    uint32_t f_pos;
    uint16_t f_flags;
    uint16_t f_count;
    short f_major; // FD_DEVICE

    int f_owner;                        /* pid or -pgrp where SIGIO should be sent */
    union file_type f_tp;               
    const struct file_operations *f_op; // don't use pointer (bug maybe)!!!!
    unsigned long f_version;
};


struct ftable {
    struct spin_lock lock;
    struct file file[NFILE];
};

// #define NAME_MAX 10
// struct _dirent {
//     long d_ino;
//     char d_name[NAME_MAX + 1];
// };


// abstract datas in disk
struct inode {
    uint8_t i_dev;
    uint32_t i_ino;  // 对任意给定的文件系统的唯一编号标识：由具体文件系统解释
    uint16_t i_mode; // 访问权限和所有权
    int ref;       // Reference count
    int valid;
    // Note: fat fs does not support hard link, reserve for vfs interface
    uint16_t i_nlink;
    uint32_t i_uid;
    uint32_t i_gid;
    uint64_t i_rdev;
    uint32_t i_size;
    uint16_t i_type;

    long i_atime;     // access time
    long i_mtime;     // modify time
    long i_ctime;     // create time
    uint64_t i_blksize; // bytes of one block
    uint64_t i_blocks;  // numbers of blocks
    // uint32_t i_blksize;
    // uint32_t i_blocks;
    //struct semaphore i_sem; /* binary semaphore */
    // struct sleeplock i_sem;

    const struct inode_operations *i_op;
    struct _superblock *i_sb;
    struct inode *i_mount;
    // struct wait_queue *i_wait;
    struct inode *parent;

    fs_t fs_type;
    union {
        struct fat32_inode_info fat32_i;
        // struct xv6inode_info xv6_i;
        // struct ext2inode_info ext2_i;
        // void *generic_ip;
    };

};

struct file_operations {
    struct file* (*alloc) (void);
    struct file* (*dup) (struct file*);
    ssize_t (*read) (struct file*, uint64_t __user, int);
    ssize_t (*write) (struct file*, uint64_t __user, int);
    int (*fstat) (struct file *, uint64_t __user);
};


struct inode_operations {
    void (*iunlock_put) (struct inode* self);
    void (*iunlock) (struct inode* self);
    void (*iput) (struct inode* self);
    void (*ilock) (struct inode* self);
    void (*itrunc) (struct inode* self);
    void (*iupdate) (struct inode* self);
    struct inode* (*idup) (struct inode* self);
    int (*idir) (struct inode* self);   // is self a directory

    // for directory inode
    struct inode* (*idirlookup) (struct inode* self, const char* name, uint32_t* poff);
    int (*idelete) (struct inode* dp, struct inode* ip);
    int (*idempty) (struct inode* dp);
    ssize_t (*igetdents) (struct inode *dp, char *buf, uint32_t len);
};


struct linux_dirent {
    uint64_t d_ino;            // 索引结点号
    int64_t d_off;             // 到下一个dirent的偏移
    unsigned short d_reclen; // 当前dirent的长度
    unsigned char d_type;    // 文件类型
    char d_name[];           //文件名
};



#endif // __VFS_FS_H__
