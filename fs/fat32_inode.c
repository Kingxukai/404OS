//ref to LostWakeup of 杭州电子科技大学
//gitlab:https://gitlab.eduxiji.net/202310336101112/LostWakeup

#include "../include/fs/fs.h"
#include "../include/fs/stat.h"
#include "../include/fs/fcntl.h"
#include "../include/disk/buffer.h"
#include "../include/usr/lib.h"
#include "../include/usr/printf.h"
#include "../include/macro.h"
#include "../include/ctype.h"
#include "../include/sched.h"

extern struct file_operations fat32_fop;
extern struct inode_operations fat32_iop;
extern const struct inode_operations* (*get_inodeops[])(void);

struct _superblock fat32_sb;
// maximum file inode in memory
#define NENTRY 50
struct{
    struct spin_lock lock;
    struct inode inode_entry[NENTRY];
} inode_table;

/* inefficient, use for debug only! */
static void print_rawstr(const char *c, uint32_t len) {
    for (int i = 0; i < len; i++) {
        if (*(c + i) == ' ') {
            printf(" ");
        } else if (isalnum(*(c + i)) || *(c + i) == '.' || *(c + i) == '~' || *(c + i) == '_') {
            printf("%c", *(c + i));
        } else {
            printf(" ");
        }
    }
}

static void print_short_dir(const dirent_s_t *buf) {
    printf("(short) ");
    printf("name: ", buf->DIR_Name);
    print_rawstr((char *)buf->DIR_Name, FAT_SFN_LENGTH);
    printf("  ");
    printf("attr: %#x\t", buf->DIR_Attr);
    printf("dev: %d\t", buf->DIR_Dev);
    printf("filesize %d\n", buf->DIR_FileSize);
    // printf("create_time_tenth %d\t", buf->DIR_CrtTimeTenth);
    // printf("create_time %d\n", buf->DIR_CrtTime);
    // printf("crea");
}

static void print_long_dir(const dirent_l_t *buf) {
    printf("(long) ");
    printf("name1: ");
    print_rawstr((char *)buf->LDIR_Name1, 10);
    printf("  ");
    printf("name2: ");
    print_rawstr((char *)buf->LDIR_Name2, 12);
    printf("  ");
    printf("name3: ");
    print_rawstr((char *)buf->LDIR_Name3, 4);
    printf("  ");
    printf("attr %#x\n", buf->LDIR_Attr);
}

void sys_print_rawfile(void) {
    int fd;
    int printdir;
    struct file *f;

    printfGreen("==============\n");
    if (argfd(0, &fd, &f) < 0) {
        printfGreen("file doesn't open!\n");
        return;
    }
    argint(1, &printdir);

    ASSERT(f->f_type == FD_INODE);
    int cnt = 0;
    int pos = 0;
    uint64_t iter_n = f->f_tp.f_inode->fat32_i.cluster_start;

    printfGreen("fd is %d\n", fd);
    struct inode *ip = f->f_tp.f_inode;
    if (ip->i_type != T_DIR && printdir == 1) {
        printfGreen("the file is not a directory\n");
        return;
    }
    int off = 0;
    // print logistic clu.no and address(in fat32.img)
    while (!ISEOF(iter_n)) {
        uint64_t addr = (iter_n - fat32_sb.fat32_sb_info.root_cluster_s) * __BPB_BytsPerSec * __BPB_SecPerClus + FSIMG_STARTADDR;
        printfGreen("cluster no: %d\t address: %p \toffset %d(%#p)\n", cnt++, addr, pos, pos);
        if (printdir == 1) {
            int first_sector = FirstSectorofCluster(iter_n);
            int init_s_n = LOGISTIC_S_NUM(pos);
            struct buffer *bp;
            for (int s = init_s_n; s < __BPB_SecPerClus; s++) {
                bp = bread(ip->i_dev, first_sector + s);
                for (int i = 0; i < 512 && i < ip->i_size; i += 32) {
                    dirent_s_t *tmp = (dirent_s_t *)(bp->data + i);
                    printf("%x ", off++);
                    if (LONG_NAME_BOOL(tmp->DIR_Attr)) {
                        print_long_dir((dirent_l_t *)(bp->data + i));
                    } else {
                        print_short_dir((dirent_s_t *)(bp->data + i));
                    }
                }
                printfRed("===Sector %d end===\n", s);
                brelse(bp);
            }
        }
        pos += __BPB_BytsPerSec * __BPB_SecPerClus;
        iter_n = fat32_next_cluster(iter_n);
    }
    printfGreen("file size is %d(%#p)\n", f->f_tp.f_inode->i_size, f->f_tp.f_inode->i_size);
    printfGreen("==============\n");
    return;
}

// init the global inode table
void inode_table_init() {
    struct inode *entry;
    //initlock(&inode_table.lock, "inode_table"); // !!!!
    for (entry = inode_table.inode_entry; entry < &inode_table.inode_entry[NENTRY]; entry++) {
        memset(entry, 0, sizeof(struct inode));
        // sema_init(&entry->i_sem, "inode_entry");
    }
}

struct inode *fat32_root_inode_init(struct _superblock *sb) 
{
    // root inode initialization
    struct inode *root_ip = (struct inode *)malloc(sizeof(struct inode));//分配内存空间来存储根 i-node
    //sema_init(&root_ip->i_sem, 1, "fat_root_inode");//初始化信号量（sema）
    
    //为根 i-node 设置设备号（i_dev）、模式（i_mode）、标记为根 i-node（i_ino = 0）、引用次数（ref = 0）、有效性（valid = 1）
    root_ip->i_dev = sb->s_dev;
    root_ip->i_mode = IMODE_NONE;//无权限访问
    // set root inode num to 0
    root_ip->i_ino = 0;
    root_ip->ref = 0;
    root_ip->valid = 1;
    // file size
    //为根 i-node 设置相关指针以及硬链接数、操作集
    root_ip->i_mount = root_ip;
    root_ip->i_sb = sb;
    root_ip->i_nlink = 1;
    root_ip->i_op = get_inodeops[FAT32]();
    root_ip->fs_type = FAT32;

    // the parent of the root is itself
    //设置根 i-node 父节点为自身，FAT 文件系统根簇编号为 2，父目录偏移量为 0，设置名称及结束字符
    root_ip->parent = root_ip;
    root_ip->fat32_i.cluster_start = 2;
    root_ip->fat32_i.parent_off = 0;
    memset(root_ip->fat32_i.fname, 0, NAME_LONG_MAX);
    root_ip->fat32_i.fname[0] = '/';
    root_ip->fat32_i.fname[1] = '\0';

    // root inode doesn't have these fields, so set these to 0
    //设置根 i-node 的访问时间、修改时间、创建时间为 0
    root_ip->i_atime = 0;
    root_ip->i_mtime = 0;
    root_ip->i_ctime = 0;
		
		//计算根 i-node 包含的簇数量和目录长度
    root_ip->fat32_i.cluster_cnt = fat32_fat_travel(root_ip, 0);
    root_ip->i_size = DIRLENGTH(root_ip);
    
    //设置根 i-node 的其它重要字段，如文件大小、i-node 类型、文件属性等
    root_ip->i_sb = sb;
    root_ip->fat32_i.DIR_FileSize = 0;
    root_ip->i_type = T_DIR;
    DIR_SET(root_ip->fat32_i.Attr);

		//确保根 i-node 的簇编号为 2，并返回初始化好的根 i-node
    ASSERT(root_ip->fat32_i.cluster_start == 2);
    return root_ip;
}

// num is a logical cluster number(within a file)
// start from 1
//num is a relative value
// num == 0 ~ return count of clusters, set the inode->fat32_i.cluster_end at the same time
// num != 0 ~ return the num'th physical cluster num
uint32_t fat32_fat_travel(struct inode *ip, uint32_t num) //ip:表示该文件/目录的 i 节点 num:表示要返回的簇的编号
{
    FAT_entry_t iter_n = ip->fat32_i.cluster_start;	//fat32_inode.c:144行，cluster_start = 2
    int cnt = 0;//使用 cnt 记录当前遍历到的簇的编号
    int prev = 0;
    while (!ISEOF(iter_n) && (num > ++cnt || num == 0))//num==0,表示必须得一直遍历直到找到EOF；如果num!=0，则只要当找到了指定的簇，将其起始位置记录为 iter_n，退出循环
    {
        prev = iter_n;
        iter_n = fat32_next_cluster(iter_n);//用于获取下一个簇的位置
    }

    if (num == 0)//如果 num 为 0，则表示已经遍历到 FAT32 链的结束
    {
        ip->fat32_i.cluster_end = prev;//函数将 “prev” 记录的最后一个簇的起始位置设置为 i 节点的 “cluster_end” 属性，表示 FAT32 链表的末尾。
        return cnt;//函数返回 cnt，表示簇的数量
    } 
    else//如果 num 不为 0，则需要进一步判断需要返回的簇的编号是否在 FAT32 链表的范围之内
    {
        if (num > cnt)//如果目标簇的编号大于 cnt，则返回上一个簇的位置
            return prev;
        return iter_n;//否则，返回目标簇的位置（即 iter_n）
    }
}

