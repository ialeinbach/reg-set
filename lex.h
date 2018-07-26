#include "tok.h"

typedef struct {
	char *src;
	int  ahead;

	toktype_t type;
	int       line;

	const char *err;
} lexer_t;

token_t emit(lexer_t *lexer);

typedef int (*lexfn_t)(lexer_t *lexer);
int regstr(lexer_t *lexer);
int number(lexer_t *lexer);
int wspace(lexer_t *lexer);

