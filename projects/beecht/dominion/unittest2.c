#include "unittest.h"
#include "dominion.h"

// BARON UNIT TESTS

int main() {
    // Set the hand
    int cards[10] = { ambassador, adventurer, council_room, feast, mine, 
                      remodel, smithy, village, baron, minion };
    struct gameState *state = newGame();
    int result;

    printf("=== BARON UNIT TESTS\n");

    // Initialize game state for first round of tests
    initializeGame(2, cards, 1, state);
    state->numBuys             = 0;
    state->coins               = 0;
    state->hand[0][0]          = baron;
    state->hand[0][1]          = estate;
    state->handCount[0]        = 2;

    // Run baron function
    result = card_effect_baron(1, state);

    // Run first set of tests
    describe("When player uses the Baron card");
    assert("it gives the player an additional buy",
            state->numBuys == 1);
    describe("When player has an estate and chooses to discard");
    assert("it returns successfully",
            result == 0);
    assert("it sends Estate card to discard",
            count_discard(estate, 0, state) == 1);
    assert("it removes Estate card from player's hand",
            count_hand(estate, 0, state) == 0);
    assert("it gives the player +4 coins",
            state->coins == 4);

    // Reset game state
    initializeGame(2, cards, 1, state);
    state->coins               = 0;
    state->hand[0][0]          = baron;
    state->hand[0][1]          = estate;
    state->handCount[0]        = 2;

    // Run baron function
    result = card_effect_baron(0, state);

    // Run second set of tests
    describe("When player has an Estate and chooses not to discard");
    assert("it returns successfully",
            result == 0);
    assert("it does not give player coins",
            state->coins == 0);
    assert("it results in the player gaining an Estate",
            count_discard(estate, 0, state) == 1);
    assert("it does not discard the player's Estate",
            count_hand(estate, 0, state) == 1);
    
    // Reset game state
    initializeGame(2, cards, 1, state);
    state->coins               = 0;
    state->hand[0][0]          = baron;
    state->handCount[0]        = 1;

    // Run baron function
    result = card_effect_baron(1, state);

    // Run third set of tests
    describe("When player does not have an Estate and chooses to discard");
    assert("it does not return successfully",
            result == -1);
    assert("it does not give player coins",
            state->coins == 0);
    assert("it results in the player gaining an Estate",
            count_discard(estate, 0, state) == 1);

    return 0;
}