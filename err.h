#ifndef _ERR_H
#define _ERR_H

#define ERR_NONE              0

/* LEXER */
#define ERR_LEXER_FAILURE     1
#define ERR_UNEXPECTED_CHAR   2
#define ERR_EXPECTED_RGSTR    3
#define ERR_EXPECTED_IDENT    4
#define ERR_EXPECTED_NUMBR    5

/* PARSER */
#define ERR_PARSER_FAILURE    6
#define ERR_EXPECTED_INSTR    7
#define ERR_INVALID_ARG_TYPE  8

/* SEMANTICS */
#define ERR_SEMANTIC_FAILURE  9
#define ERR_UNDEFINED_INSTR  10

#endif /* _ERR_H */
