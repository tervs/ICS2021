#include <common.h>

#if defined(MULTIPROGRAM) && !defined(TIME_SHARING)
# define MULTIPROGRAM_YIELD() yield()
#else
# define MULTIPROGRAM_YIELD()
#endif

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


      AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
      if (ev.keycode == AM_KEY_NONE) return 0;
      else
      {
          //printf("")
         snprintf(buf,len,"%s %s\n",keyname[ev.keycode],(ev.keydown ? "DOWN" : "UP"));
          //strcpy(buf,keyname[ev.keycode]);
          //strcat(buf,(ev.keydown ? "DOWN" : "UP"));
          //printf("event test %s\n",buf);
          return len;
      }

  
      //printf("Got  (kbd): %s (%d) %s\n", keyname[ev.keycode], ev.keycode, ev.keydown ? "DOWN" : "UP");
    
  
  return -1;
}

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  printf("just for test\n");
  int h = io_read(AM_GPU_CONFIG).height;
  int w = (uint64_t)io_read(AM_GPU_CONFIG).width;
  //uint64_t src=h;
  printf("%d  %d  %d \n",h,h,w);
  /*
  //uint64_t w = (uint64_t)io_read(AM_GPU_CONFIG).width;
  //printf("%d\n",io_read(AM_GPU_CONFIG).width);
  int h = io_read(AM_GPU_CONFIG).height;
  uint64_t src=w<<32||h;
  printf("%ld\n",src);
  memcpy(buf,&src,len);
 */
  return len;
  
  //return 0;
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  return 0;
}

void init_device() {
  Log("Initializing devices...");
  ioe_init();
}
