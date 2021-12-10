#include <fixedptc.h>
#include <stdio.h>

fixedpt A=0x599;
fixedpt B=0xfffffecd;

int main()
{
    printf("A+B  %d\n",(A+B));
    printf("A*B %d\n",fixedpt_mul( A, B))


}
