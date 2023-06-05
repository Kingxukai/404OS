set disassemble-next-line on
b fat32_inode_dirlookup
set output-radix 16
target remote : 1234
c
