
CC = clang
OUT = bin/clpac

build: src/*.c
	${CC} $^ -o ${OUT}
