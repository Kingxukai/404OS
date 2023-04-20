CROSS_COMPILE = riscv64-unknown-elf-
CFLAGS = -nostdlib -fno-builtin -march=rv64ima -mabi=lp64 -g -Wall

QEMU = qemu-system-riscv64
QFLAGS = -nographic -smp 1 -machine virt -bios none -m 128M

GDB = ${CROSS_COMPILE}gdb
CC = ${CROSS_COMPILE}gcc
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump