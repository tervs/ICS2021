#include <isa.h>
#include <memory/paddr.h>

word_t vaddr_ifetch(vaddr_t addr, int len) {
  return paddr_read(addr, len);
}

word_t vaddr_read(vaddr_t addr, int len) {
  printf("mem read in 0x%08x  len 0x%08x\n",addr,len);
  return paddr_read(addr, len);
}

void vaddr_write(vaddr_t addr, int len, word_t data) {
  printf("mem write in 0x%08x  len 0x%08x   data 0x%08x\n",addr,len,data);
  paddr_write(addr, len, data);
}
