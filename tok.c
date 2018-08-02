#include <string.h>
#include <stdio.h>

#include "tok.h"

#define IDENT_MAX 32
#define INSTR_MAX 32
const int ident_len_max = IDENT_MAX;
const int instr_cnt_max = INSTR_MAX;
char _lookup[INSTR_MAX][IDENT_MAX];
#undef IDENT_MAX
#undef INSTR_MAX

// assumes _lookup is alphabetically sorted
toktype_t lookup(char *ident, int len) {
	int cmp, curr = instr_cnt_max / 2;
	for(int jump = curr / 2; jump > 0; jump /= 2) {
		if(_lookup[curr] == 0) {
			curr -= jump;
			continue;
		}
		cmp = strncmp(ident, _lookup[curr], len);
		if(cmp == 0) {
			return INSTR;
		}
		curr += (cmp > 0) ? jump : -jump;
	}
}

const char* tok_names(toktype_t type) {
	switch(type) {
		case INSTR:   return "INSTR";
		case IDENT:   return "IDENT";
		case REGSTR:  return "REGSTR";
		case NUMBER:  return "NUMBER";
		case WSPACE:  return "WSPACE";
		case NEWLINE: return "NEWLINE";
		case ERROR:   return "ERROR";
		default:      return "UNKNOWN";
	}
}

void tok_print(token_t tok) {
	printf("[Line %d] %s: \"%.*s\"\n", tok.line, tok_names(tok.type), tok.len, tok.lexeme);
}

