#include <isa.h>
#include "local-include/reg.h"

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {

bool *success;
success=0;

printf("%s  %d   | ","$0",isa_reg_str2val("$0", success));
printf("%s  %d   | ","ra",isa_reg_str2val("ra", success));
printf("%s  %d   | ","sp",isa_reg_str2val("sp", success));
printf("%s  %d   | ","gp",isa_reg_str2val("gp", success));
printf("%s  %d   | ","tp",isa_reg_str2val("tp", success));
printf("%s  %d   | ","t0",isa_reg_str2val("t0", success));
printf("%s  %d   | ","t1",isa_reg_str2val("t1", success));
printf("%s  %d \n","t2",isa_reg_str2val("t2", success));
printf("\n");
printf("%s  %d | ","$0",isa_reg_str2val("$0", success));
printf("%s  %d | ","ra",isa_reg_str2val("ra", success));
printf("%s  %d | ","sp",isa_reg_str2val("sp", success));
printf("%s  %d | ","gp",isa_reg_str2val("gp", success));
printf("%s  %d | ","tp",isa_reg_str2val("tp", success));
printf("%s  %d | ","t0",isa_reg_str2val("t0", success));
printf("%s  %d | ","t1",isa_reg_str2val("t1", success));
printf("%s  %d \n","t2",isa_reg_str2val("t2", success));


}


word_t isa_reg_str2val(const char *s, bool *success) {
  return 0;
}
