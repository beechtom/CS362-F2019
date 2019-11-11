CFLAGS= -Wall -fpic -coverage -lm -std=c99
OUTFILE = unittestresults.out

unittestresults: test1 test2 test3 test4 test5
	@ echo "[BUILD] Compiling unit tests . . ."
	@ echo "[TESTS] Running unit tests . . ."
	@ > $(OUTFILE)
	@ ./test1 >> $(OUTFILE)
	@ ./test2 >> $(OUTFILE)
	@ ./test3 >> $(OUTFILE)
	@ ./test4 >> $(OUTFILE)
	@ ./test5 >> $(OUTFILE)
	@ echo "[GCOV]  Running gcov . . ."
	@ gcov -b -f dominion.c >> $(OUTFILE)
	@ echo "[END]   Completed! View $(OUTFILE) for test results."

test1: dominion.o unittest1.c
	@ gcc -o test1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

test2: dominion.o unittest2.c
	@ gcc -o test2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

test3: dominion.o unittest3.c
	@ gcc -o test3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

test4: dominion.o unittest4.c
	@ gcc -o test4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

test5: dominion.o unittest5.c
	@ gcc -o test5 unittest5.c -g dominion.o rngs.o $(CFLAGS)

rngs.o: rngs.h rngs.c
	@ gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	@ gcc -c dominion.c -g  $(CFLAGS)

all: unittestresults 

clean:
	rm -f *.o  *.gcov *.gcda *.gcno test1 test2 test3 test4 test5
