set disassemble-next-line on
b _malloc_
set output-radix 16
target remote : 1234
c
