#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap,fmt);
#define MAX 200
    char buf[200];
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
    const char *p, *sval;
    char fill,num[10];
    int ival,fill_width;
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
  
    }
    va_end(ap);
    output('\0');
    return cnt-1;
#undef output
}


#endif
