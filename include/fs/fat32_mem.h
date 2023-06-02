#ifndef _FAT32_MEM_H__
#define _FAT32_MEM_H__

#include "fat32_disk.h"
#include "fat32_stack.h"

struct inode;

// Oscomp
struct fat_dirent_buf {
    uint64_t d_ino;            // 索引结点号
    int64_t d_off;             // 到下一个dirent的偏移
    uint16_t d_reclen; // 当前dirent的长度
    uint8_t d_type;    // 文件类型
    int8_t d_name[];           // 文件名
};

// fat32 super block information
struct fat32_sb_info {
    // read-only
    uint32_t fatbase;        // FAT base sector
    uint32_t n_fats;         // Number of FATs (1 or 2)
    uint32_t n_sectors_fat;  // Number of sectors per FAT
    uint32_t root_cluster_s; // Root directory base cluster (start)

    // FSINFO ~ may modify
    uint32_t free_count;
    uint32_t nxt_free;
};

// fat32 inode information
struct fat32_inode_info {
    // on-disk structure
    int8_t fname[NAME_LONG_MAX];
    uint8_t Attr;             // directory attribute 该inode的属性，表示是目录还是文件
    uint8_t DIR_CrtTimeTenth; // create time
    uint16_t DIR_CrtTime;     // create time, 2 bytes
    uint16_t DIR_CrtDate;     // create date, 2 bytes
    uint16_t DIR_LstAccDate;  // last access date, 2 bytes
    // (DIR_FstClusHI << 16) | (DIR_FstClusLO)
    uint32_t cluster_start; // start num
    uint16_t DIR_WrtTime;   // Last modification (write) time.
    uint16_t DIR_WrtDate;   // Last modification (write) date.
    uint32_t DIR_FileSize;  // file size (bytes)

    // in memory structure
    uint32_t cluster_end; // end num
    uint64_t cluster_cnt; // number of clusters
    uint32_t parent_off;  // offset in parent clusters
};

// 0. init the root fat32 inode
struct inode *fat32_root_inode_init(struct _superblock *);

// 1. traverse the fat32 chain
uint32_t fat32_fat_travel(struct inode *, uint32_t);

// 2. return the next cluster number
uint32_t fat32_next_cluster(uint32_t);

// 3. allocate a new cluster
uint32_t fat32_cluster_alloc(uint32_t);

// 4. allocate a new fat entry
uint32_t fat32_fat_alloc();

// 5. set the fat entry to given value
void fat32_fat_set(uint32_t, uint32_t);

// 6. current fat32 inode
// struct inode *name_to_i(int8_t *);

// 7. the parent of current fat32 inode
// struct inode *name_to_i_parent(int8_t *, int8_t *);

struct inode *fat32_inode_dup(struct inode *);
void fat32_inode_update(struct inode *);
void fat32_inode_trunc(struct inode *);

void fat32_inode_lock(struct inode *);
void fat32_inode_unlock(struct inode *);
void fat32_inode_put(struct inode *);
void fat32_inode_unlock_put(struct inode *);

int fat32_filter_longname(dirent_l_t *, int8_t *);
struct inode *fat32_inode_dirlookup(struct inode *, const int8_t *, uint32_t *);
struct inode *fat32_inode_get(uint32_t, uint32_t, const int8_t *, uint32_t);

uint32_t fat32_inode_read(struct inode *, int, uint64_t, uint32_t, uint32_t);

// 9. write the data given the fat32 inode, offset and length
uint32_t fat32_inode_write(struct inode *, int, uint64_t, uint32_t, uint32_t);

// 10. dup a existed fat32 inode
struct inode *fat32_inode_dup(struct inode *);

// 11. find a existed or new fat32 inode
struct inode *fat32_inode_get(uint32_t, uint32_t, const int8_t *, uint32_t);

// 12. lock the fat32 inode
void fat32_inode_lock(struct inode *);

// 13. unlock the fat32 inode
void fat32_inode_unlock(struct inode *);

// 14. put the fat32 inode
void fat32_inode_put(struct inode *);

// 15. unlock and put the fat32 inode
void fat32_inode_unlock_put(struct inode *);

// 16. truncate the fat32 inode
void fat32_inode_trunc(struct inode *);

// 17. update the fat32 inode in the disk
void fat32_inode_update(struct inode *);

// 18. cat the Name1, Name2 and Name3 of dirent_l
int fat32_filter_longname(dirent_l_t *, int8_t *);

// 19. reverse the dirent_l to get the int64_t name
uint16_t fat32_longname_popstack(Stack_t *, uint8_t *, int8_t *);

// 20. the check sum of dirent_l
uint8_t ChkSum(uint8_t *);

// 21. lookup the inode given its parent inode and name
struct inode *fat32_inode_dirlookup(struct inode *, const int8_t *, uint32_t *);
struct inode *fat32_inode_get(uint32_t, uint32_t, const int8_t *, uint32_t);
//void fat32_inode_stati(struct inode *ip, struct kstat *st);
int fat32_inode_delete(struct inode *dp, struct inode *ip);

// 22. create the fat32 inode
struct inode *fat32_inode_create(int8_t *path, uint8_t type, short major, short minor);

// 23. allocate the fat32 inode
struct inode *fat32_inode_alloc(struct inode *, int8_t *, uint8_t);

// 24. init the fat32 fcb (short + int64_t)
int fat32_fcb_init(struct inode *, const uint8_t *, uint8_t, int8_t *);

// 25. the number of files with the same name prefix
uint32_t fat32_find_same_name_cnt(struct inode *, int8_t *);

// 26. the right fcb insert offset ?
uint32_t fat32_dir_fcb_insert_offset(struct inode *, uint8_t);

// 27. is empty?
int fat32_isdirempty(struct inode *);

// 28. timer to string
int fat32_time_parser(uint16_t *, int8_t *, int);

// 29. date to string
int fat32_date_parser(uint16_t *, int8_t *);

// 30. delete fat32 inode
int fat32_inode_delete(struct inode *, struct inode *);

// 31. acquire the time now
uint16_t fat32_inode_get_time(int *);

// 32. acquire the date now
uint16_t fat32_inode_get_date();

// 33. zero the cluster given cluster num
void fat32_zero_cluster(uint64_t c_num);

// 34. short name parser
void fat32_short_name_parser(dirent_s_t dirent_l, int8_t *name_buf);

// 35. load inode from disk
int fat32_inode_load_from_disk(struct inode *ip);

// 36. is the inode a directory?
int fat32_isdir(struct inode *);

#endif
