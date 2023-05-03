# OSKernel2023-404OS

Team_name:404OS  
School_name:Shenyang Aerospace University（SAU）

.
├── 404OS.ld  
├── BOOT  
│   └── boot.S  
├── common.mk  
├── gdbinit  
├── include  
│   ├── error.h  
│   ├── kernel.h  
│   ├── mm.h  
│   ├── platform.h  
│   ├── printf.h  
│   ├── riscv64.h  
│   ├── sched.h  
│   ├── sys.h  
│   ├── system.h  
│   ├── timer.h  
│   ├── trap.h  
│   ├── type.h  
│   └── uart.h  
├── kernel  
│   ├── init.c  
│   ├── kernel.c  
│   ├── sched  
│   │   ├── exit.c  
│   │   ├── fork.c  
│   │   └── sched.c  
│   ├── switch.S  
│   ├── sys.c  
│   └── system_call.c  
├── logfile  
├── Makefile  
├── mm  
│   ├── malloc.c  
│   ├── mem.S  
│   └── page.c  
├── printf  
│   ├── panic.c  
│   ├── printf.c  
│   └── uart.c  
├── README.md  
├── timer  
│   └── timer.c  
├── trap  
│   ├── plic.c  
│   └── trap.c  
└── user  
    └── user.c

