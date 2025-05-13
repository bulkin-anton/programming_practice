CFLAGS=-O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -Wcast-qual -Wwrite-strings -std=gnu11 -g -lm

solution: vector.o vector_iterator.o vectors.o xabrt.o

vector.h: vector.o

vector_iterator.h: vector_iterator.o

vectors.h: vectors.o

xabrt.h: xabrt.o

clean:
	rm -rf *.o solution

.PHONY: clean
