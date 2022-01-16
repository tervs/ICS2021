

#include <common.h>
Context* schedule(Context *prev);

int syscall_ex(Event e, Context* c);
void do_syscall(Context *c);
static Context* do_event(Event e, Context* c) {
  switch (e.event) {
    case 1:return schedule(c);break;
    case 2:do_syscall(c);break;
    case 5:return schedule(c);break;
    default: panic("Unhandled event ID = %d", e.event);
  }

  return c;
}
//printf("yield here!\n");
void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  cte_init(do_event);
}
