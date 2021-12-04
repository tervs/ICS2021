#include <unistd.h>
#include <stdio.h>
 #include <sys/time.h>
#include"NDL.h"
//extern uint32_t NDL_GetTicks();

int main()

{

struct timeval tv;

struct timezone tz;
int i=0;
 while(i<1000)
 {

     printf("tv_usec:%d\n",NDL_GetTicks());
i++;
    //printf("tv_sec:%ld   tv_usec:%lu\n",tv.tv_sec,tv.tv_usec);


 }


//printf("tz_minuteswest:%d\n",tz.tz_minuteswest);

//printf("tz_dsttime:%d\n",tz.tz_dsttime);

}


