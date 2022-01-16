#include <memory.h>
#include <proc.h>
static void *pf = NULL;
#define PGSIZE 4096
void map(AddrSpace *as, void *va, void *pa, int prot);

extern PCB *current;


void* new_page(size_t nr_page) {
  void *p = pf;
    pf = pf + nr_page * PGSIZE;
    return p;
  //return NULL;
}

static void* pg_alloc(int n) {
   void *p = new_page(n / PGSIZE);
   memset(p, 0, n);
   return p;
  //return NULL;
}

void free_page(void *p) {
  panic("not implement yet");
}

/* The brk() system call handler. */
int mm_brk(uintptr_t brk) {

  if(brk > current->max_brk){
      uint32_t tem = (current->max_brk)&0xfffff000;
      while(tem < brk){
        void* paddr = new_page(1);
        
        
        map(&current->as,(void*)current->max_brk,paddr,0);
        
        tem += 4096;
        current->max_brk += 4096;
      }
  }
      return 0;

  //return 0;
}

void init_mm() {
  pf = (void *)ROUNDUP(heap.start, PGSIZE);
  Log("free physical pages starting from %p", pf);

  vme_init(pg_alloc, free_page);
}
