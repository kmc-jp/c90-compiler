#!/bin/bash

NAME=${1%.c}
./kmc89 ${NAME}.c
llvm-dis ${NAME}.bc
llc -filetype=obj ${NAME}.ll
gcc -c print.c
gcc ${NAME}.o print.o -o ${NAME}.out
