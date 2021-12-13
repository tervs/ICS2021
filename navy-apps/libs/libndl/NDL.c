#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <assert.h>


static int evtdev = -1;
static int fbdev = -1;
static int screen_w = 0, screen_h = 0;
static int canvas_w = 0, canvas_h = 0;
static int center_x = 0, center_y = 0;


int atoi2(char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}
//size_t fs_read(int fd, void *buf, size_t len);
//int gettimeofday(struct timeval *tv, struct timezone *tz) ;

uint32_t NDL_GetTicks() {
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec;

  //printf("tv_sec:%ld   tv_usec:%lu\n",tv.tv_sec,tv.tv_usec);
  //return 0;
}

int NDL_PollEvent(char *buf, int len) {
  FILE *fp = fopen("/dev/events", "r+");
  //int fd=open("/dev/events",0,0);
  int res=fread(buf,1,len,fp);
  //printf("%d",len);
//printf("NDL_read %s \n",buf);
  fclose(fp);
  return res;
}

void NDL_OpenCanvas(int *w, int *h) 
{/*
  if (getenv("NWM_APP")) 
  {
    int fbctl = 4;
    fbdev = 5;
    screen_w = *w; screen_h = *h;
    char buf[64];
    char test[64];
    int len = sprintf(buf, "%d %d", screen_w, screen_h);
    // let NWM resize the window and create the frame buffer
    write(fbctl, buf, len);
    read(fbctl,test,len);
    printf("test: %s\n",test);
    while (1) {
      // 3 = evtdev
      int nread = read(3, buf, sizeof(buf) - 1);
      if (nread <= 0) continue;
      buf[nread] = '\0';
      if (strcmp(buf, "mmap ok") == 0) break;
    }
    close(fbctl);
  }

  */

  canvas_w = *w; canvas_h = *h;
  //read()
  //int fd=fopen("")
  char buf[128];
  //printf("fuck you\n");

  read(4,buf,16);
  char *w1=strtok(buf,":");
  char *h1=strtok(NULL,"\0");


  screen_w=atoi2(w1);
  screen_h=atoi2(h1);

  if(*w==0&&*h==0)
  {
    canvas_w = screen_w;
    canvas_h = screen_h;
  }

  else if(*w!=0&&*h!=0) 
  {canvas_w = *w; canvas_h = *h;}
  else {assert(0);}
  center_x=(screen_w-canvas_w)/2;
  center_y=(screen_h-canvas_h)/2;
  //todo要求画布大小不能超过屏幕大小
  printf("screen w %d  screen h %d \n",screen_w,screen_h);
  printf("canvas w %d  canvas h %d \n",canvas_w,canvas_h);
  printf("center x %d  center y %d \n",center_x,center_y);
  //printf("screen w %d  screen h %d \n",screen_w,screen_h);
  //printf("canvas w %d  canvas h %d \n",canvas_w,canvas_h);
  //printf("center x %d  center y %d \n",center_x,center_y);
  //printf("bufsize%d\n",sizeof(buf));
  //printf("fuck you too\n");
  //printf("%s",buf);
  //return 0;


}


void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h) 
{

 // memset(pixels,0x00ff0000,sizeof(pixels));

 //FILE *fd=fopen("/dev/fb","+r");
 //printf("fd  %d\n",fd);
 if(x==0&&y==0&&w==0&&h==0)
 {
   w=screen_w;
   h=screen_h;
 }
  x=center_x+x;
  y=center_y+y;
  lseek(5,y*screen_w+x,SEEK_SET);
  for(int j=y;j<y+canvas_h;j++)
  {
      //printf("j %d  \n",j);
      write(5,(pixels),(canvas_w));
      lseek(5,(j+1)*screen_w+x,SEEK_SET);
      //fwrite((pixels),4,(canvas_w),fd);
      
      pixels=pixels+canvas_w;
      //fprintf(fd,)
    
  }
  

}

void NDL_OpenAudio(int freq, int channels, int samples) {
}

void NDL_CloseAudio() {
}

int NDL_PlayAudio(void *buf, int len) {
  return 0;
}

int NDL_QueryAudio() {
  return 0;
}

int NDL_Init(uint32_t flags) {
  if (getenv("NWM_APP")) {
    evtdev = 3;
  }
  return 0;
}

void NDL_Quit() {
}
