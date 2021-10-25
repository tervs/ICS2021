#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
#define BUFFER_SIZE (400)

/*
static int isdigit(char c)
{
  return '0'<=c&&c<='9';
}

static int isletter(char c)
{
  return 'a'<=c&&c<='z';
}

*/

int printf(const char *fmt, ...) {
  static char printf_buffer[2*BUFFER_SIZE];
  va_list arg;
  va_start(arg,fmt);
  int ret =vsnprintf(printf_buffer,2*BUFFER_SIZE,fmt,arg);
  va_end(arg);
  char *t=printf_buffer;
  while(*t)
  {
    _putc(*t);
    t++;
  }
  return ret;
  //panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
