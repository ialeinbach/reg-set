#ifndef _REG_H
#define _REG_H

#include "lex.h"

typedef int *reg_t;

typedef struct {
	lexer_t *lex;
	reg_t *reg;
	int stat;
} regset_t;

extern const int REG_COUNT;

#endif /* _REG_H */
