#include "lex.h"

char src[] = "1234    hello  4";

lexer_t lexer = {
	.src   = src,
	.ahead = 0,
	.line  = 1
};

int main() {
	tok_print(next(&lexer));
	tok_print(next(&lexer));
	tok_print(next(&lexer));
	return 0;
}

