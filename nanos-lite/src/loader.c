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

size_t get_ramdisk_size();
size_t ramdisk_read(void *buf, size_t offset, size_t len) ;
size_t ramdisk_write(const void *buf, size_t offset, size_t len) ;

Elf_Ehdr *elf;




 



static uintptr_t loader(PCB *pcb, const char *filename) {





  //printf("0x%08x\n",*(uint32_t *)elf->e_ident);
  //assert(*(uint32_t *)elf->e_ident == 0x7f454c47);
  ramdisk_read((void *)ENTRY,0x000000,50000);
  

  printf("test2\n");
  //TODO();
  return ENTRY+0x3dc;
}

void naive_uload(PCB *pcb, const char *filename) {
  
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}

