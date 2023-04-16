@ECHO OFF

SET CC=clang
SET FLAGS=-Wall -Wextra -Wpedantic -Werror -std=c11

%CC% -c %FLAGS% -o main.o main.c
%CC% -o main main.o

DEL *.o

main