typedef enum {
	INSTR, REGSTR, NUMBER, WSPACE, ERROR
} toktype_t;

typedef struct {
	toktype_t type;
	char *data;
	int len;
	int line;
} token_t;

extern void tok_print(token_t tok);
extern toktype_t lookup(char *instr, int len);

extern const int instr_len_max;
extern const int instr_cnt_max;

