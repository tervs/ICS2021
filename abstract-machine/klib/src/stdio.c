#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)



char* my_itoa(char* dest, int n){
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
		n /= 10;
	}
	if(neg) dest[0] = '-';
	dest[len] = '\0';
	return dest;
}





int printf(const char *format, ...) {
	int len = strlen(format);
	int i = 0;
	int in_size = 0;
	va_list var_arg;
	va_start(var_arg, format);

	while(i < len){
		if(format[i] == '%'){
			int in_num = 0;
			char in_char[50] = "";
			switch(format[i+1]){
				case 'd'://%d 
					in_num = va_arg(var_arg,int);
					my_itoa(in_char,in_num);
					//strcat(str, in_char);
					putstr(in_char);
					in_size += strlen(in_char);
					i += 2;
					break;
				case 's'://%s
				 	strcpy(in_char,va_arg(var_arg, char*));
					//strcat(str,in_char);
					putstr(in_char);
					in_size += strlen(in_char);
					i += 2;
					break;
				case '0'://%02d
					in_num = va_arg(var_arg,int);
					my_itoa(in_char, in_num);
					int pwidth = format[i+2] - '0';//width of number
					for(int i = strlen(in_char); i < pwidth; ++i) {
						in_size ++;
						putch('0');
					}
					putstr(in_char);
					in_size += strlen(in_char);
					i += 4;
					break;

				default: printf("Not implememted argument type!\n");
			}
		}
		else {
			//char temp[2];
			//temp[0] = format[i];
			//temp[1] = '\0';
			//strcat(str, temp);
			putch(format[i]);
			in_size ++;
			i ++;
		}
	}
		va_end(var_arg);
		return in_size;
}
int vsprintf(char *out, const char *fmt, va_list ap) {
  return 0;
}





int sprintf(char *out, const char *fmt, ...) {
  
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
				default: assert(0);break;
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
  

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}










#endif
