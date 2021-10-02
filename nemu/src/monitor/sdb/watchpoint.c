#include "sdb.h"

#define NR_WP 32



typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char *EXPR;
  word_t x;//初始值
  int last;
} WP;

int new_wp();
void free_wp(WP *wp);
void delete(WP *linklist,int n);
void insert(WP *linklist,int n);
int get_last(WP *linklist);
bool is_empty(WP *linklist);
void watchpoint(char *e, bool *success);
void travers(WP *linklist);

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

int new_wp()
{
  if(is_empty(free_)){printf("no free watchpoint!");return -1;}
  int n=get_last(free_);
  delete(free_,n);
  insert(head,n);
  return n;
}
void free_wp(WP *wp)
{
  if(is_empty(head)){printf("no watchpoint to free!");return;}
  delete(head,wp->NO);
  insert(free_,wp->NO);
  return;

}

void delete(WP *linklist,int n)//删去链表里的n号元素。对于head，n是指定数值。对于free，n是链表尾数值，由另一个函数计算得出。
{

  int first=linklist->NO;
  for(int i=first;;i=wp_pool[i].next->NO)
  {
    if(wp_pool[i].next==&wp_pool[n])
    {
      wp_pool[i].next=wp_pool[n].next;
     break;
    }
  }

  return;
}

void insert(WP *linklist,int n)//将要插入链表的是n号元素，记录linklist指向的元素的序号作为起始值。依次检测该监视点是否是最后一个，如果是，将n号链接在后面，并将n号的next更新为null
{//若是要插入的链表是空的呢？
    int last=get_last(linklist);
    wp_pool[last].next=wp_pool[n].next;
    wp_pool[n].next=NULL;
    return;
}

int get_last(WP *linklist)
{
  int n;
    int first=linklist->NO;
    Log("first in free is %d",first);
    for(int i=first; ;i=wp_pool[i].next->NO)
    {
      if(wp_pool[i].next==NULL)
      {
        n=i;
        break;
      }
    }
  return n;
}
/*
bool is_full(WP *linklist)
{
  int count=0;
  int first=linklist->NO;
    for(int i=first;;i=wp_pool[i].next->NO)
    {
      count++;
      if((wp_pool[i].next==NULL)&&(count==32))
      {
        return true;
      }
    }
    return false;
}
*/
bool is_empty(WP *linklist)
{
  if(linklist==NULL)
  return true;
  else return false;
}

void watchpoint(char *e, bool *success)
{
  
  //int new=new_wp();
  travers(free_);

 delete(free_,10);
 travers(free_);
  //bool success=true;;
  /*
  int value=expr(e, success);
  wp_pool[new].EXPR=e;
  wp_pool[new].x=value;
  printf("%d   %s   %d\n",new,wp_pool[new].EXPR,wp_pool[new].x);
  return;
  */
}


void travers(WP *linklist)
{
    int first=linklist->NO;
    for(int i=first; ;i=wp_pool[i].next->NO)
    {
      printf("%d  ",i);
      if(wp_pool[i].next==NULL)
      {
        break;
      }
    }
}