#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)





#define BUFFER_SIZE (400)

static int isdigit(char c){
  return '0' <= c && c <= '9';
}

static int islower(char c){
  return 'a' <= c && c <= 'z';
}

int printf(const char *fmt, ...) {
  // return 0;
  static char printf_buffer[2*BUFFER_SIZE];
  va_list arg;
  va_start(arg, fmt);
  int ret = vsnprintf(printf_buffer,2*BUFFER_SIZE,fmt,arg);
  va_end(arg);
  char *t=printf_buffer;
  while(*t){
    putch(*t);
    t++;
  }
  return ret;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap){
  // return 0;
  static char vsn_buffer[BUFFER_SIZE]; // Pay attetion to this STATIC array
  static char *presentation = "0123456789abcdef";
  char* buffer = vsn_buffer;
  char *outp = out;
  int ret = 0;
  const char *ori = fmt;
  while(*fmt){
    char cur = *fmt;
    if(cur == '%'){
      ++fmt;
      char pre = '\0';
      int mnWidth = 0, outWidth = 0;
      char type = '\0';
      if(isdigit(*fmt)){
        switch(*fmt){
          case '0':
            pre = '0';
            fmt++;
            break;
          default:
            assert(0);
            break;
        }
        while(isdigit(*fmt)){
          mnWidth = mnWidth*10+((*fmt)-'0');
          fmt++;
        }
      }
      if(islower(*fmt)){
        type = *fmt;
      }
      char *cp = &buffer[BUFFER_SIZE-1];
      *cp = '\0';
      switch(type){
        case 'd':
        {
          int32_t var = va_arg(ap, int32_t);
          int isneg = 0;
          if(var < 0){
            isneg = 1;
            var = -var;
          }
          do{
            *(--cp) = presentation[var % 10];
            outWidth++;
            var /= 10;
          }while (var);
          if(isneg){
            *(--cp) = '-';
            outWidth++;
          }
          break;
        }
        case 'u':
        {
          uint32_t var = va_arg(ap, uint32_t);
          do{
            *(--cp) = presentation[var % 10];
            outWidth++;
            var /= 10;
          }while (var);
          break;
        }
        case 'p':
        {
          // Do not use uint32_t uint64_t but use unsigned long to support -m64 -m32
          unsigned long var = (unsigned long)(va_arg(ap, void *));
          do{
            *(--cp) = presentation[var % 16];
            outWidth++;
            var /= 16;
          }while (var);
          *(--cp) = 'x';
          outWidth++;
          *(--cp) = '0';
          outWidth++;
          break;
        }
        case 'x':
        {
          uint32_t var = va_arg(ap, uint32_t);
          do{
            *(--cp) = presentation[var % 16];
            outWidth++;
            var /= 16;
          }while (var);
          break;
        }

        case 's':
        {
          char *sb = va_arg(ap, char*);
          char *se = sb;
          while(*se)
            se++;
          while(se != sb){
            *(--cp) = *(--se);
            outWidth++;
          }
          break;
        }
        default:
          putch('!');
          while(*ori){
            putch(*ori);
            ori++;
          }
          assert(0);
          break;
      }
      if(pre!='\0'){
        while(outWidth<mnWidth){
          *(--cp) = pre;
          outWidth++;
        }
      }
      while(*cp){
        *outp = *cp;
        if(++ret == n)break;
        outp++;
        cp++;
      }
    }
    else{
      *outp = cur;
      outp++;
      if(++ret == n)break;
    }
    fmt++;
  }  
  *outp = '\0';
  return ret;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return vsnprintf(out,-1,fmt,ap);
}

int sprintf(char *out, const char *fmt, ...) {
  va_list arg;
  va_start(arg, fmt);
  int ret = vsprintf(out,fmt,arg);
  va_end(arg);

  // printf("%s",out);

  return ret;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  va_list arg;
  va_start(arg, fmt);
  int ret = vsnprintf(out,n,fmt,arg);
  va_end(arg);
  return ret;
}

#endif




/*

int printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap,fmt);
#define MAX 8000
    char buf[8000];
    int i,n=vsnprintf(buf,-1,fmt,ap);
    assert(n<MAX);
#undef MAX
    for(i=0;i<n;++i){
        putch(buf[i]);
    }
    return i;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
    return vsnprintf(out,-1,fmt,ap);
}

int sprintf(char *out, const char *fmt, ...) {
    va_list ap;
    va_start(ap,fmt);
    return vsnprintf(out,-1,fmt,ap);
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
    va_list ap;
    va_start(ap,fmt);
    return vsnprintf(out,n,fmt,ap);
}


int vsnprintf(char *out, size_t n, const char *fmt, va_list ap){
#define output(A) if(cnt<n-1){out[cnt++]=A;}else{va_end(ap);out[cnt]='\0';return cnt;}
    size_t cnt=0;
    int i=0;
    //double d;
    const char *p, *sval;
    char fill,num[10];
    int ival,fill_width;
    //double dval;
    uintptr_t uval;
    char cval;
    for(p=fmt;*p!='\0';++p){
        if(*p!='%'){
            output(*p);
            continue;
        }
        fill_width=0;
        fill=' ';
        //do {
            if (*p == '0') {
            fill = '0';
            ++p;
            }
            fill_width = 0;
            ++p;
            while (*p >= '0' && *p <= '9') {
                fill_width *= 10;
                fill_width += *p - '0';
                ++p;
            }
            switch (*p) {
                case 'c':
                    cval=va_arg(ap,int);
                    output(cval);
                    break;
                case 'u':
                    uval = va_arg(ap, uint32_t);
                    i = 0;
                    while (uval > 0) {
                        num[i++] = uval % 10 + '0';
                        uval /= 10;
                    }
                    while (fill_width > i) {
                        num[i++] = fill;
                    }
                    if (i == 0) {
                        output('0');
                    } else {
                        while (i > 0) {
                            output(num[--i]);
                        }
                    }
                    break;
                case 'x':
                case 'p':
                    uval = (uintptr_t) va_arg(ap, void * );
                    i = 8;
                    while (i > 0) {
                        output(
                                (uval >> ((sizeof(void *) << 3) - 4)) < 10 ?
                                (uval >> ((sizeof(void *) << 3) - 4)) + '0' :
                                (uval >> ((sizeof(void *) << 3) - 4)) - 10 + 'a');
                        uval <<= 4;
                        --i;
                    }
                    break;
                case 'd':
                    ival = va_arg(ap, int);
                    if (ival < 0) {
                        output('-');
                        ival = -ival;
                    }
                    while (ival > 0) {
                        num[i++] = ival % 10 + '0';
                        ival /= 10;
                    }
                    while (fill_width > i) {
                        num[i++] = fill;
                    }
                    if (i == 0) {
                        output('0');
                    } else {
                        while (i > 0) {
                            output(num[--i]);
                        }
                    }
                    break;
					

                case 's':
                    for (sval = va_arg(ap, char * ); *sval != '\0'; ++sval) {
                        output(*sval);
                    }
                    break;
                default:
                    if (*p < '0' || *p > '9') {
                        output(*p);
                        printf("%%%c not realized.\n");
                        assert(0);
                        cnt+=vsprintf(out+cnt,"not realized\n",ap);
                        break;
                    }
            }
        //}while(0);
    }
    va_end(ap);
    output('\0');
    return cnt-1;
#undef output
}
#endif



*/









