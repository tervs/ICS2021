#include <isa.h>
#include <regex.h>
#include <stdbool.h>
word_t sign=0;
int t;

//1 寄存器不存在 
//2 左右括号不匹配
//3 make_token有未识别字符
//4 表达式不正确。如1+1+;
//5 内存不在范围内
//expr总体用一个sucess返回秋值是否成功，所以各个部分自己的bool变量应该记录做别名

word_t  eval(int p, int q,bool *success) ;//求值的递归函数
static bool match(int p, int q);//检测括号匹配
int op_position(int p,int q);//主操作符位置
word_t get_addr(word_t x);//读取内存
word_t vaddr_read(vaddr_t addr, int len);//调用外部程序读取内存
word_t mistake_type(word_t *type);//返回错误类型
void is_pointer();
void is_negative();

enum {
  TK_NOTYPE = 256, //ac
  TK_EQ,
  TK_NUM,
  TK_HEX,//16进制数
  TK_REG,
  TK_NEQ,//不等号
  TK_AND,
  TK_OR,
  TK_POI,
  TK_NEG,

};
static struct rule 
{
  const char *regex;
  int token_type;
  int priority;
} rules[] = 
{
  {" +", TK_NOTYPE,-1},    
  {"\\+", '+',4},   
  {"\\-",'-',4},  
  {"\\*",'*',3},//乘法优先级为3,指针优先级2
  {"\\/",'/',3}, 
  {"\\(",'(',-1},
  {"\\)",')',-1},
  {"==", TK_EQ,7}, 
  {"!=", TK_NEQ,7},	
  {"&&", TK_AND,11},				//logic and
	{"\\|\\|", TK_OR,12},
  {"\\b0[xX][0-9a-fA-F]+\\b",TK_HEX,0},
  {"[0-9]+",TK_NUM,0},
  {"\\$[a-z][0-9a-z]{1,2}|\\$\\$0", TK_REG,0},
  {"\\*",'*',2},
  {"\\-",'-',2},
};


#define NR_REGEX ARRLEN(rules)
static regex_t re[NR_REGEX] = {};

//初始化，对正则表达式进行编译;
void init_regex() 
{
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) 
  {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) 
    {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token 
{
  int type;
  char str[32];
  int priority;
} Token;

static Token tokens[1024] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

//识别字符串中的字符并按位置放在tokens数组中
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

              //Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
              //i, rules[i].regex, position, substr_len, substr_len, substr_start);

              position += substr_len;
        
              if(rules[i].token_type!=TK_NOTYPE)
           {
              if(i==13)//将寄存器的储存名称去除开头的$
              {
                  tokens[j].type=rules[i].token_type;
                  strncpy(tokens[j].str,substr_start+1,substr_len-1);
                  tokens[j].priority=rules[i].priority;
              }
        
              else
              { 
                  tokens[j].type=rules[i].token_type;
                  strncpy(tokens[j].str,substr_start,substr_len);
                  tokens[j].priority=rules[i].priority;
              }
         
              j++;
            }
             //Log("position: %d  type: %d  str: %s  priority: %d",j-1,tokens[j-1].type,tokens[j-1].str,tokens[j-1].priority);
                  if(tokens[j-1].type==259)//将16进制数字转化为十进制字符串
                 {
                   uint64_t temp=strtol(tokens[j-1].str,NULL,16);
                   sprintf(tokens[j-1].str,"%ld",temp);
                   tokens[j-1].type=258;
                   //Log("now the str is %s",tokens[j-1].str);
                }
                  if(tokens[j-1].type==260)//将寄存器值取出并保存为十进制字符串
                {
                  bool is_reg_exist=true;
                  uint64_t temp=isa_reg_str2val(tokens[j-1].str,&is_reg_exist);
                  tokens[j-1].type=258;
                  if(!is_reg_exist)
                  {
                    sign=1;
                    // Log("%d\n",is_reg_exist);
                    return false;
                    } 
                  
                  sprintf(tokens[j-1].str,"%ld",temp);
                }
             Log("now position is %d  type here is %d   str is %s ",j-1,tokens[j-1].type,tokens[j-1].str);
              break;
          }

        }

      if (i == NR_REGEX) 
      {
        printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
        sign=3;
        return false;
      }
    }
    t=j-1;//t是数组长度
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
    is_pointer();
    is_negative();
    word_t ans=eval(0,t,success);
    memset(tokens, 0, sizeof(Token)*32);//将使用过的数组初始化
    return ans;
}
//递归求解
word_t  eval(int p, int q,bool *success)
{
    if (p > q) //p>q一般认为是错误表达式
    {
      *success=false;
      sign=4;
      return 0;
    }

    else if(match(p,q)==true)//假如所有括号都匹配，否则返回false
    {//Log("good match");
        if (p == q)//若出现相等，只有p=q并且位置上是数字才是可行的，否则就是无效表达式
      {
        if(tokens[p].type==TK_NUM)
        {
            uint32_t temp=strtoul(tokens[p].str,NULL,10);
            return temp;
        }
          else{sign=4;*success=false;return 0;}
       }

        else if (match(p+1,q-1)&&tokens[p].type=='('&&tokens[q].type==')') //所有括号都匹配，并且pq被一对匹配的括号包围着，则去括号
      {
        return eval(p + 1, q - 1,success);
      }
       
      else{
          int op = op_position(p,q);
          Log("op is %d  p is %d  q is  %d",op,p,q);
          word_t val2 = eval(op + 1, q,success);//因为可能出现单目运算符，故先调用val2.
      
        if(tokens[op].type==TK_POI)//是取指针运算
      {
        if(val2<2147483648){*success=false;sign=5;return 0;}
        else {return get_addr(val2);}
      }
        else if(tokens[op].type==TK_NEG)//是取负运算
      {
        return -val2;
      }
      else//已经确定是双目操作符，使用switch返回
      {
        
          word_t val1 = eval(p, op - 1,success);
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
      }
      }
     // Log("op is %d     p is %d     q is %d",op,p,q);
      }
    }
   // else {printf("bad brackets");*success= false;sign=2;}括号不正确应该已经被排除掉了
  return -1;
}


