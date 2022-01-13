
#include <fs.h>


#define ENTRY 0x83000000
extern int screen_w;
extern int screen_h;
typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);
#define file_num sizeof(file_table)/sizeof(Finfo)
size_t fb_write(const void *buf, size_t offset, size_t len);
size_t dispinfo_read(void *buf, size_t offset, size_t len) ;
size_t events_read(void *buf, size_t offset, size_t len) ;
size_t serial_write(const void *buf, size_t offset, size_t len) ;
size_t get_ramdisk_size();
size_t ramdisk_read(void *buf, size_t offset, size_t len) ;
size_t ramdisk_write(const void *buf, size_t offset, size_t len) ;
size_t fs_lseek(int fd, size_t offset, int whence);
typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  size_t open_offset;
  ReadFn read;
  WriteFn write;
} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR, DEV_KBD,  DEC_CTL, DEV_FB,    FD_FB};

 int screen_w;
int screen_h;


size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  [FD_STDIN]  = {"stdin", -1, 0, 0, invalid_read, invalid_write},
  [FD_STDOUT] = {"stdout", -1, 0, 0, invalid_read, serial_write},
  [FD_STDERR] = {"stderr", -1, 0, 0, invalid_read, serial_write},
  [DEV_KBD]   = {"/dev/events",-1,0,0,events_read,invalid_write},
  [DEC_CTL]    = {"/proc/dispinfo",-1,0,0,dispinfo_read,invalid_write},
  [DEV_FB]    = {"/dev/fb",-1,0,0,invalid_read,fb_write},

  ///
#include "files.h"
};

void init_fs() 
{
  char initbuf[128];
  dispinfo_read(initbuf,0,8);
  char *w1=strtok(initbuf,":");
  char *h1=strtok(NULL,"\0");


  screen_w=atoi(w1);
  screen_h=atoi(h1);
  file_table[DEV_FB].size=4*screen_h*screen_w;
  Log("fs init");
  //printf("0x%08x\n",file_table[DEV_FB].size);

  //fb_start=(uint32_t *)malloc(4*screen_h*screen_w);
  



  // TODO: initialize the size of /dev/fb
}







size_t fs_write(int fd, const void *buf, size_t len)
{
  //printf("write   %d\n",fd);
  WriteFn write = (file_table[fd].write == NULL) ? (WriteFn) ramdisk_write : file_table[fd].write;
  int ret=0;

  if(file_table[fd].open_offset+len>file_table[fd].size)
  {len = file_table[fd].size- file_table[fd].open_offset;}

  if(len>0)
  {
    ret=write(buf,file_table[fd].disk_offset+file_table[fd].open_offset,len);
  }
  file_table[fd].open_offset+=len;

  //printf("open_offset %d\n",file_table[fd].open_offset);
  
  return ret;
  
  //printf("open: 0x%08x    size: 0x%08x\n",file_table[fd].open_offset,file_table[fd].size);

}




int fs_open(const char *pathname, int flags, int mode)
{printf("\n\n\n\n");
  printf("%s",pathname);
  //if(strcmp(pathname,"/dev/events")){
    //printf("call opne %s\n",pathname);}
  for(int i=0;i<file_num;i++)
  {  
    if(strcmp(pathname,"/dev/events"))
  {
    printf("comp %s\n",file_table[i].name);
    printf("res %d\n",strcmp(file_table[i].name,pathname));
    
  }
    //printf("%s\n",file_table[i].name);
    //if(file_table[i].name==pathname)
  
    if(strcmp(file_table[i].name,pathname)==0)
    //if(strcmp(file_table[i].name,pathname))
    {
      //printf("%d   %s\n",i,file_table[i].name);
      fs_lseek(i,0,SEEK_SET);
      return i;
    }
  }
  assert(0);
  return 0;
}




int fs_close(int fd)
{
  return 0;
}




size_t fs_read(int fd, void *buf, size_t len)
{
  //printf("test in read\n");
  //printf("read   %d\n",fd);
  ReadFn read = (file_table[fd].read == NULL) ? (ReadFn) ramdisk_read : file_table[fd].read;
  //printf("open: 0x%08x    size: 0x%08x\n",file_table[fd].open_offset,file_table[fd].size);
  int ret=0;
  if(file_table[fd].open_offset+len>file_table[fd].size)
  {len = file_table[fd].size- file_table[fd].open_offset;}

  if(len>0)
  {
    ret=read(buf,file_table[fd].disk_offset+file_table[fd].open_offset,len);
    }
  file_table[fd].open_offset+=len;
   //printf("open_offset %d\n",file_table[fd].open_offset);
  //printf("%d\n",file_table[fd].disk_offset);
  return ret;
}

size_t fs_len(int fd)
{
  return file_table[fd].size;
}







size_t fs_lseek(int fd, size_t offset, int whence)
{
  size_t old_offset=file_table[fd].open_offset;
  switch(whence)
  {
		case SEEK_SET:file_table[fd].open_offset=offset;break;
		case SEEK_CUR:file_table[fd].open_offset+=offset;break;
		case SEEK_END:file_table[fd].open_offset=file_table[fd].size+offset;break;
    default: assert(0);
  }
   //printf("before: 0x%08x    after: 0x%08x\n",old_offset,file_table[fd].open_offset); 
    if(file_table[fd].open_offset>file_table[fd].size)
    {
        file_table[fd].open_offset=old_offset;
        return -1;
    }
    // printf("open_offset %d\n",file_table[fd].open_offset);
  return file_table[fd].open_offset;
  //return 0;
}