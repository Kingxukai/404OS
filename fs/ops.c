#include "../include/type.h"
#include "../include/fs/fs.h"
#include "../include/fs/fat32_file.h"
#include "../include/fs/fcntl.h"
#include "../include/usr/lib.h"
#include "../include/sched.h"
#include "../include/macro.h"

const struct inode_operations* (*get_inodeops[])(void);
const struct file_operations* (*get_fileops[])(void);

struct devsw devsw[NDEV];
struct ftable _ftable;

// == file layrer ==
struct file *filealloc(void) //分配一个file，返回该file指针
{
// Allocate a file structure.
// 语义：从内存中的 _ftable 中寻找一个空闲的 file 项，并返回指向该 file 的指针
    struct file *f;

    spin_lock(&_ftable.lock);
    for (f = _ftable.file; f < _ftable.file + NFILE; f++) 
    {
        if (f->f_count == 0) 
        {
            f->f_count = 1;

            // f->f_op = get_fat32_fileops();
            ASSERT(current->_cwd->fs_type==FAT32);
            f->f_op = get_fileops[current->_cwd->fs_type]();
            
            spin_unlock(&_ftable.lock);
            return f;
        }
    }
    spin_unlock(&_ftable.lock);
    return 0;
}

void generic_fileclose(struct file *f) //关闭一个file,参数：file指针
{
// Close file f.  (Decrement ref count, close when reaches 0.)
// 语义：自减 f 指向的file的引用次数，如果为0，则关闭
// 对于管道文件，调用pipeclose
// 否则，调用iput归还inode节点
    struct file ff;

    spin_lock(&_ftable.lock);
    if (f->f_count < 1)
        panic("generic_fileclose");
    if (--f->f_count > 0) 
    {
        spin_unlock(&_ftable.lock);
        return;
    }
    ff = *f;
    f->f_count = 0;
    f->f_type = FD_NONE;
    spin_unlock(&_ftable.lock);

    /*if (ff.f_type == FD_PIPE) {
        int wrable = F_WRITEABLE(&ff);
        pipeclose(ff.f_tp.f_pipe, wrable);
    } else */
    if (ff.f_type == FD_INODE || ff.f_type == FD_DEVICE) 
    {
        // begin_op();
        // fat32_inode_put(ff.f_tp.f_inode);
        ff.f_tp.f_inode->i_op->iput(ff.f_tp.f_inode);
        // end_op();
    }
}

static inline const struct file_operations* get_fat32_fileops(void) //返回一个文件操作的结构体指针
{
    // Mayer's singleton
    static const struct file_operations fops_instance = 
    {
        .dup = fat32_filedup,
        .read = fat32_fileread,
        .write = fat32_filewrite,
        //.fstat = fat32_filestat,
    };

    return &fops_instance;
}

        // Not to be moved upward 
const struct file_operations* (*get_fileops[])(void) = //定义一个指针常量数组，
{
    [FAT32] get_fat32_fileops,
    //[EXT2] get_ext2_fileops,
};



// == inode layer ==
static char *skepelem(char *path, char *name);
static struct inode *inode_namex(char *path, int nameeparent, char *name);

struct inode* name_to_i(char *path) //将path转换为inode
{
    char name[NAME_LONG_MAX];
    return inode_namex(path, 0, name);
}

struct inode* name_to_i_parent(char *path, char *name) //将path转化为父节点的inode
{
    return inode_namex(path, 1, name);
}

struct inode *find_inode(char *path, int dirfd, char *name) {
// 如果path是相对路径，则它是相对于dirfd目录而言的。
// 如果path是相对路径，且dirfd的值为AT_FDCWD，则它是相对于当前路径而言的。
// 如果path是绝对路径，则dirfd被忽略。
// 一般不对 path作检查
// 如果name字段不为null，返回的是父目录的inode节点，并填充name字段
    ASSERT(path);
    struct inode *ip;
    struct task_struct *p = current;
    if (*path == '/' || dirfd == AT_FDCWD) //如果path是"/"或者标志是处于当前工作目录
    {
        // 绝对路径 || 相对于当前路径，忽略 dirfd
        // spin_lock(&p->tlock);
        ip = (!name) ? name_to_i(path) : name_to_i_parent(path, name);//如果文件名是NULL，则把路径转化为结点；否则把父目录的结点返回
        if (ip == 0) 
        {
            // spin_unlock(&p->tlock);
            return 0;
        } 
        else 
        {
            // spin_unlock(&p->tlock);
            return ip;
        }
    } 
    else 
    {
        // path为相对于 dirfd目录的路径
        struct file *f;
        // spin_lock(&p->tlock);
        if (dirfd < 0 || dirfd >= NOFILE || (f = p->_ofile[dirfd]) == 0) 
        {
            // spin_unlock(&p->tlock);
            return 0;
        }
        struct inode *oldcwd = p->_cwd;
        p->_cwd = f->f_tp.f_inode;//当前进程的工作目录设定为文件结点
        ip = (!name) ? name_to_i(path) : name_to_i_parent(path, name);
        if (ip == 0) 
        {
            // spin_unlock(&p->tlock);
            return 0;
        }
        p->_cwd = oldcwd;
        // spin_unlock(&p->tlock);
    }

