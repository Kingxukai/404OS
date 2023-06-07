#ifndef _PRINTF_H__
#define _PRINTF_H__

#include "../print/uart.h"

int printf(const char* s, ...);

#define printfGreen(format, ...)        \
    printf("\33[1;32m" format "\33[0m", \
           ##__VA_ARGS__)
           
#define printfYellow(format, ...)       \
    printf("\33[1;33m" format "\33[0m", \
           ##__VA_ARGS__)
           
#define printfRed(format, ...)          \
    printf("\33[1;31m" format "\33[0m", \
           ##__VA_ARGS__)
           
#define printfWhite(format, ...)       \
    printf("\33[1;37m" format "\33[0m", \
           ##__VA_ARGS__)

#define Info(fmt, ...) printf("[INFO] " fmt "", ##__VA_ARGS__);

#define TEST_START(x) printf("========== START ");printf(x);printf(" ==========\n");
#define TEST_END(x) printf("========== END ");printf(x);printf(" ==========\n");

#endif
