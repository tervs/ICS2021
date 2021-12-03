#include <fs.h>

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);
#define ENTRY 0x83000000
typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  ReadFn read;
  WriteFn write;
} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_FB};


int fs_open(const char *pathname, int flags, int mode);
size_t fs_read(int fd, void *buf, size_t len);
size_t fs_write(int fd, const void *buf, size_t len);
size_t fs_lseek(int fd, size_t offset, int whence);
int fs_close(int fd);
size_t fs_len(int fd);



size_t get_ramdisk_size();
size_t ramdisk_read(void *buf, size_t offset, size_t len) ;
size_t ramdisk_write(const void *buf, size_t offset, size_t len) ;


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
  [FD_STDIN]  = {"stdin", 0, 0, invalid_read, invalid_write},
  [FD_STDOUT] = {"stdout", 0, 0, invalid_read, invalid_write},
  [FD_STDERR] = {"stderr", 0, 0, invalid_read, invalid_write},
#include "files.h"
};

void init_fs() {
  // TODO: initialize the size of /dev/fb
}

size_t fs_write(int fd, const void *buf, size_t len)
{
  return ramdisk_write(buf, file_table[fd].disk_offset,len) ;
}

int fs_open(const char *pathname, int flags, int mode)
{
  printf("%s\n",pathname);
  for(int i=0;i<23;i++)
  {
    printf("%s\n",file_table[i].name);
    if(file_table[i].name==pathname)
    //if(strcmp(file_table[i].name,pathname)==1)
    {
      
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

  ramdisk_read(buf,file_table[fd].disk_offset,len);

  //printf("%d\n",file_table[fd].disk_offset);
  return len;
}

size_t fs_len(int fd)
{
  return file_table[fd].size;
}