// find the next cluster of current cluster
uint32_t fat32_next_cluster(uint32_t cluster_cur) 
{
    ASSERT(cluster_cur >= 2 && cluster_cur < FAT_CLUSTER_MAX);
    struct buffer *bp;
    uint32_t sector_num = ThisFATEntSecNum(cluster_cur);//由簇号获取扇区号，也就是该簇所属的FAT表所处的相对扇区号
    // uint32_t sector_offset = ThisFATEntOffset(cluster_cur);
    bp = bread(fat32_sb.s_dev, sector_num);//获取一个指定设备、扇区号的buffer块
    FAT_entry_t fat_next = FAT32ClusEntryVal(bp->data, cluster_cur);//从 FAT 表中获取下一个簇的编号
    /*第一个参数 bp->data 是指向 FAT 表数据的指针，第二个参数 cluster_cur 是当前簇的编号。*/
    brelse(bp);
    /*释放缓冲区，避免内存泄漏*/
    return fat_next;
}

// allocate a free cluster
uint32_t fat32_cluster_alloc(uint32_t dev) 
{
    struct buffer *bp;

    if (!fat32_sb.fat32_sb_info.free_count) //如果超级块的信息中记录的空闲簇数为0
    {
        panic("no disk space!!!\n");//如果没有空闲的簇，则发出panic信息。
    }
    uint32_t free_num = fat32_sb.fat32_sb_info.nxt_free;//确定要分配的下一个空闲簇编号
    fat32_sb.fat32_sb_info.free_count--;//将文件系统的可用空闲簇数减一

    // the first sector
    int first_sector = FirstSectorofCluster(fat32_sb.fat32_sb_info.nxt_free);//计算簇的第一个扇区的逻辑位置。
    bp = bread(dev, first_sector);//读取第一个扇区的数据，存储在缓冲区头bp中
/*展开后就是 ((bp->data)[0] == 0x00)，判断指向数据的指针 bp->data 的第一个字节是否为 0x00。如果是，该条件就为真，表示当前的文件或目录名全部为空字符。*/
    if (NAME0_FREE_ALL((bp->data)[0]) && free_num < FAT_CLUSTER_MAX - 1) 
    {
        // next free hit
        brelse(bp); // !!!!

        fat32_fat_set(free_num, EOC);//将该空闲簇的 FAT 表项设置为结束标识符（EOC）
        fat32_sb.fat32_sb_info.nxt_free++;//并将下一个空闲簇的编号加 1
    } 
    else //如果数据区有数据
    {
        // start from the begin of fat
        brelse(bp); // !!!!

        uint32_t fat_next = fat32_fat_alloc();//调用 fat32_fat_alloc() 函数再分配一个新的空闲簇（这个簇在fat32_fat_alloc() 函数中已经被设置为了EOC）
        if (fat_next == 0)
            panic("no more space");
        fat32_sb.fat32_sb_info.nxt_free = fat_next + 1;//并将下一个空闲簇的编号设置为当前分配的簇号加 1
    }

    // update fsinfo
    fsinfo_t *fsinfo_tmp;
    bp = bread(dev, SECTOR_FSINFO);//	SECTOR_FSINFO:1--第一个 fsinfo 扇区记录的是文件系统运行时的统计信息，例如空闲簇的数量，下一个可用的空闲簇的位置等
    fsinfo_tmp = (fsinfo_t *)(bp->data);
    fsinfo_tmp->Free_Count = fat32_sb.fat32_sb_info.free_count;
    fsinfo_tmp->Nxt_Free = fat32_sb.fat32_sb_info.nxt_free;
    bwrite(bp);
    brelse(bp);

    // update fsinfo backup
    bp = bread(dev, SECTOR_FSINFO_BACKUP);//SECTOR_FSINFO_BACKUP:7--备份用于当主 fsinfo 区数据损坏时恢复文件系统
    fsinfo_tmp = (fsinfo_t *)(bp->data);
    fsinfo_tmp->Free_Count = fat32_sb.fat32_sb_info.free_count;
    fsinfo_tmp->Nxt_Free = fat32_sb.fat32_sb_info.nxt_free;
    bwrite(bp);
    brelse(bp);
	
    fat32_zero_cluster(free_num);//使用 fat32_zero_cluster() 函数来清零分配的簇中的数据
    return free_num;//返回 free_num，即分配到的空闲簇的号码
}

// allocate a new fat entry
uint32_t fat32_fat_alloc() //返回值：簇在FAT表中的相对位置
{
    struct buffer *bp;

    int c = 3;//从 FAT 表的第 3 个簇开始搜索空闲簇
    int sec = FAT_BASE;
    while (c < FAT_CLUSTER_MAX) //如果遍历整个 FAT 表项后（所有的簇）仍然没有找到空闲簇，则返回 0 表示分配失败
    {
        bp = bread(fat32_sb.s_dev, sec);
        FAT_entry_t *fats = (FAT_entry_t *)(bp->data);
        for (int s = 0; s < FAT_PER_SECTOR; s++) //遍历一个扇区中的FAT表项（一个扇区中的簇），找到 FAT 表中的空闲簇
        {
            if (fats[s] == FREE_MASK) //如果找到了空闲簇，则将 FAT 表中该簇的值设置为 EOC（表示该簇为文件的最后一个簇），并返回该簇在FAT表中的相对位置
            {
                brelse(bp); // !!!!
                fat32_fat_set(c, EOC);/*---------------EOC??pending resolution-------------*/
                return c;
            }
            c++;
            if (c > FAT_CLUSTER_MAX) //如果遍历整个 FAT 表后仍然没有找到空闲簇，则返回 0 表示分配失败
            {
                brelse(bp);
                return 0;
            }
        }
        sec++;//扇区号+1
        brelse(bp);
    }
    return 0;
}

// set fat to value
void fat32_fat_set(uint32_t cluster, uint32_t value) 
{
    struct buffer *bp;
    uint32_t sector_num = ThisFATEntSecNum(cluster);
    bp = bread(fat32_sb.s_dev, sector_num);//读FAT表所处扇区的值
    // uint32_t offset = ThisFATEntOffset(cluster);
    SetFAT32ClusEntryVal(bp->data, cluster, value);//把bp->data中偏移cluster的值写成value（即把FAT32表中cluster对应的表项值写成value）
    bwrite(bp);//写回磁盘
    brelse(bp);
}

// // Examples:
// //   skepelem("a/bb/c", name) = "bb/c", setting name = "a"
// //   skepelem("///a//bb", name) = "bb", setting name = "a"
// //   skepelem("a", name) = "", setting name = "a"
// //   skepelem("", name) = skepelem("////", name) = 0

// //   skepelem("./mnt", name) = "", setting name = "mnt"
// //   skepelem("../mnt", name) = "", setting name = "mnt"
// //   skepelem("..", name) = "", setting name = 0
// static char *skepelem(char *path, char *name) {
//     char *s;
//     int len;

//     while (*path == '/' || *path == '.')
//         path++;
//     if (*path == 0)
//         return 0;
//     s = path;
//     while (*path != '/' && *path != 0)
//         path++;
//     len = path - s;
//     if (len >= PATH_LONG_MAX)
//         memmove(name, s, PATH_LONG_MAX);
//     else {
//         memmove(name, s, len);
//         name[len] = 0;
//     }
//     while (*path == '/')
//         path++;
//     return path;
// }

// struct inode *namei(char *path) {
//     char name[NAME_LONG_MAX];
//     return fat32_inode_namex(path, 0, name);
// }

// struct inode *name_to_i_parent(char *path, char *name) {
//     return fat32_inode_namex(path, 1, name);
// }

