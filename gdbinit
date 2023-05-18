set disassemble-next-line on
b *0x8000458c
set output-radix 16
target remote : 1234
c
