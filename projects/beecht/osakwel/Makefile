CFLAGS = -Wall -fpic -coverage -lm -std=c99
UNIT_OUTFILE = unittestresults.out
RAND_OUTFILE = randomtestresults.out

unit: test1 test2 test3 test4 test5
	@ echo "[BUILD] Compiling unit tests . . ."
	@ echo "[TESTS] Running unit tests . . ."
	@ > $(UNIT_OUTFILE)
	@ ./test1 >> $(UNIT_OUTFILE)
	@ ./test2 >> $(UNIT_OUTFILE)
	@ ./test3 >> $(UNIT_OUTFILE)
	@ ./test4 >> $(UNIT_OUTFILE)
	@ ./test5 >> $(UNIT_OUTFILE)
	@ echo "[GCOV]  Running gcov . . ."
	@ gcov -b -f dominion.c >> $(UNIT_OUTFILE)
	@ echo "[END]   Completed! View $(UNIT_OUTFILE) for test results."

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

random: random1 random2 random3
	@ echo "[BUILD] Compiling random tests . . ."
	@ echo "[TESTS] Running random tests . . ."
	@ > $(RAND_OUTFILE)
	@ ./random1 >> $(RAND_OUTFILE)
	@ ./random2 >> $(RAND_OUTFILE)
	@ ./random3 >> $(RAND_OUTFILE)
	@ echo "[GCOV]  Running gcov . . ."
	@ gcov -b -f dominion.c >> $(RAND_OUTFILE)
	@ rm -f *.gcov *.gcda *.gcno
	@ echo "[END]   Completed! View $(RAND_OUTFILE) for test results."

random1: dominion.o randomtestcard1.c
	@ gcc -o random1 randomtestcard1.c -g dominion.o rngs.o -DTEST_COUNT=25000 $(CFLAGS)

random2: dominion.o randomtestcard2.c
	@ gcc -o random2 randomtestcard2.c -g dominion.o rngs.o -DTEST_COUNT=25000 $(CFLAGS)

random3: dominion.o randomtestcard3.c
	@ gcc -o random3 randomtestcard3.c -g dominion.o rngs.o -DTEST_COUNT=25000 $(CFLAGS)

rngs.o: rngs.h rngs.c
	@ gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	@ gcc -c dominion.c -g  $(CFLAGS)

all: unittestresults 

clean:
	rm -f *.o  *.gcov *.gcda *.gcno test1 test2 test3 test4 test5 random1 random2 random3
