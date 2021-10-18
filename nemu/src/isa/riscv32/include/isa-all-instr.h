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
f(blt)


def_all_EXEC_ID();
/*


Disassembly of section .text:

80000000 <_start>:
80000000:	00000413          	li	s0,0
80000004:	00009117          	auipc	sp,0x9
80000008:	ffc10113          	addi	sp,sp,-4 # 80009000 <_end>
8000000c:	0e8000ef          	jal	ra,800000f4 <_trm_init>

80000010 <check>:
80000010:	00050463          	beqz	a0,80000018 <check+0x8>
80000014:	00008067          	ret
80000018:	ff010113          	addi	sp,sp,-16
8000001c:	00100513          	li	a0,1
80000020:	00112623          	sw	ra,12(sp)
80000024:	0c4000ef          	jal	ra,800000e8 <halt>

80000028 <main>:
80000028:	fe010113          	addi	sp,sp,-32
8000002c:	00812c23          	sw	s0,24(sp)
80000030:	80000437          	lui	s0,0x80000
80000034:	00912a23          	sw	s1,20(sp)
80000038:	15040413          	addi	s0,s0,336 # 80000150 <_end+0xffff7150>
8000003c:	800004b7          	lui	s1,0x80000
80000040:	01212823          	sw	s2,16(sp)
80000044:	01312623          	sw	s3,12(sp)
80000048:	01412423          	sw	s4,8(sp)
8000004c:	01512223          	sw	s5,4(sp)
80000050:	01612023          	sw	s6,0(sp)
80000054:	00112e23          	sw	ra,28(sp)
80000058:	11848493          	addi	s1,s1,280 # 80000118 <_end+0xffff7118>
8000005c:	03840993          	addi	s3,s0,56
80000060:	1f400913          	li	s2,500
80000064:	12c00a93          	li	s5,300
80000068:	06400b13          	li	s6,100
8000006c:	03200a13          	li	s4,50
80000070:	00042783          	lw	a5,0(s0)
80000074:	09600713          	li	a4,150
80000078:	00440413          	addi	s0,s0,4
8000007c:	02f94063          	blt	s2,a5,8000009c <main+0x74>
80000080:	00fa2733          	slt	a4,s4,a5
80000084:	40e006b3          	neg	a3,a4
80000088:	06400713          	li	a4,100
8000008c:	00fac863          	blt	s5,a5,8000009c <main+0x74>
80000090:	04b00713          	li	a4,75
80000094:	00fb4463          	blt	s6,a5,8000009c <main+0x74>
80000098:	0326f713          	andi	a4,a3,50
8000009c:	0004a503          	lw	a0,0(s1)
800000a0:	00448493          	addi	s1,s1,4
800000a4:	40e50533          	sub	a0,a0,a4
800000a8:	00153513          	seqz	a0,a0
800000ac:	f65ff0ef          	jal	ra,80000010 <check>
800000b0:	fd3410e3          	bne	s0,s3,80000070 <main+0x48>
800000b4:	00100513          	li	a0,1
800000b8:	f59ff0ef          	jal	ra,80000010 <check>
800000bc:	01c12083          	lw	ra,28(sp)
800000c0:	01812403          	lw	s0,24(sp)
800000c4:	01412483          	lw	s1,20(sp)
800000c8:	01012903          	lw	s2,16(sp)
800000cc:	00c12983          	lw	s3,12(sp)
800000d0:	00812a03          	lw	s4,8(sp)
800000d4:	00412a83          	lw	s5,4(sp)
800000d8:	00012b03          	lw	s6,0(sp)
800000dc:	00000513          	li	a0,0
800000e0:	02010113          	addi	sp,sp,32
800000e4:	00008067          	ret

800000e8 <halt>:
800000e8:	00050513          	mv	a0,a0
800000ec:	0000006b          	0x6b
800000f0:	0000006f          	j	800000f0 <halt+0x8>

800000f4 <_trm_init>:
800000f4:	80000537          	lui	a0,0x80000
800000f8:	ff010113          	addi	sp,sp,-16
800000fc:	11450513          	addi	a0,a0,276 # 80000114 <_end+0xffff7114>
80000100:	00112623          	sw	ra,12(sp)
80000104:	f25ff0ef          	jal	ra,80000028 <main>
80000108:	00050513          	mv	a0,a0
8000010c:	0000006b          	0x6b
80000110:	0000006f          	j	80000110 <_trm_init+0x1c>
*/