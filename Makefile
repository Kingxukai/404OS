include common.mk

SRCS_ASM = \
	BOOT/boot.S \
	kernel/switch.S \
	kernel/lock/atomic.S \
	mm/mem.S \

SRCS_C = \
	kernel/kernel.c \
	kernel/sys.c \
	kernel/errno.c \
	kernel/signal.c \
	kernel/ctype.c \
	kernel/errno.c \
	kernel/lock/spin_lock.c \
	kernel/system_call.c \
	kernel/sched/sched.c \
	kernel/sched/fork.c \
	kernel/sched/exit.c \
	kernel/sched/wait.c \
	init/init.c \
	print/printf.c \
	print/printk.c \
	print/panic.c \
	string/string.c \
	timer/timer.c \
	timer/time.c \
	mm/malloc.c \
	mm/page.c \
	mm/mm.c \
	trap/trap.c \
	trap/plic.c \
	driver/uart.c \
	driver/buffer.c \
	driver/virtio.c \
	fs/fat32_disk.c \
	fs/fat32_file.c \
	fs/fat32_inode.c \
	fs/fat32_stack.c \
	fs/fd.c \
	fs/ops.c \
	user/user.c

OBJS = $(SRCS_ASM:.S=.o)
OBJS += $(SRCS_C:.c=.o)

.DEFAULT_GOAL := all
all: kernel-qemu

kernel-qemu: ${OBJS}
	${CC} ${CFLAGS} -T 404OS.ld -o kernel-qemu $^
	${OBJCOPY} -O binary kernel-qemu os.bin

%.o : %.c
	${CC} ${CFLAGS} -c -o $@ $<

%.o : %.S
	${CC} ${CFLAGS} -c -o $@ $<

run: all
	@${QEMU} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	@${QEMU} ${QFLAGS} -kernel kernel-qemu

.PHONY : debug
debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------------------------------"
	@${QEMU} ${QFLAGS} -kernel kernel-qemu -s -S &
	@${GDB} kernel-qemu -q -x gdbinit

.PHONY : code
code: all
	@${OBJDUMP} -S kernel-qemu | less

.PHONY : clean
clean:
	rm -rf \
	BOOT/*.o \
	init/*.o \
	driver/*.o \
	kernel/*.o \
	kernel/sched/*.o \
	kernel/lock/*.o \
	timer/*.o \
	trap/*.o \
	mm/*.o \
	print/*.o \
	string/*.o \
	driver/*.o \
	fs/*.o \
	user/*.o \
	*.o \
	*.bin \
	kernel-qemu

