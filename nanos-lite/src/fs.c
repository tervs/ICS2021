#include <fs.h>

#define ENTRY 0x83000000
typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);


extern size_t serial_write(const void *buf, size_t offset, size_t len) ;
size_t get_ramdisk_size();
size_t ramdisk_read(void *buf, size_t offset, size_t len) ;
size_t ramdisk_write(const void *buf, size_t offset, size_t len) ;
typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  size_t open_offset;
  ReadFn read;
  WriteFn write;
} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_FB};




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
#include "files.h"
};

void init_fs() {
  // TODO: initialize the size of /dev/fb
}







size_t fs_write(int fd, const void *buf, size_t len)
{
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
{
  //printf("%s\n",pathname);
  for(int i=0;i<23;i++)
  {
    //printf("%s\n",file_table[i].name);
    //if(file_table[i].name==pathname)
    if(strcmp(file_table[i].name,pathname)==0)
    //if(strcmp(file_table[i].name,pathname))
    {
      //printf("%d   %s\n",i,file_table[i].name);
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
  //printf("open: 0x%08x    size: 0x%08x\n",file_table[fd].open_offset,file_table[fd].size);
  int ret=0;
  if(file_table[fd].open_offset+len>file_table[fd].size)
  {len = file_table[fd].size- file_table[fd].open_offset;}

  if(len>0)
  {
    ret=ramdisk_read(buf,file_table[fd].disk_offset+file_table[fd].open_offset,len);
    }
  file_table[fd].open_offset+=len;
  // printf("open_offset %d\n",file_table[fd].open_offset);
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