// Read data from fa32 inode.
uint32_t fat32_inode_read(struct inode *ip, int user_dst, uint64_t dst, uint32_t off, uint32_t n) 
{
    uint32_t tot = 0, m;
    struct buffer *bp;

    // 是一个目录
    int fileSize = ip->i_size;

    // 特判合法
    if (off > fileSize || off + n < off)// 如果读取的偏移量 off 大于该文件的总长度 fileSize，且off+n没有溢出（防止数据溢出）
        return 0;
    if (off + n > fileSize)//如果偏移量off + 读取数据大小n > 文件大小，那么读取数据大小 = 文件大小 - 偏移量，也就是把读取范围调整为从偏移量开始->文件末尾
        n = fileSize - off;

    FAT_entry_t iter_n = ip->fat32_i.cluster_start;// FAT32 文件系统使用链式簇分配方式来存储文件数据。inode 中的 cluster_start 表示文件的第一个簇在 FAT 表中的簇号。因此我们可以通过该簇号以及读取的偏移量，找到数据对应的簇号。

    uint32_t C_NUM_off = LOGISTIC_C_NUM(off) + 1;//LOGISTIC_C_NUM(off) 返回一个cluster num:偏移的簇的数量
    // find the target cluster of off
    iter_n = fat32_fat_travel(ip, C_NUM_off);//得到簇的目标位置

    int init_s_n = LOGISTIC_S_NUM(off);//LOGISTIC_S_NUM(off) 返回一个sector num:偏移的扇区的数量
    int init_s_offset = LOGISTIC_S_OFFSET(off);//LOGISTIC_S_OFFSET(off) 返回一个在扇区上的偏移的字节数

    uint32_t ret = 0;
    // read the target sector
    while (!ISEOF(iter_n) && tot < n)  //不断读取簇中的每个扇区，直到读取到需要读取的字节数 n 或者到达文件末尾。
    {
        int first_sector = FirstSectorofCluster(iter_n);//得到该簇的第一个扇区
        for (int s = init_s_n; s < (ip->i_sb->sectors_per_block) && tot < n; s++)//在每个簇中，该循环会读取每个扇区的数据，直到读取到需要读取的字节数或者到达了文件末尾。第一次，从之前得到的偏移的扇区数开始遍历。 条件：不超过扇区数的限制，且已读取的总字节数tot，小于目标读取字节数n
        {
            bp = bread(ip->i_dev, (uint32_t)first_sector + s);//得到一个该扇区的缓冲块
            m = MIN(BUFFER_SIZE - init_s_offset, n - tot);//计算将要读取的字节数：512 - 偏移的字节数 和 目标读取的字节数 - 已读取的字节数 之中更小的一个。

            memcpy((uint64_t *)dst, (uint64_t *)(bp->data + init_s_offset), m);
            brelse(bp);

            tot += m;
            dst += m;
            init_s_offset = 0;
        }
        if (tot == n || ret == -1)//如果出错了或者读取的字节数已经到n了，退出循环
            break;
        init_s_n = 0;//从下一个簇开始的第一个扇区开始遍历

        iter_n = fat32_next_cluster(iter_n);//得到该簇的下一个簇
    }
    if (ret == 0)//正常返回
        return tot;//返回总读取字节数
    else
        return ret;//返回-1
}

// Write data to fat32 inode
// 写 inode 文件，从偏移量 off 起， 写 src 的 n 个字节的内容
uint32_t fat32_inode_write(struct inode *ip, int user_src, uint64_t src, uint32_t off, uint32_t n) {
    uint32_t tot = 0, m;
    struct buffer *bp;

    // 是一个目录
    int fileSize = ip->i_size;

    if (off > fileSize || off + n < off)
        return -1;
    if (off + n > DataSec * ip->i_sb->sector_size)
        return -1;

    FAT_entry_t iter_n = ip->fat32_i.cluster_start;

    FAT_entry_t next;
    uint32_t C_NUM_off = LOGISTIC_C_NUM(off) + 1;
    // find the target cluster of off
    iter_n = fat32_fat_travel(ip, C_NUM_off);

    if (C_NUM_off > ip->fat32_i.cluster_cnt) {
        FAT_entry_t fat_new = fat32_cluster_alloc(ROOTDEV);
        fat32_fat_set(iter_n, fat_new);

        // uint32_t first_sector = FirstSectorofCluster(fat_new); // debug
        // uint32_t sec_pos = DEBUG_SECTOR(ip, first_sector); // debug
        // printf("%d\n",sec_pos); // debug
        iter_n = fat_new;
        ip->fat32_i.cluster_cnt++;
        ip->fat32_i.cluster_end = fat_new;
    }
    // TODO: off如果超出文件大小。
    // 这里先假设off不会超出文件大小。

    int init_s_n = LOGISTIC_S_NUM(off);
    int init_s_offset = LOGISTIC_S_OFFSET(off);

    uint32_t ret = 0;
    // read the target sector
    while ((!ISEOF(iter_n) && tot < n)) {
        int first_sector = FirstSectorofCluster(iter_n);
        for (int s = init_s_n; s < ip->i_sb->sectors_per_block && tot < n; s++) {
            bp = bread(ip->i_dev, first_sector + s);
            m = MIN(BUFFER_SIZE - init_s_offset, n - tot);

            /*if (either_copyin(bp->data + init_s_offset, user_src, src, m) == -1) {
                brelse(bp);
                ret = -1;
                break;
            }*/
            bwrite(bp); // !!!!
            brelse(bp);
            tot += m;
            src += m;
            init_s_offset = 0;
        }
        if (tot == n || ret == -1)
            break;
        init_s_n = 0;
        next = fat32_next_cluster(iter_n);
        if (ISEOF(next)) {
            FAT_entry_t fat_new = fat32_cluster_alloc(ROOTDEV);
            fat32_fat_set(iter_n, fat_new);
            iter_n = fat_new;
            ip->fat32_i.cluster_cnt++;
            ip->fat32_i.cluster_end = fat_new;
        } else {
            iter_n = next;
        }
    }
    if (off + n > fileSize) {
        if (ip->i_type == T_FILE)
            ip->i_size = off + tot;
        else
            ip->i_size = CEIL_DIVIDE(off + tot, ip->i_sb->cluster_size) * (ip->i_sb->cluster_size);
    }
    fat32_inode_update(ip);
    if (ret == 0)
        return tot;
    else
        return ret;
}

struct inode *fat32_inode_dup(struct inode *ip)//引用次数+1返回一个结点 
{
    spin_lock(&inode_table.lock);
    ip->ref++;
    spin_unlock(&inode_table.lock);
    return ip;
}

// get a inode , move it from disk to memory
struct inode *fat32_inode_get(uint32_t dev, uint32_t inum, const char *name, uint32_t parentoff) 
{
    struct inode *ip = NULL, *empty = NULL;
    spin_lock(&inode_table.lock);

    // Is the fat32 inode already in the table?
    for (ip = inode_table.inode_entry; ip < &inode_table.inode_entry[NENTRY]; ip++) //遍历所有inode
    {
        if (ip->ref > 0 && ip->i_dev == dev && ip->i_ino == inum) //检查当前的 inode 结构体是否与函数调用参数匹配。如果这个 inode 已经被加载到了内存中，则直接将它的引用计数值加 1 并返回指向它的指针
        {
            ip->ref++;
            spin_unlock(&inode_table.lock);
            return ip;
        }
        if (empty == NULL && ip->ref == 0) // Remember empty slot.
            empty = ip;//记录空闲的 inode 结构体指针。如果当前 inode 结构体未被占用（ip->ref == 0），则将这个 inode 结构体指针记录为空闲指针变量 empty。这个变量用于后续的回收空闲 inode 结构体的步骤。
    }
//找到了匹配的inode就返回ip；如果没找到则接下来应该返回一个空闲指针；如果没有空闲指针，就panic
    // Recycle an fat32 entry.
    if (empty == NULL)//如果没有找到空闲的 inode 结构体指针，则发生内核崩溃（panic）。这说明系统中没有空闲的 inode 结构体可供使用了。
        panic("fat32_inode_get: no space");

    empty->i_sb = &fat32_sb;//设置inode的超级块
    empty->i_dev = dev;
    empty->i_ino = inum;//设置inode的编号
    empty->ref = 1;//引用数 = 1，表示已经被加载到内存中
    empty->valid = 0;//将 inode 的 valid 标志位设置为 0，表示该 inode 的缓存中的数据可能不准确，需要进行刷新或重新加载
    empty->fat32_i.parent_off = parentoff;//设置 inode 的父 inode 在目录中的偏移量
    empty->i_op = get_inodeops[FAT32]();//设置 inode 的操作函数指针，指向 FAT32 文件系统相关的操作函数，如读写、文件系统扩展等操作
    empty->fs_type = FAT32;

    strncpy(empty->fat32_i.fname, name, strlen(name));//将文件/目录名称拷贝到 inode 结构体中

    spin_unlock(&inode_table.lock);
    return empty;
}

