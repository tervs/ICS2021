#include <nterm.h>
#include <stdarg.h>
#include <unistd.h>
#include <SDL.h>

char handle_key(SDL_Event *ev);

static void sh_printf(const char *format, ...) {
  static char buf[256] = {};
  va_list ap;
  va_start(ap, format);
  int len = vsnprintf(buf, 256, format, ap);
  va_end(ap);
  term->write(buf, len);
}

static void sh_banner() {
  sh_printf("Built-in Shell in NTerm (NJU Terminal)\n\n");
}

static void sh_prompt() {
  sh_printf("sh> ");
}

static void sh_handle_cmd(const char *cmd) {
  SDL_Surface *screen = SDL_SetVideoMode(0, 0, 32, SDL_HWSURFACE);
  uint32_t *x=(uint32_t *)screen->pixels;//malloc(4*400*300);
  x=(uint32_t *)malloc(screen->w*screen->h);
  memset(x,0,4*400*300);
    //NDL_DrawRect(x,0,0,0,0);
SDL_UpdateRect(screen,0,0,0,0);


  char s[100];
  //printf("len %d\n",strlen(cmd));
  int len=strlen(cmd);
  strcpy(s,cmd);
  s[len-1]='\0';
  //printf("success\n");
  //printf("len%dlen\n",s[len-1]);
  //s[len]
  
  execve(s,0,0);
  
}

void builtin_sh_run() {
  sh_banner();
  sh_prompt();

  while (1) {
    SDL_Event ev;
    if (SDL_PollEvent(&ev)) {
      //printf("recieve key\n");
      if (ev.type == SDL_KEYUP || ev.type == SDL_KEYDOWN) {
        const char *res = term->keypress(handle_key(&ev));
        if (res) {
          sh_handle_cmd(res);
          sh_prompt();
        }
      }
    }
    refresh_terminal();
  }
}
