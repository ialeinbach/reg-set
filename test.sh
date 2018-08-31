#!/bin/bash

echo ""

./tidy.sh

echo ""

echo -n "Compiling tok.c ... " && gcc -c -DTESTING tok.c -o test_tok.o && gcc -c tok.c -o tok.o && echo "DONE"
echo -n "Compiling lex.c ... " && gcc -c -DTESTING lex.c -o test_lex.o && gcc -c lex.c -o lex.o && echo "DONE"
echo -n "Compiling sem.c ... " && gcc -c -DTESTING sem.c -o test_sem.o && gcc -c sem.c -o sem.o && echo "DONE"

echo ""

echo -n "Building tok ... " && gcc             test_tok.o -o tok && echo "DONE"
echo -n "Building lex ... " && gcc       test_lex.o tok.o -o lex && echo "DONE"
echo -n "Building sem ... " && gcc test_sem.o lex.o tok.o -o sem && echo "DONE"
echo ""

echo -n "Running lex and sem tests ... "

if [ "$#" -eq 0 ]; then
	echo -n "NONE"
fi

echo ""
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
	./sem "$testcase"
	let "i+=1"
done

if [ "$#" -ne 0 ]; then
	echo "DONE"
	echo ""
fi

./tidy.sh

echo ""
