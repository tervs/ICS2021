#include <common.h>

extern uint64_t g_nr_guest_instr;
extern uint64_t addr;
FILE *mtrace_log_fp = NULL;

void init_mtrace(const char *log_file) {
  mtrace_log_fp = stdout;
  if (log_file != NULL) {
    FILE *fp = fopen(log_file, "w");
    Assert(fp, "Can not open '%s'", log_file);
    mtrace_log_fp = fp;
  }
  Log("Mtrace Log is written to %s", log_file ? log_file : "stdout");
}

bool mtrace_log_enable() {
  return MUXDEF(CONFIG_MTRACE, (addr>=0x80000000)&&(addr<=0x88000000), false);
}
