#include <am.h>
#include <nemu.h>
#include <klib.h>

static AddrSpace kas = {};
static void* (*pgalloc_usr)(int) = NULL;
static void (*pgfree_usr)(void*) = NULL;
static int vme_enable = 0;
extern char _pmem_start;
static Area segments[] = {      // Kernel memory mappings
  NEMU_PADDR_SPACE
};

#define USER_SPACE RANGE(0x40000000, 0x80000000)

static inline void set_satp(void *pdir) {
  uintptr_t mode = 1ul << (__riscv_xlen - 1);
  //printf("%x\n",(mode | ((uintptr_t)pdir >> 12)));
  asm volatile("csrw satp, %0" : : "r"(mode | ((uintptr_t)pdir >> 12)));
  //while(1);
}





static inline uintptr_t get_satp() {
  uintptr_t satp;
  asm volatile("csrr %0, satp" : "=r"(satp));
  return satp << 12;
}





bool vme_init(void* (*pgalloc_f)(int), void (*pgfree_f)(void*)) {
  //printf("%x\n",&(_pmem_start));
  //while(1);
  return true;
  pgalloc_usr = pgalloc_f;
  pgfree_usr = pgfree_f;

  kas.ptr = pgalloc_f(PGSIZE);

  int i;
  for (i = 0; i < LENGTH(segments); i ++) {
    void *va = segments[i].start;
    for (; va < segments[i].end; va += PGSIZE) {
      
      map(&kas, va, va, 0);
      
    }
  }
  
  set_satp(kas.ptr);
  
  vme_enable = 1;
  
  return true;

//return true;
}

void map(AddrSpace *as, void *va, void *pa, int prot) {

}




void protect(AddrSpace *as) {
  PTE *updir = (PTE*)(pgalloc_usr(PGSIZE));
  as->ptr = updir;
  as->area = USER_SPACE;
  as->pgsize = PGSIZE;
  // map kernel space
  memcpy(updir, kas.ptr, PGSIZE);
}





void unprotect(AddrSpace *as) {
}





void __am_get_cur_as(Context *c) {
  c->pdir = (vme_enable ? (void *)get_satp() : NULL);
}






void __am_switch(Context *c) {
  if (vme_enable && c->pdir != NULL) {
    set_satp(c->pdir);
  }
}














Context *ucontext(AddrSpace *as, Area kstack, void *entry) {
  //assert(0);
  Context *c = kstack.end - sizeof(Context);
  *c = (Context) { 0 };
  c->mepc=(uintptr_t)entry;
  c->mstatus=(c->mstatus)|(0x00000008);
  //c->gpr[10]=(intptr_t)arg;
  //printf("Ucontext pc %x\n",c->mepc);
  return c;
  //return NULL;
}
