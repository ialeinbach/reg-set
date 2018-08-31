#include <stdio.h>
#include <string.h>

#ifdef TESTING
#include <stdlib.h>
#endif /* TESTING */

#include "tok.h"

int sprint_token(char *str, token_t tok) {
	char *s = str;
	s += sprintf(s, "[Line %d] ", tok.line);
	s += sprint_toktype(s, tok.type);
	s += sprintf(s, " \"%.*s\"", tok.len, tok.data);
	*s++ = '\0';
	return s - str;
}

int sprint_toktype(char *str, toktype_t typ) {
	switch(typ) {
		case IDENT: strncpy(str, "IDENT", 5); return 5;
		case RGSTR: strncpy(str, "RGSTR", 5); return 5;
		case NUMBR: strncpy(str, "NUMBR", 5); return 5;
		case DELIM: strncpy(str, "DELIM", 5); return 5;
		case ERROR: strncpy(str, "ERROR", 5); return 5;
		default:    return 0;
	}
}

#ifdef TESTING
int main(int argc, char *argv[]) {
	printf("No tests written.\n");
	return EXIT_SUCCESS;
}
#endif /* TESTING */

