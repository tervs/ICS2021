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

static uint32_t *enterpoint;

static uint32_t *program_start;

static uint16_t *program_size;
void get_elf();


 //static size_t open_offset[100];
//static uint32_t *p;
//p=(uint32_t *)(ENTRY);

//static uint32_t *phstart=



static uintptr_t loader(PCB *pcb, const char *filename) {

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
#ifdef TEST
  uint32_t *x= (uint32_t*)(ENTRY);
  for(int i=0;i<5000;i++)
  {
    printf("0x%08x  0x%08x\n",x,*x);
    x++;
    //x=x+i;
  }
#endif

}

void naive_uload(PCB *pcb, const char *filename) {
  
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = 0x%08x", entry);
 
  ((void(*)())entry) ();
  
}

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
/*
static uint32_t *elf_start;
static uint32_t *enterpoint;
static uint32_t *program_start;
static uint16_t *program_size;
*/