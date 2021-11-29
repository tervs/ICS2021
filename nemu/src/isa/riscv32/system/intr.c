#include <isa.h>

rtlreg_t _mepc;
rtlreg_t _mstatus=0x1800;
rtlreg_t _mcause;
rtlreg_t _mtvec;


word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
    _mepc=epc;

  return 0;
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
