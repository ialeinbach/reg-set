#include <string.h>
#include <stdio.h>

#include "tok.h"

#define INSTR_LEN_MAX 32
#define INSTR_CNT_MAX 32
const int instr_len_max = INSTR_LEN_MAX;
const int instr_cnt_max = INSTR_CNT_MAX;
char _lookup[INSTR_CNT_MAX][INSTR_LEN_MAX];
#undef INSTR_LEN_MAX
#undef INSTR_CNT_MAX

// assumes _lookup is alphabetically sorted
toktype_t lookup(char *instr, int len) {
	int cmp, curr = instr_cnt_max / 2;
	for(int jump = curr / 2; jump > 0; jump /= 2) {
		if(_lookup[curr] == 0) {
			curr -= jump;
			continue;
		}
		cmp = strncmp(instr, _lookup[curr], len);
		if(cmp == 0) {
			return INSTR;
		}
		curr += (cmp > 0) ? jump : -jump;
	}
	return ERROR;
}

const char* tok_names(toktype_t type) {
	switch(type) {
		case INSTR:  return "INSTR";
		case REGSTR: return "REGSTR";
		case NUMBER: return "NUMBER";
		case WSPACE: return "WSPACE";
		case ERROR:  return "ERROR";
		default:     return "UNKNOWN";
	}
}

void tok_print(token_t tok) {
	printf("[Line %d] %s: \"%.*s\"\n", tok.line, tok_names(tok.type), tok.len, tok.lexeme);
}

