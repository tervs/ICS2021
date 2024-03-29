#include "../local-include/reg.h"
#include <cpu/ifetch.h>
#include <isa-all-instr.h>

int32_t sign_extend(int32_t value, uint32_t bits,uint32_t sign)
{
    assert(bits > 0 && bits < 32);
    uint32_t mask = ((~0U) >> (bits - 1)) << (bits - 1);
    if (sign != 0)
        value |= mask;
    else
        value &= ~mask;
    return value;
}







def_all_THelper();

static uint32_t get_instr(Decode *s) {
  return s->isa.instr.val;
}

// decode operand helper
#define def_DopHelper(name) \
  void concat(decode_op_, name) (Decode *s, Operand *op, word_t val, bool flag)

static def_DopHelper(i) {
  op->imm = val;
}

static def_DopHelper(r) {
  bool is_write = flag;
  static word_t zero_null = 0;
  op->preg = (is_write && val == 0) ? &zero_null : &gpr(val);
}

static def_DHelper(I) {
  decode_op_r(s, id_src1, s->isa.instr.i.rs1, false);
  decode_op_i(s, id_src2, s->isa.instr.i.simm11_0, false);
  decode_op_r(s, id_dest, s->isa.instr.i.rd, true);
}

static def_DHelper(U) {
  decode_op_i(s, id_src1, s->isa.instr.u.imm31_12<<12, true);
  
  decode_op_r(s, id_dest, s->isa.instr.u.rd, true);
}

static def_DHelper(S) {
  decode_op_r(s, id_src1, s->isa.instr.s.rs1, false);
  sword_t simm = (s->isa.instr.s.simm11_5 << 5) | s->isa.instr.s.imm4_0;
  decode_op_i(s, id_src2, simm, false);
  decode_op_r(s, id_dest, s->isa.instr.s.rs2, false);
}

static def_DHelper(J) {
  sword_t offset=(s->isa.instr.j.imm20<<20)|(s->isa.instr.j.imm19_12<<12)|(s->isa.instr.j.imm11<<11)|(s->isa.instr.j.imm10_1<<1);
  offset=(offset<<11)>>11;
  //printf("0x%08x\n\n\n\n\n",offset);
  decode_op_i(s, id_src1, offset, false);
  decode_op_r(s, id_dest, s->isa.instr.j.rd, true);
}

static def_DHelper(R) {
  decode_op_r(s, id_src1, s->isa.instr.r.rs1, false);
  decode_op_r(s, id_src2, s->isa.instr.r.rs2, false);
  decode_op_r(s, id_dest, s->isa.instr.r.rd, true);
}

static def_DHelper(B) {
  decode_op_r(s, id_src1, s->isa.instr.s.rs1, false);
  sword_t offset = (s->isa.instr.b.imm12 << 12) | (s->isa.instr.b.imm11 << 11) |(s->isa.instr.b.imm10_5 << 5) |(s->isa.instr.b.imm4_1 << 1) ;

  offset=sign_extend(offset,13,s->isa.instr.b.imm12);
 // printf("offset is 0x%08x\n",offset);
  decode_op_i(s, id_src2, offset, false);
  decode_op_r(s, id_dest, s->isa.instr.s.rs2, false);
}



def_THelper(load) {
  def_INSTR_TAB("??????? ????? ????? 010 ????? ????? ??", lw);
  def_INSTR_TAB("??????? ????? ????? 100 ????? ????? ??", lbu);
  def_INSTR_TAB("??????? ????? ????? 001 ????? ????? ??", lh);
  def_INSTR_TAB("??????? ????? ????? 101 ????? ????? ??", lhu);
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", lb);
  return EXEC_ID_inv;
}

def_THelper(store) {
  def_INSTR_TAB("??????? ????? ????? 010 ????? ????? ??", sw);
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", sb);
  def_INSTR_TAB("??????? ????? ????? 001 ????? ????? ??", sh);
  
  return EXEC_ID_inv;
}

def_THelper(imm) {
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", addi);
  def_INSTR_TAB("??????? ????? ????? 010 ????? ????? ??", slti);
  def_INSTR_TAB("??????? ????? ????? 011 ????? ????? ??", sltiu);
  def_INSTR_TAB("??????? ????? ????? 100 ????? ????? ??", xori);
  def_INSTR_TAB("??????? ????? ????? 110 ????? ????? ??", ori);
  def_INSTR_TAB("??????? ????? ????? 111 ????? ????? ??", andi);
  def_INSTR_TAB("??????? ????? ????? 001 ????? ????? ??", slli);
  def_INSTR_TAB("0000000 ????? ????? 101 ????? ????? ??", srli);
  def_INSTR_TAB("0100000 ????? ????? 101 ????? ????? ??", srai);
   
  return EXEC_ID_inv;
}

