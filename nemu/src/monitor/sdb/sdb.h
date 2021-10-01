#ifndef __SDB_H__
#define __SDB_H__

#include <common.h>



word_t expr(char *e, bool *success);
word_t mistake_type(word_t *type);
void watchpoint(char *e, bool *success);


#endif
