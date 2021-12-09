#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

static int evtdev = -1;
static int fbdev = -1;
static int screen_w = 0, screen_h = 0;
static int canvas_w = 0, canvas_h = 0;
//size_t fs_read(int fd, void *buf, size_t len);
//int gettimeofday(struct timeval *tv, struct timezone *tz) ;

uint32_t NDL_GetTicks() {
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_usec;


  
  //printf("tv_sec:%ld   tv_usec:%lu\n",tv.tv_sec,tv.tv_usec);
  //return 0;
}

int NDL_PollEvent(char *buf, int len) {
  FILE *fp = fopen("/share/files/num", "r+");
  //int fd=open("/dev/events",0,0);
  fread(buf,1,len,fp);
  //printf("%d",len);
//printf("NDL_read %s \n",buf);
  fclose(fp);
  return len;
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
printf("     fuck you\n");
  read(4,buf,16);
  char *w1=strtok(buf,":");
  char *h1=strtok(NULL,"\0");
  printf("fuck you\n");
  printf("%s\n",w1);
  int w2=atoi(w1);
  printf("w2   %d\n",w2);
  printf("%s\n",h1);
  //printf("bufsize%d\n",sizeof(buf));
  //printf("fuck you too\n");
  //printf("%s",buf);
  //return 0;


}


void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h) {
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
