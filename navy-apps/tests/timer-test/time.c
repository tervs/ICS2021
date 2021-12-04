#include <unistd.h>
#include <stdio.h>
 #include <sys/time.h>



int main()

{

struct timeval tv;

struct timezone tz;

 while(tv.tv_sec<10)
 {
     gettimeofday(&tv,NULL);


    printf("tv_sec:%ld   tv_usec:%lu\n",tv.tv_sec,tv.tv_usec);


 }


//printf("tz_minuteswest:%d\n",tz.tz_minuteswest);

//printf("tz_dsttime:%d\n",tz.tz_dsttime);

}


