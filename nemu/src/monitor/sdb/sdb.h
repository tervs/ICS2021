#ifndef __SDB_H__
#define __SDB_H__

#include <common.h>



word_t expr(char *e, bool *success);
void mistake_type();
void watchpoint(char *e, bool *success);
void newdelete(int n);
void wp_info();
int diff();
#endif
