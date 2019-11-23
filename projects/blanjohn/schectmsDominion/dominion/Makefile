CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittest: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 
	gcov unittest1.c -b -f >> unittestresult.out
	cat unittest1.c.gcov >> unittestresult.out

	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 
	gcov unittest2.c -b -f >> unittestresult.out
	cat unittest2.c.gcov >> unittestresult.out

	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 
	gcov unittest3.c -b -f >> unittestresult.out
	cat unittest3.c.gcov >> unittestresult.out

	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 
	gcov unittest4.c -b -f >> unittestresult.out
	cat unittest4.c.gcov >> unittestresult.out

	gcc -o unittest5 -g unittest5.c dominion.o rngs.o $(CFLAGS)
	./unittest5 
	gcov unittest5.c -b -f >> unittestresult.out
	cat unittest5.c.gcov >> unittestresult.out

randomtest: randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o rngs.o

	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2
	gcov randomtestcard2.c -b -f >> randomtestresult.out
	cat randomtestcard2.c.gcov >> randomtestresult.out

	gcc -o randomtestcard3 -g randomtestcard3.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard3
	gcov randomtestcard3.c -b -f >> randomtestresult.out
	cat randomtestcard3.c.gcov >> randomtestresult.out

	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1
	gcov randomtestcard1.c -b -f >> randomtestresult.out
	cat randomtestcard1.c.gcov >> randomtestresult.out


runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
