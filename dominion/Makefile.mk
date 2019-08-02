CFLAGS= -Wall -fpic -coverage -lm -std=c99 -ftest-coverage -fprofile-arcs

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest5.c randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.c rngs.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	unittest1 >> unittest1results.out
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	unittest2 >> unittest2results.out
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
	unittest3 >> unittest3results.out
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
	unittest4 >> unittest4results.out
	gcc -o unittest5 unittest5.c -g dominion.o rngs.o $(CFLAGS)
	unittest5 >> unittest5results.out
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	cardtest1 >> cardtest1results.out
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	cardtest2 >> cardtest2results.out
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	cardtest3 >> cardtest3results.out
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	cardtest4 >> cardtest4results.out
	gcc -o cardtest5 cardtest5.c -g dominion.o rngs.o $(CFLAGS)
	cardtest5 >> cardtest5results.out
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)
	randomtestcard1 >> randomtest1results.out
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
	randomtestcard2 >> randomtest2results.out
	gcc -o randomtestcard3 randomtestcard3.c -g dominion.o rngs.o $(CFLAGS)
	randomtestcard3 >> randomtest3results.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