// 获取fat32 inode的锁 并加载 磁盘中的short dirent to mem
void fat32_inode_lock(struct inode *ip) 
{
    struct buffer *bp;
    if (ip == NULL || ip->ref < 1)
        panic("inode lock");

    if (ip->valid == 0) 
    {
        uint32_t sector_num = FATINUM_TO_SECTOR(ip->i_ino);
        uint32_t sector_offset = FATINUM_TO_OFFSET(ip->i_ino);
        // uint32_t sec_pos = DEBUG_SECTOR(ip, sector_num); // debug
        // printf("%d\n",sec_pos);
        bp = bread(ip->i_dev, sector_num);
        dirent_s_t *dirent_s_tmp = (dirent_s_t *)bp->data + sector_offset;

        ip->fat32_i.Attr = dirent_s_tmp->DIR_Attr;//获取文件/目录对应属性信息Attr
        ip->fat32_i.cluster_start = DIR_FIRST_CLUS(dirent_s_tmp->DIR_FstClusHI, dirent_s_tmp->DIR_FstClusLO);//获取文件/目录对应的起始簇号
        if (ip->fat32_i.cluster_start == fat32_sb.fat32_sb_info.root_cluster_s && fat32_namecmp(ip->fat32_i.fname, "/")) 
        {//如果该文件/目录的起始簇号为root簇号，且文件名不是"/"，则panic，不正常
            panic("this disk image has error \n");
        }
        // !!!
        if (ip->fat32_i.cluster_start != 0) //如果起始簇号不为0，则遍历FAT表，获取簇数目
        {
            ip->fat32_i.cluster_cnt = fat32_fat_travel(ip, 0);
        } 
        else 
        {
            printfRed("the cluster_start of the file %s is zero\n ", ip->fat32_i.fname);
        }
        ip->fat32_i.DIR_CrtTimeTenth = dirent_s_tmp->DIR_CrtTimeTenth;

				/*获取目录项各时间信息*/
        ip->fat32_i.DIR_CrtTime = dirent_s_tmp->DIR_CrtTime;
        ip->fat32_i.DIR_CrtDate = dirent_s_tmp->DIR_CrtDate;
        ip->fat32_i.DIR_LstAccDate = dirent_s_tmp->DIR_LstAccDate;
        ip->fat32_i.DIR_WrtTime = dirent_s_tmp->DIR_WrtTime;
        ip->fat32_i.DIR_CrtDate = dirent_s_tmp->DIR_CrtDate;
        // memmove((void *)&ip->fat32_i.DIR_CrtTime, (void *)&dirent_s_tmp->DIR_CrtTime, sizeof(dirent_s_tmp->DIR_CrtTime));
        // memmove((void *)&ip->fat32_i.DIR_CrtDate, (void *)&dirent_s_tmp->DIR_CrtDate, sizeof(dirent_s_tmp->DIR_CrtDate));
        // memmove((void *)&ip->fat32_i.DIR_LstAccDate, (void *)&dirent_s_tmp->DIR_LstAccDate, sizeof(dirent_s_tmp->DIR_LstAccDate));
        // memmove((void *)&ip->fat32_i.DIR_WrtTime, (void *)&dirent_s_tmp->DIR_WrtTime, sizeof(dirent_s_tmp->DIR_WrtTime));
        // memmove((void *)&ip->fat32_i.DIR_WrtDate, (void *)&dirent_s_tmp->DIR_WrtDate, sizeof(dirent_s_tmp->DIR_WrtDate));
        ip->fat32_i.DIR_FileSize = dirent_s_tmp->DIR_FileSize;

        ip->i_rdev = dirent_s_tmp->DIR_Dev;

        if (ip->i_rdev)//判断文件/目录是否为设备文件，并设置inode的类型i_type
            ip->i_type = T_DEVICE; // device?
        else if (DIR_BOOL(ip->fat32_i.Attr))
            ip->i_type = T_DIR;
        else
            ip->i_type = T_FILE;

        if (ip->i_type == T_FILE)// 根据inode类型设置i_size
            ip->i_size = ip->fat32_i.DIR_FileSize;
        else if (ip->i_type == T_DIR)
            ip->i_size = DIRLENGTH(ip);
        else if (ip->i_type == T_DEVICE)
            ip->i_size = 0;

        ip->i_mode = READONLY_GET(dirent_s_tmp->DIR_Attr);//获取目录项对应权限信息Reserve，存储在inode->i_mode中

        // ip->i_op = get_fat32_iops();
        ip->i_op = get_inodeops[FAT32]();// 获取文件系统对应的inode操作函数指针
        ip->fs_type = FAT32;
        // ip->i_sb = &fat32_sb;

        brelse(bp);
        ip->valid = 1;
        if (ip->fat32_i.Attr == 0)//竟然是0？？
            panic("fat32_inode_lock: no Attr");
    }
}

int fat32_inode_load_from_disk(struct inode *ip) 
{
    struct buffer *bp;
    if (ip->valid == 0) 
    {
        uint32_t sector_num = FATINUM_TO_SECTOR(ip->i_ino);//将ino号转化为扇区号
        uint32_t sector_offset = FATINUM_TO_OFFSET(ip->i_ino);//得到在一个扇区上偏移的PCB号
        // uint32_t sec_pos = DEBUG_SECTOR(ip, sector_num); // debug
        // printf("%d\n",sec_pos);
        bp = bread(ip->i_dev, sector_num);//读一个缓冲块
        dirent_s_t *dirent_s_tmp = (dirent_s_t *)bp->data + sector_offset;//得到这个缓冲块上的偏移PCB号对应的地址

        ip->fat32_i.Attr = dirent_s_tmp->DIR_Attr;
        ip->fat32_i.cluster_start = DIR_FIRST_CLUS(dirent_s_tmp->DIR_FstClusHI, dirent_s_tmp->DIR_FstClusLO);
        if (ip->fat32_i.cluster_start == fat32_sb.fat32_sb_info.root_cluster_s && !fat32_namecmp(ip->fat32_i.fname, "/")) 
        {
            return -1;
        }
        // !!!
        if (ip->fat32_i.cluster_start != 0) 
        {
            ip->fat32_i.cluster_cnt = fat32_fat_travel(ip, 0);
        } 
        else 
        {
            printfRed("the cluster_start of the file %s is zero\n ", ip->fat32_i.fname);
        }
        ip->fat32_i.DIR_CrtTimeTenth = dirent_s_tmp->DIR_CrtTimeTenth;

        ip->fat32_i.DIR_CrtTime = dirent_s_tmp->DIR_CrtTime;
        ip->fat32_i.DIR_CrtDate = dirent_s_tmp->DIR_CrtDate;
        ip->fat32_i.DIR_LstAccDate = dirent_s_tmp->DIR_LstAccDate;
        ip->fat32_i.DIR_WrtTime = dirent_s_tmp->DIR_WrtTime;
        ip->fat32_i.DIR_CrtDate = dirent_s_tmp->DIR_CrtDate;
        // memmove((void *)&ip->fat32_i.DIR_CrtTime, (void *)&dirent_s_tmp->DIR_CrtTime, sizeof(dirent_s_tmp->DIR_CrtTime));
        // memmove((void *)&ip->fat32_i.DIR_CrtDate, (void *)&dirent_s_tmp->DIR_CrtDate, sizeof(dirent_s_tmp->DIR_CrtDate));
        // memmove((void *)&ip->fat32_i.DIR_LstAccDate, (void *)&dirent_s_tmp->DIR_LstAccDate, sizeof(dirent_s_tmp->DIR_LstAccDate));
        // memmove((void *)&ip->fat32_i.DIR_WrtTime, (void *)&dirent_s_tmp->DIR_WrtTime, sizeof(dirent_s_tmp->DIR_WrtTime));
        // memmove((void *)&ip->fat32_i.DIR_WrtDate, (void *)&dirent_s_tmp->DIR_WrtDate, sizeof(dirent_s_tmp->DIR_WrtDate));
        ip->fat32_i.DIR_FileSize = dirent_s_tmp->DIR_FileSize;

        ip->i_rdev = dirent_s_tmp->DIR_Dev;

        if (ip->i_rdev)
            ip->i_type = T_DEVICE; // device?
        else if (DIR_BOOL(ip->fat32_i.Attr))//是路径？
            ip->i_type = T_DIR;
        else//是文件？
            ip->i_type = T_FILE;

        if (ip->i_type == T_FILE)//是文件
            ip->i_size = ip->fat32_i.DIR_FileSize;
        else if (ip->i_type == T_DIR)//是路径
            ip->i_size = DIRLENGTH(ip);
        else if (ip->i_type == T_DEVICE)//是设备
            ip->i_size = 0;

        ip->i_mode = READONLY_GET(dirent_s_tmp->DIR_Attr);

        brelse(bp);
        ip->valid = 1;
        if (ip->fat32_i.Attr == 0)
            panic("fat32_inode_lock: no Attr");
    }
    return 1;
}

// 释放fat32 inode的锁
void fat32_inode_unlock(struct inode *ip) 
{
    // if (ip == 0 || !holdingsleep(&ip->i_sem) || ip->ref < 1)
    if (ip == NULL || ip->ref < 1)
        panic("fat32 unlock");
}

// fat32 inode put : trunc and update
void fat32_inode_put(struct inode *ip) {
    spin_lock(&inode_table.lock);

    if (ip->ref == 1 && ip->valid && ip->i_nlink == 0) {

        spin_unlock(&inode_table.lock);
        fat32_inode_trunc(ip);
        ip->fat32_i.Attr = 0;
        fat32_inode_update(ip);
        ip->valid = 0;

        spin_lock(&inode_table.lock);
    }

    ip->ref--;
    spin_unlock(&inode_table.lock);
}

