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

def_EHelper(add) {

  //printf("xxx\n");
  rtl_add(s, ddest, dsrc1, dsrc2);
}


def_EHelper(sub) {

  //printf("xxx\n");
  rtl_sub(s, ddest, dsrc1, dsrc2);
}

def_EHelper(sltiu) {

  rtl_li(s,ddest,!interpret_relop(RELOP_LTU, id_src1->imm, id_src2->imm));

   //rtl_jrelop(s, ddest, dsrc1, (id_src2->imm));
}


def_EHelper(jal) {
  
  rtl_li(s, ddest, s->pc);
  rtl_addi(s, ddest, ddest, id_src1->imm);
  rtl_jr(s,ddest);
  rtl_li(s, ddest, s->snpc);
}

def_EHelper(jalr) {
  rtl_li(s, ddest, s->pc+4);
  rtl_addi(s,dsrc1,dsrc1, ((id_src2->imm)<<20)>>20);
  rtl_li(s, dsrc1, (*dsrc1>>1)<<1);
  rtl_jr(s,dsrc1);
}
