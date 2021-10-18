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
f(or)
//f(sll)
//f(mv) 
//f(slti) f(sltiu) f(xori)\f(ori) f(andi) 

def_all_EXEC_ID();

/*

Disassembly of section .text:

80000000 <_start>:
80000000:	00000413          	li	s0,0
80000004:	00009117          	auipc	sp,0x9
80000008:	ffc10113          	addi	sp,sp,-4 # 80009000 <_end>
8000000c:	114000ef          	jal	ra,80000120 <_trm_init>

80000010 <check>:
80000010:	00050463          	beqz	a0,80000018 <check+0x8>
80000014:	00008067          	ret
80000018:	ff010113          	addi	sp,sp,-16
8000001c:	00100513          	li	a0,1
80000020:	00112623          	sw	ra,12(sp)
80000024:	0f0000ef          	jal	ra,80000114 <halt>

80000028 <main>:
80000028:	fd010113          	addi	sp,sp,-48
8000002c:	03212023          	sw	s2,32(sp)
80000030:	01312e23          	sw	s3,28(sp)
80000034:	01412c23          	sw	s4,24(sp)
80000038:	800009b7          	lui	s3,0x80000
8000003c:	80000a37          	lui	s4,0x80000
80000040:	80000937          	lui	s2,0x80000
80000044:	01512a23          	sw	s5,20(sp)
80000048:	01612823          	sw	s6,16(sp)
8000004c:	01712623          	sw	s7,12(sp)
80000050:	02112623          	sw	ra,44(sp)
80000054:	34898b93          	addi	s7,s3,840 # 80000348 <_end+0xffff7348>
80000058:	02812423          	sw	s0,40(sp)
8000005c:	02912223          	sw	s1,36(sp)
80000060:	01812423          	sw	s8,8(sp)
80000064:	01912223          	sw	s9,4(sp)
80000068:	148a0a13          	addi	s4,s4,328 # 80000148 <_end+0xffff7148>
8000006c:	34898993          	addi	s3,s3,840
80000070:	00000a93          	li	s5,0
80000074:	38890913          	addi	s2,s2,904 # 80000388 <_end+0xffff7388>
80000078:	04000b13          	li	s6,64
8000007c:	0009ac83          	lw	s9,0(s3)
80000080:	0049a483          	lw	s1,4(s3)
80000084:	000a0c13          	mv	s8,s4
80000088:	000b8413          	mv	s0,s7
8000008c:	00042783          	lw	a5,0(s0)
80000090:	00442603          	lw	a2,4(s0)
80000094:	004c2703          	lw	a4,4(s8)
80000098:	00fc87b3          	add	a5,s9,a5
8000009c:	000c2503          	lw	a0,0(s8)
800000a0:	0197b6b3          	sltu	a3,a5,s9
800000a4:	00c48633          	add	a2,s1,a2
800000a8:	00c686b3          	add	a3,a3,a2
800000ac:	00f54533          	xor	a0,a0,a5
800000b0:	00d747b3          	xor	a5,a4,a3
800000b4:	00f56533          	or	a0,a0,a5
800000b8:	00153513          	seqz	a0,a0
800000bc:	00840413          	addi	s0,s0,8
800000c0:	f51ff0ef          	jal	ra,80000010 <check>
800000c4:	008c0c13          	addi	s8,s8,8
800000c8:	fc8912e3          	bne	s2,s0,8000008c <main+0x64>
800000cc:	008a8a93          	addi	s5,s5,8
800000d0:	00898993          	addi	s3,s3,8
800000d4:	040a0a13          	addi	s4,s4,64
800000d8:	fb6a92e3          	bne	s5,s6,8000007c <main+0x54>
800000dc:	02c12083          	lw	ra,44(sp)
800000e0:	02812403          	lw	s0,40(sp)
800000e4:	02412483          	lw	s1,36(sp)
800000e8:	02012903          	lw	s2,32(sp)
800000ec:	01c12983          	lw	s3,28(sp)
800000f0:	01812a03          	lw	s4,24(sp)
800000f4:	01412a83          	lw	s5,20(sp)
800000f8:	01012b03          	lw	s6,16(sp)
800000fc:	00c12b83          	lw	s7,12(sp)
80000100:	00812c03          	lw	s8,8(sp)
80000104:	00412c83          	lw	s9,4(sp)
80000108:	00000513          	li	a0,0
8000010c:	03010113          	addi	sp,sp,48
80000110:	00008067          	ret

80000114 <halt>:
80000114:	00050513          	mv	a0,a0
80000118:	0000006b          	0x6b
8000011c:	0000006f          	j	8000011c <halt+0x8>

80000120 <_trm_init>:
80000120:	80000537          	lui	a0,0x80000
80000124:	ff010113          	addi	sp,sp,-16
80000128:	14050513          	addi	a0,a0,320 # 80000140 <_end+0xffff7140>
8000012c:	00112623          	sw	ra,12(sp)
80000130:	ef9ff0ef          	jal	ra,80000028 <main>
80000134:	00050513          	mv	a0,a0
80000138:	0000006b          	0x6b
8000013c:	0000006f          	j	8000013c <_trm_init+0x1c>

*/