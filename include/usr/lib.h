#ifndef _LIB_H_
#define _LIB_H_

void* _malloc_(uint32_t size);
void _free_(void*,int size);
void *memset(void *dest, int c, uint64_t n);
void memcpy(uint32_t* from, uint32_t* to, uint64_t size);
void strncpy(char *from,char* to,int n);
int strlen(char* s);
int strncmp(char* s1,char* s2, int n);
int strcmp(char* s1,char* s2);
void str_toupper(char *str);
int str_split(const char *str, const char ch, char *str1, char *str2);
void *memmove(void *dst, const void *src, int n);
int get_mode();
void sleep();
void wakeup();
pid_t wait();

#define free(adr) _free_((void*)(adr),0)
#define malloc(x) _malloc_(x)

#endif
