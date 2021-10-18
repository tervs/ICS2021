#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  
  bool s=difftest_check_reg("s0",pc,(*ref_r).gpr[0]._32,gpr(0));
  
  
  return s;
}

void isa_difftest_attach() {
}
