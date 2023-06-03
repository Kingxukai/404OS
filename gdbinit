set disassemble-next-line on
b sys_execve
set output-radix 16
target remote : 1234
c
