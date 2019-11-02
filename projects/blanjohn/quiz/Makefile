CFLAGS = -Wall -coverage -fpic -lm

all: testme run

testme:
	gcc -o testme testme.c -g $(CFLAGS)

run:
	./testme 

.PHONY: all

clean:
	rm -f testme *.gcno *.gcda	*.out