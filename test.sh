#!/bin/bash

./tidy.sh

echo ""

echo -n "Compiling tok.c ... " && gcc -c tok.c -o tok.o && echo "DONE"

echo -n "Compiling lex.c ... " && gcc -c -DTESTING lex.c -o test_lex.o && gcc -c lex.c -o lex.o && echo "DONE"
echo -n "Compiling par.c ... " && gcc -c -DTESTING par.c -o test_par.o && gcc -c par.c -o par.o && echo "DONE"

echo ""

echo -n "Building lexer tests ... "  && gcc test_lex.o       tok.o -o lex && echo "DONE"
echo -n "Building parser tests ... " && gcc test_par.o lex.o tok.o -o par && echo "DONE"

echo ""

echo -n "Running lexer and parser tests ... "

if [ "$#" -eq 0 ]; then
	echo "NONE"
	exit 1
else
	echo ""
fi

echo ""

i=0
for testcase in "$@"; do
	echo "[[ TEST $i ]]"
	echo ""
	echo "Input"
	echo "-----"
	echo "$testcase"
	echo ""
	echo "Tokens"
	echo "------"
	./lex "$testcase"
	echo ""
	echo "Statements"
	echo "----------"
	./par "$testcase"
	echo ""
	let "i+=1"
done

echo "DONE"
echo ""

