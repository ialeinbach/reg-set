typedef enum {
	INSTR,
	RGSTR,
	NUMBR,
	DELIM,
	ERROR
} toktype_t;

typedef struct {
	toktype_t type;
	int line;

	// lexeme (ptr to src)
	char *data;
	int len;
} token_t;

extern int sprint_token(char *str, token_t tok);
extern int sprint_toktype(char *str, toktype_t typ);

