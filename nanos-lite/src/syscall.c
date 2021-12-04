#include <common.h>
#include "syscall.h"

 uintptr_t a[4];

uintptr_t sys_yield();
uintptr_t sys_exit();
uintptr_t sys_write();
uintptr_t sys_brk();
uintptr_t sys_open();
uintptr_t sys_lseek();
uintptr_t sys_read();
uintptr_t sys_close();
uintptr_t sys_gettimeofday();
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
  



  printf("\n");
  printf("a0 %d  a1 %d  a2 0x%08x  a3 %d\n",a[0],a[1],a[2],a[3]);
  switch (a[0]) {
    case 0: c->GPRx=sys_exit();break;
    case 1: c->GPRx=sys_yield();break;
    case 2: c->GPRx=sys_open();break;
    case 3: c->GPRx=sys_read();break;
    case 4: c->GPRx=sys_write();break;
    case 7: c->GPRx=sys_close();break;
    case 8: c->GPRx=sys_lseek();break;
    case 9: c->GPRx=0;sys_brk();break;
    case 19:c->GPRx=sys_gettimeofday();break;
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
  
    printf("syscall write \n");
    int ret=fs_write(a[1],(void *)(a[2]),a[3]);
    //printf("0x%08x\n",ret);
    return ret;
  

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
  //printf("a1 %d  a2 0x%08x  a3 %d\n",a[1],a[2],a[3]);
  printf("syscall lseek\n");
  return fs_lseek(a[1],a[2],a[3]);
  //return 1;
}

uintptr_t sys_read()
{
  printf("syscall read\n");
  int ret=fs_read(a[1],(void *)(a[2]),a[3]);
  //printf("0x%08x\n",ret);
  return ret;
}

uintptr_t sys_close()
{
  printf("syscall close\n");
  return fs_close(a[1]);
}


uintptr_t sys_gettimeofday()
{
  //printf("fusck you\n");
  intptr_t * time_us;
  time_us=( intptr_t * )(a[2]);
    *time_us=io_read(AM_TIMER_UPTIME).us;
    printf("time_us  %lu\n",io_read(AM_TIMER_UPTIME).us);
  
  return 0;
}



