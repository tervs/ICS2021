#include <common.h>

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

int main(int argc, char *argv[]) {

 // printf("here?\n");
  /* Initialize the monitor. */

  printf("%d\n",argc);
  printf("%s\n",*argv);
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

  
  /* Start engine. */
  engine_start();

  return 0;//is_exit_status_bad();
}
