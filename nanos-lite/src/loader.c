#include <proc.h>
#include <elf.h>

#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif

size_t get_ramdisk_size();



Elf_Ehdr *elf;
static uintptr_t loader(PCB *pcb, const char *filename) {
  //printf("0x%08x\n",*(uint32_t *)elf->e_ident);
  //assert(*(uint32_t *)elf->e_ident == 0x7f454c47);

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

