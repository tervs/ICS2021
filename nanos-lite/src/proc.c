#include <proc.h>

#define MAX_NR_PROC 4

static PCB pcb[MAX_NR_PROC] __attribute__((used)) = {};
static PCB pcb_boot = {};
PCB *current = NULL;


void context_kload(PCB* pcb,void(*entry)(void*),void *arg){
  Area stack = {pcb->stack,pcb->stack + STACK_SIZE};

  printf("st:%p->%p\n",stack.start,stack.end);
  pcb->cp=kcontext(stack,entry,arg);
  printf("pcb->cp:%p\n",pcb->cp);
} 




void naive_uload(PCB *pcb, const char *filename);

void switch_boot_pcb() {
  current = &pcb_boot;
}

void hello_fun(void *arg) {
  int j = 1;
  while (1) {
    Log("Hello World from Nanos-lite with arg '%p' for the %dth time!", (uintptr_t)arg, j);
    j ++;
    yield();
  }
}

void init_proc() {
  context_kload(&pcb[0], hello_fun, NULL);
  switch_boot_pcb();

  Log("Initializing processes...");
  //naive_uload(NULL, "/bin/nterm");
  // load program here

}

Context* schedule(Context *prev) {
  // save the context pointer
current->cp = prev;

// always select pcb[0] as the new process
current = &pcb[0];

// then return the new context
return current->cp;
  return NULL;
}
