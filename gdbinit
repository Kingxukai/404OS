set disassemble-next-line on
b fork.c:44
set output-radix 16
target remote : 1234
c
