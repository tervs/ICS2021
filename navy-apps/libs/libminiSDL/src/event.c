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
  char *a;
  char *b;
  if (NDL_PollEvent(buf, sizeof(buf)))
  {
    a=strtok(buf," ");
    b=strtok(NULL,"\n");

    printf("a: %s   b %s\n",a,b);
  }
  return 1;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  return NULL;
}
