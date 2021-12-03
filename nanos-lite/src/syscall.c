#include <common.h>
#include "syscall.h"

uintptr_t sys_yield();
uintptr_t sys_exit();
uintptr_t sys_write();
void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  



  //printf("%d\n\n\n\n",a[0]);
  switch (a[0]) {
    case 0: c->GPRx=sys_exit();break;
    case 1: c->GPRx=sys_yield();break;
    case 4: c->GPRx=sys_write();break;
    default: panic("Unhandled syscall ID = %d", a[1]);
  }
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
  printf("syscall 4\n");
  return 0;
}