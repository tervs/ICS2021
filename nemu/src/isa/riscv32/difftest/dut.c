#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"
extern const char *regs[];

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {

bool s=true;
bool s0=true;
  for(int i=0;i<32;i++)
  {
     s=difftest_check_reg(regs[i],pc,(*ref_r).gpr[i]._32,gpr(i));
     if(!s){s0=false;}
  }
  if(cpu.pc!=(*ref_r).pc)
  {
    Log("You got wrong pc! right = 0x%08x   wrong = 0x%08x ",(*ref_r).pc,cpu.pc);
    return false;
  }
 return s0;
}

void isa_difftest_attach() {
}
