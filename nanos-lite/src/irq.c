#include <common.h>


void syscall_ex(Event e, Context* c);

static Context* do_event(Event e, Context* c) {
  switch (e.event) {
    case 1:printf("yield here!\n");break;
    case 2:printf("syscall\n");break;
    default: panic("Unhandled event ID = %d", e.event);
  }

  return c;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  cte_init(do_event);
}
