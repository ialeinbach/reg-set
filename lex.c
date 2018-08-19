#include <stdio.h>
#ifdef TESTING
	#include <stdlib.h>
	#include "tok.h"
#endif
#include "lex.h"
#include "stat.h"

#define INSTR_LEN_MAX 3

const char RGSTR_PREFIX = '@';
const int LEX_FN_COUNT = 4;

int is_digit(char ch) {
	return ch >= '0' && ch <= '9';
}

int is_ident(char ch) {
	return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch == '_';
}

int tokenize(lexer_t *lex, toktype_t typ, int len) {
	lex->tok.data = lex->src;
	lex->tok.len  = len;
	lex->tok.type = typ;

	lex->src += len;
	return len;
}

// lexfn_t
int lex_numbr(lexer_t *lex) {
	char *end = lex->src;
	if(!is_digit(*end)) {
		return 0;
	}
	while(is_digit(*++end));
	return tokenize(lex, NUMBR, end - lex->src);
}

// lexfn_t
int lex_rgstr(lexer_t *lex) {
	if(*lex->src != RGSTR_PREFIX) {
		return 0;
	}
	char *start = lex->src++;
	int c = lex_numbr(lex) + 1;
	lex->src = start;
	return tokenize(lex, c > 1 ? RGSTR : ERROR, c);
}

// lexfn_t
int lex_instr(lexer_t *lex) {
	char *end = lex->src;
	if(!is_ident(*end)) {
		return 0;
	}
	int c = 1;
	do {
		if(!is_ident(*++end)) {
			return tokenize(lex, INSTR, c);
		}
	} while(++c <= INSTR_LEN_MAX);
	lex->stat = STAT_INSTR_TOO_LONG;
	return tokenize(lex, ERROR, c);
}

// lexfn_t
int lex_delim(lexer_t *lex) {
	return *lex->src == ';' ? tokenize(lex, DELIM, 1) : 0;
}

// naming?
lexfn_t* lexfn() {
	static lexfn_t *fn = NULL;
	if(fn == NULL) {
		fn = (lexfn_t*)malloc(sizeof(lexfn_t) * LEX_FN_COUNT);
		fn[0] = lex_rgstr;
		fn[1] = lex_instr;
		fn[2] = lex_numbr;
		fn[3] = lex_delim;
	}
	return fn;
}

// lexfn_t
int skip_wspace(lexer_t *lex) {
	char *start = lex->src;
	for(;;) {
		switch(*lex->src) {
			case '\n':
				++lex->tok.line;
			case '\t':
			case ' ':
				++lex->src;
				continue;
		default:
				return lex->src - start;
		}
	}
}

int next_token(lexer_t *lex, token_t *tok) {
	char *start = lex->src;
	skip_wspace(lex);
	if(*lex->src == '\0') {
		lex->stat = STAT_DONE;
		tokenize(lex, DELIM, 0);
		*tok = lex->tok;
		return lex->src - start;
	}
	int read;
	lexfn_t *target = lexfn();
	for(int i = 0; i < LEX_FN_COUNT; ++i) {
		if((read = target[i](lex)) > 0) {
			*tok = lex->tok;
			return lex->src - start;
		}
	}
	lex->stat = STAT_UNEXPECTED_CHAR;
	return lex->src - start;
}

#ifdef TESTING
int main(int argc, char *argv[]) {
	if(argc != 2) {
		return EXIT_FAILURE;
	}
	lexer_t lex = {
		.src = argv[1],
		.tok = (token_t){
			.line = 1
		},
		.stat = 0
	};
	token_t tok;
	char *buf = (char*)malloc(sizeof(char) * 1024);
	while(lex.stat == 0) {
		next_token(&lex, &tok);
		printf("  ");
		sprint_token(buf, tok);
		printf("%s\n", buf);
	}
	printf("STATUS: %d\n", lex.stat);
	return EXIT_SUCCESS;
}
#endif
#undef RGSTR_PREFIX