    return ip;
}

static char *skepelem(char *path, char *name) {
// Examples:
//   skepelem("a/bb/c", name) = "bb/c", setting name = "a"
//   skepelem("///a//bb", name) = "bb", setting name = "a"
//   skepelem("a", name) = "", setting name = "a"
//   skepelem("", name) = skepelem("////", name) = 0

//   skepelem("./mnt", name) = "", setting name = "mnt"
//   skepelem("../mnt", name) = "", setting name = "mnt"
//   skepelem("..", name) = "", setting name = 0
    char *s;
    int len;

    while (*path == '/' || *path == '.')
        path++;
    if (*path == 0)
        return 0;
    s = path;
    while (*path != '/' && *path != 0)
        path++;
    len = path - s;
    if (len >= PATH_LONG_MAX)
        memmove(name, s, PATH_LONG_MAX);
    else {
        memmove(name, s, len);
        name[len] = 0;
    }
    while (*path == '/')
        path++;
    return path;
}

static struct inode *inode_namex(char *path, int nameeparent, char *name) {
    struct inode *ip = NULL, *next = NULL, *cwd = current->_cwd;
    ASSERT(cwd);
    if (*path == '/') 
    {
        ASSERT(cwd->i_sb);
        ASSERT(cwd->i_sb->root);
        struct inode *rip = cwd->i_sb->root; 
        // ip = fat32_inode_dup(cwd->i_sb->root);
        ip = rip->i_op->idup(rip);//得到一个当前进程所处文件系统下的root的结点
    }
    else if (strncmp(path, "..", 2) == 0) //如果是指向父节点
    {
        ip = cwd->parent->i_op->idup(cwd->parent);//得到一个当前进程的工作目录下的父进程的结点
    } 
    else 
    {
        // ip = fat32_inode_dup(cwd);
        ip = cwd->i_op->idup(cwd);//得到一个当前进程工作目录的结点
    }

    while ((path = skepelem(path, name)) != 0) //得到一个相对路径
    {
        // fat32_inode_lock(ip);
        ip->i_op->ilock(ip);
        // not a directory?
        // if (!DIR_BOOL(ip->fat32_i.Attr)) {
        if (!ip->i_op->idir(ip)) //如果不是一个目录结点
        {
            // fat32_inode_unlock_put(ip);
            ip->i_op->iunlock_put(ip);
            return 0;
        }
        if (nameeparent && *path == '\0') 
        {
            // Stop one level early.
            // fat32_inode_unlock(ip);
            ip->i_op->iunlock(ip);
            return ip;
        }
        // if ((next = fat32_inode_dirlookup(ip, name, 0)) == 0) {
        if ((next = ip->i_op->idirlookup(ip,name,0) ) == 0) //没找到
        {
            // fat32_inode_unlock_put(ip);
            ip->i_op->iunlock_put(ip);
            return 0;
        }
        // fat32_inode_unlock_put(ip);
        ip->i_op->iunlock_put(ip);
        ip = next;
    }

    if (nameeparent) 
    {
        // fat32_inode_put(ip);
        ip->i_op->iput(ip);
        return 0;
    }

    if (!ip->i_op) 
    {
        // Log("ip iop invalid!");
        // ip->i_op = get_fat32_iops();
        ASSERT(cwd->fs_type==FAT32);
        ip->i_op = get_inodeops[cwd->fs_type]();
    }

    return ip;
}

static inline const struct inode_operations* get_fat32_iops(void) {
    static const struct inode_operations iops_instance = {
        .iunlock_put = fat32_inode_unlock_put,
        .iunlock = fat32_inode_unlock,
        .iput = fat32_inode_put,
        .ilock = fat32_inode_lock,
        .itrunc = fat32_inode_trunc,
        .iupdate = fat32_inode_update,
        .idirlookup = fat32_inode_dirlookup,
        .idelete = fat32_inode_delete,
        .idempty = fat32_isdirempty,
        .igetdents = fat32_getdents,
        .idup = fat32_inode_dup,
        .idir = fat32_isdir,
    };

    return &iops_instance;
}

static inline const struct inode_operations* get_ext2_iops(void) {
    ASSERT(0);
    return NULL;
}

        // Not to be moved upward
const struct inode_operations* (*get_inodeops[])(void) = {
    [FAT32] get_fat32_iops,
    [EXT2] get_ext2_iops,
};
