#include <NDL.h>
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define keyname(k) #k,

    char *keycode=NULL;
    char *type=NULL;
static const char *keyname[] = {
  "NONE",
  _KEYS(keyname)
};
#define NR_KEY (sizeof(keyname) / sizeof(keyname[0]))
static uint8_t keystate[NR_KEY];
int SDL_PushEvent(SDL_Event *ev) {

  return 0;
}

int SDL_PollEvent(SDL_Event *ev) {

  //type=strtok(NULL,"\0");
  return 0;
}
/*
int SDL_WaitEvent(SDL_Event *event) {

  char buf[64];


  if (NDL_PollEvent(buf, sizeof(buf)))
  {

    keycode=strtok(buf," ");
    type=strtok(NULL,"\0");
    //event->key.type=SDL_KEYDOWN;
    //event->key.keysym.sym=SDLK_UP;//keyname[keycode];
    //event->key.keysym.sym=keycode;
    printf("key %s   type  %s\n",keycode,type);
    return 1;

  }
  //printf("%s\n",keycode);
  return 1;
}
*/
int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  return NULL;
}


int SDL_WaitEvent(SDL_Event *event) {
  char key[64]={0};
  memset(key,0,sizeof(key));
  key[0] = '0';
  int keycode = 0;

  printf("%s\n",key);
  char* str = key+3;
  if(NDL_PollEvent(key,sizeof(key)))
  {
  for(int i = 0,cnt = 0;i < sizeof(keyname);i+=sizeof(keyname[cnt]),cnt+=1)
  {
    if(!strncmp(keyname[cnt],str,strlen(str))&&!strncmp(keyname[cnt],str,strlen(keyname[cnt]))) {
        keycode = cnt;
        break;
      }
    assert(i <= sizeof(keyname));
  }
  }
  //printf("in waitevent\n");
  if(key[1] == 'u')
  {
    event->key.keysym.sym = keycode;
    event->type = SDL_KEYUP;
    keystate[keycode] = 0;
  }
  else if(key[1] == 'd'){
    event->key.keysym.sym = keycode;
    event->type = SDL_KEYDOWN;
    keystate[keycode] = 1;
  }
  else assert(0);
  printf("keycode %s ",keyname[keycode]);
  return 0;
}