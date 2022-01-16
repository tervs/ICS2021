#include <isa.h>

void dev_raise_intr() {
    cpu.INTR=1;
    printf("test\n")
}
