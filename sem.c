#include <stdlib.h>
#include <string.h>

#include "tok.h"
#include "lex.h"
#include "sem.h"
#include "reg.h"
#include "stat.h"

#ifdef TESTING
#include <stdio.h>
#endif /* TESTING */

const int MAX_ARG_COUNT = 3;

// for testing
void tst(regset_t *regset, value_t *argv) { return; };

insfn_t lookup(char *name, int len) {
	static const int count = 1;
	static const struct { char *name; insfn_t instr; } lookup_table[] = {
		{ .name = "tst", .instr = tst }
	};
	for(int i = 0; i < count; ++i) {
		if(strncmp(name, lookup_table[i].name, len) == 0) {
			return lookup_table[i].instr;
		}
	}
	return NULL;
}

void eval_numbr(token_t *tok, value_t *val) {
	char tmp, *nul;

	// temporarily null-terminate for atoi
	nul = tok->data + tok->len;
	tmp = *nul;
	*nul = 0;
	val->value.numbr = atoi(tok->data);
	*nul = tmp;

	val->type = tok->type;
	return;
}

void eval_rgstr(token_t *tok, value_t *val) {
	eval_numbr(tok, val);
	val->type = tok->type;
	return;
}

int next_instr(lexer_t *lex, stmt_t *stmt) {
	int stat;
	if((stat = check_lexer(lex)) != STAT_OK) {
		return stat;
	}
	token_t tok;
	for(;;) {
		next_token(lex, &tok);
		if((stat = check_lexer(lex)) != STAT_OK) {
			return stat;
		}
		switch(tok.type) {
			case DELIM:
				continue; // skip empty stmt
			case IDENT:
				if((stmt->instr = lookup(tok.data, tok.len)) == NULL) {
					return STAT_UNDEFINED_INSTR;
				}
				return STAT_OK;
			default:
				return STAT_EXPECTED_IDENT;
		}
	}
}

int next_argv(lexer_t *lex, stmt_t *stmt) {
	int stat;
	if((stat = check_lexer(lex)) != STAT_OK) {
		return stat;
	}
	token_t tok;
	value_t *argv = stmt->argv;
	int argc = 0;
	while(argc < MAX_ARG_COUNT) {
		next_token(lex, &tok);
		if((stat = check_lexer(lex)) != STAT_OK) {
			goto DONE;
		}
		switch(tok.type) {
			case RGSTR:
				eval_rgstr(&tok, argv);
				break;
			case NUMBR:
				eval_numbr(&tok, argv);
				break;
			default:
				stat = STAT_INVALID_ARG_TYPE;
			case DELIM:
				goto DONE;
		}
		++argc;
		++argv;
	}
DONE:
	stmt->argc = argc;
	return stat;
}

int next_stmt(lexer_t *lex, stmt_t *stmt) {
	int stat;
	if((stat = next_instr(lex, stmt)) != STAT_OK) {
		return stat;
	}
	if((stat = next_argv(lex, stmt)) != STAT_OK) {
		return stat;
	}
	return STAT_OK;
}

#ifdef TESTING
int main(int argc, char *argv[]) {
	if(argc != 2) {
		return EXIT_FAILURE;
	}
	lexer_t lex = {
		.text = argv[1],
		.buf  = (token_t){ .line = 1 },
		.stat = STAT_OK
	};
	value_t argv_buf[MAX_ARG_COUNT];
	stmt_t stmt = {
		.instr = NULL,
		.argv = argv_buf,
		.argc = 0
	};
	int stat;
	do {
		switch(stat = next_stmt(&lex, &stmt)) {
			case STAT_DONE:
			case STAT_OK:
				printf("instr: %p\n", stmt.instr);
				for(int i = 0; i < stmt.argc; ++i) {
					printf("arg%d: %d\n", i, stmt.argv[i]);
				}
			default:
				printf("status: %d\n\n", stat);
				break;
		}
	} while(stat == STAT_OK);
	return EXIT_SUCCESS;
}
#endif /* TESTING */

