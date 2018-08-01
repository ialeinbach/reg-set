#include "tok.h"

typedef struct {
	char *src;
	int  ahead;

	toktype_t type;
	int       line;

	const char *err;
} lexer_t;

typedef int (*lexfn_t)(lexer_t *lexer);

extern token_t emit(lexer_t *lexer);

extern int regstr(lexer_t *lexer);
extern int number(lexer_t *lexer);
extern int wspace(lexer_t *lexer);
extern int ident(lexer_t *lexer);
extern token_t next(lexer_t *lexer);

