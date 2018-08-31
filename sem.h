#ifndef _SEM_H
#define _SEM_H

#include "reg.h"

typedef union {
	int     numbr;
	int     rgstr;
} _value_t;

typedef struct {
	_value_t value;
	int type;
} value_t;

typedef void (*insfn_t)(regset_t *regset, value_t *argv);

typedef struct {
	insfn_t instr;
	value_t *argv;
	int argc;
} stmt_t;

extern const int MAX_ARGC;

extern insfn_t lookup(char *name, int len);
extern int next_stmt(lexer_t *lex, stmt_t *stmt);

#endif /* _SEM_H */

