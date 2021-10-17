def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
}

def_EHelper(auipc) {
  rtl_li(s, ddest, id_src1->imm);
  rtl_addi(s, ddest, ddest, s->pc);
}


def_EHelper(addi) {
  rtl_addi(s, ddest, dsrc1, (id_src2->imm));
}


def_EHelper(jal) {
  
  rtl_li(s, ddest, s->pc);
  rtl_addi(s, ddest, ddest, id_src1->imm);
  rtl_jr(s,ddest);
  rtl_li(s, ddest, s->snpc);
}//maybe wrong

def_EHelper(jalr) {
  rtl_li(s, ddest, s->pc+4);
  rtl_li(s, s0, s->pc);
  rtl_addi(s, s0, s0, ((id_src2->imm)<<20)>>20);
  printf(" ((id_src2->imm)<<20)>>20  0x%08x\n",*s0);
  rtl_li(s, s0, (*s0>>1)<<1);
  rtl_jr(s,s0);
  //s->dnpc=(*s0>>1)<<1;
  //rtl_jr(s, ddest, id_src1->imm);
}
