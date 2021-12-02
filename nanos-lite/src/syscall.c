#include <common.h>
#include "syscall.h"
void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  //printf("%d\n\n\n\n",a[0]);
  switch (a[0]) {
    case 0: printf("syscall 0\n");halt(0);break;
    case 1: printf("syscall 1\n");yield();break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}