// unlock and put
void fat32_inode_unlock_put(struct inode *ip) {
    fat32_inode_unlock(ip);
    fat32_inode_put(ip);
}

// truncate the fat32 inode
void fat32_inode_trunc(struct inode *ip) {
    FAT_entry_t iter_n = ip->fat32_i.cluster_start;
    // FAT_entry_t end = 0;
    // uint32_t FAT_sector_num;
    // uint32_t FAT_sector_offset;

    // truncate the data
    while (!ISEOF(iter_n)) {
        FAT_entry_t fat_next = fat32_next_cluster(iter_n);
        fat32_fat_set(iter_n, EOC);
        iter_n = fat_next;
    }
    fat32_inode_delete(ip->parent, ip);
    ip->fat32_i.cluster_start = 0;
    ip->fat32_i.cluster_end = 0;
    ip->fat32_i.parent_off = 0;
    ip->fat32_i.cluster_cnt = 0;
    ip->fat32_i.DIR_FileSize = 0;
    ip->i_rdev = 0;
    ip->i_mode = IMODE_NONE;
    ip->i_size = 0;
    fat32_inode_update(ip);
}

// update
void fat32_inode_update(struct inode *ip) {
    struct buffer *bp;
    bp = bread(ip->i_dev, FATINUM_TO_SECTOR(ip->i_ino));
    dirent_s_t *dirent_s_tmp = (dirent_s_t *)bp->data + FATINUM_TO_OFFSET(ip->i_ino);

    // root has no fcb, so we don't update it!!!
    if (ip->i_ino == 0) {
        brelse(bp);
        return;
    }
    // uint32_t sec_num = DEBUG_SECTOR(ip, FATINUM_TO_SECTOR(ip->i_ino)); // debug
    dirent_s_tmp->DIR_Attr = ip->fat32_i.Attr;
    dirent_s_tmp->DIR_LstAccDate = ip->fat32_i.DIR_LstAccDate;
    dirent_s_tmp->DIR_WrtDate = ip->fat32_i.DIR_WrtDate;
    dirent_s_tmp->DIR_WrtTime = ip->fat32_i.DIR_WrtTime;
    // memmove((void *)&dirent_s_tmp->DIR_LstAccDate, (void *)&ip->fat32_i.DIR_LstAccDate, sizeof(ip->fat32_i.DIR_LstAccDate));
    // memmove((void *)&dirent_s_tmp->DIR_WrtDate, (void *)&ip->fat32_i.DIR_WrtDate, sizeof(ip->fat32_i.DIR_WrtDate));
    // memmove((void *)&dirent_s_tmp->DIR_WrtTime, (void *)&ip->fat32_i.DIR_WrtTime, sizeof(ip->fat32_i.DIR_WrtTime));
    dirent_s_tmp->DIR_FstClusHI = DIR_FIRST_HIGH(ip->fat32_i.cluster_start);
    dirent_s_tmp->DIR_FstClusLO = DIR_FIRST_LOW(ip->fat32_i.cluster_start);
    // dirent_s_tmp->DIR_FileSize = ip->i_size;
    if (ip->i_type == T_DIR || ip->i_type == T_DEVICE) {
        dirent_s_tmp->DIR_FileSize = 0;
    } else {
        dirent_s_tmp->DIR_FileSize = ip->i_size;
    }

    dirent_s_tmp->DIR_Attr |= ip->i_mode;
    if (ip->i_type == T_DEVICE)
        dirent_s_tmp->DIR_Dev = ip->i_dev;
    else
        dirent_s_tmp->DIR_Dev = 0;

    bwrite(bp);
    brelse(bp);
}

int fat32_filter_longname(dirent_l_t *dirent_l_tmp, char *ret_name) {
    int idx = 0;
    for (int i = 0; i < 5; i++) {
        ret_name[idx++] = LONG_NAME_CHAR_MASK(dirent_l_tmp->LDIR_Name1[i]);
        if (!LONG_NAME_CHAR_VALID(dirent_l_tmp->LDIR_Name1[i]))
            return idx;
    }
    for (int i = 0; i < 6; i++) {
        ret_name[idx++] = LONG_NAME_CHAR_MASK(dirent_l_tmp->LDIR_Name2[i]);
        if (!LONG_NAME_CHAR_VALID(dirent_l_tmp->LDIR_Name2[i]))
            return idx;
    }
    for (int i = 0; i < 2; i++) {
        ret_name[idx++] = LONG_NAME_CHAR_MASK(dirent_l_tmp->LDIR_Name3[i]);
        if (!LONG_NAME_CHAR_VALID(dirent_l_tmp->LDIR_Name3[i]))
            return idx;
    }
    return idx;
}

uint16_t fat32_longname_popstack(Stack_t *fcb_stack, uint8_t *fcb_s_name, char *name_buf) {
    int name_idx = 0;
    uint16_t long_valid = 0;
    dirent_l_t fcb_l_tmp;
    if (stack_is_empty(fcb_stack)) {
        return 0;
    }
    uint8_t cnt = 1;
    // reverse the stack to check every long directory entry
    while (!stack_is_empty(fcb_stack)) {
        fcb_l_tmp = stack_pop(fcb_stack);
        if (!stack_is_empty(fcb_stack) && cnt != fcb_l_tmp.LDIR_Ord) {
            return 0;
        } else {
            cnt++;
        }
        uint8_t checksum = ChkSum(fcb_s_name);
        if (fcb_l_tmp.LDIR_Chksum != checksum) {
            //panic("check sum error");
            return 0;
        }
        char l_tmp[14];
        memset(l_tmp, 0, sizeof(l_tmp));
        int l_tmp_len = fat32_filter_longname(&fcb_l_tmp, l_tmp);
        for (int i = 0; i < l_tmp_len; i++) {
            name_buf[name_idx++] = l_tmp[i];
        }
    }
    name_buf[name_idx] = '\0';
    long_valid = LAST_LONG_ENTRY_BOOL(fcb_l_tmp.LDIR_Ord) ? 1 : 0;
    return long_valid;
}

// checksum
uint8_t ChkSum(uint8_t *pFcbName) {
    uint8_t Sum = 0;
    for (short FcbNameLen = 11; FcbNameLen != 0; FcbNameLen--) {
        Sum = ((Sum & 1) ? 0x80 : 0) + (Sum >> 1) + *pFcbName++;
    }
    return Sum;
}

struct inode *fat32_inode_dirlookup(struct inode *ip, const char *name, uint32_t *poff) 
{
    if (!DIR_BOOL((ip->fat32_i.Attr)))//如果不是目录
        panic("dirlookup not DIR");
    struct buffer *bp;
    struct inode *ip_search;
    FAT_entry_t iter_n = ip->fat32_i.cluster_start;

    char name_buf[NAME_LONG_MAX];
    memset(name_buf, 0, sizeof(name_buf));//初始化为0
    Stack_t fcb_stack;
    stack_init(&fcb_stack);

