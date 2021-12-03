#include <common.h>
#include "syscall.h"

 uintptr_t a[4];

uintptr_t sys_yield();
uintptr_t sys_exit();
uintptr_t sys_write();
uintptr_t sys_brk();


int count=0;
void do_syscall(Context *c) {
 
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  



  //printf("%d\n\n\n\n",a[0]);
  switch (a[0]) {
    case 0: c->GPRx=sys_exit();break;
    case 1: c->GPRx=sys_yield();break;
    case 4: c->GPRx=sys_write();break;
    case 9: c->GPRx=sys_brk();break;
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
  printf("syscall 0\n");
  halt(0);
  return 0;
}

uintptr_t sys_write()
{
if(a[1]==1||a[1]==2)
{
  //printf("syscall 4\n");
  
  count++;
  char *ch=(char *)(a[2]);
  for(int i=0;i<a[3];i++)
  {
    putch(*(ch+i));
  }

  return a[3];
}
printf("you see here?\n");
return -1;
}

uintptr_t sys_brk()
{
  printf("syscall brk   addr: 0x%08x\n",a[1]);

  return 0;
}