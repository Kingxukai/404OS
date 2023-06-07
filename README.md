# OSKernel2023-404OS

<mark>Team_name:404OS\
School_name:Shenyang Aerospace University（SAU）</mark>

## 文件树(file tree)

. \
├── 404OS.ld --链接脚本 \
├── BOOT --内核启动 \
├── common.mk --配置文件 \
├── gdbinit --gdb初始化 \
├── include --头文件 \
│   ├── asm --汇编相关 \
│   ├── print --输出 \
│   └── usr --通用库 \
├── init --初始化 \
├── kernel --内核代码 \
│   ├── lock --锁 \
│   ├── sched --进程调度 \
├── logfile.md --日志 \
├── Makefile \
├── mm --内存相关 \
├── fs --文件系统 \
├── string --字符串 \
├── print --输出 \
├── README.md \
├── timer --定时器 \
├── trap --中断 \
└── user --用户 

**比赛说明：**
	由于本次比赛时间比较紧迫，加之接触操作系统时间不够，对内核理解不太深，一个人完成整个比赛过程也很困难。因此未能完成比赛所有的要求，很遗憾;
	但是，这并不代表参加这次比赛没有意义，相反，我克服了很多障碍，比如阅读riscv sbi-specification、riscv privileged specification等英文文档，阅读了非常长且复杂的linux、xv6、rcore等非常棒且值得学习的开源OS内核代码，这都让我受益匪浅；同时，也很感谢给予帮助过的一些同学或者是开源工作者，这也鼓励着我以后加入开源社区，为他人的coding提供更多有意义的帮助和便利，也只有这样才会推动技术的发展。
	虽然本次比赛因此没有做好全面的系统规划，以及对内核的盲点较多，导致比赛结果不满意，但是本内核中还是有许多可借鉴学习之处。比如switch_to、trap_vector、schedule等在陷入和进程切换方面都有作者自己的见解，同时在系统调用的处理方面也增加了一些magic。希望可以帮到后续读者

**已完成：**

```
1.一个完整的多任务进程的调度（多级反馈队列的时间片轮转）
2.fork execve wait waitpid waitppid等简单的系统调用
3.automic spin lock：原子性的自旋锁
4.fs:基于virt平台virtio的fat32文件系统，可以正确挂载的sdcard，并识别文件系统（参考lostwakeup队）
5.一个简单的可分配的堆，使用page_alloc/malloc进行动态分配，page_free/free进行释放
```

**未完成：**

```
1.分页和虚拟内存：这一点是最遗憾的，因为对本次内核的接触比较晚，所以很多事情都是靠自己一点点摸索的，所以一开始并不知道不设置S-mode和分页会对评测的影响很大。然后由于比赛系统的要求，不得不加入了S-mode来避免和SBI的地址冲突；且因为elf文件的特殊格式，需要实现虚拟地址到物理地址的转化，而此时再加入一个完善的分页系统已经时间不够了。因此未能完成评测，这一点非常遗憾
2.多核启动：本内核在进入入口前，已经为多核启动做足了准备：在boot.S中，第hart0直接进入kerne_start完成内核相关初始化；其他核j wfi等待hart0中断；但由于时间紧迫，未能完成这一点
3.线程：本内核仅仅只有对进程的管理，未引入线程的概念
```



**内核运行截图**

![1](/home/wxk/Desktop/404OS/oskernel2023-404os/screenshot/kernel_entry.png)

![1](/home/wxk/Desktop/404OS/oskernel2023-404os/screenshot/runtime.png)
