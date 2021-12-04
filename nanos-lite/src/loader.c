#include <proc.h>
#include <elf.h>
#include <stdio.h>

#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif
#define ENTRY 0x83000000
//extern static Finfo file_table[];
//#define TEST

Elf_Ehdr *elf;
size_t get_ramdisk_size();
size_t ramdisk_read(void *buf, size_t offset, size_t len) ;
size_t ramdisk_write(const void *buf, size_t offset, size_t len) ;

int fs_open(const char *pathname, int flags, int mode);
size_t fs_read(int fd, void *buf, size_t len);
size_t fs_write(int fd, const void *buf, size_t len);
size_t fs_lseek(int fd, size_t offset, int whence);
int fs_close(int fd);
size_t fs_len(int fd);

 //static size_t open_offset[100];



static uintptr_t loader(PCB *pcb, const char *filename) {

  if(filename!=NULL)
  {
  //printf("0x%08x\n",get_ramdisk_size());
  int fd=fs_open(filename,0,0);
  size_t len=fs_len(fd);
  fs_read(fd,(void *)ENTRY,len);
  //assert(*(uint32_t *)elf->e_ident == 0x7f454c47);
  //ramdisk_read((void *)ENTRY,0x000000,get_ramdisk_size());
  //printf("%d   %d\n",fd,len);

  printf("test2\n");
  return ENTRY+0x5ab8;





  }

return 0;
#ifdef TEST
  uint32_t *x= (uint32_t*)(ENTRY);
  for(int i=0;i<5000;i++)
  {
    printf("0x%08x  0x%08x\n",x,*x);
    x++;
    //x=x+i;
  }
#endif
  //return 0;
}

void naive_uload(PCB *pcb, const char *filename) {
  
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}

