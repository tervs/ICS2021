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
f(bge)


def_all_EXEC_ID();

/*


Disassembly of section .text:

80000000 <_start>:
80000000:	00000413          	li	s0,0
80000004:	00009117          	auipc	sp,0x9
80000008:	ffc10113          	addi	sp,sp,-4 # 80009000 <_end>
8000000c:	118000ef          	jal	ra,80000124 <_trm_init>

80000010 <check>:
80000010:	00050463          	beqz	a0,80000018 <check+0x8>
80000014:	00008067          	ret
80000018:	ff010113          	addi	sp,sp,-16
8000001c:	00100513          	li	a0,1
80000020:	00112623          	sw	ra,12(sp)
80000024:	0f4000ef          	jal	ra,80000118 <halt>

80000028 <bubble_sort>:
80000028:	80000537          	lui	a0,0x80000
8000002c:	14850513          	addi	a0,a0,328 # 80000148 <_end+0xffff7148>
80000030:	04c50613          	addi	a2,a0,76
80000034:	01300593          	li	a1,19
80000038:	00050793          	mv	a5,a0
8000003c:	02b05063          	blez	a1,8000005c <bubble_sort+0x34>
80000040:	0007a703          	lw	a4,0(a5)
80000044:	0047a683          	lw	a3,4(a5)
80000048:	00e6d663          	bge	a3,a4,80000054 <bubble_sort+0x2c>
8000004c:	00d7a023          	sw	a3,0(a5)
80000050:	00e7a223          	sw	a4,4(a5)
80000054:	00478793          	addi	a5,a5,4
80000058:	fec794e3          	bne	a5,a2,80000040 <bubble_sort+0x18>
8000005c:	fff58593          	addi	a1,a1,-1
80000060:	ffc60793          	addi	a5,a2,-4
80000064:	00a60663          	beq	a2,a0,80000070 <bubble_sort+0x48>
80000068:	00078613          	mv	a2,a5
8000006c:	fcdff06f          	j	80000038 <bubble_sort+0x10>
80000070:	00008067          	ret

80000074 <main>:
80000074:	fe010113          	addi	sp,sp,-32
80000078:	00912a23          	sw	s1,20(sp)
8000007c:	800004b7          	lui	s1,0x80000
80000080:	00812c23          	sw	s0,24(sp)
80000084:	01212823          	sw	s2,16(sp)
80000088:	01312623          	sw	s3,12(sp)
8000008c:	00112e23          	sw	ra,28(sp)
80000090:	14848913          	addi	s2,s1,328 # 80000148 <_end+0xffff7148>
80000094:	f95ff0ef          	jal	ra,80000028 <bubble_sort>
80000098:	14848493          	addi	s1,s1,328
8000009c:	00000413          	li	s0,0
800000a0:	01400993          	li	s3,20
800000a4:	0004a503          	lw	a0,0(s1)
800000a8:	00448493          	addi	s1,s1,4
800000ac:	40850533          	sub	a0,a0,s0
800000b0:	00153513          	seqz	a0,a0
800000b4:	00140413          	addi	s0,s0,1
800000b8:	f59ff0ef          	jal	ra,80000010 <check>
800000bc:	ff3414e3          	bne	s0,s3,800000a4 <main+0x30>
800000c0:	00100513          	li	a0,1
800000c4:	f4dff0ef          	jal	ra,80000010 <check>
800000c8:	00000413          	li	s0,0
800000cc:	f5dff0ef          	jal	ra,80000028 <bubble_sort>
800000d0:	01400493          	li	s1,20
800000d4:	00092503          	lw	a0,0(s2)
800000d8:	00490913          	addi	s2,s2,4
800000dc:	40850533          	sub	a0,a0,s0
800000e0:	00153513          	seqz	a0,a0
800000e4:	00140413          	addi	s0,s0,1
800000e8:	f29ff0ef          	jal	ra,80000010 <check>
800000ec:	fe9414e3          	bne	s0,s1,800000d4 <main+0x60>
800000f0:	00100513          	li	a0,1
800000f4:	f1dff0ef          	jal	ra,80000010 <check>
800000f8:	01c12083          	lw	ra,28(sp)
800000fc:	01812403          	lw	s0,24(sp)
80000100:	01412483          	lw	s1,20(sp)
80000104:	01012903          	lw	s2,16(sp)
80000108:	00c12983          	lw	s3,12(sp)
8000010c:	00000513          	li	a0,0
80000110:	02010113          	addi	sp,sp,32
80000114:	00008067          	ret

80000118 <halt>:
80000118:	00050513          	mv	a0,a0
8000011c:	0000006b          	0x6b
80000120:	0000006f          	j	80000120 <halt+0x8>

80000124 <_trm_init>:
80000124:	80000537          	lui	a0,0x80000
80000128:	ff010113          	addi	sp,sp,-16
8000012c:	14450513          	addi	a0,a0,324 # 80000144 <_end+0xffff7144>
80000130:	00112623          	sw	ra,12(sp)
80000134:	f41ff0ef          	jal	ra,80000074 <main>
80000138:	00050513          	mv	a0,a0
8000013c:	0000006b          	0x6b
80000140:	0000006f          	j	80000140 <_trm_init+0x1c>
*/