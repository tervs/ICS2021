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
void strace();

static uint32_t sec;
static uint32_t usec;





void do_syscall(Context *c) {
 
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;

  //strace();

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
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
  //is_reg_display();
}


uintptr_t sys_yield()
{
  
  yield();
  return 0;
}

uintptr_t sys_exit()
{
  
  halt(0);
  return 0;
}

uintptr_t sys_write()
{
  
   
    int ret=fs_write(a[1],(void *)(a[2]),a[3]);
    //printf("0x%08x\n",ret);
    return ret;
  

}

uintptr_t sys_brk()
{
  
  return 0;
}

uintptr_t sys_open()
{
  char *ch=(char *)(a[1]);
  //printf("%s\n",ch);

  
  int fd=fs_open(ch,0,0);
  //printf("%d\n",fd);

  return fd; 
}

uintptr_t sys_lseek()
{
  //printf("a1 %d  a2 0x%08x  a3 %d\n",a[1],a[2],a[3]);
  
  return fs_lseek(a[1],a[2],a[3]);
  //return 1;
}

uintptr_t sys_read()
{
  
  int ret=fs_read(a[1],(void *)(a[2]),a[3]);
  //printf("0x%08x\n",ret);
  return ret;
}

uintptr_t sys_close()
{
  
  return fs_close(a[1]);
}


uintptr_t sys_gettimeofday()
{

  
  uint32_t x=(uint32_t)(io_read(AM_TIMER_UPTIME).us);
  sec=x/1000000;
  usec=x;


  uint32_t* times=( uint32_t * )(a[1]);
  uint32_t* timeus=( uint32_t * )(a[2]);
  *times=sec;
  *timeus=usec; 
  return 0;
}


void strace()
{
  printf("\n");
  printf("a0 %d  a1 0x%08x  a2 0x%08x  a3 %d\n",a[0],a[1],a[2],a[3]);
  switch (a[0]) {
    case 0: printf("syscall exit\n");break;
    case 1: printf("syscall yield\n");break;
    case 2: printf("syscall open\n");break;
    case 3: printf("syscall read\n");break;
    case 4: printf("syscall write \n");break;
    case 7: printf("syscall close\n");break;
    case 8: printf("syscall lseek\n");break;
    case 9: printf("syscall brk \n");break;
    case 19:printf("syscall  gettimeofday\n");break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}
