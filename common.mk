CROSS_COMPILE = riscv64-unknown-elf-
CFLAGS = -nostdlib -fno-builtin -march=rv64ima -mabi=lp64 -mcmodel=medany -g -Wall -Wno-unused-but-set-variable

QEMU = qemu-system-riscv64
QFLAGS = -nographic -smp 1 -machine virt -bios default -m 128M \
-drive file=../sdcard.img,if=none,format=raw,id=x0 \
-device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0 \
-global virtio-mmio.force-legacy=false

GDB = ${CROSS_COMPILE}gdb
CC = ${CROSS_COMPILE}gcc
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump
