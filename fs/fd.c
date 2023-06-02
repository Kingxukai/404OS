#include "../include/fs/fs.h"
#include "../include/lock.h"
#include "../include/sched.h"

static uint64_t argraw(int n) {
    struct task_struct *p = current;
    switch (n) {
    case 0:
        return p->context.a0;
    case 1:
        return p->context.a1;
    case 2:
        return p->context.a2;
    case 3:
        return p->context.a3;
    case 4:
        return p->context.a4;
    case 5:
        return p->context.a5;
    }
    panic("argraw");
    return -1;
}

int argint(int n, int *ip) {
    *ip = argraw(n);
    if (*ip < 0)
        return -1;
    else
        return 0;
}
int argfd(int n, int *pfd, struct file **pf) 
{
    int fd;
    struct file *f;
    struct task_struct *p = current;
    argint(n, &fd);
    if (fd < 0 || fd >= NOFILE)
        return -1;

    // in case another thread writes after the current thead reads
    if ((f = current->_ofile[fd]) == 0) {
        return -1;
    } else {
        if (pfd)
            *pfd = fd;
        if (pf)
            *pf = f;
    }
    return 0;
}
