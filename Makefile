include common.mk

SRCS_ASM = \
	BOOT/boot.S \
	kernel/switch.S \
	mm/mem.S \

SRCS_C = \
	kernel/kernel.c \
	kernel/init.c \
	kernel/sys.c \
	kernel/errno.c \
	kernel/signal.c \
	kernel/lock/flock.c \
	kernel/system_call.c \
	kernel/sched/sched.c \
	kernel/sched/fork.c \
	kernel/sched/exit.c \
	kernel/sched/wait.c \
	printf/uart.c \
	printf/printf.c \
	printf/panic.c \
	timer/timer.c \
	mm/malloc.c \
	mm/page.c \
	trap/trap.c \
	trap/plic.c \
	user/user.c

OBJS = $(SRCS_ASM:.S=.o)
OBJS += $(SRCS_C:.c=.o)

.DEFAULT_GOAL := all
all: 404OS.elf

# start.o must be the first in dependency!
404OS.elf: ${OBJS}
	${CC} ${CFLAGS} -T 404OS.ld -o 404OS.elf $^
	${OBJCOPY} -O binary 404OS.elf 404OS.bin

%.o : %.c
	${CC} ${CFLAGS} -c -o $@ $<

%.o : %.S
	${CC} ${CFLAGS} -c -o $@ $<

run: all
	@${QEMU} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	@${QEMU} ${QFLAGS} -kernel 404OS.elf

.PHONY : debug
debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------------------------------"
	@${QEMU} ${QFLAGS} -kernel 404OS.elf -s -S &
	@${GDB} 404OS.elf -q -x gdbinit

.PHONY : code
code: all
	@${OBJDUMP} -S 404OS.elf | less

.PHONY : clean
clean:
	rm -rf BOOT/*.o kernel/*.o kernel/sched/*.o timer/*.o trap/*.o mm/*.o printf/*.o user/*.o printf/*.o include/*.o *.bin *.elf

