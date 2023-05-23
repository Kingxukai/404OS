set disassemble-next-line on
b *0x80000e8c
set output-radix 16
target remote : 1234
c
