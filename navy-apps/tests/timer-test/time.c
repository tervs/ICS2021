#include <unistd.h>
#include <stdio.h>
 #include <sys/time.h>

int main() 
{
    struct timeval *tv;

    gettimeofday(tv,NULL);
    while(1)
    {
     printf("tv_sec:%ld\n",(tv->tv_sec));
     printf("tv_usec:%ld\n",tv->tv_usec);


    }
  return 0;
}