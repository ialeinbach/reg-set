typedef enum {
	INSTR, REGSTR, NUMBER, WSPACE, NEWLINE, ERROR
} toktype_t;

typedef struct {
	toktype_t type;
	char *lexeme;
	int len;
	int line;
} token_t;

