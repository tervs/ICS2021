#include "sdb.h"

#define NR_WP 32


typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char *EXPR;
  word_t x;//初始值
  int last;

  /* TODO: Add more members if necessary */

} WP;

WP* new_wp();
void free_wp(WP *wp);


static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp()
{
  if(free_==NULL){printf("no free watchpoint");return 0;}
  else
  {

    return free_;
  }
}
void free_wp(WP *wp);

void delete(WP *linklist,int n)
{
  bool empty=false;
  for(int i=0;i<NR_WP;i++)
  {
    if(wp_pool[i].next==&wp_pool[n])
    {
      wp_pool[i].next=wp_pool[n].next;
      empty=false;
    }
  }
  if(empty){linklist=NULL;}

  
}