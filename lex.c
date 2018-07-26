#include <stdio.h>

#include "lex.h"

token_t emit(lexer_t *lexer) {
	token_t tok = {
		.type   = lexer->type,
		.lexeme = lexer->src - lexer->ahead,
		.len    = lexer->ahead,
		.line   = lexer->line
	};
	return tok;
}

// lexfn_t
int wspace(lexer_t *lexer) {
	for(int c = 0; ; ++c) {
		switch(*lexer->src) {
			case '\n':
				++lexer->line;
			case '\t':
			case ' ':
				continue;
			default:
				return c;
		}
	}
}

// lexfn_t
int number(lexer_t *lexer) {
	for(int c = 0; ; ++c) {
		switch(*lexer->src) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				++lexer->src;
				continue;
			default:
				if(c > 0) {
					lexer->type = NUMBER;
				}
				return c;
		}
	}
}

// lexfn_t
int regstr(lexer_t *lexer) {
	int c = 0;
	if(*lexer->src == '@') {
		++lexer->src;
		if((c = number(lexer)) == 0) {
			lexer->type = ERROR;
			lexer->err = "invalid register name";
		} else {
			++c; // account for '@'
			lexer->type = REGSTR;
		}
	}
	return c;
}

// lexfn_t
int instr(lexer_t *lexer) {
	return 0;
	/*
	for(int c = 0; ; ++c) {
		switch(*lexer->src) {
		}
	}
	*/
}

token_t next(lexer_t *lexer) {
	wspace(lexer);
	if(!(regstr(lexer) || instr(lexer) || number(lexer))) {
		if(lexer->type != ERROR) {
			lexer->type = ERROR;
			lexer->err = "unexpected character";
		}
	}
	return emit(lexer);
}

int main() {
	printf("hello\n");
}
