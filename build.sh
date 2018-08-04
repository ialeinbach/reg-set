#!/bin/bash

./tidy.sh

echo -n "Compiling tok.c ... " && gcc -c tok.c -o tok.o && echo "DONE" && \
echo -n "Compiling lex.c ... " && gcc -c lex.c -o lex.o && echo "DONE"

