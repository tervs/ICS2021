#include <common.h>
#include <sys/time.h>

#if defined(MULTIPROGRAM) && !defined(TIME_SHARING)
# define MULTIPROGRAM_YIELD() yield()
#else
# define MULTIPROGRAM_YIELD()
#endif

int fs_open(const char *pathname, int flags, int mode);
size_t fs_read(int fd, void *buf, size_t len);
size_t fs_write(int fd, const void *buf, size_t len);
size_t fs_lseek(int fd, size_t offset, int whence);
int fs_close(int fd);
size_t fb_write(const void *buf, size_t offset, size_t len);
  extern int screen_w;
  extern int screen_h;


#define NAME(key) \
  [AM_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [AM_KEY_NONE] = "NONE",
  AM_KEYS(NAME)
};

size_t serial_write(const void *buf, size_t offset, size_t len) 
{
  //printf("test\n\n\n\n\n\n\n\n\n");  
  char *ch=(char *)(buf);
  for(int i=0;i<len;i++)
  {
    putch(*(ch+i));
  }
  printf("\n");
  return len;
  
  //return len;
}

size_t events_read(void *buf, size_t offset, size_t len) {

//printf("test\n");
      AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
      if (ev.keycode == AM_KEY_NONE) return 0;
      else
      {
          //printf("")
         snprintf(buf,len,"%s %s",(ev.keydown ? "kd" : "ku"),keyname[ev.keycode]);
          //strcpy(buf,keyname[ev.keycode]);
          //strcat(buf,(ev.keydown ? "DOWN" : "UP"));
          //printf("event test %s\n",buf);
          return len;
      }

  
      //printf("Got  (kbd): %s (%d) %s\n", keyname[ev.keycode], ev.keycode, ev.keydown ? "DOWN" : "UP");
    
  
  return -1;
}



size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  //printf("0x%08x\n",(uint32_t)(buf));
  int h = io_read(AM_GPU_CONFIG).height;
  int w = io_read(AM_GPU_CONFIG).width;
  //uint64_t src=(w<<32)|h;
  //printf("%u  %u \n",h,w);
  //strcpy(buf,(char *)h);
  //char s[128];
  sprintf(buf,"%d:%d\n",w,h);
  //printf("test in disinfo   %s\n",buf);

  return len;
  
  //return 0;
}
size_t fb_write(const void *buf, size_t offset, size_t len) {


    uint32_t *pixels= (uint32_t *)buf;
  
 //printf("w:   %d   h  %d\n",screen_w,screen_h); 
  int x=offset%(screen_w);
  int y=offset/(screen_w);
  //printf("x  %d   y %d ",x,y);


  
  
  io_write(AM_GPU_FBDRAW, x, y,pixels, len, 1, true);

  return 0;
}
//在这里处理超出的字符



void init_device() {
  Log("Initializing devices...");
  ioe_init();

  
}
