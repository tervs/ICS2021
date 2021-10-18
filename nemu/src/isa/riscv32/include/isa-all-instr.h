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
f(bltu)


def_all_EXEC_ID();
/*

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

80000028 <main>:
80000028:	fe010113          	addi	sp,sp,-32
8000002c:	00812c23          	sw	s0,24(sp)
80000030:	80000437          	lui	s0,0x80000
80000034:	00912a23          	sw	s1,20(sp)
80000038:	01212823          	sw	s2,16(sp)
8000003c:	1a840493          	addi	s1,s0,424 # 800001a8 <_end+0xffff71a8>
80000040:	80000937          	lui	s2,0x80000
80000044:	01312623          	sw	s3,12(sp)
80000048:	00112e23          	sw	ra,28(sp)
8000004c:	01412423          	sw	s4,8(sp)
80000050:	16890913          	addi	s2,s2,360 # 80000168 <_end+0xffff7168>
80000054:	02048993          	addi	s3,s1,32
80000058:	1a840413          	addi	s0,s0,424
8000005c:	00042503          	lw	a0,0(s0)
80000060:	00092783          	lw	a5,0(s2)
80000064:	00440413          	addi	s0,s0,4
80000068:	00755513          	srli	a0,a0,0x7
8000006c:	40f50533          	sub	a0,a0,a5
80000070:	00153513          	seqz	a0,a0
80000074:	f9dff0ef          	jal	ra,80000010 <check>
80000078:	00490913          	addi	s2,s2,4
8000007c:	ff3410e3          	bne	s0,s3,8000005c <main+0x34>
80000080:	80000937          	lui	s2,0x80000
80000084:	14890913          	addi	s2,s2,328 # 80000148 <_end+0xffff7148>
80000088:	00048993          	mv	s3,s1
8000008c:	00400413          	li	s0,4
80000090:	00c00a13          	li	s4,12
80000094:	0009a503          	lw	a0,0(s3)
80000098:	00092783          	lw	a5,0(s2)
8000009c:	00498993          	addi	s3,s3,4
800000a0:	40855533          	sra	a0,a0,s0
800000a4:	40f50533          	sub	a0,a0,a5
800000a8:	00153513          	seqz	a0,a0
800000ac:	00140413          	addi	s0,s0,1
800000b0:	f61ff0ef          	jal	ra,80000010 <check>
800000b4:	00490913          	addi	s2,s2,4
800000b8:	fd441ee3          	bne	s0,s4,80000094 <main+0x6c>
800000bc:	80000937          	lui	s2,0x80000
800000c0:	18890913          	addi	s2,s2,392 # 80000188 <_end+0xffff7188>
800000c4:	00400413          	li	s0,4
800000c8:	00c00993          	li	s3,12
800000cc:	0004a503          	lw	a0,0(s1)
800000d0:	00092783          	lw	a5,0(s2)
800000d4:	00448493          	addi	s1,s1,4
800000d8:	00855533          	srl	a0,a0,s0
800000dc:	40f50533          	sub	a0,a0,a5
800000e0:	00153513          	seqz	a0,a0
800000e4:	00140413          	addi	s0,s0,1
800000e8:	f29ff0ef          	jal	ra,80000010 <check>
800000ec:	00490913          	addi	s2,s2,4
800000f0:	fd341ee3          	bne	s0,s3,800000cc <main+0xa4>
800000f4:	01c12083          	lw	ra,28(sp)
800000f8:	01812403          	lw	s0,24(sp)
800000fc:	01412483          	lw	s1,20(sp)
80000100:	01012903          	lw	s2,16(sp)
80000104:	00c12983          	lw	s3,12(sp)
80000108:	00812a03          	lw	s4,8(sp)
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
80000134:	ef5ff0ef          	jal	ra,80000028 <main>
80000138:	00050513          	mv	a0,a0
8000013c:	0000006b          	0x6b
80000140:	0000006f          	j	80000140 <_trm_init+0x1c>
*/