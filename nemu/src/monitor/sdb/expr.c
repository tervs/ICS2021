#include <isa.h>
#include <regex.h>
#include <stdbool.h>

int t;





word_t  eval(int p, int q) ;
static bool check_parentheses(int p, int q);
static bool match(int p, int q);
int op_position(int p,int q);


enum {
  TK_NOTYPE = 256, TK_EQ,TK_NUM,
};



static struct rule {
  const char *regex;
  int token_type;
} rules[] = {
  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal
  {"\\-",'-'},
  {"\\*",'*'},
  {"\\/",'/'},
  {"\\(",'('},
  {"\\)",')'},
  {"[0-9]+",TK_NUM},
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
} Token;



static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
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
        
        if(i!=TK_NOTYPE)
        {
      tokens[position].type=i;
        strcpy(tokens[position].str,rules[i].regex);
        }

       
        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        /*switch (rules[i].token_type) {
          default: TODO();
        }
        */

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  t=position;
  return true;
}

word_t expr(char *e, bool *success) 
{
  if (!make_token(e)) 
  {
    *success = false;
    return 0;
  }
 
return eval(0,t);
}

word_t  eval(int p, int q)
{
    if (p > q) 
    { 
    return -1;
    }
    

    else if (p == q)
    {
      return atoi(tokens[p].str);
    }


    else if (check_parentheses(p, q) == true) 
    {
    return eval(p + 1, q - 1);
    }
    

    else 
    {
    int op = op_position(p,q);
    word_t val1 = eval(p, op - 1);
    word_t val2 = eval(op + 1, q);

    switch (tokens[op].type) 
    {
      case '+': return val1 + val2;
      case '-': return val1 - val2; 
      case '*': return val1 * val2;
      case '/': return val1 / val2;
      //default: //assert(0);
    }

    }

return 0; 
  }



int op_position(int p,int q)
{
  int x=p;
  int bracket=0;
  for(int i=p;i<=q;i++)
  {
    
    if(tokens[i].type!='('&&bracket==0)
    {
        if(tokens[i].type=='+'||'-')
      {
          x=i;
      }
        else if((tokens[i].type=='*'||'/')&&(tokens[x].type!='+'||'-'))
      {
          x=i;
      }
    }

    if(tokens[i].type==')')
      {
          bracket--;
      }
    if(tokens[i].type=='(')
      {
          bracket++;
      }
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
}

//将去空格之后的tokens保存成一个一个新的字符串数组，tokens.str似乎已经是这样的数组了
//利用新字符串数组，编写函数求解op位置
//编写括号匹配函数，检测某字符串两侧是否互相匹配


  //int op_position(char *e)
 