/*
#include <common.h>

void do_syscall(Context *c);

static Context* do_event(Event e, Context* c) {
  //printf("%d\n",e.event);
  switch (e.event) {
    case EVENT_SYSCALL: do_syscall(c); break;
    case EVENT_YIELD: printf("Yield\n"); break;
    
    default: panic("Unhandled event ID = %d", e.event);
  }

  return c;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  cte_init(do_event);
}
*/

#include <common.h>


int syscall_ex(Event e, Context* c);
void do_syscall(Context *c);
static Context* do_event(Event e, Context* c) {
  switch (e.event) {
    case 1:printf("yield here!\n");break;
    case 2:do_syscall(c);break;
    default: panic("Unhandled event ID = %d", e.event);
  }

  return c;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  cte_init(do_event);
}
