typedef enum {
	INSTR, IDENT, REGSTR, NUMBER, WSPACE, NEWLINE, ERROR
} toktype_t;

typedef struct {
	toktype_t type;
	char *lexeme;
	int len;
	int line;
} token_t;

extern void tok_print(token_t tok);
extern toktype_t lookup(char* ident, int len);

extern const int ident_len_max;
extern const int instr_cnt_max;

