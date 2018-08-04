#!/bin/bash

echo ""
echo ".-----."
echo "|Setup|"
echo "'-----'"
echo ""

./tidy.sh

echo -n "Compiling tok.c ... " && gcc -c -DTESTING tok.c && echo "DONE" && \
echo -n "Compiling lex.c ... " && gcc -c -DTESTING lex.c && echo "DONE" && \
echo -n "Linking ... "         && gcc lex.o tok.o        && echo "DONE"

echo ""
echo ".-----."
echo "|Tests|"
echo "'-----'"
echo ""

for testcase in "$@"; do
	echo "INPUT: \"$testcase\""
	./a.out "$testcase"
	echo ""
done

