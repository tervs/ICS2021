#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
//#include<stdio.h>
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

char* my_itoa(char* dest, int n){
	/*transfer int into char[]*/
	//int outn = n;
	if(n == 0) {
		dest[0] = '0';
		dest[1] = '\0';
		return dest;
	}
	
	int len = 0;
	int neg = 0;
	if(n < 0) {
		neg = 1;
		len ++;
		n = -n;
	}
	int temp = n;
	while(temp > 0){
		len ++;
		temp /= 10;
	}
	
	for(int i = 0; i < len; ++i){
		int x = n % 10;
		dest[len - i - 1] = x + '0';
		//printf("dest[%d] = %c\n", len-i-1,dest[len-i-1]);
		n /= 10;
	}
	if(neg) dest[0] = '-';
	dest[len] = '\0';
	//printf("%d -> %s\n",outn,dest);
	return dest;
}





int myprintf(const char *fmt, ...) {
  
  /*
  static char printf_buffer[2*BUFFER_SIZE];
  va_list arg;
  va_start(arg,fmt);
  int ret =myvsnprintf(printf_buffer,2*BUFFER_SIZE,fmt,arg);
  va_end(arg);
  char *t=printf_buffer;
  while(*t)
  {
    putch(*t);
    t++;
  }
  return ret;
*/
  
  //panic("Not implemented");
  return 0;
}






/*
int myvsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  
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


int myvsprintf(char *out, const char *fmt, va_list ap) {
  return myvsnprintf(out,-1,fmt,ap);

}
*/
int mysprintf(char *out, const char *fmt, ...) {
  
  int len = strlen(fmt);
	int i = 0;
	int in_size = 0;
	va_list var_arg;
	va_start(var_arg, fmt);
	out[0] = '\0';

	while(i < len){
		if(fmt[i] == '%'){
			int in_num = 0;
			char in_char[50] = "";
			switch(fmt[i+1]){
				case 'd'://%d 
					in_num = va_arg(var_arg,int);
					my_itoa(in_char,in_num);
					strcat(out, in_char);
					in_size += strlen(in_char);
					break;
				case 's'://%s
				 	strcpy(in_char,va_arg(var_arg, char*));
					strcat(out,in_char);
					in_size += strlen(in_char);
					break;
				default: assert(0);break;//printf("Not implememted argument type!\n");
			}
			i += 2;
		}
		else {
			char temp[2];
			temp[0] = fmt[i];
			temp[1] = '\0';
			strcat(out, temp);
			in_size ++;
			i ++;
		}
	}
		va_end(var_arg);
		return in_size;
}
  
  /*
  va_list arg;
  va_start(arg,fmt);
  int ret =myvsprintf(out,fmt,arg);
  va_end(arg);

  return ret;
  */
  //panic("Not implemented");





int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}





#endif


/*
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



