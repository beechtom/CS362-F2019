#include <stdbool.h>
#include <stdio.h>
#include "dominion.h"

void describe(char* description) {
    printf("%s\n", description);
}

void assert(char* test, bool pass) {
    if (pass)
        printf("\t\033[32m%s\033[0m\n", test);
    else
        printf("\t\033[31m%s\033[0m\n", test);
}

int count_discard(int card, int player, struct gameState* state) {
    int count = 0;
    for (int i = 0; i < state->discardCount[player]; i++)
        if (state->discard[player][i] == card)
            count++;
    return count;
}

int count_hand(int card, int player, struct gameState* state) {
    int count = 0;
    for (int i = 0; i < state->handCount[player]; i++)
        if (state->hand[player][i] == card)
            count++;
    return count;
}
