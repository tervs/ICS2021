#include <NDL.h>
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#define keyname(k) #k,

static const char *keyname[] = {
  "NONE",
  _KEYS(keyname)
};

int SDL_PushEvent(SDL_Event *ev) {
  return 0;
}

int SDL_PollEvent(SDL_Event *ev) {
  return 0;
}

int SDL_WaitEvent(SDL_Event *event) {
  
  char buf[64];
  //char *a;
  //char *b;

  
  if (NDL_PollEvent(buf, sizeof(buf)))
  {
    printf("waitevent %s\n",buf);
    for(int i=0;i<64;i++)
    {
      printf("%d  %c",i,buf[i]);
    }
    //char *w1=strtok(buf," ");
    //char *h1=strtok(NULL,"\0");
    //printf("a  %s  %s\n",w1,h1);
    //b=strtok(NULL,"\n");

   // printf("a: %s   b %s\n",a,b);
  }
  
  return 1;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  return NULL;
}
