#include <unistd.h>
#include <stdio.h>

int main() {
  write(1, "Hello World!\n", 13);
  int i = 2;
  volatile int j = 0;
  while (1) {
    j ++;
    if (j == 1000) {
      printf("Fello World from Navy-apps for the %dth time!\n", i ++);
      return 0;
    }
  }
  return 0;
}