    int first_sector;
    uint32_t off = 0;
    // FAT seek cluster chains
    while (!ISEOF(iter_n))//不是文件结束
    {
        first_sector = FirstSectorofCluster(iter_n);//得到簇的第一个扇区
        // sectors in a cluster
        for (int s = 0; s < (ip->i_sb->sectors_per_block); s++) //遍历每个扇区
        {
            bp = bread(ip->i_dev, first_sector + s);//读一个扇区对应的buf

            dirent_s_t *fcb_s = (dirent_s_t *)(bp->data);
            dirent_l_t *fcb_l = (dirent_l_t *)(bp->data);
            int idx = 0;
            // FCB in a sector
            while (idx < FCB_PER_BLOCK) //遍历一个块中的FCB
            {
                // long dirctory item push into the stack
                // the first long directory in the data region
                if (NAME0_FREE_ALL(fcb_s[idx].DIR_Name[0])) //如果目录项的开头首字母是0
                {
                    brelse(bp);
                    stack_free(&fcb_stack);
                    return NULL;
                }
                while (LONG_NAME_BOOL(fcb_l[idx].LDIR_Attr) && idx < FCB_PER_BLOCK) //长文件名，入栈
                {
                    // printf("%d, %d, %d\n",LONG_NAME_BOOL(fcb_l[idx].LDIR_Attr), first_long_dir(ip), idx < FCB_PER_BLOCK);
                    stack_push(&fcb_stack, fcb_l[idx++]);
                    off++;//入栈，偏移量++
                }

                // pop stack 首先检查了目录项是否是长目录项，并检查了短文件名的首个字符是否是 0xE5 或 0x00。
                if (!LONG_NAME_BOOL(fcb_l[idx].LDIR_Attr) && !NAME0_FREE_BOOL(fcb_s[idx].DIR_Name[0]) && idx < FCB_PER_BLOCK) 
                {//如果name[0] == 0XE5||0X00
                    memset(name_buf, 0, sizeof(name_buf));
                    //如果都不是，则调用了函数 fat32_longname_popstack 从 fcb_stack 中弹出一个长目录项，然后将目录项的所有名称部分都复制到 name_buf 字符数组中。
                    uint16_t long_valid = fat32_longname_popstack(&fcb_stack, fcb_s[idx].DIR_Name, name_buf);

                    // if the long directory is invalid
                    if (!long_valid) //如果弹出的长目录项是无效的，则调用函数 fat32_short_name_parser 从短文件名中解析出名称，复制到 name_buf 中。
                    {
                        fat32_short_name_parser(fcb_s[idx], name_buf);
                    }

                    //  search for?
                    if (fat32_namecmp(name, name_buf) == 0) //然后，将 name_buf 中的名称与传入的 name 进行比较，如果匹配，则认为已找到所需的 inode，将它们的位置指针赋值给 poff，释放缓冲区，然后调用函数 fat32_inode_get 获取 inode。
                    {
                        // inode matches path element
                        if (poff)
                            *poff = off;
                        brelse(bp);
                        //函数 fat32_inode_get 将返回找到的 inode，该 inode 携带了所需的路径信息和文件的一些元数据信息。
                        ip_search = fat32_inode_get(ip->i_dev, SECTOR_TO_FATINUM(first_sector + s, idx), name, off);
                        ip_search->parent = ip;
                        ip_search->i_nlink = 1;

                        stack_free(&fcb_stack);
                        return ip_search;
                    }
                }
                idx++;//FCB下标+1
                off++;
            }
            brelse(bp);
        }
        iter_n = fat32_next_cluster(iter_n);//下一个簇
    }
    stack_free(&fcb_stack);
    return NULL;
}

// direntory link (hard link)
int fat32_inode_dirlink(struct inode *dp, char *name) {
    // int off;
    struct inode *ip;

    // Check that name is not present.
    if ((ip = fat32_inode_dirlookup(dp, name, 0)) != 0) {
        fat32_inode_put(ip);
        return -1;
    }
    ip->i_nlink++;
    fat32_inode_put(ip);
    return 0;
}

// create a new inode
struct inode *fat32_inode_create(char *path, uint8_t type, short major, short minor) {
    struct inode *ip = NULL, *dp = NULL;
    char name[NAME_LONG_MAX];

    // without parent fat_entry
    if ((dp = name_to_i_parent(path, name)) == 0)
        return NULL;
    fat32_inode_lock(dp);
    // fat32_inode_load_from_disk(dp);

    // have existed?
    if ((ip = fat32_inode_dirlookup(dp, name, 0)) != 0) {
        fat32_inode_unlock_put(dp);
        fat32_inode_lock(ip);

        // fat32_inode_load_from_disk(ip);
        //  if (type == T_FILE && (ip->i_type == T_FILE || ip->i_type == T_DEVICE))
        //      return ip;
        fat32_inode_unlock_put(ip);
        return ip;
        // return NULL;
    }

    // haven't exited
    if ((ip = fat32_inode_alloc(dp, name, type)) == 0) {
        fat32_inode_unlock_put(dp);
        return NULL;
    }
#ifdef __DEBUG_FS__
    if (type == T_FILE)
        printfRed("create : create file, %s\n", path);
    else if (type == T_DEVICE)
        printfRed("create : create device, %s\n", path);
    else if (type == T_DIR)
        printfRed("create : create directory, %s\n", path);
#endif
    fat32_inode_lock(ip);
    // fat32_inode_load_from_disk(ip);

    ip->i_nlink = 1;
    ip->i_rdev = mkrdev(major, minor);
    ip->i_type = type;
    fat32_inode_update(ip);

    if (type == T_DIR) { // Create . and .. entries.
        // // No ip->nlink++ for ".": avoid cyclic ref count.
        // if (fat32_inode_dirlink(ip, ".") < 0 || fat32_inode_dirlink(ip, "..") < 0)
        //     goto fail;
        // TODO : dirlink

        // direntory . and .. , write them to the disk
        uint8_t fcb_dot_char[64];
        memset(fcb_dot_char, 0, sizeof(fcb_dot_char));
        fat32_fcb_init(ip, (const uint8_t *)".", ATTR_DIRECTORY, (char *)fcb_dot_char);
        uint32_t tot = fat32_inode_write(ip, 0, (uint64_t)fcb_dot_char, 0, 32);
        ASSERT(tot == 32);

        uint8_t fcb_dotdot_char[64];
        memset(fcb_dotdot_char, 0, sizeof(fcb_dotdot_char));
        fat32_fcb_init(ip, (const uint8_t *)"..", ATTR_DIRECTORY, (char *)fcb_dotdot_char);
        tot = fat32_inode_write(ip, 0, (uint64_t)fcb_dotdot_char, 32, 32);
        ASSERT(tot == 32);
    }

    // if (fat32_inode_dirlink(dp, name) < 0)
    //     goto fail;

    if (type == T_DIR) {
        // now that success is guaranteed:
        fat32_inode_update(dp);
    }

    fat32_inode_unlock_put(dp); // !!! bug

    return ip;
}

// allocate a new inode
struct inode *fat32_inode_alloc(struct inode *dp, char *name, uint8_t type) 
{
    uint8_t attr;
    if (type == T_DIR)
        DIR_SET(attr);
    else
        NONE_DIR_SET(attr);
    uint8_t fcb_char[FCB_MAX_LENGTH];
    memset(fcb_char, 0, sizeof(fcb_char));
    int fcb_cnt = fat32_fcb_init(dp, (const uint8_t *)name, attr, (char *)fcb_char);
    // uint32_t sector_pos = FirstSectorofCluster(dp->fat32_i.cluster_start) * 512; // debug
    uint32_t offset = fat32_dir_fcb_insert_offset(dp, fcb_cnt);
    uint32_t tot = fat32_inode_write(dp, 0, (uint64_t)fcb_char, offset * sizeof(dirent_l_t), fcb_cnt * sizeof(dirent_l_t));

    ASSERT(tot == fcb_cnt * sizeof(dirent_l_t));

    struct inode *ip_new;

    uint32_t fcb_new_off = (offset + fcb_cnt - 1) * sizeof(dirent_s_t);
    uint32_t C_NUM = LOGISTIC_C_NUM(fcb_new_off) + 1;
    // find the target cluster of off
    uint32_t target_cluster = fat32_fat_travel(dp, C_NUM);
    uint32_t first_sector = FirstSectorofCluster(target_cluster);

    uint32_t C_OFFSET = LOGISTIC_C_OFFSET(fcb_new_off);
    uint32_t sector_num = first_sector + C_OFFSET / fat32_sb.sector_size;
    uint32_t sector_offset = (C_OFFSET % fat32_sb.sector_size) / sizeof(dirent_l_t);
    uint32_t fat_num = SECTOR_TO_FATINUM(sector_num, sector_offset);

    // // first_sector = FirstSectorofCluster(target_cluster); // debug
    // sector_num = first_sector + C_OFFSET / FCB_PER_BLOCK;
    // uint32_t sec_pos = DEBUG_SECTOR(dp, sector_num); // debug
    // printf("%d\n",sec_pos); // debug

    ip_new = fat32_inode_get(dp->i_dev, fat_num, name, offset + fcb_cnt - 1);
    ip_new->i_nlink = 1;
    ip_new->ref = 1;
    ip_new->parent = dp;
    ip_new->i_type = type;
    
    ip_new->i_op = get_inodeops[FAT32]();
    ip_new->fs_type = FAT32;
    // ip_new->i_sb = &fat32_sb;

    // uint32_t fat_num_dp = SECTOR_TO_FATINUM(first_sector, 0); // debug
    // uint32_t sector_pos = FirstSectorofCluster(ip_new->fat32_i.cluster_start) * 512; // debug
    return ip_new;
}

