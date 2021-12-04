#include <unistd.h>
#include <stdio.h>
 #include <sys/time.h>

int main() 
{
    printf("test\n");
    struct timeval *tv;
printf("test\n");
    gettimeofday(tv,NULL);
    long int x=(*tv).tv_sec;
printf("%ld\n",x);
    printf("tv_sec:%ld\n",(*tv).tv_sec);
     printf("tv_usec:%ld\n",(*tv).tv_usec);


  return 0;
}