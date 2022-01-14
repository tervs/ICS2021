#include <proc.h>

#define MAX_NR_PROC 4

static PCB pcb[MAX_NR_PROC] __attribute__((used)) = {};
static PCB pcb_boot = {};
PCB *current = NULL;
uintptr_t loader(PCB *pcb, const char *filename);

void context_kload(PCB* pcb,void(*entry)(void*),void *arg){
  //printf("entry %x\n",entry);
  Area stack = {pcb->stack,pcb->stack + STACK_SIZE};

  //printf("stack:%p->%p\n",stack.start,stack.end);
  pcb->cp=kcontext(stack,entry,arg);
  //printf("pcb->cp:%p\n",pcb->cp);
} 
void context_uload(PCB *pcb, const char *filename, char *const argv[], char *const envp[])
{
    Area ustack = {pcb->stack,pcb->stack + STACK_SIZE};
  intptr_t entry=loader(pcb,filename);
  int size = 0, size_argv = 0, size_envp = 0, argc = 0, envc = 0;
    while (argv[argc] != NULL)
  {
    size_argv += strlen(argv[argc]) + 1;
    argc++;
  }
  while (envp[envc] != NULL)
  {
    size_envp += strlen(envp[envc]) + 1;
    envc++;
  }
    size = size_envp + size_argv + sizeof(uintptr_t) * (argc + 4 + envc);
  size = size - size % sizeof(uintptr_t);
  void *ret = pcb->as.area.end - size;
  void *args_start = ustack.end - size;
  void *str_start = args_start + sizeof(uintptr_t) * (argc + 3 + envc);

  memset(args_start, 0, ustack.end - args_start);
  *(uintptr_t *)args_start = argc;
  for (int i = 0; i < argc; i++)
  {
    memcpy(str_start, argv[i], strlen(argv[i]));
    *(uintptr_t *)(args_start + sizeof(uintptr_t) * (i + 1)) = (uintptr_t)str_start;
    str_start += strlen(argv[i]) + 1;
  }
  *(uintptr_t *)(args_start + sizeof(uintptr_t) * (1 + argc)) = 0;
  for (int i = 0; i < envc; i++)
  {
    memcpy(str_start, envp[i], strlen(envp[i]));
    *(uintptr_t *)(args_start + sizeof(uintptr_t) * (argc + 2 + i)) = (uintptr_t)str_start;
    str_start += strlen(envp[i]) + 1;
  }
  *(uintptr_t *)(args_start + sizeof(uintptr_t) * (argc + 2 + envc)) = 0;
  //printf("entry %x\n",entry);

  //printf("file %s enter at %x\n",filename,entry);
  //printf("stack:%p->%p\n",stack.start,stack.end);
  pcb->cp=ucontext(NULL,ustack,(void *)entry);
  //pcb->cp->GPRx = (uintptr_t)heap.end; 
  pcb->cp->GPRx = (uintptr_t)ret;
  //printf("pcb->cp:%p\n",pcb->cp);nt
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
  context_kload(&pcb[0], hello_fun, (void *)0xffffffff);
  context_uload(&pcb[1], "/bin/pal",NULL,NULL);
  switch_boot_pcb();

  Log("Initializing processes...");
  //naive_uload(NULL, "/bin/nterm");
  // load program here

}

Context* schedule(Context *prev) {
  //printf("current->cp %x\n",current->cp);
  //printf("call schedule to switch pcb\n");
  // save the context pointer
current->cp = prev;
//printf("prev %x\n",prev);
// always select pcb[0] as the new process
//current = &pcb[0];
current = (current == &pcb[0] ? &pcb[1] : &pcb[0]);
//printf("pcb0 %x\n",&pcb[0]);
//printf("return from sch  %x\n",current->cp);
// then return the new context
return current->cp;

  //return NULL;
}
