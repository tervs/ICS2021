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
  rtl_sub(s, ddest, dsrc1, dsrc2);
}

def_EHelper(sltiu) {

  //printf("src1 0x%08x       imm 0x%08x\n" ,*(id_src1->preg), id_src2->imm);
 rtl_li(s,ddest,interpret_relop(RELOP_LTU, *(id_src1->preg), id_src2->imm));
}

def_EHelper(jal) {
  
  rtl_li(s, ddest, s->pc);
  rtl_addi(s, ddest, ddest, id_src1->imm);
  rtl_jr(s,ddest);
  rtl_li(s, ddest, s->snpc);
}

def_EHelper(jalr) {
  //printf("origin is 0x%08x\n",id_src2->imm);
  //printf("shift is 0x%08x\n",((id_src2->imm)<<20)>>20);

  rtl_li(s, ddest, s->pc+4);
  rtl_addi(s,dsrc1,dsrc1, ((id_src2->imm)<<20)>>20);


  rtl_li(s, dsrc1, (*dsrc1>>1)<<1);
  rtl_jr(s,dsrc1);
}

def_EHelper(beq) {
  rtl_li(s, s0, s->pc);
  rtl_addi(s, s0, s0, id_src2->imm);
  rtl_jrelop(s,RELOP_EQ,dsrc1,ddest,*s0);
}

def_EHelper(bne) {
  rtl_li(s, s0, s->pc);
  rtl_addi(s, s0, s0, id_src2->imm);
  rtl_jrelop(s,RELOP_NE,dsrc1,ddest,*s0);

  /*
  printf("rs1  0x%08x \n",*dsrc1);
  printf("rs2  0x%08x \n",*ddest);
  printf("offset 0x%08x\n",(id_src2->imm<<20)>>20);
  printf("s0 0x%08x\n",*s0);
  */
}
