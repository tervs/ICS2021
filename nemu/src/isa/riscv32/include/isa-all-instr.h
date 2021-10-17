#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(lui) f(lw) f(sw) f(inv) f(nemu_trap) \
f(addi) \
f(auipc)\
f(jal)\
f(jalr)
//f(mv) 
//f(slti) f(sltiu) f(xori)\f(ori) f(andi) 

def_all_EXEC_ID();


/*
Disassembly of section .text:

80000000 <_start>:
80000000:	00000413          	li	s0,0
80000004:	00009117          	auipc	sp,0x9
80000008:	ffc10113          	addi	sp,sp,-4 # 80009000 <_end>
8000000c:	00c000ef          	jal	ra,80000018 <_trm_init>

80000010 <main>:
80000010:	00000513          	li	a0,0
80000014:	00008067          	ret

80000018 <_trm_init>:
80000018:	80000537          	lui	a0,0x80000
8000001c:	ff010113          	addi	sp,sp,-16
80000020:	03850513          	addi	a0,a0,56 # 80000038 <_end+0xffff7038>
80000024:	00112623          	sw	ra,12(sp)
80000028:	fe9ff0ef          	jal	ra,80000010 <main>
8000002c:	00050513          	mv	a0,a0
80000030:	0000006b          	0x6b
80000034:	0000006f          	j	80000034 <_trm_init+0x1c>

*/