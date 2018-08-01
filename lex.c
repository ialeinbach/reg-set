#include <stdio.h>

#include "lex.h"

token_t emit(lexer_t *lexer) {
	token_t tok = {
		.type   = lexer->type,
		.lexeme = lexer->src,
		.len    = lexer->ahead,
		.line   = lexer->line
	};
	lexer->src += lexer->ahead;
	return tok;
}

// lexfn_t
int wspace(lexer_t *lexer) {
	char *ch = lexer->src;

	for(int c = 0; ; ++c) {
		switch(*ch++) {
			case '\n':
				++lexer->line;
			case '\t':
			case ' ':
				continue;
			default:
				lexer->src += c;
				return c;
		}
	}
}

// lexfn_t
int number(lexer_t *lexer) {
	char *ch = lexer->src;

	char curr;
	for(int c = 0; ; ++c) {
		curr = *ch++;

		if(curr < '0' || curr > '9') {
			if(c > 0) {
				lexer->type = NUMBER;
				lexer->ahead += c;
			}
			return c;
		}
	}
}

// lexfn_t
int regstr(lexer_t *lexer) {
	if(*lexer->src != '@') {
		return 0;
	}
	int c = 1;

	++lexer->src;
	c += number(lexer);
	if(c == 1) { // only '@'
		lexer->type = ERROR;
		lexer->err = "invalid register name";
	} else {
		lexer->type = REGSTR;
		lexer->ahead += c;
	}
	--lexer->src;

	return c;
}

// lexfn_t
int ident(lexer_t *lexer) {
	char *ch = lexer->src;

	char curr;
	for(int c = 0; ; ++c) {
		if(c >= ident_len_max) {
			lexer->type = ERROR;
			lexer->err = "identfier too long";
			return c;
		}
		curr = *ch++;
		if(curr != '_' && (curr < 'a' || curr > 'z') && (curr < 'A' || curr > 'Z')) {
			if(c > 0) {
				lexer->type = lookup(lexer->src, c);
				lexer->ahead += c;
			}
			return c;
		}
	}
}

token_t next(lexer_t *lexer) {
	wspace(lexer);
	if(!regstr(lexer) && !ident(lexer) && !number(lexer)) {
		if(lexer->type != ERROR) {
			lexer->type = ERROR;
			lexer->err = "unexpected character";
		}
	}
	return emit(lexer);
}

