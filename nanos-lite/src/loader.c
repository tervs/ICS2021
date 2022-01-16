

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
//static uint32_t *p;
//p=(uint32_t *)(ENTRY);

//static uint32_t *phstart=



uintptr_t loader(PCB *pcb, const char *filename) {
  //TODO();
  //uint32_t size = get_ramdisk_size();
  //printf("%d\n",size);
  Elf_Ehdr elfhdr;
  Elf_Phdr prohdr;
  //printf("test in load %s\n",filename);
  size_t fd = fs_open(filename,0,0);
  //printf("%d\n",fd);
  fs_read(fd,&elfhdr,sizeof(Elf_Ehdr));
  //printf("%x %x\n",elfhdr.e_phoff,elfhdr.e_phnum);
  assert(fd != -1);
  //printf("%x %x %x %d\n",elfhdr.e_entry,elfhdr.e_phentsize,elfhdr.e_ehsize,elfhdr.e_phnum);
  //assert(0);
  for(int i = 0;i < elfhdr.e_phnum;i++)
  {
    //printf("i is %d\n",i);
    fs_lseek(fd,elfhdr.e_phoff+i*sizeof(Elf_Phdr),SEEK_SET);
    //rintf("test 1\n");
    fs_read(fd,&prohdr,sizeof(Elf_Phdr));
    //printf("out\n");
    assert(0);
    if(prohdr.p_type == PT_LOAD){
      //printf("test 2\n");
      fs_lseek(fd,prohdr.p_offset,SEEK_SET);
      //printf("fucccc\n");
      fs_read(fd,(void *)prohdr.p_vaddr,prohdr.p_filesz);
      //printf("test 3\n");
      //printf("from %x %x size = %x \n",prohdr.p_vaddr,prohdr.p_offset,prohdr.p_filesz);
      memset((void*)(prohdr.p_vaddr+prohdr.p_filesz),0,prohdr.p_memsz-prohdr.p_filesz);
      //printf("test 4\n");
    }//之前用的memcpy，不愧是我
    
  }
  fd = fs_close(fd);
  assert(fd == 0);
  //printf("%s File Loaded\n",filename);
  //printf("entry point %x\n",elfhdr.e_entry);
  //assert(0);
  return elfhdr.e_entry;

/*
  if(filename!=NULL)
  {
  //printf("0x%08x\n",get_ramdisk_size());
 
  int fd=fs_open(filename,0,0);

  size_t len=fs_len(fd);

  fs_read(fd,(void *)ENTRY,len);
  //printf("test2\n");

  get_elf();

  //printf("0x%08x\n\n\n\n",*enterpoint);
  
  
  //void *p1=(void *)(p);
  return (uintptr_t)(*enterpoint);
  //printf("0x%08x\n",*(p+6));

  }

return 0;

*/
}

void naive_uload(PCB *pcb, const char *filename) {
  
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = 0x%08x", entry);
 
  ((void(*)())entry) ();
  
}
/*
void get_elf()
{
   uint32_t *elf_start;
   uint32_t *program_offset;
  elf_start=(uint32_t *)(ENTRY);
  enterpoint=elf_start+6;
  program_offset=elf_start+7;
  program_start=(uint32_t *)((uintptr_t)(*program_offset+ENTRY));
  program_size=(uint16_t *)(ENTRY);
  program_size=program_size+21;



    for(int i=0;i<(*program_size/2);i=i+8)
  {
    //printf("test 0x%08x\n",*(program_start+i+5)-*(program_start+i+4));
    //printf("file 0x%08x\n",(*(program_start+i+3)+*(program_start+i+4)));
    memset((uint32_t *)((uintptr_t)(*(program_start+i+3)+*(program_start+i+4))),0,*(program_start+i+5)-*(program_start+i+4));
        //printf("i %d   0x%08x\n",i,*(program_start+i) );
    }


}

*/