# OSKernel2023-404OS

<mark>Team_name:404OS\
School_name:Shenyang Aerospace University（SAU）</mark>

## 文件树(file tree)

.
├── 404OS.ld<br>
├── BOOT<br>
│   └── boot.S<br>
├── common.mk<br>
├── gdbinit<br>
├── include<br>
│   ├── asm<br>
│   │   ├── riscv64.h<br>
│   │   └── system.h<br>
│   ├── errno.h<br>
│   ├── kernel.h<br>
│   ├── lock.h<br>
│   ├── mm.h<br>
│   ├── platform.h<br>
│   ├── print<br>
│   │   ├── printk.h<br>
│   │   └── uart.h<br>
│   ├── sched.h<br>
│   ├── signal.h<br>
│   ├── sys.h<br>
│   ├── timer.h<br>
│   ├── trap.h<br>
│   ├── type.h<br>
│   └── usr<br>
│       ├── lib.h<br>
│       ├── printf.h<br>
│       └── unistd.h<br>
├── init<br>
│   └── init.c<br>
├── kernel<br>
│   ├── errno.c<br>
│   ├── init.c<br>
│   ├── kernel.c<br>
│   ├── lock<br>
│   │   └── flock.c<br>
│   ├── sched<br>
│   │   ├── exit.c<br>
│   │   ├── fork.c<br>
│   │   ├── sched.c<br>
│   │   └── wait.c<br>
│   ├── signal.c<br>
│   ├── switch.S<br>
│   ├── sys.c<br>
│   └── system_call.c<br>
├── logfile.md<br>
├── Makefile<br>
├── mm<br>
│   ├── malloc.c<br>
│   ├── mem.S<br>
│   └── page.c<br>
├── print<br>
│   ├── panic.c<br>
│   ├── printf.c<br>
│   ├── printk.c<br>
│   └── uart.c<br>
├── README.md<br>
├── timer<br>
│   └── timer.c<br>
├── trap<br>
│   ├── plic.c<br>
│   └── trap.c<br>
└── user<br>
    └── user.c<br>
