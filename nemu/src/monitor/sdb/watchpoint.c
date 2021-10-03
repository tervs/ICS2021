#include "sdb.h"

#define NR_WP 8



typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char *EXPR;
  word_t value;//初始值
} WP;

int new_wp();
void free_wp(int n);
void delete(WP **linklist,int n);
void insert(WP **linklist,int n);
int get_last(WP *linklist);
bool is_empty(WP *linklist);
bool search(WP *linklist,int n);
void watchpoint(char *e, bool *success);
void travers(WP *linklist);
void newdelete(int n);
void wp_info();
void strcopy(char *EXPR,char *e);


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
  int n=get_last(free_);
  delete(&free_,n);
  insert(&head,n);
  return n;
}




void free_wp(int n)
{
  delete(&head,n);
  insert(&free_,n);
  return;
}





void delete(WP **linklist,int n)//删去链表里的n号元素。对于head，n是指定数值。对于free，n是链表尾数值，由另一个函数计算得出。
{

  int first=(*linklist)->NO;
  if(first==n)
  {
    *linklist=wp_pool[n].next;
    //Log("empty. so %d",(*linklist)->NO);
    return;
  }
  else
  {
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
{
    if(is_empty(*linklist))
    {
      Log("is empty ? %d",is_empty(*linklist));
      *linklist=&wp_pool[n];

      wp_pool[n].next=NULL;

      return;
    }
    else{
    int last=get_last(*linklist);
    Log("last number is %d",last);
    wp_pool[last].next=&wp_pool[n];
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
  //Log("%d",(linklist==NULL));
  if(linklist==NULL)
  
  return true;
  else return false;
}





void travers(WP *linklist)
{
  if(is_empty(linklist)){printf("empty linklist!\n");return;}

  else
  {
    int first=linklist->NO;
    for(int i=first; ;i=wp_pool[i].next->NO)
    {
      printf("%d    %s    %d\n",i,wp_pool[i].EXPR,wp_pool[i].value);
      if(wp_pool[i].next==NULL)
      {
        printf("\n");
        break;
      }
    }
  }
}




bool search(WP *linklist,int n)
{
  if(is_empty(linklist))
  {//printf("empty linklist!");
  return false;}
  else
  {
    int first=linklist->NO;
    for(int i=first; ;i=wp_pool[i].next->NO)
    {
      if(wp_pool[i].NO==n)
      {
        return true;
      }
      else if(wp_pool[i].next==NULL)
      {
        //printf("search failed");
        return false;
      }

    }
  }

}


void watchpoint(char *e, bool *success)
{
  if(is_empty(free_)){printf("no free watchpoint!\n");return ;}
  else
  {

    bool success = true;
	  uint32_t val = expr(e,&success);
    if(success)
    {
      int n=new_wp();
      Log("?");
      strcpy(wp_pool[n].EXPR,"1+1");
      Log("?");
      (&wp_pool[n])->value=val;
    printf("%s\n",wp_pool[n].EXPR);
    printf("%u\n",wp_pool[n].value);
    printf("head: \n");travers(head);
    printf("free: \n");travers(free_);

    }


    /*
    int n=new_wp();
    Log("?");
      strcpy(wp_pool[n].EXPR,e);
     Log("?");
    //wp_pool[n].EXPR=e;
    uint32_t x;
    x=expr(e, success);
    wp_pool[n].value=x;

    */



printf("%s\n",wp_pool[7].EXPR);
    return;


    
  }

}



void newdelete(int n)
{
  if(!search(head,n)){printf("no such watchpoint in use!\n");return;}
  
  else if(is_empty(head)){printf("no watchpoint to free!\n");return;}
  free_wp(n);
  printf("head: \n");travers(head);

  printf("free: \n");travers(free_);

}

void wp_info()
{
  travers(head);
  printf("%s",wp_pool[7].EXPR);
}
/*
void strcopy(char *EXPR,char *e)
{
  int n=strlen(e);
  printf("%d\n",n);
  printf("%s\n",e);
  int count=0;
  for(int i=0;i<n;i++)
  {
    printf("%d\n",i);
    if(e[i]!=' ')
    {

        EXPR[count]=e[i];
        printf("%d",count);
        count++;
    }
  }
  //return EXPR;
}
*/
//delete一个不在列表里的监视点会出错