set disassemble-next-line on
b do_syscall
set output-radix 16
target remote : 1234
c
