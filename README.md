# OSKernel2023-404OS

<mark>Team_name:404OS\
School_name:Shenyang Aerospace University（SAU）</mark>\

## 文件树(file tree)

.\
├── 404OS.ld\
├── BOOT\
│   └── boot.S\
├── common.mk\
├── driver\
├── fs\
├── gdbinit\
├── include\
│   ├── errno.h\
│   ├── kernel.h\
│   ├── lib.h\
│   ├── mm.h\
│   ├── platform.h\
│   ├── printf.h\
│   ├── riscv64.h\
│   ├── sched.h\
│   ├── signal.h\
│   ├── sys.h\
│   ├── system.h\
│   ├── timer.h\
│   ├── trap.h\
│   ├── type.h\
│   ├── uart.h\
│   └── unistd.h\
├── kernel\
│   ├── errno.c\
│   ├── init.c\
│   ├── kernel.c\
│   ├── sched\
│   │   ├── exit.c\
│   │   ├── fork.c\
│   │   ├── sched.c\
│   │   └── wait.c\
│   ├── signal.c\
│   ├── switch.S\
│   ├── sys.c\
│   └── system_call.c\
├── logfile\
├── Makefile\
├── mm\
│   ├── malloc.c\
│   ├── mem.S\
│   └── page.c\
├── printf\
│   ├── panic.c\
│   ├── printf.c\
│   └── uart.c\
├── README.md\
├── timer\
│   └── timer.c\
├── trap\
│   ├── plic.c\
│   └── trap.c\
└── user\
    └── user.c\
