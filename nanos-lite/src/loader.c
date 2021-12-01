#include <proc.h>
#include <elf.h>

#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif
Elf_Ehdr *elf;
static uintptr_t loader(PCB *pcb, const char *filename) {
  printf("test1\n");
  assert(1);
  //assert(*(uint32_t *)elf->e_ident == 0x7f454c47);
  printf("test2\n");
  TODO();
  return 0;
}

void naive_uload(PCB *pcb, const char *filename) {
  
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}

