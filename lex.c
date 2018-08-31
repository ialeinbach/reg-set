#include <stdbool.h>

#ifdef TESTING
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif /* TESTING */

#include "tok.h"
#include "lex.h"
#include "stat.h"

const int LEX_FN_COUNT = 4;

int expected(toktype_t type) {
	switch(type) {
		case NUMBR: return STAT_EXPECTED_NUMBR;
		case RGSTR: return STAT_EXPECTED_RGSTR;
		case IDENT: return STAT_EXPECTED_IDENT;
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
				++lex->buf.line;
			case '\t':
			case ' ':
				++lex->text;
				continue;
			default:
				return lex->text - start;
		}
	}
}

int check_lexer(lexer_t *lex) {
	int stat = lex->stat;
	if(stat != STAT_OK && stat != STAT_DONE) {
		stat = STAT_LEXER_FAILURE;
	}
	return stat;
}

void tokenize(lexer_t *lex, toktype_t type, int len) {
	// tokenize into buf
	lex->buf.data = lex->text;
	lex->buf.type = type;
	lex->buf.len  = len;

	// advance lexer
	lex->text += len;
}

bool lex_sequence(lexer_t *lex, char prefix, bool (*valid)(char), toktype_t type, int max) {
	if(*lex->text != prefix) {
		return false;
	}
	char *ch = ++lex->text;
	if(!valid(*ch)) {
		--lex->text;
		lex->stat = expected(type);
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

// lexfn_t
bool lex_numbr(lexer_t *lex) {
	return lex_sequence(lex, '#', is_digit, NUMBR, 0);
}

// lexfn_t
bool lex_rgstr(lexer_t *lex) {
	return lex_sequence(lex, '@', is_digit, RGSTR, 0);
}

// lexfn_t
bool lex_instr(lexer_t *lex) {
	return lex_sequence(lex, '_', is_ident, IDENT, 0);
}

// lexfn_t
bool lex_delim(lexer_t *lex) {
	bool found = *lex->text == ';';
	if(found) {
		tokenize(lex, DELIM, 1);
	}
	return found;
}

lexfn_t *get_lexfn() {
	// order defines precedence
	static lexfn_t lexfn[] = {
		lex_instr,
		lex_rgstr,
		lex_numbr,
		lex_delim
	};
	return lexfn;
}

int next_token(lexer_t *lex, token_t *tok) {
	if(lex->stat != STAT_OK) {
		return 0;
	}
	int len = skip_whitespace(lex);
	if(*lex->text == '\0') {
		lex->stat = STAT_DONE;
		tokenize(lex, DELIM, 0);
		goto DONE;
	}
	lexfn_t *lexfn = get_lexfn();
	for(int i = 0; i < LEX_FN_COUNT; ++i) {
		if((*lexfn++)(lex)) {
			len += lex->buf.len;
			goto DONE;
		}
	}
	lex->stat = STAT_UNEXPECTED_CHAR;
	tokenize(lex, ERROR, 1);
DONE:
	*tok = lex->buf;
	return len;
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
	token_t tok;
	char buf[1024] = { '[', ' ', ']' };
	while(lex.stat == STAT_OK) {
		next_token(&lex, &tok);
		sprintf(buf+3, "%d", lex.stat < 10 ? lex.stat : -1);
		strncpy(buf+1, buf+3, 1); // single digit or '-'
		sprint_token(buf+3, tok);
		printf("%s\n", buf);
	}
	return EXIT_SUCCESS;
}
#endif

