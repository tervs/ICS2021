#include <common.h>
#include "syscall.h"

 uintptr_t a[4];

uintptr_t sys_yield();
uintptr_t sys_exit();
uintptr_t sys_write();
uintptr_t sys_brk();
uintptr_t sys_open();
uintptr_t sys_lseek();
int fs_open(const char *pathname, int flags, int mode);
size_t fs_read(int fd, void *buf, size_t len);
size_t fs_write(int fd, const void *buf, size_t len);
size_t fs_lseek(int fd, size_t offset, int whence);
int fs_close(int fd);

int count=0;
void do_syscall(Context *c) {
 
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  



  printf("a0  %d\n\n",a[0]);
  switch (a[0]) {
    case 0: c->GPRx=sys_exit();break;
    case 1: c->GPRx=sys_yield();break;
    case 2: c->GPRx=sys_open();break;
    case 4: c->GPRx=sys_write();break;
    case 8: c->GPRx=sys_lseek();break;
    case 9: c->GPRx=0;sys_brk();break;
    default: panic("Unhandled syscall ID = %d", a[1]);
  }

  //is_reg_display();
}


uintptr_t sys_yield()
{
  printf("syscall 1\n");
  yield();
  return 0;
}

uintptr_t sys_exit()
{
  printf("syscall exit\n");
  halt(0);
  return 0;
}

uintptr_t sys_write()
{

if(a[1]==1||a[1]==2)
{
  printf("syscall write \n");
  //printf("syscall 4\n");
  
  //printf("%d\n",count);
  //count++;
  char *ch=(char *)(a[2]);
  for(int i=0;i<a[3];i++)
  {
    putch(*(ch+i));
  }
  printf("\n");
  //printf("a0 %d  a1 0x%08x  a2 %d\n",a[1],a[2],a[3]);
  return a[3];
}
//printf("you see here?\n");
return -1;
}

uintptr_t sys_brk()
{
  printf("syscall brk \n");
  return 0;
}

uintptr_t sys_open()
{
  char *ch=(char *)(a[1]);
  //printf("%s\n",ch);

  printf("syscall open\n");
  int fd=fs_open(ch,0,0);
  //printf("%d\n",fd);

  return fd; 
}

uintptr_t sys_lseek()
{
  printf("syscall lseek\n");
  return 1;
}










