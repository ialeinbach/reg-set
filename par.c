#include <stdlib.h>
#include <string.h>

#include "tok.h"
#include "lex.h"
#include "par.h"
#include "err.h"

#ifdef TESTING
#include <stdio.h>
#endif /* TESTING */

bool next_stmt(parser_t *par) {
	lexer_t *lex = par->lex;
	statement_t *stmt = &par->stmt;
	for(;;) {
		if(lex->done) {
			return false;
		}
		if(lex->err != ERR_NONE || !next_token(lex)) {
			par->err = ERR_LEXER_FAILURE;
			lex->done = true;
			return false;
		}
		switch(lex->tok.type) {
			case IDENT:
				stmt->instr = lex->tok;
				break;
			case DELIM:
				continue;
			default:
				par->err = ERR_EXPECTED_INSTR;
				lex->done = true;
				return false;
		}
		token_t *argv = stmt->argv;
		stmt->argc = 0;
		while(stmt->argc <= MAX_ARG_COUNT && next_token(lex)) {
			switch(lex->tok.type) {
				case RGSTR:
				case NUMBR:
					*argv++ = lex->tok;
					++stmt->argc;
					continue;
				default:
					par->err = ERR_INVALID_ARG_TYPE;
					lex->done = true;
					return false;
				case DELIM:
					return true;
			}
		}
		return true;
	}
}

#ifdef TESTING
int main(int argc, char *argv[]) {
	if(argc != 2) {
		return EXIT_FAILURE;
	}
	lexer_t lex = {
		.text = argv[1],
		.tok = (token_t){ .line = 1 },
		.err = ERR_NONE,
		.done = false
	};
	token_t argbuf[MAX_ARG_COUNT];
	parser_t par = {
		.lex = &lex,
		.stmt = (statement_t){ .argv = argbuf },
		.err = ERR_NONE,
		.done = false
	};
	char buf[128];
	while(next_stmt(&par)) {
		sprint_token(buf, par.stmt.instr);
		printf("INSTR: %s\n", buf);
		for(int i = 0; i < par.stmt.argc; ++i) {
			sprint_token(buf, par.stmt.argv[i]);
			printf("ARG %d: %s\n", i, buf);
		}
		printf("\n");
	}
	printf("parser error: %d\n", par.err);
	printf("lexer error: %d\n", lex.err);
	return EXIT_SUCCESS;
}
#endif /* TESTING */
