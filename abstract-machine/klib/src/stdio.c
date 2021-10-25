#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
//#include<stdio.h>
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
#define BUFFER_SIZE (400)


static int isdigit(char c)
{
  return '0'<=c&&c<='9';
}

static int isletter(char c)
{
  return 'a'<=c&&c<='z';
}



int printf(const char *fmt, ...) {
  static char printf_buffer[2*BUFFER_SIZE];
  va_list arg;
  va_start(arg,fmt);
  int ret =vsnprintf(printf_buffer,2*BUFFER_SIZE,fmt,arg);
  va_end(arg);
  char *t=printf_buffer;
  while(*t)
  {
    putch(*t);
    t++;
  }
  return ret;
  //panic("Not implemented");
}







int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  
  static char vsn_buffer[BUFFER_SIZE];
  static char *presentation ="0123456789abcdef";
  char *buffer=vsn_buffer;
  char *outp=out;
  int ret =0;
  //const char *ori=fmt;
  while(*fmt)
  {
    char cur=*fmt;
    if(cur=='%')
    {
      ++fmt;
      char pre='\0';
      int mnWidth=0,outWidth=0;
      char type='\0';
      if(isdigit(*fmt))
      {
        switch(*fmt)
        {
          case'0':
            pre='0';
            fmt++;
            break;
          default:
            assert(0);
            break;
        }
        while(isdigit(*fmt))
        {
          mnWidth=mnWidth*10+((*fmt)-'0');
          fmt++;
        }
      }
      if(isletter(*fmt))
      {
        type=*fmt;
      }
      char *cp=&buffer[BUFFER_SIZE-1];
      *cp='\0';
      switch(type)
      {
        case'd':
        {
            int32_t var =va_arg(ap,int32_t);
            int isneg=0;
            if(var<0)
            {
              isneg=1;
              var=-var;
            }
            do{
              *(--cp)=presentation[var%10];
              outWidth++;
              var/=10;
            }while(var);
            if(isneg)
            {
              *(--cp)='-';
              outWidth++;
            }
            break;
          }

        case'u':
        {
            uint32_t var=va_arg(ap,uint32_t);
            do
            {
              *(--cp)=presentation[var%10];
              outWidth++;
              var/=10;
            } while (var);
            break;
          }

        case'p':
        {
            unsigned long var =(unsigned long)(va_arg(ap,void*));
            do{
              *(--cp)=presentation[var%16];
              outWidth++;
              var/=16;
            }while (var);
            *(--cp)='x';
            outWidth++;
            *(--cp)='0';
            outWidth++;
            break;
          }
        
        case 'x':
        {
          uint32_t var=va_arg(ap,uint32_t);
            do
            {
              *(--cp)=presentation[var%16];
              outWidth++;
              var/=10;
            } while (var);
            break;
        }
       /* 
        case'f':
        {
          double var =va_arg(ap,double);
          int32_t _int=(int32_t)(var*10000);
          int isneg=0;
          if(_int<0)
          {
            isneg=1;
            _int=-_int;
          }
        
          for(int i=0;i<4;i++)
          {
            *(--cp)=presentation[_int%10];
            outWidth++;
              _int/=10;
          }
          *(--cp)='.';
          outWidth++;
          do{

            *(--cp)=presentation[_int%10];
            outWidth++;
              _int/=10;
          }while(_int);
            
            if(isneg)
            {
              *(--cp)='-';
              outWidth++;
            }
            break;
        
        }
*/
        case's':
        {
          char *sb=va_arg(ap,char*);
          char *se=sb;
          while(*se)se++;
          while(se!=sb)
          {
            *(--cp)=*(--se);
            outWidth++;
          }
          break;
        }

        default:
        
        
        assert(0);

        break;
      }


      if(pre!='\0')
      {
        while(outWidth<mnWidth)
        {
          *(--cp)=pre;
          outWidth++;
        }
      }

      while(*cp)
      {
        *out=*cp;
        if(++ret==n)break;
        outp++;
        cp++;
      }
    }

    else{
      *outp=cur;
      outp++;
      if(++ret==n)break;
    }

    fmt++;
  }
*outp='\0';
return ret;
  
  
  //panic("Not implemented");
}


int vsprintf(char *out, const char *fmt, va_list ap) {
  return vsnprintf(out,-1,fmt,ap);

}

int sprintf(char *out, const char *fmt, ...) {
  va_list arg;
  va_start(arg,fmt);
  int ret =vsprintf(out,fmt,arg);
  va_end(arg);

  return ret;
  
  //panic("Not implemented");
}



/*
int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}
*/




#endif




