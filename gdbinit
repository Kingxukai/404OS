set disassemble-next-line on
b kernel.c:45
set output-radix 16
target remote : 1234
c
