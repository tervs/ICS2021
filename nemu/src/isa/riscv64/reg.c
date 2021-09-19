#include <isa.h>
#include "local-include/reg.h"

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
rtlreg_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
  uint16_t ax, cx, dx, bx, sp, bp, si, di;
  uint8_t al, cl, dl, bl, ah, ch, dh, bh;
  eax = cpu.eax;
  ecx = cpu.ecx;
  edx = cpu.edx;
  ebx = cpu.ebx;
  esp = cpu.esp;
  ebp = cpu.ebp;
  esi = cpu.esi;
  edi = cpu.edi;
  //打印8个寄存器
  printf("EAX: %#010x, ECX: %#010x, EDX: %#010x, EBX: %#010x, \nESP: %#010x, EBP: %#010x, ESI: %#010x, EDI: %#010x\n", eax, ecx, edx, ebx, esp, ebp, esi, edi);
 
  ax = reg_w(R_AX);
  cx = reg_w(R_CX);
  dx = reg_w(R_DX);
  bx = reg_w(R_BX);
  sp = reg_w(R_SP);
  bp = reg_w(R_BP);
  si = reg_w(R_SI);
  di = reg_w(R_DI);
  //打印8个寄存器
  printf("AX: %#010x, CX: %#010x, DX: %#010x, BX: %#010x, \nSP: %#010x, BP: %#010x, SI: %#010x, DI: %#010x\n", ax, cx, dx, bx, sp, bp, si, di);
 
  al = reg_b(R_AL);
  cl = reg_b(R_CL);
  dl = reg_b(R_DL);
  bl = reg_b(R_BL);
  ah = reg_b(R_AH);
  ch = reg_b(R_CH);
  dh = reg_b(R_DH);
  bh = reg_b(R_BH);
  //打印8个寄存器
  printf("AL: %#010x, CL: %#010x, DL: %#010x, BL: %#010x, \nAH: %#010x, CH: %#010x, DH: %#010x, BH: %#010x\n", al, cl, dl, bl, ah, ch, dh, bh);



}

word_t isa_reg_str2val(const char *s, bool *success) {
  return 0;
}
