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
f(rem)


def_all_EXEC_ID();
/*


Disassembly of section .text:

80000000 <_start>:
80000000:	00000413          	li	s0,0
80000004:	00009117          	auipc	sp,0x9
80000008:	ffc10113          	addi	sp,sp,-4 # 80009000 <_end>
8000000c:	0f8000ef          	jal	ra,80000104 <_trm_init>

80000010 <check>:
80000010:	00050463          	beqz	a0,80000018 <check+0x8>
80000014:	00008067          	ret
80000018:	ff010113          	addi	sp,sp,-16
8000001c:	00100513          	li	a0,1
80000020:	00112623          	sw	ra,12(sp)
80000024:	0d4000ef          	jal	ra,800000f8 <halt>

80000028 <main>:
80000028:	fe010113          	addi	sp,sp,-32
8000002c:	00912a23          	sw	s1,20(sp)
80000030:	800004b7          	lui	s1,0x80000
80000034:	00812c23          	sw	s0,24(sp)
80000038:	01212823          	sw	s2,16(sp)
8000003c:	01312623          	sw	s3,12(sp)
80000040:	01412423          	sw	s4,8(sp)
80000044:	01512223          	sw	s5,4(sp)
80000048:	00112e23          	sw	ra,28(sp)
8000004c:	06400413          	li	s0,100
80000050:	00000a93          	li	s5,0
80000054:	1f400993          	li	s3,500
80000058:	06400a13          	li	s4,100
8000005c:	00a00913          	li	s2,10
80000060:	12848493          	addi	s1,s1,296 # 80000128 <_end+0xffff7128>
80000064:	00140413          	addi	s0,s0,1
80000068:	05340e63          	beq	s0,s3,800000c4 <main+0x9c>
8000006c:	032447b3          	div	a5,s0,s2
80000070:	03444633          	div	a2,s0,s4
80000074:	0327e7b3          	rem	a5,a5,s2
80000078:	032466b3          	rem	a3,s0,s2
8000007c:	02f78733          	mul	a4,a5,a5
80000080:	02c60533          	mul	a0,a2,a2
80000084:	02d685b3          	mul	a1,a3,a3
80000088:	02f707b3          	mul	a5,a4,a5
8000008c:	02c50633          	mul	a2,a0,a2
80000090:	02d586b3          	mul	a3,a1,a3
80000094:	00c787b3          	add	a5,a5,a2
80000098:	00d787b3          	add	a5,a5,a3
8000009c:	fc8794e3          	bne	a5,s0,80000064 <main+0x3c>
800000a0:	002a9793          	slli	a5,s5,0x2
800000a4:	00f487b3          	add	a5,s1,a5
800000a8:	0007a503          	lw	a0,0(a5)
800000ac:	001a8a93          	addi	s5,s5,1
800000b0:	40850533          	sub	a0,a0,s0
800000b4:	00153513          	seqz	a0,a0
800000b8:	00140413          	addi	s0,s0,1
800000bc:	f55ff0ef          	jal	ra,80000010 <check>
800000c0:	fb3416e3          	bne	s0,s3,8000006c <main+0x44>
800000c4:	ffca8513          	addi	a0,s5,-4
800000c8:	00153513          	seqz	a0,a0
800000cc:	f45ff0ef          	jal	ra,80000010 <check>
800000d0:	01c12083          	lw	ra,28(sp)
800000d4:	01812403          	lw	s0,24(sp)
800000d8:	01412483          	lw	s1,20(sp)
800000dc:	01012903          	lw	s2,16(sp)
800000e0:	00c12983          	lw	s3,12(sp)
800000e4:	00812a03          	lw	s4,8(sp)
800000e8:	00412a83          	lw	s5,4(sp)
800000ec:	00000513          	li	a0,0
800000f0:	02010113          	addi	sp,sp,32
800000f4:	00008067          	ret

800000f8 <halt>:
800000f8:	00050513          	mv	a0,a0
800000fc:	0000006b          	0x6b
80000100:	0000006f          	j	80000100 <halt+0x8>

80000104 <_trm_init>:
80000104:	80000537          	lui	a0,0x80000
80000108:	ff010113          	addi	sp,sp,-16
8000010c:	12450513          	addi	a0,a0,292 # 80000124 <_end+0xffff7124>
80000110:	00112623          	sw	ra,12(sp)
80000114:	f15ff0ef          	jal	ra,80000028 <main>
80000118:	00050513          	mv	a0,a0
8000011c:	0000006b          	0x6b
80000120:	0000006f          	j	80000120 <_trm_init+0x1c>
*/