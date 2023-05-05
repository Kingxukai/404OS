display/z $a5
display/z $a4

set disassemble-next-line on
<<<<<<< HEAD
b *0x80004330
=======
b _start
>>>>>>> e83086dec04d5b07f95b1fc8010490e02451cf51
set output-radix 16
target remote : 1234
c
