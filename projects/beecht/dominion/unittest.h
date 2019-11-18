#include <stdbool.h>
#include <stdio.h>
#include "dominion.h"

void describe(char* description) {
    printf("%s\n", description);
}

void assert(char* test, int fails) {
    if (fails)
        printf("\t\033[31m%s\033[0m\t\033[33m[%d failures]\033[0m\n", test, fails);
    else
        printf("\t\033[32m%s\033[0m\n", test);
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

int count_deck(int card, int player, struct gameState* state) {
    int count = 0;
    for (int i = 0; i < state->deckCount[player]; i++)
        if (state->deck[player][i] == card)
            count++;
    return count;
}

void initializeRandomGame(struct gameState *state, struct gameState *state_start, int test_card) {
    int players             = rand() % (MAX_PLAYERS - 1) + 2;
    int seed                = rand() % __INT_MAX__;
    int card_picked[24]     = {0};
    int cards[10];

    // Set the cards in the supply, but guarantee we have a Baron
    for (int j = 0; j < 9; j++) {
        int card;
        do {
            card = rand() % 18 + 6;
        } while(card_picked[card] > 0);
        cards[j] = card;
        card_picked[card]++;
    }
    cards[9] = baron;

    // Initialize the game
    initializeGame(players, cards, seed, state);

    // Draw each player's hand
    for (int j = 0; j < players; j++) {
        int hand = rand() % 10 + 1;
        for (int k = 0; k < hand; k++)
            state->hand[j][k] = rand() % 18 + 6;
        state->handCount[j] = hand;
    }

    // Fill each player's deck
    for (int j = 0; j < players; j++) {
        int deck = rand() % MAX_DECK;
        for (int k = 0; k < deck; k++)
            state->deck[j][k] = rand() % 18 + 6;
        state->deckCount[j] = deck;
    }

    // Set other state values ~randomly~
    state->numBuys    = rand() % 10;
    state->numActions = rand() % 10;
    state->coins      = rand() % 20;

    // Copy the state of the game
    memcpy(state_start, state, sizeof *state);
}

bool unless(bool statement) {
    return ! statement;
}