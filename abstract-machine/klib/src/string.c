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

/*
    char *t=(char*)&s;
    if(t==NULL){panic("NULL STRING!");}
    else
    {
      int i=0;
      while(*(t++)!='\0')
      {
        
        i=i+1;
      }
      return i;
    }
*/
    
}

char *strcpy(char *dst, const char *src) {
  
    const char* su;
  char *sc;
  for(sc = dst, su = src; (*sc++ = *su++) != '\0';);
  return dst;
  
  /*
  char *t=(char*)&src;
  if(t==NULL){panic("NULL STRING!");}
  while ((*dst++ = *src++) != '\0');
  return *src;

  */
  //panic("Not implemented");
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  panic("Not implemented");
}

int strcmp(const char *s1, const char *s2) {
  
    while(*s1 && *s2){
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
  panic("Not implemented");
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  panic("Not implemented");
}

int memcmp(const void *s1, const void *s2, size_t n) {
  panic("Not implemented");
}

#endif
