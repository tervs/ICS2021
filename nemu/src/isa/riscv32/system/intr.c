#include <isa.h>
//#include<../rtl.h>
extern rtlreg_t _mepc;
extern rtlreg_t _mstatus;
extern rtlreg_t _mcause;
extern rtlreg_t _mtvec;
#define IRQ_TIMER 0x80000007  // for riscv32

word_t isa_raise_intr(word_t NO, vaddr_t *epc,vaddr_t *dnpc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
  //printf("0x%08x\n\n\n\n",*epc);
  //printf("0x%08x\n\n\n\n",_mtvec);
  printf("before 0x%08x in nemu\n",_mstatus);
  int mie=_mstatus&(0x00000008);
  _mstatus=_mstatus&(0xfffffff7);
  if(!mie){
    _mstatus=_mstatus&(0xffffff7f);
  }else{_mstatus=_mstatus|(0x00000080);}
    _mepc=*epc;
    _mcause=NO;
    *dnpc=_mtvec;
    printf("mstatus 0x%08x in nemu\n",_mstatus);
    //_mepc=_mepc+4;
    //asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));
    //asm volatile("li a7, -1; ");
  return  0x80001350;//_mtvec;
}




word_t isa_query_intr() {  
  if ( cpu.INTR ) {
    cpu.INTR = false;
    return IRQ_TIMER;
  }
  return INTR_EMPTY;
  
}
