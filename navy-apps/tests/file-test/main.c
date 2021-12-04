#include <stdio.h>
#include <assert.h>

int main() {
  FILE *fp = fopen("/share/files/num", "r+");
  assert(fp);

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  assert(size == 5000);

  fseek(fp, 500 * 5, SEEK_SET);
  int i, n;
  for (i = 500; i < 1000; i ++) {
    printf("test       1      %d\n",i);
    fscanf(fp, "%d", &n);
    printf("test       2      %d\n",n);
    assert(n == i + 1);
    printf("test       3      %d\n",i);
  }




  fseek(fp, 0, SEEK_SET);
  for (i = 0; i < 500; i ++) {
    fprintf(fp, "%4d\n", i + 1 + 1000);
  }







  for (i = 500; i < 1000; i ++) 
  {
    printf("1     %d\n",i);
    fscanf(fp, "%d", &n);
    printf("2     %d\n",i);
    assert(n == i + 1);
    printf("3     %d\n",i);
  }

printf("6 from main\n");




  fseek(fp, 0, SEEK_SET);
  for (i = 0; i < 500; i ++) {
    fscanf(fp, "%d", &n);
    assert(n == i + 1 + 1000);
  }

  fclose(fp);

  printf("PASS!!!\n");

  return 0;
}