// fcb init
// 为 long_name 初始化若干个 dirent_l_t 和一个dirent_s_t，写入 fcb_char中，返回需要的 fcb 总数
int fat32_fcb_init(struct inode *ip_parent, const uint8_t *long_name, uint8_t attr, char *fcb_char) 
{
    dirent_s_t dirent_s_cur;
    memset((void *)&dirent_s_cur, 0, sizeof(dirent_s_cur));
    // dirent_l_t dirent_l_cur;
    dirent_s_cur.DIR_Attr = attr;

    uint32_t long_idx = -1;

    // . and ..
    if (!fat32_namecmp((const char *)long_name, ".") || !fat32_namecmp((const char *)long_name, "..")) {
        strncpy((char *)dirent_s_cur.DIR_Name, (const char *)long_name, strlen((const char *)long_name));
        dirent_s_cur.DIR_FileSize = 0;
        dirent_s_cur.DIR_FstClusHI = DIR_FIRST_HIGH(ip_parent->fat32_i.cluster_start);
        dirent_s_cur.DIR_FstClusLO = DIR_FIRST_LOW(ip_parent->fat32_i.cluster_start);
        memmove(fcb_char, &dirent_s_cur, sizeof(dirent_s_cur));
        return 1;
    }

    int ret_cnt = 0;
    char file_name[NAME_LONG_MAX];
    char file_ext[4];
    /*short dirent*/
    int name_len = strlen((const char *)long_name);
    // 数据文件
    if (!DIR_BOOL(attr)) {
        if (str_split((const char *)long_name, '.', file_name, file_ext) == -1) {
            // printfRed("it is a file without extname\n");
            strncpy(file_name, (char *)long_name, 8);
            dirent_s_cur.DIR_Name[8] = 0x20;
            dirent_s_cur.DIR_Name[9] = 0x20;
            dirent_s_cur.DIR_Name[10] = 0x20;
        } 
        else 
        {
            str_toupper(file_ext);
            strncpy((char *)dirent_s_cur.DIR_Name + 8, file_ext, 3); // extend name
            if (strlen(file_ext) == 2) 
            {
                dirent_s_cur.DIR_Name[10] = 0x20;
            }
            if (strlen(file_ext) == 1) 
            {
                dirent_s_cur.DIR_Name[10] = 0x20;
                dirent_s_cur.DIR_Name[9] = 0x20;
            }
        }

        str_toupper(file_name);
        strncpy((char *)dirent_s_cur.DIR_Name, (char *)file_name, 8);
        if (strlen((char *)long_name) > 8) 
        {
            long_idx = fat32_find_same_name_cnt(ip_parent, file_name);
            dirent_s_cur.DIR_Name[6] = '~';
            dirent_s_cur.DIR_Name[7] = long_idx + 0x31;
        }
    } else {
        // 目录文件
        strncpy(file_name, (char *)long_name, 11);

        str_toupper(file_name);
        strncpy((char *)dirent_s_cur.DIR_Name, file_name, 8);
        if (strlen((const char *)long_name) > 8) {
            long_idx = fat32_find_same_name_cnt(ip_parent, file_name);

            // strncpy(dirent_s_cur.DIR_Name + 8, file_name + (name_len - 3), 3); // last three char
            dirent_s_cur.DIR_Name[6] = '~';
            dirent_s_cur.DIR_Name[7] = long_idx + 0x31;
            memset(dirent_s_cur.DIR_Name + 8, 0x20, 3);
        }
    }
    dirent_s_cur.DIR_FileSize = 0;

    uint32_t first_c = fat32_cluster_alloc(ip_parent->i_dev);
    dirent_s_cur.DIR_FstClusHI = DIR_FIRST_HIGH(first_c);
    dirent_s_cur.DIR_FstClusLO = DIR_FIRST_LOW(first_c);

    /*push long dirent into stack*/
    Stack_t fcb_stack;
    stack_init(&fcb_stack);
    // int iter_order = 1;      // the compiler says it's an unused variable
    uint8_t checksum = ChkSum(dirent_s_cur.DIR_Name);
#ifdef __DEBUG_FS__
    printf("inode init : pid %d, %s, checksum = %x \n", current()->pid, long_name, checksum);
#endif
    int char_idx = 0;
    // every long name entry
    int ord_max = CEIL_DIVIDE(name_len, FAT_LFN_LENGTH);
    for (int i = 1; i <= ord_max; i++) {
        dirent_l_t dirent_l_cur;
        memset((void *)&(dirent_l_cur), 0xFF, sizeof(dirent_l_cur));
        if (char_idx == name_len)
            break;

        // order
        if (i == ord_max)
            dirent_l_cur.LDIR_Ord = LAST_LONG_ENTRY_SET(i);
        else
            dirent_l_cur.LDIR_Ord = i;

        // Name
        int end_flag = 0;
        for (int i = 0; i < 5 && !end_flag; i++) {
            dirent_l_cur.LDIR_Name1[i] = LONG_NAME_CHAR_SET(long_name[char_idx]);
            if (!LONG_NAME_CHAR_VALID(long_name[char_idx]))
                end_flag = 1;
            char_idx++;
        }
        for (int i = 0; i < 6 && !end_flag; i++) {
            dirent_l_cur.LDIR_Name2[i] = LONG_NAME_CHAR_SET(long_name[char_idx]);
            if (!LONG_NAME_CHAR_VALID(long_name[char_idx]))
                end_flag = 1;
            char_idx++;
        }
        for (int i = 0; i < 2 && !end_flag; i++) {
            dirent_l_cur.LDIR_Name3[i] = LONG_NAME_CHAR_SET(long_name[char_idx]);
            if (!LONG_NAME_CHAR_VALID(long_name[char_idx]))
                end_flag = 1;
            char_idx++;
        }

        // Attr  and  Type
        dirent_l_cur.LDIR_Attr = ATTR_LONG_NAME;
        dirent_l_cur.LDIR_Type = 0;

        // check sum
        dirent_l_cur.LDIR_Chksum = checksum;

        // must set to zero
        dirent_l_cur.LDIR_Nlinks = 0;
        stack_push(&fcb_stack, dirent_l_cur);
    }

    dirent_l_t fcb_l_tmp;
    while (!stack_is_empty(&fcb_stack)) {
        fcb_l_tmp = stack_pop(&fcb_stack);
        memmove(fcb_char, &fcb_l_tmp, sizeof(fcb_l_tmp));
        fcb_char = fcb_char + sizeof(fcb_l_tmp);
        ret_cnt++;
    }
    // the first long dirent
    fcb_l_tmp.LDIR_Nlinks = 1;
    memmove(fcb_char, &dirent_s_cur, sizeof(dirent_s_cur));
    stack_free(&fcb_stack);
    return ret_cnt + 1;
    // TODO: 获取当前时间和日期，还有TimeTenth
}

// find the same prefix and same extend name !!!
uint32_t fat32_find_same_name_cnt(struct inode *ip, char *name) 
{
    if (!DIR_BOOL((ip->fat32_i.Attr)))
        panic("find same name cnt not DIR");

    struct buffer *bp;
    FAT_entry_t iter_n = ip->fat32_i.cluster_start;

    int first_sector;
    int ret = 0;

    str_toupper(name);
    // FAT seek cluster chains
    while (!ISEOF(iter_n)) {
        first_sector = FirstSectorofCluster(iter_n);
        // sectors in a cluster
        for (int s = 0; s < (ip->i_sb->sectors_per_block); s++) {
            bp = bread(ip->i_dev, first_sector + s);
            dirent_s_t *fcb_s = (dirent_s_t *)(bp->data);
            int idx = 0;
            // FCB in a sector
            while (idx < FCB_PER_BLOCK) {
                if (!LONG_NAME_BOOL(fcb_s[idx].DIR_Attr) && !NAME0_FREE_BOOL(fcb_s[idx].DIR_Name[0])) {
                    // is our search for?
                    // extend name should be matched!!!
                    if (!strncmp((char *)fcb_s[idx].DIR_Name, name, 6) && fcb_s[idx].DIR_Name[6] == '~') {
                        ret++;
                    }
                }
                if (NAME0_FREE_ALL(fcb_s[idx].DIR_Name[0])) {
                    brelse(bp);
                    return ret;
                }
                idx++;
            }
            brelse(bp);
        }
        iter_n = fat32_next_cluster(iter_n);
    }
    return ret;
}

// 获取fcb的插入位置(可以插入到碎片中)
// 在目录节点中找到能插入 fcb_cnt_req 个 fcb 的启始偏移位置，并返回它
uint32_t fat32_dir_fcb_insert_offset(struct inode *ip, uint8_t fcb_cnt_req) 
{
    struct buffer *bp;
    FAT_entry_t iter_n = ip->fat32_i.cluster_start;
    // uint32_t FAT_sec_no;   // the compiler says it's an unused variable
    uint32_t first_sector;

    uint8_t fcb_free_cnt = 0;
    uint32_t offset_ret_base = DIRLENGTH(ip) / sizeof(dirent_l_t);
    uint32_t offset_ret_final = 0; // 为通过编译给一个初始值

    uint32_t idx = 0;
    while (!ISEOF(iter_n)) {
        first_sector = FirstSectorofCluster(iter_n);
        for (int s = 0; s < ip->i_sb->sectors_per_block; s++) {
            bp = bread(ip->i_dev, first_sector + s);
            dirent_s_t *diernt_s_tmp = (dirent_s_t *)(bp->data);
            for (int i = 0; i < FCB_PER_BLOCK; i++, idx++) {
                if (!NAME0_FREE_BOOL(diernt_s_tmp[i].DIR_Name[0])) {
                    fcb_free_cnt = 0;
                    offset_ret_final = offset_ret_base;
                } else {
                    if (fcb_free_cnt == 0) {
                        offset_ret_final = idx;
                    }
                    fcb_free_cnt++;
                    if (fcb_free_cnt == fcb_cnt_req) {
                        brelse(bp);
                        return offset_ret_final;
                    }
                }
            }
            brelse(bp);
        }
        iter_n = fat32_next_cluster(iter_n);
    }
    return offset_ret_final;
}

