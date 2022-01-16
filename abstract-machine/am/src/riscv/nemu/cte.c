#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>
#include <arch/riscv32-nemu.h>
//extern struct Context;
//extern uint32_t _mepc;
//extern rtlreg_t _mepc;
static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {

 printf("mcause  0x%08x\n\n",c->mcause);
//printf("0x%08x\n",c->mepc);
  //printf("\n\n\n\n\n\n\n");
  if (user_handler) {
    Event ev = {0};
    switch (c->mcause) {
      case -1:ev.event=EVENT_YIELD;break;
      //case 0x0000000b: ev.event = EVENT_SYSCALL;break;
      case 0x00000000: ev.event = EVENT_SYSCALL;break;
      case 0x00000001: ev.event = EVENT_SYSCALL;break;
      case 0x00000002: ev.event = EVENT_SYSCALL;break;
      case 0x00000003: ev.event = EVENT_SYSCALL;break;
      case 0x00000004: ev.event = EVENT_SYSCALL;break;
      case 0x00000007: ev.event = EVENT_SYSCALL;break;
      case 0x00000008: ev.event = EVENT_SYSCALL;break;
      case 0x00000009: ev.event = EVENT_SYSCALL;break;
      case 0x00000013: ev.event = EVENT_SYSCALL;break;
      case 0x00000019: ev.event = EVENT_SYSCALL;break;
      case 0x80000007:ev.event=EVENT_IRQ_TIMER;break;
      //case 0:ev.event = EVENT_SYSCALL;break;
      default: ev.event = EVENT_ERROR; break;
    }
  //printf("begin excute\n");
    c = user_handler(ev, c);
    //printf("c addr %x\n",(uintptr_t)c);
    /*
    uint32_t cp=(uint32_t )c;
    uint32_t x0=0;
    printf("c addr %x\n",(uintptr_t)c);
    asm volatile
    ("add sp,%[src2],%[src]"
    :
    :[src]"r"(cp),[src2]"r"(x0)
    );
    */
    //printf("c addr %x\n",(uintptr_t)c);
    /*
    uint32_t *pt=(uint32_t *)(uintptr_t)c;
    
    for(int i=0;i<=36;i++)
    {
      printf("i:%d  pt:%x  *pt:%x\n",i,pt,*pt);
      pt++;
    }
    
    */
    assert(c != NULL);
  }
  //printf("end call\n");
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
  //assert(0);
  //assert(0);
    Context *c = kstack.end - sizeof(Context);
  *c = (Context) { 0 };
  c->mepc=(uintptr_t)entry;
  c->gpr[10]=(intptr_t)arg;
  //assert(0);
  //printf("mepc  %x\n",c->mepc);
  return c;
  //return NULL;
}

void yield() {
  asm volatile("li a7, -1; ecall");
  //printf("0x%08x",gpr(17));
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
