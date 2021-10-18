#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(lui) f(lw) f(sw) f(inv) f(nemu_trap) \
f(addi) \
f(auipc)\
f(jal)\
f(jalr)\
f(add)
//f(mv) 
//f(slti) f(sltiu) f(xori)\f(ori) f(andi) 

def_all_EXEC_ID();


/*
Disassembly of section .text:

80000000 <_start>:
80000000:	00000413          	li	s0,0
80000004:	00009117          	auipc	sp,0x9
80000008:	ffc10113          	addi	sp,sp,-4 # 80009000 <_end>
8000000c:	0fc000ef          	jal	ra,80000108 <_trm_init>

80000010 <check>:
80000010:	00050463          	beqz	a0,80000018 <check+0x8>
80000014:	00008067          	ret
80000018:	ff010113          	addi	sp,sp,-16
8000001c:	00100513          	li	a0,1
80000020:	00112623          	sw	ra,12(sp)
80000024:	0d8000ef          	jal	ra,800000fc <halt>

80000028 <main>:
80000028:	fd010113          	addi	sp,sp,-48
8000002c:	01312e23          	sw	s3,28(sp)
80000030:	01412c23          	sw	s4,24(sp)
80000034:	01512a23          	sw	s5,20(sp)
80000038:	80000a37          	lui	s4,0x80000
8000003c:	80000ab7          	lui	s5,0x80000
80000040:	800009b7          	lui	s3,0x80000
80000044:	01612823          	sw	s6,16(sp)
80000048:	01712623          	sw	s7,12(sp)
8000004c:	01812423          	sw	s8,8(sp)
80000050:	02112623          	sw	ra,44(sp)
80000054:	22ca0c13          	addi	s8,s4,556 # 8000022c <_end+0xffff722c>
80000058:	02812423          	sw	s0,40(sp)
8000005c:	02912223          	sw	s1,36(sp)
80000060:	03212023          	sw	s2,32(sp)
80000064:	12ca8a93          	addi	s5,s5,300 # 8000012c <_end+0xffff712c>
80000068:	22ca0a13          	addi	s4,s4,556
8000006c:	00000b13          	li	s6,0
80000070:	24c98993          	addi	s3,s3,588 # 8000024c <_end+0xffff724c>
80000074:	04000b93          	li	s7,64
80000078:	000a2903          	lw	s2,0(s4)
8000007c:	000a8493          	mv	s1,s5
80000080:	000c0413          	mv	s0,s8
80000084:	00042503          	lw	a0,0(s0)
80000088:	0004a783          	lw	a5,0(s1)
8000008c:	00440413          	addi	s0,s0,4
80000090:	00a90533          	add	a0,s2,a0
80000094:	40f50533          	sub	a0,a0,a5
80000098:	00153513          	seqz	a0,a0
8000009c:	f75ff0ef          	jal	ra,80000010 <check>
800000a0:	00448493          	addi	s1,s1,4
800000a4:	fe8990e3          	bne	s3,s0,80000084 <main+0x5c>
800000a8:	00100513          	li	a0,1
800000ac:	008b0b13          	addi	s6,s6,8
800000b0:	f61ff0ef          	jal	ra,80000010 <check>
800000b4:	004a0a13          	addi	s4,s4,4
800000b8:	020a8a93          	addi	s5,s5,32
800000bc:	fb7b1ee3          	bne	s6,s7,80000078 <main+0x50>
800000c0:	00100513          	li	a0,1
800000c4:	f4dff0ef          	jal	ra,80000010 <check>
800000c8:	02c12083          	lw	ra,44(sp)
800000cc:	02812403          	lw	s0,40(sp)
800000d0:	02412483          	lw	s1,36(sp)
800000d4:	02012903          	lw	s2,32(sp)
800000d8:	01c12983          	lw	s3,28(sp)
800000dc:	01812a03          	lw	s4,24(sp)
800000e0:	01412a83          	lw	s5,20(sp)
800000e4:	01012b03          	lw	s6,16(sp)
800000e8:	00c12b83          	lw	s7,12(sp)
800000ec:	00812c03          	lw	s8,8(sp)
800000f0:	00000513          	li	a0,0
800000f4:	03010113          	addi	sp,sp,48
800000f8:	00008067          	ret

800000fc <halt>:
800000fc:	00050513          	mv	a0,a0
80000100:	0000006b          	0x6b
80000104:	0000006f          	j	80000104 <halt+0x8>

80000108 <_trm_init>:
80000108:	80000537          	lui	a0,0x80000
8000010c:	ff010113          	addi	sp,sp,-16
80000110:	12850513          	addi	a0,a0,296 # 80000128 <_end+0xffff7128>
80000114:	00112623          	sw	ra,12(sp)
80000118:	f11ff0ef          	jal	ra,80000028 <main>
8000011c:	00050513          	mv	a0,a0
80000120:	0000006b          	0x6b
80000124:	0000006f          	j	80000124 <_trm_init+0x1c>
*/