int op_position(int p,int q)  //用于寻找主操作符位置，p是token数组开始位置，q是结束.
{
  int x=p;//x用来记录op，也就是主操作符位置，初始化为-1,
  int bracket=0;//用于记录括号，遇到左括号+1,右括号-1.为0意味着没有括号

  for(int i=p;i<=q;i++)
  {

    //Log("x: %d  x.type: %d  x.priority: %d  i: %d  i.type: %d  x.priority: %d  bracket: %d,"
    //,x,tokens[x].type,tokens[x].priority,i,tokens[i].type,tokens[i].priority,bracket);
    if(tokens[i].type=='(')
    {bracket++;}//假如遇到（，变量+1.

    else if(bracket==0)//当bracket为0,也就是不在一个括号内的时候，才执行扫描判断。
    {
      if(tokens[i].priority>=tokens[x].priority)
      {
        if((tokens[x].priority==2)&&(tokens[i].priority==2)){Log("skip!");continue;}
        else{x=i;}//主要是考虑到连续两个单目操作，主运算符应该是外面的那个
      }
    }
   
    else if(tokens[i].type==')')
    {bracket--;}//当遇到），bracket-1。
  }
  
  return x;
}

word_t get_addr(word_t x)
{
  printf("%08x\n",x);
  word_t n=0;
  for(int i=0;i<4;i++)
  {
    
    n=n*256+vaddr_read(x, 1);
    x++;
  }
  return n;
}

static bool match(int p, int q)
{
  if(q<p){return false;}
  int bracket=0;
for(int i=p;i<=q;i++)
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
            //异常处理，包括对于括号匹配，对于非法表达式（--），除0,
            //颜色高亮
}

word_t mistake_type(word_t *type)
{
  word_t x=sign;
  sign=0;
  return x;
}

void is_pointer()
{

  for (int i = 0; i <=t; i++) 
  {
    bool s=(tokens[i - 1].priority !=0)&&(tokens[i - 1].type!=')');
    if (tokens[i].type == '*' && (i == 0 || s) ) 
    {
      tokens[i].type = TK_POI;
      tokens[i].priority = 2;
      Log("position %d is POI",i);
    }
  }
}


void is_negative()
{

  for (int i = 0; i <=t; i++) 
  {
    bool s=(tokens[i - 1].priority !=0)&&(tokens[i - 1].type!=')');
    if (tokens[i].type == '-' && (i == 0 || s) ) 
    {
      tokens[i].type = TK_NEG;
      tokens[i].priority = 2;
      Log("position %d is NEG",i);
    }
  }
}


 