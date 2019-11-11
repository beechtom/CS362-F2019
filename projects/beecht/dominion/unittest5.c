#include "unittest.h"
#include "dominion.h"

// TRIBUTE UNIT TESTS

int main() {
    // Set the hand
    int cards[10] = { tribute, adventurer, council_room, feast, mine, 
                      remodel, smithy, village, baron, minion };
    struct gameState *state = newGame();
    int result;

    printf("=== TRIBUTE UNIT TESTS\n");

    // Initialize game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]      = tribute;
    state->handCount[0]    = 1;
    state->discardCount[1] = 0;
    state->deckCount[1]    = 0;

    // Run tribute function
    result = card_effect_tribute(state);

    describe("When next player has an empty deck and empty discard");
    assert("it returns unsuccessfully",
            result == -1);
    assert("it does not discard tribute",
            state->handCount[0] == 1);

    // Initialize game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]      = tribute;
    state->handCount[0]    = 1;
    state->discard[1][0]   = copper;
    state->discardCount[1] = 1;
    state->deckCount[1]    = 0;

    // Run tribute function
    result = card_effect_tribute(state);

    describe("When next player has an empty deck");
    assert("it shuffles the discard and puts it in the deck",
            state->deckCount[1] == 1 && state->deck[1][0] == copper);

    // Initialize game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]      = tribute;
    state->handCount[0]    = 1;
    state->deck[1][0]      = copper;
    state->deck[1][1]      = copper;
    state->deckCount[1]    = 2;
    state->discardCount[1] = 0;
    state->numActions      = 0;
    state->coins           = 0;

    // Run tribute function
    result = card_effect_tribute(state);

    describe("When next player draws two identical treasure cards");
    assert("it returns successfully",
            result == 0);
    assert("it removes both cards from the next player's deck",
            state->deckCount[1] == 0);
    assert("it discards both treasure cards",
            state->discardCount[1] == 2 && count_discard(copper, 1, state) == 2);
    assert("it discards the tribute card",
            state->discardCount[0] == 0 && count_discard(tribute, 0, state));
    assert("it ignores the second treasure and only gives +2 coins",
            state->coins == 2);

    // Initialize game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]      = tribute;
    state->handCount[0]    = 1;
    state->deck[1][0]      = curse;
    state->deck[1][1]      = estate;
    state->deckCount[1]    = 2;
    state->discardCount[1] = 0;
    state->numActions      = 0;
    state->coins           = 0;

    // Run tribute function
    result = card_effect_tribute(state);

    describe("When next player draws two different victory cards");
    assert("it returns successfully",
            result == 0);
    assert("it removes both victory cards from the next player's deck",
            state->deckCount[1] == 0);
    assert("it discards both victory cards",
            state->discardCount[1] == 2 &&
            count_discard(curse, 1, state) == 1 &&
            count_discard(estate, 1, state) == 1);
    assert("it gives the player +4 cards",
            state->handCount[0] == 4);

    // Initialize game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]      = tribute;
    state->handCount[0]    = 1;
    state->deck[1][0]      = feast;
    state->deck[1][1]      = mine;
    state->deckCount[1]    = 2;
    state->discardCount[1] = 0;
    state->numActions      = 0;
    state->coins           = 0;

    // Run tribute function
    result = card_effect_tribute(state);

    describe("When next player draws two different action cards");
    assert("it returns successfully",
            result == 0);
    assert("it removes both action cards from the next player's deck",
            state->deckCount[1] == 0);
    assert("it discards both action cards",
            state->discardCount[1] == 2 &&
            count_discard(feast, 1, state) == 1 &&
            count_discard(mine, 1, state) == 1);
    assert("it gives the player +4 actions",
            state->numActions == 4);

    // Initialize game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]      = tribute;
    state->handCount[0]    = 1;
    state->deck[0][0]      = copper;
    state->deck[0][1]      = copper;
    state->deckCount[0]    = 2;
    state->deck[1][0]      = feast;
    state->deck[1][1]      = copper;
    state->deckCount[1]    = 2;
    state->discardCount[1] = 0;
    state->numActions      = 0;
    state->coins           = 0;

    // Run tribute function
    result = card_effect_tribute(state);

    describe("When next player draws two different types of cards");
    assert("it returns successfully",
            result == 0);
    assert("it does not affect the player's deck",
            state->deckCount[0] == 2);
    assert("it removes both cards from the next player's deck",
            state->deckCount[1] == 0);
    assert("it does not discard cards from the player's deck",
            state->discardCount[0] == 0);
    assert("it discards both cards",
            state->discardCount[1] == 2 &&
            count_discard(feast, 1, state) == 1 &&
            count_discard(copper, 1, state) == 1);
    assert("it gives the player +2 coins and +2 actions",
            state->coins == 2 && state->numActions == 2);

    return 0;
}