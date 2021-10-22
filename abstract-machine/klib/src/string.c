#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>
//#include <assert.h>
#include<stdio.h>
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
    const char *sc;
    for(sc = s; *sc != '\0'; ++sc);
    return (sc-s); 
}

char *strcpy(char *dst, const char *src) {
  
    const char* su;
    char *sc;
    for(sc = dst, su = src; (*sc++ = *su++) != '\0';);
    return dst;
 
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
    char *s;
    for(s=dst; *s != '\0'; s++);
    for(; (*s=*src) != '\0'; s++,src++);
    return dst;

}

int strcmp(const char *s1, const char *s2) {
  
    while(*s1 && *s2)
    {
    if(*s1 != *s2)
      return *s1 - *s2;
    s1++;
    s2++;
    }
  return *s1 - *s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  char *p=s;
  while(n--){*p++=c;}
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
   char *ptr = out;
	const char *s = in;
	while (n--) *ptr++=*s++;
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
 const unsigned char *c1,*c2;
 int res = 0;
 for (c1 = s1, c2 = s2;n>0;++c1,++c2,n--)
 if ((res=*c1-*c2)!=0) break;
 return res;
}

#endif
