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
  extern int screen_w;
  extern int screen_h;


#define NAME(key) \
  [AM_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [AM_KEY_NONE] = "NONE",
  AM_KEYS(NAME)
};

size_t serial_write(const void *buf, size_t offset, size_t len) {
  for(int i = 0; i < len;i ++) {
      putch(((char*)buf)[i]);
    }
  return len;
}



size_t events_read(void *buf, size_t offset, size_t len) {
  AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
  if(ev.keycode == AM_KEY_NONE) {
    //memset(buf,0,len);
    return 0;
  }
  else{
    memset(buf,0,len);
    if(ev.keydown)
    {
      sprintf((char*)buf,"kd %s\n",keyname[ev.keycode]);
    }
    else sprintf((char*)buf,"ku %s\n",keyname[ev.keycode]);
    //printf("%s %d",(char*)buf,strlen((char*)buf));
    return strlen((char*)buf);

  }
}

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  int w = io_read(AM_GPU_CONFIG).width;
  int h = io_read(AM_GPU_CONFIG).height;
  return sprintf((char*)buf,"%d:%d\n",w,h);
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  /*
  int w = io_read(AM_GPU_CONFIG).width;
  int h = io_read(AM_GPU_CONFIG).height;
  int x = (offset/4)%w;
  int y = (offset/4)/w;
  if(offset+len > w*h*4) len = w*h*4 - offset;

  io_write(AM_GPU_FBDRAW,x,y,(uint32_t*)buf,len/4,1,false);
  //io_write(AM_GPU_FBDRAW, 0, 0, NULL, 0, 0, true);
  assert(offset <= w*h*4);
  return len;
  */


    uint32_t *pixels= (uint32_t *)buf;
  
 //printf("w:   %d   h  %d\n",screen_w,screen_h); 
  int x=offset%(screen_w);
  int y=offset/(screen_w);
  //printf("x  %d   y %d ",x,y);


  
  
  io_write(AM_GPU_FBDRAW, x, y,pixels, len, 1, true);

  return 0;
}
//在这里处理超出的字符

size_t fb_sync(const void *buf,size_t offset,size_t len)
{
  assert(((char*)buf)[0] == '1');
  //printf("refresh\n");
  assert(offset == 0);
  io_write(AM_GPU_FBDRAW, 0, 0, NULL, 0, 0, true);
  return 1;
}



void init_device() {
  Log("Initializing devices...");
  ioe_init();

  
}
