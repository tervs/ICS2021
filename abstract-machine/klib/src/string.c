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
  const char*su;
  char*sc;
  size_t i=0;
  for(sc=dst,su=src;i<n&&(*sc++=*su++)!='\0';i++)
  
  for(;i<n;i++)*sc++='\0';
  return dst;
  
  
  
  
  //panic("Not implemented");
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
  size_t i=0;
  while(*s1&&*s2&&i<n)
  {
    if(*s1!=*s2)
      return *s1-*s2;
    s1++;
    s2++;
    i++;
  }
  
  return i==n?0:(*s1-*s2);
  
  
  //panic("Not implemented");
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

char *strtok(char *str, const char *delim)
{
	assert(delim != NULL); //分隔符字符串不能为空
	static char* left = NULL; //局部静态变量：保存剩余的字符串
	if(str == NULL) //如果str为空，则使用剩余的字符串
		str = left;
	if(str == NULL)
		return NULL;
	
	const char *p;
	bool flag;
	while(*str != 0) //去除起始部分的分隔符
	{
		p = delim;
		flag = false;
		while(*p != 0) //判断当前字符是否属于分隔符
		{
			if(*p++ == *str)
			{
				flag = true;
				break;
			}
		}
		if(!flag)
			break;
		++str;
	}
	char *s = str; //str保留住字符串起始指针
	while(*s != 0) //当遇到第一个分隔符是停止
	{
		p = delim;
		flag = false;
		while(*p != 0) //判断当前字符是否属于分隔符
		{
			if(*p++ == *s)
			{
				flag = true;
                *s = 0;
				break;
			}
		}
		++s;
		if(flag)
		{
			left = s;
			return str;
		}
	}
	left = NULL; //到字符串末尾也没遇到分隔符，没有剩余串了。
	return str;
}
/*
char* strtok (char* str, const char* delim)
{
	// 生成替换字符表
	char table[256] = {0};
    while (*delim != '\0')
    {
        table[*delim] = 1;
        delim++;
    }

	// 使用 static 类型指针保存上一次函数调用时的字符串地址
	static char* pstr = NULL;
	if (str != NULL)
	{
		pstr = str;
	}

	// 保证 pstr 指向以非替换字符为首的子字符串
	while (*pstr != '\0' && table[*pstr] == 1)
	{
		pstr++;
	}	

	// ret 保存返回子字符串的首地址
	char* rst = (*pstr != '\0') ? pstr : NULL;

	while (*pstr != '\0')
	{
        if (table[*pstr] == 1)
        {
            // 切割得到子字符串，且 pstr 最后指向子字符串的下一字符
            *pstr++ = '\0';
            break;
        }
        else
        {
            pstr++;
        }
	}
    
	return rst;
}

*/
#endif