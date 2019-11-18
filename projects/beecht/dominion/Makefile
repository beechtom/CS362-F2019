CFLAGS= -Wall -fpic -coverage -lm -std=c99
OUTFILE = randomtestresults.out

randomtestresults: test1 test2 test3
	@ echo "[BUILD] Compiling random tests . . ."
	@ echo "[TESTS] Running random tests . . ."
	@ > $(OUTFILE)
	@ ./test1 >> $(OUTFILE)
	@ ./test2 >> $(OUTFILE)
	@ ./test3 >> $(OUTFILE)
	@ echo "[GCOV]  Running gcov . . ."
	@ gcov -b -f dominion.c >> $(OUTFILE)
	@ echo "[END]   Completed! View $(OUTFILE) for test results."

test1: dominion.o randomtestcard1.c
	@ gcc -o test1 randomtestcard1.c -g dominion.o rngs.o -DTEST_COUNT=25000 $(CFLAGS)

test2: dominion.o randomtestcard2.c
	@ gcc -o test2 randomtestcard2.c -g dominion.o rngs.o -DTEST_COUNT=25000 $(CFLAGS)

test3: dominion.o randomtestcard3.c
	@ gcc -o test3 randomtestcard3.c -g dominion.o rngs.o -DTEST_COUNT=25000 $(CFLAGS)

rngs.o: rngs.h rngs.c
	@ gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	@ gcc -c dominion.c -g  $(CFLAGS)

all: unittestresults 

clean:
	rm -f *.o  *.gcov *.gcda *.gcno test1 test2 test3
