#ifndef _LEX_H
#define _LEX_H

#include <stdbool.h>

#define MAX_INSTR_LEN 3

typedef struct {
	char *text;
	token_t buf;
	int stat;
} lexer_t;

typedef bool (*lexfn_t)(lexer_t *lex);

extern int next_token(lexer_t *lex, token_t *tok);
extern int check_lexer(lexer_t *lex);

#endif /* _LEX_H */

