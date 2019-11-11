#include "unittest.h"
#include "dominion.h"

// MINION UNIT TESTS

int main() {
    // Set the hand
    int cards[10] = { ambassador, adventurer, council_room, feast, mine, 
                      remodel, smithy, village, baron, minion };
    struct gameState *state = newGame();
    int result;

    printf("=== MINION UNIT TESTS\n");

    // Initialize game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]   = minion;
    state->handCount[0] = 1;
    state->handCount[1] = 5;
    state->numActions   = 0;
    state->coins        = 0;

    for (int i = 0; i < state->handCount[1]; i++)
        state->hand[1][i] = copper;

    // Run minion function
    result = card_effect_minion(1, 0, 0, state);

    describe("When player chooses +2 coins");
    assert("it returns successfully",
            result == 0);
    assert("it gives player +1 action",
            state->numActions == 1);
    assert("it gives player +2 coins",
            state->coins == 2);
    assert("it discards minion card",
            count_hand(minion, 0, state) == 0 && count_discard(minion, 0, state) == 1);
    assert("it does not give player extra cards",
            state->handCount[0] == 0);
    assert("it does not cause other players to discard their hand",
            state->handCount[1] == 5 && state->discardCount[1] == 0);

    // Initialize game state
    initializeGame(3, cards, 1, state);
    state->hand[0][0]   = minion;
    state->hand[0][1]   = copper;
    state->handCount[0] = 2;
    state->handCount[1] = 5;
    state->handCount[2] = 4;
    state->numActions   = 0;

    for (int i = 0; i < state->handCount[1]; i++)
        state->hand[1][i] = copper;
    for (int i = 0; i < state->handCount[2]; i++)
        state->hand[2][i] = copper;

    // Run minion function
    result = card_effect_minion(0, 1, 0, state);

    describe("When player chooses +4 cards");
    assert("it returns successfully",
            result == 0);
    assert("it gives player +1 action",
            state->numActions == 1);
    assert("it sends player's remaining hand to discard",
            count_discard(copper, 0, state) == 1);
    assert("it gives player +4 cards",
            state->handCount[0] == 4);
    assert("it causes other players with >4 cards in hand to discard their hands",
            state->discardCount[1] == 5);
    assert("it causes other players with >4 cards in hand to draw 4 cards",
            state->handCount[1] == 4);
    assert("it does nothing to other players with <=4 cards in their hand",
            state->discardCount[2] == 0 && state->handCount[2] == 4);

    // Initialize game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]   = minion;
    state->handCount[0] = 1;

    // Run minion function
    result = card_effect_minion(0, 1, 0, state);

    assert("it gives player +4 cards even if their hand was empty",
            result == 0 && state->handCount[0] == 4);

    return 0;
}