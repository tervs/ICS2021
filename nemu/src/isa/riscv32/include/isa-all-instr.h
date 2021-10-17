#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(lui) f(lw) f(sw) f(inv) f(nemu_trap) \
f(addi) \
f(auipc)\
f(jal)\
f(jalr) 
//f(slti) f(sltiu) f(xori)\f(ori) f(andi) 

def_all_EXEC_ID();
