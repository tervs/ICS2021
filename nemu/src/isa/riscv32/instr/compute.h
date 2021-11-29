def_EHelper(lui) {
  //printf("test\n\n\n\n\n\n\n\n");
  rtl_li(s, ddest, id_src1->imm);
}

def_EHelper(auipc) {
  rtl_li(s, ddest, id_src1->imm);
  rtl_addi(s, ddest, ddest, s->pc);
}

def_EHelper(addi) {
  //printf("test\n\n\n\n\n\n\n\n");
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

def_EHelper(slti) {

  //printf("src1 0x%08x       imm 0x%08x\n" ,*(id_src1->preg), id_src2->imm);
 rtl_li(s,ddest,interpret_relop(RELOP_LT, *(id_src1->preg), id_src2->imm));
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
  //printf("s->pc  0x%08x\n",s->pc);
  rtl_addi(s, s0, s0, id_src2->imm);
  //printf("imm  0x%08x\n",id_src2->imm);
  //printf("s0 0x%08x\n",*s0);
  //printf("\n");
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

def_EHelper(blt) {
  rtl_li(s, s0, s->pc);
  rtl_addi(s, s0, s0, id_src2->imm);
  rtl_jrelop(s,RELOP_LT,dsrc1,ddest,*s0);
}

def_EHelper(bltu) {
  rtl_li(s, s0, s->pc);
  rtl_addi(s, s0, s0, id_src2->imm);
  rtl_jrelop(s,RELOP_LTU,dsrc1,ddest,*s0);
}

def_EHelper(bge) {
  rtl_li(s, s0, s->pc);
  rtl_addi(s, s0, s0, id_src2->imm);
  rtl_jrelop(s,RELOP_GE,dsrc1,ddest,*s0);
}

def_EHelper(bgeu) {
  rtl_li(s, s0, s->pc);
  rtl_addi(s, s0, s0, id_src2->imm);
  rtl_jrelop(s,RELOP_GEU,dsrc1,ddest,*s0);
}






def_EHelper(slt) {
 rtl_li(s,ddest,interpret_relop(RELOP_LT, *(id_src1->preg), *(id_src2->preg)));
}

def_EHelper(sltu) {

  //printf("src1 0x%08x       imm 0x%08x\n" ,*(id_src1->preg), id_src2->imm);
 rtl_li(s,ddest,interpret_relop(RELOP_LTU, *(id_src1->preg), *(id_src2->preg)));
}

def_EHelper(xor) {
  rtl_xor(s, ddest, dsrc1, dsrc2);
}

def_EHelper(xori) {
  rtl_xori(s, ddest, dsrc1, (id_src2->imm));
}

def_EHelper(or) {
  rtl_or(s, ddest, dsrc1, dsrc2);
}

def_EHelper(ori) {
  rtl_ori(s, ddest, dsrc1, (id_src2->imm));
}

def_EHelper(sra) {
  rtl_sra(s, ddest, dsrc1, dsrc2);
}

def_EHelper(srai) {

  
  // printf("offset 0x%08x\n",id_src2->imm);
  rtl_srai(s, ddest, dsrc1, (id_src2->imm));
}// no branch .while shamt 5!=0, instruction is invalid

def_EHelper(andi) {
  rtl_andi(s, ddest, dsrc1, (id_src2->imm));
}

def_EHelper(and) {

  //printf("xxx\n");
  rtl_and(s, ddest, dsrc1, dsrc2);
}

def_EHelper(sll) {
  rtl_sll(s, ddest, dsrc1, dsrc2);
}

def_EHelper(slli) {
  rtl_slli(s, ddest, dsrc1, (id_src2->imm));
}

def_EHelper(srl) {
  rtl_srl(s, ddest, dsrc1, dsrc2);
}

def_EHelper(srli) {
  rtl_srli(s, ddest, dsrc1, (id_src2->imm));
}






def_EHelper(mul) {
  rtl_mulu_lo(s, ddest, dsrc1,dsrc2);
}//maybe wrong

def_EHelper(mulh) {
  rtl_muls_hi(s, ddest, dsrc1,dsrc2);
}//maybe wrong

def_EHelper(mulhu) {
  rtl_mulu_hi(s, ddest, dsrc1,dsrc2);
}//maybe wrong


def_EHelper(div) {
  rtl_divs_q(s, ddest, dsrc1,dsrc2);
}//maybe wrong

def_EHelper(rem) {
  //printf("test\n");
  rtl_divs_r(s, ddest, dsrc1,dsrc2);
}//maybe wrong

def_EHelper(remu) {
  //printf("test\n");
  rtl_divu_r(s, ddest, dsrc1,dsrc2);
}//maybe wrong

def_EHelper(divu) {
  rtl_divu_q(s, ddest, dsrc1,dsrc2);
}//maybe wrong



//uint32_t csr[4096];

def_EHelper(csrrwi) {
  //printf("test\n\n\n\n\n\n\n\n");
  //rtl_li(s, ddest, csr[id_src2->imm]);
  //rtl_li(s, &csr[id_src2->imm], *(id_src1->preg));
  //printf("%d\n" ,(csr[id_src2->imm]));
}

def_EHelper(csrrs) {
  printf("test\n\n\n\n\n\n\n\n");
  //rtl_li(s, ddest, csr[id_src2->imm]);
  //rtl_or(s, &csr[id_src2->imm], dsrc1, &csr[id_src2->imm]);
  //printf("test\n\n\n\n\n\n\n\n");
  //rtl_li(s, ddest, csr[id_src2->imm]);
  //rtl_li(s, &csr[id_src2->imm], *(id_src1->preg));
  //printf("%d\n" ,(csr[id_src2->imm]));
}

def_EHelper(csrrw) {
  //printf("test\n\n\n\n\n\n\n\n");
  rtlreg_t *temp=NULL;
  switch(id_src2->imm){
  case 833: temp=mepc;break;
  case 768: temp=mstatus;break;
  case 834: temp=mcause;break;
  case 773: temp=mtvec;break;
  }
  rtl_li(s, ddest, *temp);
  //rtl_or(s, &csr[id_src2->imm], dsrc1, &csr[id_src2->imm]);
  //printf("test\n\n\n\n\n\n\n\n");
  //rtl_li(s, ddest, csr[id_src2->imm]);
  rtl_li(s, temp, *(id_src1->preg));
  //printf("%d\n" ,(csr[id_src2->imm]));
}

def_EHelper(ecall) {
  printf("test\n\n\n\n\n\n\n\n");

  //rtl_li(s, ddest, csr[id_src2->imm]);
  //rtl_or(s, &csr[id_src2->imm], dsrc1, &csr[id_src2->imm]);
  //printf("test\n\n\n\n\n\n\n\n");
  //rtl_li(s, ddest, csr[id_src2->imm]);
  //rtl_li(s, &csr[id_src2->imm], *(id_src1->preg));
  //printf("%d\n" ,(csr[id_src2->imm]));
}