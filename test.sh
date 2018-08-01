#!/bin/bash

echo ""
echo ".-----."
echo "|Setup|"
echo "'-----'"
echo ""

./tidy.sh

echo -n "Compiling tok.c ... "      && gcc -c tok.c               && echo "DONE" && \
echo -n "Compiling tok_test.c ... " && :                          && echo "DONE" && \
echo -n "Compiling lex.c ... "      && gcc -c lex.c               && echo "DONE" && \
echo -n "Compiling lex_test.c ... " && gcc -c lex_test.c          && echo "DONE" && \
echo -n "Linking ... "              && gcc lex_test.o lex.o tok.o && echo "DONE" && \

echo ""
echo ".------."
echo "|Output|"
echo "'------'"
echo ""

./a.out

echo ""

