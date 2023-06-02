#ifndef _PRINTK_H__
#define _PRINTK_H__

#define printkGreen(format, ...)        \
    printk("\33[1;32m" format "\33[0m", \
           ##__VA_ARGS__)
           
#define printkYellow(format, ...)       \
    printk("\33[1;33m" format "\33[0m", \
           ##__VA_ARGS__)
           
#define printkRed(format, ...)          \
    printk("\33[1;31m" format "\33[0m", \
           ##__VA_ARGS__)
           
#define printkWhite(format, ...)       \
    printk("\33[1;37m" format "\33[0m", \
           ##__VA_ARGS__)

void printk(const char * s, ... );
void panic(char *s);

#endif
