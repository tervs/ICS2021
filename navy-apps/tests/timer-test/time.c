#include <unistd.h>
#include <stdio.h>
 #include <sys/time.h>



int main()

{

struct timeval tv;

struct timezone tz;
 printf("test\n");
gettimeofday(&tv,NULL);

 printf("test\n");

printf("tv_sec:%ld\n",tv.tv_sec);

printf("tv_usec:%ld\n",tv.tv_usec);

//printf("tz_minuteswest:%d\n",tz.tz_minuteswest);

//printf("tz_dsttime:%d\n",tz.tz_dsttime);

}


