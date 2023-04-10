CROSS_COMPILE := riscv64-unknown-elf-
CFLAGS 	:= -march=rv64ima -mabi=ilp64 -fno-omit-frame-pointer -ggdb -g -Wall -O -Werror
QEMU 	:= qemu-system-riscv64
QFLAGS 	:= -nographic -smp 1 -machine virt -bios none
GDB 	:= gdb-multiarch
CC 		:= ${CROSS_COMPILE}gcc

OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump

CFLAGS 	+= -MD
CFLAGS 	+= -mcmodel=medany
CFLAGS 	+= -ffreestanding -fno-common -nostdlib -mno-relax



target_dir	:= 	target

.DEFAULT_GOAL := all

.PHONY: 