#include "unittest.h"
#include "dominion.h"

// MINE UNIT TESTS

int main() {
    // Set the hand
    int cards[10] = { ambassador, adventurer, council_room, feast, mine, 
                      remodel, smithy, village, baron, minion };
    struct gameState *state = newGame();
    int result;

    printf("=== MINE UNIT TESTS\n");

    // Initialize game state for first round of tests
    initializeGame(2, cards, 1, state);
    state->hand[0][0]   = mine;
    state->hand[0][1]   = copper;
    state->handCount[0] = 2;

    // Run mine function
    result = card_effect_mine(1, silver, 0, state);

    describe("When player trashes a treasure and buys one worth 3 more");
    assert("it returns successfully",
            result == 0);
    assert("it adds more expensive treasure to hand",
            count_hand(silver, 0, state) == 1);
    assert("it removes trashed treasure from hand",
            count_hand(copper, 0, state) == 0);
    assert("it does not send trashed treasure to discard",
            count_discard(copper, 0, state) == 0);
    assert("it discards mine card",
            count_hand(mine, 0, state) == 1);

    // Reset game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]        = mine;
    state->hand[0][1]        = copper;
    state->handCount[0]      = 2;
    state->supplyCount[gold] = 1;

    // Run mine function
    result = card_effect_mine(1, gold, 0, state);

    describe("When player trashes a treasure and buys one worth >3 more");
    assert("it returns unsuccessfully",
            result == -1);
    assert("it does not add more expensive treasure to hand",
            count_hand(gold, 0, state) == 0);
    assert("it does not remove more expensive treasure from supply",
            state->supplyCount[gold] == 1);
    assert("it does not trash treasure from hand",
            count_hand(copper, 0, state) == 1);
    assert("it does not discard mine card",
            count_hand(mine, 0, state) == 1);

    // Reset game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]   = mine;
    state->hand[0][1]   = gold;
    state->handCount[0] = 2;

    // Run mine function
    result = card_effect_mine(1, silver, 0, state);

    describe("When player trashes a treasure and buys one worth less");
    assert("it returns successfully",
            result == 0);
    assert("it adds less expensive treasure to hand",
            count_hand(silver, 0, state) == 1);
    assert("it removes trashed treasure from hand",
            count_hand(gold, 0, state) == 0);

    // Reset game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]         = mine;
    state->hand[0][1]         = gold;
    state->handCount[0]       = 2;
    state->supplyCount[feast] = 1;

    // Run mine function
    result = card_effect_mine(1, feast, 0, state);

    describe("When player trashes a treasure and buys a non-treasure card");
    assert("it returns unsuccessfully",
            result == -1);
    assert("it does not add non-treasure to hand",
            count_hand(feast, 0, state) == 0);
    assert("it does not remove non-treasure from supply",
            state->supplyCount[feast] == 1);
    assert("it does not trash treasure from hand",
            count_hand(gold, 0, state) == 1);
    assert("it does not discard mine card",
            count_hand(mine, 0, state) == 1);

    // Reset game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]          = mine;
    state->hand[0][1]          = feast;
    state->handCount[0]        = 2;
    state->supplyCount[copper] = 1;

    // Run mine function
    result = card_effect_mine(1, copper, 0, state);

    describe("When player trashes a non-treasure card");
    assert("it returns unsuccessfully",
            result == -1);
    assert("it does not add treasure to hand",
            count_hand(copper, 0, state) == 0);
    assert("it does not remove treasure from supply",
            state->supplyCount[copper] == 1);
    assert("it does not trash non-treasure from hand",
            count_hand(feast, 0, state) == 1);
    assert("it does not discard mine card",
            count_hand(mine, 0, state) == 1);

    // Reset game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]          = mine;
    state->hand[0][1]          = copper;
    state->handCount[0]        = 2;
    state->supplyCount[silver] = 0;

    // Run mine function
    result = card_effect_mine(1, silver, 0, state);

    describe("When player attempts to buy a treasure with an empty supply");
    assert("it returns unsuccessfully",
            result == -1);
    assert("it does not add treasure to hand",
            count_hand(silver, 0, state) == 0);
    assert("it does not trash treasure from hand",
            count_hand(copper, 0, state) == 1);
    assert("it does not discard mine card",
            count_hand(mine, 0, state) == 1);

    return 0;
}