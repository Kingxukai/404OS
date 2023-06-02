#ifndef _FAT32_FILE_H__
#define _FAT32_FILE_H__

#include "fs.h"

extern struct devsw devsw[];

void fat32_fileinit(void);
struct file *fat32_filedup(struct file *);
ssize_t fat32_fileread(struct file *, uint64_t, int n);
int fat32_filestat(struct file *, uint64_t addr);
ssize_t fat32_filewrite(struct file *, uint64_t, int n);
void fat32_getcwd(char *buf);
ssize_t fat32_getdents(struct inode *dp, char *buf, uint32_t len);

int argfd(int n, int *pfd, struct file **pf);
int argint(int n, int *ip);
// implement file_operations( ==ignore== )
// char *fat32_getcwd(char *__user buf, size_t size);
// int fat32_pipe2(int fd[2], int flags);
// int fat32_dup(int fd);
// int fat32_dup3(int oldfd, int newfd, int flags);
// int fat32_chdir(const char *path);
// int fat32_openat(int dirfd, const char *pathname, int flags, mode_t mode);
// int fat32_close(int fd);
// ssize_t fat32_getdents64(int fd, void *dirp, size_t count);
// ssize_t fat32_read(int fd, void *buf, size_t count);
// ssize_t fat32_write(int fd, const void *buf, size_t count);
// int fat32_linkat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, int flags);
// int fat32_unlinkat(int dirfd, const char *pathname, int flags);
// int fat32_mkdirat(int dirfd, const char *pathname, mode_t mode);
// int fat32_umount2(const char *target, int flags);
// int fat32_mount(const char *source, const char *target, const char *filesystemtype, unsigned long mountflags, const void *data);
// int fat32_fstat(int fd, struct kstat *statbuf);

// inline const struct file_operations *get_fat32_fops() {
//     const static struct file_operations fat32_file_operations = {
//         .chdir = fat32_chdir,
//         .close = fat32_close,
//         .dup3 = fat32_dup3,
//         // .fstat = fat32_fstat,
//         .getcwd = fat32_getcwd,
//         .getdents64 = fat32_getdents64,
//         .linkat = fat32_linkat,
//         .mkdirat = fat32_mkdirat,
//         .mount = fat32_mount,
//         .write = fat32_write,
//     };

//     return &fat32_file_operations;
// }
#endif
