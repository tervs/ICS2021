#include <isa.h>
//#include<../rtl.h>
extern rtlreg_t _mepc;
extern rtlreg_t _mstatus;
extern rtlreg_t _mcause;
extern rtlreg_t _mtvec;


word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
    _mepc=epc;
    _mcause=NO;
    epc=_mtvec;
  return 0;
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
