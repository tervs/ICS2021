#include <isa.h>
//#include<../rtl.h>
extern rtlreg_t _mepc;
extern rtlreg_t _mstatus;
extern rtlreg_t _mcause;
extern rtlreg_t _mtvec;


word_t isa_raise_intr(word_t NO, vaddr_t *epc,vaddr_t *dnpc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
  printf("0x%08x\n\n\n\n",*epc);
  printf("0x%08x\n\n\n\n",_mtvec);
    _mepc=*epc;
    _mcause=NO;
    *dnpc=_mtvec;
  return 0;
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
