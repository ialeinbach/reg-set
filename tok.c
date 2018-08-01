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

void tok_print(token_t tok) {
	printf("[Line %d] \"%.*s\"\n", tok.line, tok.len, tok.lexeme);
}
