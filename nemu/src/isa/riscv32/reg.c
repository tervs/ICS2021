#include <isa.h>
#include "local-include/reg.h"

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {

//printf("0x%08x",gpr(0));

bool *success;

success=0;

for(int i=0;i<32;i++)
{
  printf("%s  0x%08x\n    ",regs[i],gpr(i));
}
printf("%s  0x%08x    ","$0",isa_reg_str2val("$0", success));
/*printf("%s  %d    ","ra",isa_reg_str2val("ra", success));
printf("%s  %d    ","sp",isa_reg_str2val("sp", success));
printf("%s  %d    ","gp",isa_reg_str2val("gp", success));
printf("%s  %d    ","tp",isa_reg_str2val("tp", success));
printf("%s  %d    ","t0",isa_reg_str2val("t0", success));
printf("%s  %d    ","t1",isa_reg_str2val("t1", success));
printf("%s  %d \n","t2",isa_reg_str2val("t2", success));
printf("\n");
printf("%s  %d    ","s0",isa_reg_str2val("s0", success));
printf("%s  %d    ","s1",isa_reg_str2val("s1", success));
printf("%s  %d    ","a0",isa_reg_str2val("a0", success));
printf("%s  %d    ","a1",isa_reg_str2val("a1", success));
printf("%s  %d    ","a2",isa_reg_str2val("a2", success));
printf("%s  %d    ","a3",isa_reg_str2val("a3", success));
printf("%s  %d    ","a4",isa_reg_str2val("a4", success));
printf("%s  %d \n","a5",isa_reg_str2val("a5", success));
printf("\n");
printf("%s  %d    ","a6",isa_reg_str2val("a6", success));
printf("%s  %d    ","a7",isa_reg_str2val("a7", success));
printf("%s  %d    ","s2",isa_reg_str2val("s2", success));
printf("%s  %d    ","s3",isa_reg_str2val("s3", success));
printf("%s  %d    ","s4",isa_reg_str2val("s4", success));
printf("%s  %d    ","s5",isa_reg_str2val("s5", success));
printf("%s  %d    ","s6",isa_reg_str2val("s6", success));
printf("%s  %d \n","s7",isa_reg_str2val("s7", success));
printf("\n");
printf("%s  %d    ","s8",isa_reg_str2val("s8", success));
printf("%s  %d    ","s9",isa_reg_str2val("s9", success));
printf("%s  %d    ","s10",isa_reg_str2val("s10", success));
printf("%s  %d    ","s11",isa_reg_str2val("s11", success));
printf("%s  %d    ","t3",isa_reg_str2val("t3", success));
printf("%s  %d    ","t4",isa_reg_str2val("t4", success));
printf("%s  %d    ","t5",isa_reg_str2val("t5", success));
printf("%s  %d \n","t6",isa_reg_str2val("t6", success));
printf("\n");
*/
}


word_t isa_reg_str2val(const char *s, bool *success) 
{
  return gpr(0);
}
