def_EHelper(lw) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 4);
}

def_EHelper(lb) {
  rtl_lms(s, ddest, dsrc1, id_src2->imm, 1);
}

def_EHelper(lbu) {
 // printf("0x%08x\n",*dsrc1);
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 1);
}//zero extend

def_EHelper(lh) {
  rtl_lms(s, ddest, dsrc1, id_src2->imm, 2);
}

def_EHelper(lhu) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 2);
}

def_EHelper(sw) {
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 4);
}

def_EHelper(sb) {
  //printf("0x%08x\n",id_src2->imm);
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 1);
}

def_EHelper(sh) {
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 2);
}