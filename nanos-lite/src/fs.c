
#include <fs.h>

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);

size_t ramdisk_read(void *buf, size_t offset, size_t len);
size_t ramdisk_write(const void *buf, size_t offset, size_t len);
size_t get_ramdisk_size();

size_t fs_len(int fd);
size_t serial_write(const void *buf, size_t offset, size_t len);
size_t events_read(void *buf, size_t offset, size_t len);
size_t dispinfo_read(void *buf, size_t offset, size_t len);
size_t fb_write(const void *buf, size_t offset, size_t len);

typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  //size_t open_offset;
  ReadFn read;
  WriteFn write;
  size_t open_offset;
} Finfo;
static int scr_w,scr_h;
enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_EVENT,FD_DISPINFO,FD_FB};

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
  [FD_STDIN]  = {"stdin", 0, 0, invalid_read, invalid_write,0},
  [FD_STDOUT] = {"stdout", 0, 0, invalid_read, serial_write,0},
  [FD_STDERR] = {"stderr", 0, 0, invalid_read, serial_write,0},
  [FD_EVENT]={"/dev/events",0,0,events_read,invalid_write,0},
  [FD_DISPINFO]={"/proc/dispinfo",128,0,dispinfo_read,invalid_write,0},
  [FD_FB]={"/dev/fb",0,0,invalid_read,fb_write,0},
#include "files.h"
};

int fs_open(const char* pathname,int flags, int mode){
  //printf("%s\n",pathname);
  int p=0;
  int n=(int)(sizeof(file_table)/sizeof(Finfo));
  for(p=0;p<n;p++){
    //printf("%s\n",file_table[p].name);
    if(strcmp(pathname,file_table[p].name)==0){
      file_table[p].open_offset=0;
      //printf("p:%d,offset%d\n",p,file_table[p].open_offset);
      return p;
  }
  }
  assert(p!=n);
  return -1;
}

int fs_close(int fd){//wait to be modified
  return 0;
}

//每次对文件读写多少字节，就偏移多少
size_t fs_read(int fd,void* buf,size_t len){
  Finfo* p=&file_table[fd];
  if(p->read==NULL){
  //printf("0x%p\n",p->disk_offset);
  //printf("0x%p\n",p->open_offset);
  //printf("%p\t,%p\n",p->open_offset,p->size);
  assert(p->open_offset<=p->size);

  /*if(p->size >= p->open_offset+len){
    ramdisk_read(buf,p->disk_offset+p->open_offset,len);
    p->open_offset=len+p->open_offset;
    assert(p->open_offset<=p->size);
    return len;
  }else if(p->size <= p->open_offset+len){
    ramdisk_read(buf,p->disk_offset+p->open_offset,p->size-p->open_offset);
    p->open_offset=p->size;
    assert(p->open_offset<=p->size);
    return p->size-p->open_offset;
  }*///??????怎么这个就错了

  size_t po=p->open_offset;
  size_t pd=p->disk_offset;
  size_t ps=p->size;
  if(ps >= po + len){
    ramdisk_read(buf,pd + po , len);
    p->open_offset=po + len;
    assert(p->open_offset<=p->size);
    return len;
  }else if(ps < po + len){
    ramdisk_read(buf,pd + po, ps - po);
    p->open_offset=ps;
    assert(p->open_offset<=p->size);
    return ps - po;
  }
  assert(0);
  return 0;
  }else{
    int flag=p->read(buf,p->open_offset,len);//fuck
    p->open_offset+=len;
    return flag;
  }

}

size_t fs_lseek(int fd,size_t offset,int whence){
  Finfo* p=&file_table[fd];
  int flag=0;
  //printf("mae:%d\n",p->open_offset);
  if(whence==SEEK_SET){
    //assert(offset>=0&&offset<=p->size);
    if(offset>=0&&offset<=p->size){
    p->open_offset=offset;flag=1;}
  }else if(whence==SEEK_CUR){
    //assert(offset+p->open_offset>=0 && offset+p->open_offset<=p->size);
    if(offset+p->open_offset>=0 && offset+p->open_offset<=p->size){
    p->open_offset+=offset;flag=1;}
  }else if(whence==SEEK_END){
    assert(offset<=0);
    p->open_offset=p->size+offset;
  }
  //printf("after:%d\n",p->open_offset);
  if(flag==0) {return -1;}
  return p->open_offset;
}

size_t fs_write(int fd,const void *buf,size_t len){

  Finfo* p=&file_table[fd];
  //if(p->write!=NULL) printf("budengyu nulllll\n");
  //else printf("dengyunullll\n");
  if(p->write==NULL){//ordinary write
  //wait to modify fd==0
  size_t po=p->open_offset;
  size_t pd=p->disk_offset;
  size_t ps=p->size;
  if(ps >= po + len){
    ramdisk_write(buf,pd + po , len);
    p->open_offset=po + len;
    assert(p->open_offset<=p->size);
    return len;
  }else if(ps < po + len){
    ramdisk_write(buf,pd + po, ps - po);
    p->open_offset=ps;
    assert(p->open_offset<=p->size);
    return ps - po;
  }
  assert(0);
  return 0;
  } else if(p->write!=NULL){//serial write
  //printf("333333333333333333\n");
    int flag=p->write(buf,p->open_offset,len);
    p->open_offset+=len;
    return flag;
  } 
  return 0;
}

void init_fs() {
  // TODO: initialize the size of /dev/fb
  scr_w=io_read(AM_GPU_CONFIG).width;
  scr_h=io_read(AM_GPU_CONFIG).height;
  file_table[FD_FB].size=4*scr_w*scr_h;
  //printf("%d\n",file_table[FD_FB].size);
}

size_t fs_len(int fd)
{
  return file_table[fd].size;
}