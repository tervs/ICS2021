#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>
//extern uint32_t _mepc;
//extern rtlreg_t _mepc;
static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {

 //printf("0x%08x\n",c->mcause);
//printf("0x%08x\n",c->mepc);
  //printf("\n\n\n\n\n\n\n");
  if (user_handler) {
    Event ev = {0};
    switch (c->mcause) {
      case 0x0000000b: ev.event = EVENT_YIELD;break;
      case 0x00000001: ev.event = EVENT_SYSCALL;break;
      case 0:ev.event = EVENT_SYSCALL;break;
      default: ev.event = EVENT_ERROR; break;
    }

    c = user_handler(ev, c);
    assert(c != NULL);
  }
  //_mepc=_mepc+4;
  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  return NULL;
}

void yield() {
  asm volatile("li a7, 0xb; ecall");
  //printf("0x%08x",gpr(17));
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
