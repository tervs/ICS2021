#include <NDL.h>
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#define keyname(k) #k,

    char *keycode=NULL;
    char *type=NULL;
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
  NDL_PollEvent(buf, sizeof(buf));
  printf("%s\n",buf);
printf("%s\n",buf);
//printf("sfkhsklajhd \n");
//printf("dsfdsfds   %c\n",buf[0]);
  //if (NDL_PollEvent(buf, sizeof(buf)))
  //{
    
    //return -1;
    //printf("%s\n",buf);
    /*
    for(int j=0;j<i;j++)
    {
      //return 1;
      printf("%c",buf[j]);
    }
    */
    //printf("djskfklf\n");
    //keycode=strtok(buf," ");
    //event->key.type=SDL_KEYDOWN;
    //event->key.keysym.sym=SDLK_UP;//keyname[keycode];
    //event->key.keysym.sym=keycode;
    //printf("%s\n",keycode);
    //char *type=strtok(NULL,"\0");

    //printf("%c \n",buf[0]);
    /*
    for(int i=0;i<64;i++)
    {
      printf("%d  %c",i,buf[i]);
    }
    */
    //char *w1=strtok(buf," ");
    //printf("%s\n",w1);
    //event->key
    //char *h1=strtok(NULL,"\0");
    //printf("a  %s  %s\n",w1,h1);
    //b=strtok(NULL,"\n");

   // printf("a: %s   b %s\n",a,b);
  //}
  //printf("%s\n",keycode);
  return 1;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  return NULL;
}
