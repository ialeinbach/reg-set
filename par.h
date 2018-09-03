#ifndef _PAR_H
#define _PAR_H

#include <stdbool.h>

#include "tok.h"
#include "lex.h"

#define MAX_ARG_COUNT 3

typedef struct {
	token_t instr;
	token_t *argv;
	int argc;
} statement_t;

typedef struct {
	lexer_t *lex;
	statement_t stmt;
	int err;
	bool done;
} parser_t;

extern bool next_stmt(parser_t *par);

#endif /* _PAR_H */

