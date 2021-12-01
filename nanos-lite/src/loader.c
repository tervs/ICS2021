#include <proc.h>
#include <elf.h>

#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif

#define N 100000
size_t get_ramdisk_size();
size_t ramdisk_read(void *buf, size_t offset, size_t len) ;
size_t ramdisk_write(const void *buf, size_t offset, size_t len) ;
size_t buf[N];

Elf_Ehdr *elf;
static uintptr_t loader(PCB *pcb, const char *filename) {
  //printf("0x%08x\n",*(uint32_t *)elf->e_ident);
  //assert(*(uint32_t *)elf->e_ident == 0x7f454c47);
  ramdisk_read(buf,0x000000,0x04df0);
  for(int i=0;i<0x04df0;i++)
  {
    printf("0x%08x  0x%08x  ",i,buf[i]);
  }
  uint32_t x=get_ramdisk_size();
  printf("%d\n",x);
  printf("test2\n");
  TODO();
  return 0;
}

void naive_uload(PCB *pcb, const char *filename) {
  
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}

