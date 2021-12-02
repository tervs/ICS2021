#include <common.h>


void syscall_ex(Event e, Context* c);

static Context* do_event(Event e, Context* c) {
  switch (e.event) {
    case 1:printf("yield here!\n");break;
    case 2:syscall_ex( e, c);break;
    default: panic("Unhandled event ID = %d", e.event);
  }

  return c;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  cte_init(do_event);
}


void syscall_ex(Event e, Context* c)
{
      switch (c->mcause) {
      case 0: ;break;
      //case 1: yield();break;
      //case 0:ev.event = EVENT_SYSCALL;break;
      default: panic("syscall_ex fail\n"); break;
    }

}