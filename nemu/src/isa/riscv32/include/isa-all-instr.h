#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(lui) f(lw) f(sw) f(inv) f(nemu_trap) \
f(addi) \
f(auipc)\
f(jal)\
f(jalr)\
f(add)\
f(sub)\
f(sltiu)\
f(beq)\
f(bne)\
f(sltu)\
f(xor)\
f(or)\
f(sb)\
f(srai)\
f(lbu)\
f(and)\
f(andi)\
f(sll)\
f(xori)\
f(ori)\
f(bge)\
f(mul)\
f(div)\
f(lh)\
f(lhu)\
f(slli)\
f(srl)\
f(srli)\
f(sh)\
f(rem)\
f(blt)\
f(slt)\
f(sra)\
f(bltu)\
f(mulh)\
f(divu)\
f(bgeu)

def_all_EXEC_ID();