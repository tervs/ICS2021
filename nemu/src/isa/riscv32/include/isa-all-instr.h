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
f(mul)


def_all_EXEC_ID();

/*

80000000 <_start>:
80000000:	00000413          	li	s0,0
80000004:	00009117          	auipc	sp,0x9
80000008:	ffc10113          	addi	sp,sp,-4 # 80009000 <_end>
8000000c:	0f4000ef          	jal	ra,80000100 <_trm_init>

80000010 <check>:
80000010:	00050463          	beqz	a0,80000018 <check+0x8>
80000014:	00008067          	ret
80000018:	ff010113          	addi	sp,sp,-16
8000001c:	00100513          	li	a0,1
80000020:	00112623          	sw	ra,12(sp)
80000024:	0d0000ef          	jal	ra,800000f4 <halt>

80000028 <main>:
80000028:	ff010113          	addi	sp,sp,-16
8000002c:	80000737          	lui	a4,0x80000
80000030:	00912223          	sw	s1,4(sp)
80000034:	00112623          	sw	ra,12(sp)
80000038:	12470493          	addi	s1,a4,292 # 80000124 <_end+0xffff7124>
8000003c:	00812423          	sw	s0,8(sp)
80000040:	01212023          	sw	s2,0(sp)
80000044:	12470713          	addi	a4,a4,292
80000048:	00000793          	li	a5,0
8000004c:	00a00693          	li	a3,10
80000050:	00f72023          	sw	a5,0(a4)
80000054:	00178793          	addi	a5,a5,1
80000058:	00470713          	addi	a4,a4,4
8000005c:	fed79ae3          	bne	a5,a3,80000050 <main+0x28>
80000060:	02848593          	addi	a1,s1,40
80000064:	00048613          	mv	a2,s1
80000068:	00b00693          	li	a3,11
8000006c:	00062703          	lw	a4,0(a2)
80000070:	00100793          	li	a5,1
80000074:	02f70733          	mul	a4,a4,a5
80000078:	00178793          	addi	a5,a5,1
8000007c:	fed79ce3          	bne	a5,a3,80000074 <main+0x4c>
80000080:	00e62023          	sw	a4,0(a2)
80000084:	00460613          	addi	a2,a2,4
80000088:	feb612e3          	bne	a2,a1,8000006c <main+0x44>
8000008c:	00048613          	mv	a2,s1
80000090:	00b00693          	li	a3,11
80000094:	00062703          	lw	a4,0(a2)
80000098:	00100793          	li	a5,1
8000009c:	02f74733          	div	a4,a4,a5
800000a0:	00178793          	addi	a5,a5,1
800000a4:	fed79ce3          	bne	a5,a3,8000009c <main+0x74>
800000a8:	00e62023          	sw	a4,0(a2)
800000ac:	00460613          	addi	a2,a2,4
800000b0:	feb612e3          	bne	a2,a1,80000094 <main+0x6c>
800000b4:	00000413          	li	s0,0
800000b8:	00a00913          	li	s2,10
800000bc:	0004a503          	lw	a0,0(s1)
800000c0:	00448493          	addi	s1,s1,4
800000c4:	40850533          	sub	a0,a0,s0
800000c8:	00153513          	seqz	a0,a0
800000cc:	00140413          	addi	s0,s0,1
800000d0:	f41ff0ef          	jal	ra,80000010 <check>
800000d4:	ff2414e3          	bne	s0,s2,800000bc <main+0x94>
800000d8:	00c12083          	lw	ra,12(sp)
800000dc:	00812403          	lw	s0,8(sp)
800000e0:	00412483          	lw	s1,4(sp)
800000e4:	00012903          	lw	s2,0(sp)
800000e8:	00000513          	li	a0,0
800000ec:	01010113          	addi	sp,sp,16
800000f0:	00008067          	ret

800000f4 <halt>:
800000f4:	00050513          	mv	a0,a0
800000f8:	0000006b          	0x6b
800000fc:	0000006f          	j	800000fc <halt+0x8>

80000100 <_trm_init>:
80000100:	80000537          	lui	a0,0x80000
80000104:	ff010113          	addi	sp,sp,-16
80000108:	12050513          	addi	a0,a0,288 # 80000120 <_end+0xffff7120>
8000010c:	00112623          	sw	ra,12(sp)
80000110:	f19ff0ef          	jal	ra,80000028 <main>
80000114:	00050513          	mv	a0,a0
80000118:	0000006b          	0x6b
8000011c:	0000006f          	j	8000011c <_trm_init+0x1c>
*/