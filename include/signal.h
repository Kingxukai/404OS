#ifndef _SIGNAL_H__
#define _SIGNAL_H__

//ref Linux011

#define SIGHUP 1 // Hang Up – 挂断控制终端或进程。
#define SIGINT 2 // Interrupt – 来自键盘的中断。
#define SIGQUIT 3 // Quit – 来自键盘的退出。
#define SIGILL 4 // Illeagle – 非法指令。
#define SIGTRAP 5 // Trap – 跟踪断点。
#define SIGABRT 6 // Abort – 异常结束。
#define SIGIOT 6 // IO Trap – 同上。
#define SIGUNUSED 7 // Unused – 没有使用。
#define SIGFPE 8 // FPE – 协处理器出错。
#define SIGKILL 9 // Kill – 强迫进程终止。
#define SIGUSR1 10 // User1 – 用户信号1，进程可使用。
#define SIGSEGV 11 // Segment Violation – 无效内存引用。
#define SIGUSR2 12 // User2 – 用户信号2，进程可使用。
#define SIGPIPE 13 // Pipe – 管道写出错，无读者。
#define SIGALARM 14 // Alarm – 实时定时器报警。
#define SIGTERM 15 // Terminate – 进程终止。
#define SIGSTKFLT 16 // Stack Fault – 栈出错（协处理器）。
#define SIGCHLD 17 // Child – 子进程停止或被终止。
#define SIGCONT 18 // Continue – 恢复进程继续执行。
#define SIGSTOP 19 // Stop – 停止进程的执行。
#define SIGTSTP 20 // TTY Stop – tty 发出停止进程，可忽略。
#define SIGTTIN 21 // TTY In – 后台进程请求输入。
#define SIGTTOU 22 // TTY Out – 后台进程请求输出。

//here we set each signal to corresponding bit
#define SIG_HUP     (1<<(SIGHUP-1))
#define SIG_INT     (1<<(SIGINT-1))
#define SIG_QUIT    (1<<(SIGQUIT-1))
#define SIG_ILL     (1<<(SIGILL-1))
#define SIG_TRAP    (1<<(SIGTRAP-1))
#define SIG_ABRT    (1<<(SIGABRT-1))
#define SIG_IOT     (1<<(SIGIOT-1))
#define SIG_UNUSED  (1<<(SIGUNUSED-1))
#define SIG_FPE     (1<<(SIGFPE-1))
#define SIG_KILL    (1<<(SIGKILL-1))
#define SIG_USR1    (1<<(SIGUSR1-1))
#define SIG_SEGV    (1<<(SIGSEGV-1))
#define SIG_USR2    (1<<(SIGUSR2-1))
#define SIG_PIPE    (1<<(SIGPIPE-1))
#define SIG_ALARM   (1<<(SIGALRM-1))
#define SIG_TERM    (1<<(SIGTERM-1))
#define SIG_STKFLT  (1<<(SIGSTKFLT-1))
#define SIG_CHLD    (1<<(SIGCHLD-1))
#define SIG_CONT    (1<<(SIGCONT-1))
#define SIG_STOP    (1<<(SIGSTOP-1))
#define SIG_TSTP    (1<<(SIGTSTP-1))
#define SIG_TTIN    (1<<(SIGTTIN-1))
#define SIG_TTOU    (1<<(SIGTTOU-1))

#endif
