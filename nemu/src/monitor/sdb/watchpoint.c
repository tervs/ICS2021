#include "sdb.h"

#define NR_WP 32



typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char *EXPR;
  word_t x;//初始值
} WP;

int new_wp();
void free_wp(WP *wp);
void delete(WP **linklist,int n);
void insert(WP **linklist,int n);
int get_last(WP *linklist);
bool is_empty(WP *linklist);
void watchpoint(char *e, bool *success);
void travers(WP *linklist);
void newdelete(int n);

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
  delete(&free_,n);
  insert(&head,n);
  return n;
}




void free_wp(WP *wp)
{
  if(is_empty(head)){printf("no watchpoint to free!");return;}
  delete(&head,wp->NO);
  insert(&free_,wp->NO);
  return;

}





void delete(WP **linklist,int n)//删去链表里的n号元素。对于head，n是指定数值。对于free，n是链表尾数值，由另一个函数计算得出。
{

  int first=(*linklist)->NO;
  Log("%d",first);
  Log("%d",n);
  if(first==n)
  {
    Log("????");
    *linklist=wp_pool[n].next;
    Log("%d",(*linklist)->NO);
    return;
  }
  else
  {
    Log("%d",(*linklist)->NO);
    for(int i=first;;i=wp_pool[i].next->NO)
  {
    if(wp_pool[i].next==&wp_pool[n])
    {
      wp_pool[i].next=wp_pool[n].next;
     break;
    }
  }
  }
  return;
}





void insert(WP **linklist,int n)//将要插入链表的是n号元素，记录linklist指向的元素的序号作为起始值。依次检测该监视点是否是最后一个，如果是，将n号链接在后面，并将n号的next更新为null
{//若是要插入的链表是空的呢？
    if(is_empty(*linklist))
    {
      Log("%d",is_empty(*linklist));
      *linklist=&wp_pool[n];
      wp_pool[n].next=NULL;
      Log("%d",(*linklist)->NO);
      return;
    }
    else{
    int last=get_last(*linklist);
    Log("%d",last);
    wp_pool[last].next=wp_pool[n].next;
    Log("success");
    wp_pool[n].next=NULL;
    return;
    }
   
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





bool is_empty(WP *linklist)
{
  if(linklist==NULL)
  return true;
  else return false;
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





void watchpoint(char *e, bool *success)
{
  Log("%d",free_->NO);
  travers(free_);
  delete(&free_,0);
  travers(free_);
  Log("%d",free_->NO);
  insert(&head,0);
  Log("%d",head->NO);
  travers(head);
  delete(&free_,1);
  Log("%d",free_->NO);
travers(free_);

insert(&head,1);
travers(head);


}

void newdelete(int n)
{
  delete(&free_,n);
  travers(free_);
}





//delete不能删除第一个元素
//insert 似乎插入第一个元素有问题