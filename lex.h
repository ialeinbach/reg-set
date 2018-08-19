typedef struct {
	char *src;
	token_t tok;
	int stat;
} lexer_t;

extern int next(token_t *tok, lexer_t *lex);

typedef int (*lexfn_t)(lexer_t *lex);

