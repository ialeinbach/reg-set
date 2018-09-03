#ifndef _LEX_H
#define _LEX_H

#include <stdbool.h>

#include "tok.h"

#define MAX_INSTR_LEN 3

typedef struct {
	char *text;
	token_t tok;
	int err;
	bool done;
} lexer_t;

typedef bool (*lexfn_t)(lexer_t *lex);

extern bool next_token(lexer_t *lex);

#endif /* _LEX_H */

