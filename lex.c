#include <stdbool.h>

#ifdef TESTING
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif /* TESTING */

#include "tok.h"
#include "lex.h"
#include "err.h"

const int LEX_FN_COUNT = 4;

int expected(toktype_t type) {
	switch(type) {
		case NUMBR: return ERR_EXPECTED_NUMBR;
		case RGSTR: return ERR_EXPECTED_RGSTR;
		case IDENT: return ERR_EXPECTED_IDENT;
		default:
			return -1;
	}
}

bool is_digit(char ch) {
	return ch >= '0' && ch <= '9';
}

bool is_ident(char ch) {
	return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch == '_';
}

int skip_whitespace(lexer_t *lex) {
	char *start = lex->text;
	for(;;) {
		switch(*lex->text) {
			case '\n':
				++lex->tok.line;
			case '\t':
			case ' ':
				++lex->text;
				continue;
			default:
				return lex->text - start;
		}
	}
}


void tokenize(lexer_t *lex, toktype_t type, int len) {
	lex->tok.text = lex->text;
	lex->tok.type = type;
	lex->tok.len = len;
	lex->text += len;
	return;
}

bool lex_sequence(lexer_t *lex, char prefix, bool (*valid)(char), toktype_t type, int max) {
	if(*lex->text != prefix) {
		return false;
	}
	char *ch = ++lex->text;
	if(!valid(*ch)) {
		--lex->text;
		lex->err = expected(type);
		return true;
	}
	int len = 1;
	if(max == 0) {
		while(valid(*++ch)) {
			++len;
		}
	} else {
		while(valid(*++ch) && len < max) {
			++len;
		}
	}
	tokenize(lex, type, len);
	return true;
}

bool lex_numbr(lexer_t *lex) {
	return lex_sequence(lex, '#', is_digit, NUMBR, 0);
}

bool lex_rgstr(lexer_t *lex) {
	return lex_sequence(lex, '@', is_digit, RGSTR, 0);
}

bool lex_instr(lexer_t *lex) {
	return lex_sequence(lex, '_', is_ident, IDENT, MAX_INSTR_LEN);
}

bool lex_delim(lexer_t *lex) {
	bool found = *lex->text == ';';
	if(found) {
		tokenize(lex, DELIM, 1);
	}
	return found;
}

lexfn_t *get_lexfn() {
	static lexfn_t lexfn[] = {
		lex_instr,
		lex_rgstr,
		lex_numbr,
		lex_delim
	};
	return lexfn;
}

bool next_token(lexer_t *lex) {
	if(lex->done || lex->err != ERR_NONE) {
		return false;
	}
	skip_whitespace(lex);
	if(*lex->text == '\0') {
		lex->done = true;
		tokenize(lex, DELIM, 0);
		return true;
	}
	lexfn_t *lexfn = get_lexfn();
	for(int i = 0; i < LEX_FN_COUNT; ++i) {
		if((*lexfn++)(lex)) {
			return lex->err == ERR_NONE;
		}
	}
	lex->err = ERR_UNEXPECTED_CHAR;
	lex->done = true;
	return false;
}

#ifdef TESTING
int main(int argc, char *argv[]) {
	if(argc != 2) {
		return EXIT_FAILURE;
	}
	lexer_t lex = {
		.text = argv[1],
		.tok  = (token_t){ .line = 1 },
		.err  = ERR_NONE,
		.done = false
	};
	char buf[128];
	while(next_token(&lex)) {
		sprint_token(buf, lex.tok);
		printf("%s\n", buf);
	}
	printf("\n");
	printf("lexer error: %d\n", lex.err);
	return EXIT_SUCCESS;
}
#endif /* TESTING */