def_THelper(reg) {
  
  def_INSTR_TAB("0000000 ????? ????? 000 ????? ????? ??", add);
  def_INSTR_TAB("0100000 ????? ????? 000 ????? ????? ??", sub);
  def_INSTR_TAB("0000000 ????? ????? 001 ????? ????? ??", sll);
  def_INSTR_TAB("0000000 ????? ????? 010 ????? ????? ??", slt);
  def_INSTR_TAB("0000000 ????? ????? 011 ????? ????? ??", sltu);
  def_INSTR_TAB("0000000 ????? ????? 100 ????? ????? ??", xor);
  def_INSTR_TAB("0000000 ????? ????? 101 ????? ????? ??", srl);
  def_INSTR_TAB("0100000 ????? ????? 101 ????? ????? ??", sra);
  def_INSTR_TAB("0000000 ????? ????? 110 ????? ????? ??", or);
  def_INSTR_TAB("0000000 ????? ????? 111 ????? ????? ??", and);
  def_INSTR_TAB("0000001 ????? ????? 000 ????? ????? ??", mul);
  def_INSTR_TAB("0000001 ????? ????? 001 ????? ????? ??", mulh);
  def_INSTR_TAB("0000001 ????? ????? 011 ????? ????? ??", mulhu);
  def_INSTR_TAB("0000001 ????? ????? 100 ????? ????? ??", div);
  def_INSTR_TAB("0000001 ????? ????? 110 ????? ????? ??", rem);
  def_INSTR_TAB("0000001 ????? ????? 101 ????? ????? ??", divu);
  def_INSTR_TAB("0000001 ????? ????? 111 ????? ????? ??", remu);
 // printf("%d\n",EXEC_ID_inv); 
  return EXEC_ID_inv;
}

def_THelper(branch) {
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", beq);
  def_INSTR_TAB("??????? ????? ????? 001 ????? ????? ??", bne);
  def_INSTR_TAB("??????? ????? ????? 100 ????? ????? ??", blt);
  def_INSTR_TAB("??????? ????? ????? 101 ????? ????? ??", bge);
  def_INSTR_TAB("??????? ????? ????? 111 ????? ????? ??", bgeu);
  def_INSTR_TAB("??????? ????? ????? 110 ????? ????? ??", bltu);
  //printf("%d\n",EXEC_ID_inv); 

  //def_INSTR_TAB("??????? ????? ????? 111 ????? ????? ??", bgeu);
  
  return EXEC_ID_inv;
}

def_THelper(csr) {
  def_INSTR_TAB("??????? ????? ????? 101 ????? ????? ??", csrrwi);
  def_INSTR_TAB("??????? ????? ????? 010 ????? ????? ??", csrrs);
  def_INSTR_TAB("??????? ????? ????? 001 ????? ????? ??", csrrw);
  def_INSTR_TAB("??????? 00000 ????? 000 ????? ????? ??", ecall);
  //printf("test\n\n\n\n\n\n\n\n");
  def_INSTR_TAB("0011000 00010 00000 000 00000 ????? ??", mret);
  
  //printf("test\n\n\n\n\n\n\n\n");
  //printf("%d\n\n\n\n\n\n\n",EXEC_ID_inv); 
  return EXEC_ID_inv;
}




def_THelper(main) {
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 00000 11", I     , load);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 01000 11", S     , store);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 01101 11", U     , lui);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 00101 11", U     , auipc);
  def_INSTR_TAB  ("??????? ????? ????? ??? ????? 11010 11",         nemu_trap);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 00100 11", I     , imm);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 11011 11", J     , jal);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 11001 11", I     , jalr);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 01100 11", R     , reg);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 11000 11", B     , branch);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 11100 11", I     , csr);
  
  return table_inv(s);
};

int isa_fetch_decode(Decode *s) {
  s->isa.instr.val = instr_fetch(&s->snpc, 4);
  int idx = table_main(s);
  //printf("%d\n",idx);
  return idx;
}