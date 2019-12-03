CC = gcc
TESTEXT = c
CFLAGS = -Wall -fpic -coverage -lm -std=c99

OUTFILE = unittestresults.out

TESTDIR = tests
INCDIR = .
EXECDIR = execs

TESTS = $(shell find $(TESTDIR) -type f -name '*.$(TESTEXT)')
EXECS = $(TESTS:$(TESTDIR)/%.$(TESTEXT)=$(EXECDIR)/%)

unittestresults: $(EXECS)
	@ echo "[RUN]   Running all tests . . ."
	@ > $(OUTFILE)
	@ for f in $(shell ls ${EXECDIR}); do $(EXECDIR)/$$f >> $(OUTFILE); done
	@ echo "[GCOV]  Running gcov . . ."
	@ gcov -b -f dominion.c >> $(OUTFILE)
	@ echo "[END]   Completed! View $(OUTFILE) for test results."

$(EXECDIR)/%: $(TESTDIR)/%.$(TESTEXT) dominion.o
	@ mkdir -p $(EXECDIR)
	@ echo [BUILD] Compiling $< . . .
	@ $(CC) -I $(INCDIR) -g dominion.o rngs.o $(CFLAGS) -o $@ $<

rngs.o: rngs.h rngs.c
	@ $(CC) -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	@ $(CC) -c dominion.c -g  $(CFLAGS)

clean:
	rm -rf $(EXECDIR) $(OUTFILE) *.o *.gcov *.gcda *.gcno
