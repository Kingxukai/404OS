set disassemble-next-line on
b *0x80000ee0
set output-radix 16
target remote : 1234
c
