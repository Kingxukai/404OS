CROSS_COMPILE := riscv64-unknown-elf-    #指定使用的交叉编译工具链的前缀

CFLAGS := -march=rv64ima -mabi=ilp64 -fno-omit-frame-pointer -ggdb -g -Wall -O -Werror    #编译器选项 
        -nostdlib：禁用标准库，即不使用C标准库。
        -fno-builtin：禁用内置函数，即不使用C编译器内部提供的函数。
        
        -march=rv64ima：指定目标体系结构为rv64ima，即64位RISC-V指令集，支持整数、乘法、原子操作等指令。
        -march=rv64g：表示编译器使用RISC-V 64位指令集，包括整型、浮点型和向量型指令
        #如果只需要使用整型和原子操作指令，可以使用-march=rv64ima选项；如果需要使用浮点和向量指令集，可以使用-march=rv64g选项。
        
        -mabi=lp64：指定使用ILP64数据模型，即int、long、指针等类型都是64位的。
        -mabi=lp64f表示编译器使用LP64F数据模型，即long和指针占用64位，int和short占用32位，float占用32位，double占用64位。这种数据模型适用于大多数应用程序。
        
        -g：生成调试信息，方便调试程序。
        -ggdb -g：生成调试信息，方便调试程序。

        -Wall：开启所有警告，以便编译器尽可能地检测潜在的问题。
        -Werror：将警告视为错误，即如果有任何警告则终止编译过程。

        -O：开启优化，以提高代码执行效率。
        -fno-omit-frame-pointer：保留帧指针，以方便调试代码。
        -MD：生成依赖关系文件。
        -mcmodel=medany：选择中等模型的代码模型，适用于任何大小的程序。
        -ffreestanding：指定编译器生成的程序是没有宿主环境的独立程序。
        -fno-common：禁用common变量，即禁止多个文件共享未初始化的全局变量。
        -nostdlib：禁用标准库的使用。
        -mno-relax：禁用指令宽度调整。
        -I.：指定头文件的搜索路径。
        

QEMU := qemu-system-riscv64      #模拟器的名称和选项，用于在虚拟机中运行操作系统。

QFLAGS := -nographic -smp 1 -machine virt -bios none     #模拟器选项
        -M virt：指定模拟器模拟的机型为virt。
        -machine sifive_u：指定模拟器模拟的机型为SiFive Unleashed开发板。
        -machine virt：指定模拟器模拟的机型为virt。
        -cpu rv64：指定模拟器使用64位RISC-V CPU。
        -smp n：指定模拟器的CPU核心数量。
        -m size：指定模拟器的内存大小，单位为MB。
        -nographic：禁用图形界面，使用字符终端代替。
        -bios none：禁用BIOS。
        -kernel file：指定要加载的内核文件。
        -drive file=filename,format=format：指定虚拟磁盘映像文件和格式。
        -device dev：添加设备到模拟器，如网卡、声卡等。
        -serial mon:stdio：将串行端口重定向到标准输入/输出。
        -netdev user,id=id,hostfwd=hostport:guestport：启用用户模式网络设备，并将主机端口转发到客户机端口。
        -no-reboot：在退出模拟器时不执行重启操作。
        -snapshot：将虚拟机设置为快照模式，所有更改将保存在内存中，而不会写入磁盘。

GDB := gdb-multiarch    #GDB调试器的名称和选项，用于调试操作系统。

CC := ${CROSS_COMPILE}gcc   #gcc编译工具

OBJCOPY = ${CROSS_COMPILE}objcopy   #二进制文件转换工具
OBJDUMP = ${CROSS_COMPILE}objdump   #目标文件反汇编工具

