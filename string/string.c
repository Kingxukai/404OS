#include "../include/type.h"
#include "../include/ctype.h"

char *strncpy(char *s, const char *t, int n) 
{
    char *os;

    os = s;
    while (n-- > 0 && (*s++ = *t++) != 0)
        ;
    while (n-- > 0)
        *s++ = 0;
    return os;
}

int strlen(char* s)
{
	int total = 0;
	while(*(s++))
	{
		total++;
	}
	return total;
}

int strncmp(char* s1,char* s2, int n)
{
	while(n--)
	{
		if(*s1++ != *s2++)return 1;
	}
	return 0;
}

int strcmp(char* s1,char* s2)
{
	int total1 = strlen(s1);
	int total2 = strlen(s2);
	if(total1 != total2)return 1;
	while(total1--)
	{
		if(*s1++ != *s2++)return 1;
	}
	return 0;
}

void *memmove(void *dst, const void *src, int n) 
{
    const char *s;
    char *d;

    if (n == 0)
        return dst;

    s = src;
    d = dst;
    if (s < d && s + n > d) 
    {
        s += n;
        d += n;
        while (n-- > 0) 
        {
            *--d = *--s;
        }

    } 
    else
        while (n-- > 0) 
        {
            // if (d == NULL || s == NULL) {
            //     Log("ready\n");
            // }
            *d++ = *s++;
        }

    return dst;
}

void* memcpy(void *dst, const void *src, int n)
{
	return memmove(dst, src, n);
}

void str_toupper(char *str) {
    if (str != NULL) {
        while (*str != '\0') {
            *str = toupper(*str);
            str++;
        }
    }
}

static char *strchr(const char *str, int c) {
    while (*str != '\0') {
        if (*str == (char)c) {
            return (char *)str;
        }
        str++;
    }
    if (c == '\0') {
        return (char *)str;
    }
    return NULL;
}

int str_split(const char *str, const char ch, char *str1, char *str2) {
    char *p = strchr(str, ch);
    if (p == NULL) {
        return -1;
    }
    strncpy(str1, str, p - str);
    strncpy(str2, p + 1, strlen(str) - 1 - (p - str));

    return 1;
}
