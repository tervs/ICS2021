#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include<stdbool.h>
//#include "vaddr.h"

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();
word_t vaddr_read(vaddr_t addr, int len);
word_t expr(char *e, bool *success); 

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() 
{
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_p(char *args) {
  char *EXPR = strtok(NULL, "\0");
  uint32_t x;
  
  bool success=true;;

  //uint32_t sign=0;
  x=expr(EXPR, &success);

  if(!success){printf("Bad Expression!\n");}
  
  else {printf("%u\n",x);}
  //Log("%d",sign);
  //printf("%d   %s",tokens[0].type,tokens[0].token_type);
  //printf("%s", EXPR);
  return 0;
}



static int cmd_t(char *args) {
  int x;
  x=4&&0;
  
  printf("%d",x);
  return 0;
}


static int cmd_q(char *args) {
  return -1;
}

static int cmd_si(char *args) {
   char *arg = strtok(NULL, " ");
   uint64_t n=0;
   
   if(arg==NULL)
   {
   cpu_exec(1);
   return 0;}
   n=atoi(arg);
   if(n==0)
   {printf("Unable to run the command");}
   else{
   cpu_exec(n);
   }
return 0;
}




static int cmd_x(char *args) 
{
 
 
  char *N = strtok(NULL, " ");
uint32_t n=atoi(N);
assert(n!=0);
/*if(n==0)
  {
    printf("wrong");
    return 0;
  }*/
     char *arg = strtok(NULL, " ");
     uint64_t addr=strtol(arg,NULL,16);
   printf("%ld\n",addr) ;
     word_t x;
     for(int j=0;j<n;j++)
     {
        printf("0x%08lx    ",addr);
        //printf("0x");
        /*
        for(int i=0;i<4;i++)
      {
      x=vaddr_read(addr, 1);
      printf("%02x",x);
     // printf("%d",x);
      addr++;
      }
      printf("\n");
*/
     }
     
 x=vaddr_read(addr, 4);
      printf("%08x",x);
    
return 0;

}





static int cmd_info(char *args) 
{
     char *arg = strtok(NULL, " ");
   // printf("%s",arg);
     
	if(strcmp(arg,"r")==0){
  
  isa_reg_display();
  }
  else if(strcmp(arg,"w")==0)
  {
  printf("to be completed");
  }
  else{printf("wrong command");}

return 0;

}





static int cmd_help(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  {"si","single step",cmd_si},
  {"info","print ",cmd_info},
  {"x","print virtual memory",cmd_x},
  {"p","expression",cmd_p},
  {"t","test",cmd_t}


  /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,0
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) 
    {
      if (strcmp(cmd, cmd_table[i].name) == 0)
       {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
