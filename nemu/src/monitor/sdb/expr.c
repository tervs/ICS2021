#include <isa.h>
#include <regex.h>
#include <stdbool.h>

int t;





//word_t  eval(int p, int q,bool *success) ;
//static bool check_parentheses(int p, int q);
//static bool match(int p, int q);
//int op_position(int p,int q);


enum {
  TK_NOTYPE = 256, //ac
  TK_EQ,
  TK_NUM,
  TK_HEX,//16进制数
	//TK_REG0,//寄存器取值
  TK_REG,
  TK_NEQ,//不等号
  TK_AND,
  TK_OR,

};



static struct rule {
  const char *regex;
  int token_type;
  int priority;
} rules[] = 
{
  {" +", TK_NOTYPE,-1},    
  {"\\+", '+',4},   
  {"\\-",'-',4},  
  {"\\*",'*',3},//乘法优先级为3,指针优先级2
  {"\\/",'/',4}, 
  {"\\(",'(',-1},
  {"\\)",')',-1},
  {"==", TK_EQ,7}, 
  {"!=", TK_NEQ,7},	
  {"&&", TK_AND,11},				//logic and
	{"\\|\\|", TK_OR,12},
  {"\\b0[xX][0-9a-fA-F]+\\b",TK_HEX,0},
  {"[0-9]+",TK_NUM,0},
  {"\\$[a-z][0-9a-z]{1,2}|\\$\\$0", TK_REG,0},
};






#define NR_REGEX ARRLEN(rules)
static regex_t re[NR_REGEX] = {};


void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}





typedef struct token {
  int type;
  char str[32];
  int priority;
} Token;



static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) 
{
    int position = 0;
    int i;
    regmatch_t pmatch;
    nr_token = 0;
    int j=0;
    while (e[position] != '\0') 
    {
        /* Try all rules one by one. */
        for (i = 0; i < NR_REGEX; i ++) 
        {
            if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) 
      
          {
              char *substr_start = e + position;
              int substr_len = pmatch.rm_eo;

              Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
              i, rules[i].regex, position, substr_len, substr_len, substr_start);

              position += substr_len;
        
              if(rules[i].token_type!=TK_NOTYPE)
           {
              if(i==13)
              {
                  tokens[j].type=rules[i].token_type;
                  strncpy(tokens[j].str,substr_start+1,substr_len-1);
              }
        
              else
              { 
                  tokens[j].type=rules[i].token_type;
                  strncpy(tokens[j].str,substr_start,substr_len);
              }
         
              j++;
            }
                  if(tokens[j-1].type==259)
                 {
                   uint64_t temp=strtol(tokens[j-1].str,NULL,16);
                   sprintf(tokens[j-1].str,"%ld",temp);
                   Log("now the str is %s",tokens[j-1].str);
                }
              //else{Log("warning of space");break;}
              Log("now position is %d  type here is %d   str is %s ",j-1,tokens[j-1].type,tokens[j-1].str);
              break;
          }

        }

      if (i == NR_REGEX) 
      {
        printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
        return false;
      }
     // Log("%d",j);
    }
    t=j-1;
    Log("%d  ",t);
    return true;
}


word_t expr(char *e, bool *success) 
{
  if (!make_token(e)) 
  {
    *success = false;
    return 0;
  }
 
  int ans=-1;//eval(0,t,success);
    memset(tokens, 0, sizeof(Token)*32);
return ans;
}
/*
word_t  eval(int p, int q,bool *success)
{
    if (p > q) 
    { 
   *success=false;
   return 0;
    
    }
    

    else if (p == q)
    {
      return atoi(tokens[p].str);
    }


    else if (check_parentheses(p, q) == true) 
    {
    return eval(p + 1, q - 1,success);
    Log("%d\n", check_parentheses(p,q));
    }
    

    else 
    {
    int op = op_position(p,q);
    if(op==-1){exit(0);}
    Log("op is %d  p is %d  q is  %d",op,p,q);
    word_t val1 = eval(p, op - 1,success);
    word_t val2 = eval(op + 1, q,success);

    switch (tokens[op].type) 
    {
      case '+': return val1 + val2;
      case '-': return val1 - val2; 
      case '*': return val1 * val2;
      case '/': return val1 / val2;
      case TK_EQ:return val1 ==val2;
      case TK_NEQ:return val1 !=val2;
      case TK_AND:return val1 &&val2;
      case TK_OR:return val1 ||val2;
      case TK_REG: return 0;

    }
 Log("op is %d     p is %d     q is %d",op,p,q);
    }
   
return -1;
  }



int op_position(int p,int q)  //用于寻找主操作符位置，p是token数组开始位置，q是结束.
{
  int x=0;//x用来记录op，也就是主操作符位置，初始化为-1,
  int bracket=0;//用于记录括号，遇到左括号+1,右括号-1.为0意味着没有括号

  
  //for(int i=p;i<=q;i++)
  //{
  //  if(x==-1&&((tokens[i].type=='+')||(tokens[i].type=='-')||(tokens[i].type=='*')||(tokens[i].type=='/')))
  //  {
  //    x=i;
  //  }
  //}
  
  //找到第一个操作符的位置，无论这个符号是什么。从p到q扫描，直到遇到第一个操作符，然后结束循环。
  //此时x记录着第一个操作符的位置。
 // Log("the first op is %d",x);
  //接下来正式寻找主操作符。

  for(int i=p;i<=q;i++)
  {
    if(tokens[i].type=='(')
    {bracket++;}//假如遇到（，变量+1.

    else if(bracket==0)//当bracket为0,也就是不在一个括号内的时候，才执行扫描判断。
    {
       if(tokens[i].type=='+'||tokens[i].type=='-')
      {x=i;}//当最新遇到的 操作符是+或者——，更新x为最新的位置。
     
        else if((tokens[i].type=='*'||tokens[i].type=='/')&&(tokens[x].type!='+'&&tokens[x].type!='-'))
      {x=i;}//假如最新遇到的操作符是*或/，并且当前已经记录的x对应的操作符不为+或-，更新。
      
    }
   
    else if(tokens[i].type==')')
    {bracket--;}//当遇到），bracket-1。

   // Log("now x is %d and type of x is %d  while i is %d and type is %d  bracket is %d",x,tokens[x].type,i,tokens[i].type,bracket);
  
    }
  return x;
}



static bool check_parentheses(int p, int q)
{
    if(tokens[p].type!='('||tokens[q].type!=')')
    return false;
    else{
      return match(p,q);
    }
}


static bool match(int p, int q)
{
  

  int bracket=0;
for(int i=p+1;i<q;i++)
{
    switch(tokens[i].type)
            {
              case '(':
                bracket++;
                 break;

              case ')':
               bracket--;
                break;

              default:
                break;
            }
            if(bracket<0)
            {
              return false;
              break;
            }
}
            
            if(bracket==0)
            {
              return true;
            }
            else return false;
            TODO();
            // (4+3))*((2-1) is wrong.
            //异常处理，包括对于括号匹配，对于非法表达式（--），除0,
            //负数进行运算
            //最大整数长度拓展
            //颜色高亮
}

//将去空格之后的tokens保存成一个一个新的字符串数组，tokens.str似乎已经是这样的数组了
//利用新字符串数组，编写函数求解op位置
//编写括号匹配函数，检测某字符串两侧是否互相匹配


*/



 