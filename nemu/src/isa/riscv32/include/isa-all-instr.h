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
f(ori)


def_all_EXEC_ID();

/*


Disassembly of section .text:

80000000 <_start>:
80000000:	00000413          	li	s0,0
80000004:	00009117          	auipc	sp,0x9
80000008:	ffc10113          	addi	sp,sp,-4 # 80009000 <_end>
8000000c:	1fc000ef          	jal	ra,80000208 <_trm_init>

80000010 <check>:
80000010:	00050463          	beqz	a0,80000018 <check+0x8>
80000014:	00008067          	ret
80000018:	ff010113          	addi	sp,sp,-16
8000001c:	00100513          	li	a0,1
80000020:	00112623          	sw	ra,12(sp)
80000024:	1d8000ef          	jal	ra,800001fc <halt>

80000028 <getbit>:
80000028:	4035d793          	srai	a5,a1,0x3
8000002c:	00f50533          	add	a0,a0,a5
80000030:	00054783          	lbu	a5,0(a0)
80000034:	0075f593          	andi	a1,a1,7
80000038:	00100513          	li	a0,1
8000003c:	00b515b3          	sll	a1,a0,a1
80000040:	00f5f533          	and	a0,a1,a5
80000044:	00a03533          	snez	a0,a0
80000048:	00008067          	ret

8000004c <setbit>:
8000004c:	4035d793          	srai	a5,a1,0x3
80000050:	ff010113          	addi	sp,sp,-16
80000054:	00f50533          	add	a0,a0,a5
80000058:	00a12623          	sw	a0,12(sp)
8000005c:	0075f793          	andi	a5,a1,7
80000060:	00100593          	li	a1,1
80000064:	00f595b3          	sll	a1,a1,a5
80000068:	00c12783          	lw	a5,12(sp)
8000006c:	02061063          	bnez	a2,8000008c <setbit+0x40>
80000070:	0007c783          	lbu	a5,0(a5)
80000074:	fff5c593          	not	a1,a1
80000078:	00f5f5b3          	and	a1,a1,a5
8000007c:	00c12783          	lw	a5,12(sp)
80000080:	00b78023          	sb	a1,0(a5)
80000084:	01010113          	addi	sp,sp,16
80000088:	00008067          	ret
8000008c:	0007c783          	lbu	a5,0(a5)
80000090:	00f5e5b3          	or	a1,a1,a5
80000094:	00c12783          	lw	a5,12(sp)
80000098:	0ff5f593          	zext.b	a1,a1
8000009c:	00b78023          	sb	a1,0(a5)
800000a0:	01010113          	addi	sp,sp,16
800000a4:	00008067          	ret

800000a8 <main>:
800000a8:	fe010113          	addi	sp,sp,-32
800000ac:	faa00793          	li	a5,-86
800000b0:	00000593          	li	a1,0
800000b4:	00c10513          	addi	a0,sp,12
800000b8:	00112e23          	sw	ra,28(sp)
800000bc:	00f10623          	sb	a5,12(sp)
800000c0:	000106a3          	sb	zero,13(sp)
800000c4:	f65ff0ef          	jal	ra,80000028 <getbit>
800000c8:	00154513          	xori	a0,a0,1
800000cc:	0ff57513          	zext.b	a0,a0
800000d0:	f41ff0ef          	jal	ra,80000010 <check>
800000d4:	00100593          	li	a1,1
800000d8:	00c10513          	addi	a0,sp,12
800000dc:	f4dff0ef          	jal	ra,80000028 <getbit>
800000e0:	f31ff0ef          	jal	ra,80000010 <check>
800000e4:	00200593          	li	a1,2
800000e8:	00c10513          	addi	a0,sp,12
800000ec:	f3dff0ef          	jal	ra,80000028 <getbit>
800000f0:	00154513          	xori	a0,a0,1
800000f4:	0ff57513          	zext.b	a0,a0
800000f8:	f19ff0ef          	jal	ra,80000010 <check>
800000fc:	00300593          	li	a1,3
80000100:	00c10513          	addi	a0,sp,12
80000104:	f25ff0ef          	jal	ra,80000028 <getbit>
80000108:	f09ff0ef          	jal	ra,80000010 <check>
8000010c:	00400593          	li	a1,4
80000110:	00c10513          	addi	a0,sp,12
80000114:	f15ff0ef          	jal	ra,80000028 <getbit>
80000118:	00154513          	xori	a0,a0,1
8000011c:	0ff57513          	zext.b	a0,a0
80000120:	ef1ff0ef          	jal	ra,80000010 <check>
80000124:	00500593          	li	a1,5
80000128:	00c10513          	addi	a0,sp,12
8000012c:	efdff0ef          	jal	ra,80000028 <getbit>
80000130:	ee1ff0ef          	jal	ra,80000010 <check>
80000134:	00600593          	li	a1,6
80000138:	00c10513          	addi	a0,sp,12
8000013c:	eedff0ef          	jal	ra,80000028 <getbit>
80000140:	00154513          	xori	a0,a0,1
80000144:	0ff57513          	zext.b	a0,a0
80000148:	ec9ff0ef          	jal	ra,80000010 <check>
8000014c:	00700593          	li	a1,7
80000150:	00c10513          	addi	a0,sp,12
80000154:	ed5ff0ef          	jal	ra,80000028 <getbit>
80000158:	eb9ff0ef          	jal	ra,80000010 <check>
8000015c:	00c10513          	addi	a0,sp,12
80000160:	00100613          	li	a2,1
80000164:	00800593          	li	a1,8
80000168:	ee5ff0ef          	jal	ra,8000004c <setbit>
8000016c:	00c10513          	addi	a0,sp,12
80000170:	00000613          	li	a2,0
80000174:	00900593          	li	a1,9
80000178:	ed5ff0ef          	jal	ra,8000004c <setbit>
8000017c:	00c10513          	addi	a0,sp,12
80000180:	00100613          	li	a2,1
80000184:	00a00593          	li	a1,10
80000188:	ec5ff0ef          	jal	ra,8000004c <setbit>
8000018c:	00c10513          	addi	a0,sp,12
80000190:	00000613          	li	a2,0
80000194:	00b00593          	li	a1,11
80000198:	eb5ff0ef          	jal	ra,8000004c <setbit>
8000019c:	00c10513          	addi	a0,sp,12
800001a0:	00100613          	li	a2,1
800001a4:	00c00593          	li	a1,12
800001a8:	ea5ff0ef          	jal	ra,8000004c <setbit>
800001ac:	00c10513          	addi	a0,sp,12
800001b0:	00000613          	li	a2,0
800001b4:	00d00593          	li	a1,13
800001b8:	e95ff0ef          	jal	ra,8000004c <setbit>
800001bc:	00c10513          	addi	a0,sp,12
800001c0:	00100613          	li	a2,1
800001c4:	00e00593          	li	a1,14
800001c8:	e85ff0ef          	jal	ra,8000004c <setbit>
800001cc:	00c10513          	addi	a0,sp,12
800001d0:	00000613          	li	a2,0
800001d4:	00f00593          	li	a1,15
800001d8:	e75ff0ef          	jal	ra,8000004c <setbit>
800001dc:	00d14503          	lbu	a0,13(sp)
800001e0:	fab50513          	addi	a0,a0,-85
800001e4:	00153513          	seqz	a0,a0
800001e8:	e29ff0ef          	jal	ra,80000010 <check>
800001ec:	01c12083          	lw	ra,28(sp)
800001f0:	00000513          	li	a0,0
800001f4:	02010113          	addi	sp,sp,32
800001f8:	00008067          	ret

800001fc <halt>:
800001fc:	00050513          	mv	a0,a0
80000200:	0000006b          	0x6b
80000204:	0000006f          	j	80000204 <halt+0x8>

80000208 <_trm_init>:
80000208:	80000537          	lui	a0,0x80000
8000020c:	ff010113          	addi	sp,sp,-16
80000210:	22850513          	addi	a0,a0,552 # 80000228 <_end+0xffff7228>
80000214:	00112623          	sw	ra,12(sp)
80000218:	e91ff0ef          	jal	ra,800000a8 <main>
8000021c:	00050513          	mv	a0,a0
80000220:	0000006b          	0x6b
80000224:	0000006f          	j	80000224 <_trm_init+0x1c>

*/