inline int fat32_isdir(struct inode *ip) {
    return DIR_BOOL(ip->fat32_i.Attr);
}

// 一个目录除了 .. 和 . 是否为空？
int fat32_isdirempty(struct inode *ip) 
{
    struct buffer *bp;
    FAT_entry_t iter_n = ip->fat32_i.cluster_start;
    uint32_t first_sector;

    while (!ISEOF(iter_n)) {
        first_sector = FirstSectorofCluster(iter_n);

        for (int s = 0; s < ip->i_sb->sectors_per_block; s++) {
            bp = bread(ip->i_dev, first_sector + s);
            dirent_s_t *diernt_s_tmp = (dirent_s_t *)(bp->data);
            for (int i = 0; i < FCB_PER_BLOCK; i++) {
                // not free
                if (!NAME0_FREE_BOOL(diernt_s_tmp[i].DIR_Name[0])) {
                    if (fat32_namecmp((char *)diernt_s_tmp[i].DIR_Name, ".") && fat32_namecmp((char *)diernt_s_tmp[i].DIR_Name, "..")) {
                        brelse(bp); // !!!!
                        return NULL;
                    }
                }
            }
            brelse(bp);
        }
        iter_n = fat32_next_cluster(iter_n);
    }
    return 1;
}

// get time string
// int fat32_time_parser(uint16_t *time_in, char *str, int ms) {
//     uint32_t CreateTimeMillisecond;
//     uint32_t TimeSecond = time_in->second_per_2 << 1;
//     uint32_t TimeMinute = time_in->minute;
//     uint32_t TimeHour = time_in->hour;

//     if (ms) {
//         CreateTimeMillisecond = (uint32_t)(ms)*10; // 计算毫秒数
//         sprintf(str, "%d:%02d:%02d.%03d", TimeHour, TimeMinute, TimeSecond, CreateTimeMillisecond);
//     } else {
//         sprintf(str, "%d:%02d:%02d", TimeHour, TimeMinute, TimeSecond);
//     }

//     return 1;
// }

// get date string
// int fat32_date_parser(uint16_t *date_in, char *str) {
//     uint32_t TimeDay = date_in->day;
//     uint32_t TimeMonth = date_in->month;
//     uint32_t TimeYear = date_in->year + 1980;

//     sprintf(str, "%04d-%02d-%02d", TimeYear, TimeMonth, TimeDay);

//     return 1;
// }

void fat32_inode_stati(struct inode *ip, struct kstat *st) 
{
    ASSERT(ip && st);
    st->st_atime_sec = ip->i_atime;
    st->st_atime_nsec = ip->i_atime * 1000000000;
    st->st_blksize = ip->i_blksize;
    st->st_blocks = ip->i_blocks;
    st->st_ctime_sec = ip->i_ctime;
    st->st_ctime_nsec = ip->i_ctime * 1000000000;
    st->st_dev = ip->i_dev;
    st->st_gid = ip->i_gid;
    st->st_ino = ip->i_ino;
    st->st_mode = ip->i_mode;
    st->st_mtime_sec = ip->i_mtime;
    st->st_mtime_nsec = ip->i_mtime * 1000000000;
    st->st_nlink = ip->i_nlink;
    st->st_rdev = ip->i_rdev;
    st->st_size = ip->i_size;
    st->st_uid = ip->i_uid;
    return;
}

// delete inode given its parent dp
int fat32_inode_delete(struct inode *dp, struct inode *ip) 
{
    int str_len = strlen(ip->fat32_i.fname);
    int off = ip->fat32_i.parent_off;
    ASSERT(off > 0);
    int long_dir_len = CEIL_DIVIDE(str_len, FAT_LFN_LENGTH); // 上取整
    char fcb_char[FCB_MAX_LENGTH];
    memset(fcb_char, 0, sizeof(fcb_char));
    for (int i = 0; i < long_dir_len + 1; i++)
        fcb_char[i * 32] = 0xE5;
    ASSERT(off - long_dir_len > 0);
#ifdef __DEBUG_FS__
    printf("inode delete : pid %d, %s, off = %d, long_dir_len = %d\n", current()->pid, ip->fat32_i.fname, off, long_dir_len);
#endif
    uint32_t tot = fat32_inode_write(dp, 0, (uint64_t)fcb_char, (off - long_dir_len) * sizeof(dirent_s_t), (long_dir_len + 1) * sizeof(dirent_s_t));
    ASSERT(tot == (long_dir_len + 1) * sizeof(dirent_l_t));
    return 0;
}

// zero cluster
void fat32_zero_cluster(uint64_t c_num) 
{
    struct buffer *bp;
    int first_sector;
    first_sector = FirstSectorofCluster(c_num);//通过调用 FirstSectorofCluster 函数计算出要清空的簇对应的第一个扇区号 first_sector
    for (int s = 0; s < (fat32_sb.sectors_per_block); s++) //循环读取要清空的簇的每个扇区
    {
        bp = bread(fat32_sb.s_dev, first_sector + s);//使用 bread() 函数读取簇号对应的扇区数据，并把数据存储到bp的data成员中
        memset(bp->data, 0, BUFFER_SIZE);//使用 memset() 函数将扇区数据清空为 0
        bwrite(bp);//使用 bwrite() 函数将清空后的扇区数据写回磁盘
        brelse(bp);//使用 brelse() 函数释放访问这些数据时所用的缓存
    }
    return;
}

void fat32_short_name_parser(dirent_s_t dirent_s, char *name_buf) {
    int len_name = 0;
    for (int i = 0; i < 8; i++) {
        if (dirent_s.DIR_Name[i] != 0x20) {
            name_buf[len_name++] = dirent_s.DIR_Name[i];
        }
    }
    if (dirent_s.DIR_Name[8] != 0x20) {
        name_buf[len_name++] = '.';
        for (int i = 8; i < 11; i++) {
            if (dirent_s.DIR_Name[i] != 0x20) {
                name_buf[len_name++] = dirent_s.DIR_Name[i];
            }
        }
    }
    name_buf[len_name] = '\0';
}

// get time string
// int fat32_time_parser(uint16_t *time_in, char *str, int ms) {
//     uint32_t CreateTimeMillisecond;
//     uint32_t TimeSecond = time_in->second_per_2 << 1;
//     uint32_t TimeMinute = time_in->minute;
//     uint32_t TimeHour = time_in->hour;

//     if (ms) {
//         CreateTimeMillisecond = (uint32_t)(ms)*10; // 计算毫秒数
//         sprintf(str, "%d:%02d:%02d.%03d", TimeHour, TimeMinute, TimeSecond, CreateTimeMillisecond);
//     } else {
//         sprintf(str, "%d:%02d:%02d", TimeHour, TimeMinute, TimeSecond);
//     }

//     return 1;
// }

// get date string
// int fat32_date_parser(uint16_t *date_in, char *str) {
//     uint32_t TimeDay = date_in->day;
//     uint32_t TimeMonth = date_in->month;
//     uint32_t TimeYear = date_in->year + 1980;

//     sprintf(str, "%04d-%02d-%02d", TimeYear, TimeMonth, TimeDay);

//     return 1;
// }

// get time now
// uint16_t fat32_inode_get_time(int *ms) {
//     // TODO
//     // uint16_t time_ret;
//     // uint64_t count;

//     // asm volatile("rdtime %0" : "=r"(count));
//     // // second and its reminder
//     // uint64_t tick_per_second = 10000000;   // 时钟频率为 32.768 kHz
//     // uint64_t seconds = count / tick_per_second;
//     // uint64_t remainder = count % tick_per_second;

//     // // hour minute second
//     // uint64_t total_seconds = (uint32_t)seconds;
//     // uint64_t sec_per_hour = 3600;
//     // uint64_t sec_per_minute = 60;

//     // time_ret.hour = total_seconds / sec_per_hour;
//     // time_ret.minute = (total_seconds / sec_per_minute) % 60;
//     // time_ret.second_per_2 = (total_seconds % 60)>>1;
//     // if(ms)
//     // {
//     //     // million second
//     //     uint64_t tick_per_ms = tick_per_second / 1000;
//     //     *ms = remainder / tick_per_ms;
//     // }
//     // return time_ret;

//     return TODO();
// }

// get date now
// uint16_t fat32_inode_get_date() {
//     // TODO
// }
