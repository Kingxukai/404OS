display/z $a5
display/z $a4

set disassemble-next-line on
b *0x80004330
set output-radix 16
target remote : 1234
c
