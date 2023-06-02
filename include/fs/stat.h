#ifndef _STAT_H__
#define _STAT_H__

// type
#define T_DIR 1    // Directory
#define T_FILE 2   // File
#define T_DEVICE 3 // Device

// device
#define mkrdev(ma, mi) ((uint32_t)((ma) << 8 | (mi)))
#define CONSOLE 1

typedef unsigned long int dev_t;
typedef unsigned long int ino_t;
typedef unsigned long int nlink_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef long int off_t;
typedef long int blksize_t;
typedef long int blkcnt_t;
typedef unsigned int mode_t;
typedef long int off_t;

struct kstat {
    uint64_t st_dev;
    uint64_t st_ino;
    mode_t st_mode;
    uint32_t st_nlink;
    uint32_t st_uid;
    uint32_t st_gid;
    uint64_t st_rdev;
    unsigned long __pad;
    off_t st_size;
    uint32_t st_blksize;
    int __pad2;
    uint64_t st_blocks;
    long st_atime_sec;
    long st_atime_nsec;
    long st_mtime_sec;
    long st_mtime_nsec;
    long st_ctime_sec;
    long st_ctime_nsec;
    unsigned __unused[2];
};

#endif // __FS_STAT_H__
