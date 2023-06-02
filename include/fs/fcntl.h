#ifndef _FCNTL_H__
#define _FCNTL_H__

// f_flags
#define O_RDONLY 0x000//只读的方式打开文件
#define O_WRONLY 0x001//只写的方式打开文件
#define O_RDWR 0x002//以读写方式打开文件
#define O_CREATE 0x40//如果文件不存在，则创建文件；如果文件已存在，则以指定方式打开
#define O_DIRECTORY 0x0200000//表示打开的对象是目录而不是文件
// #define O_CREATE 0x200      // for xv6
#define O_TRUNC 0x400

//用于检查一个文件指针 fp 是否可写或可读。它们使用文件指针中的 f_flags 成员来判断。
#define F_WRITEABLE(fp) ((fp)->f_flags > 0 ? 1 : 0)
#define F_READABLE(fp) (((fp)->f_flags & O_WRONLY) == O_WRONLY ? 0 : 1)

// f_mode
#define IMODE_READONLY 0x01//只读访问模式
#define IMODE_NONE 0x00//无权限访问模式

//内存映射
#define PROT_NONE 0x0//不允许任何访问
#define PROT_READ 0x1//页面可以被读取
#define PROT_WRITE 0x2//页面可以被写入
#define PROT_EXEC 0x4//页面可以执行

//内存映射标志用于指定 mmap 的行为
#define MAP_FILE 0//映射文件到内存（实际上是虚拟内存空间)
#define MAP_SHARED 0x01//共享内存映射，对映射内存的更改会影响该文件的所有其他映射
#define MAP_PRIVATE 0x02//私有内存映射，对映射内存的更改不会影响到该文件的其他映射，而是通过 COW（拷贝写）操作管理

//用当前工作目录（current working directory）作为参考
#define AT_FDCWD -100

#endif // __FCNTL_H__
