#include "unittest.h"
#include "dominion.h"

// AMBASSADOR UNIT TESTS

int main() {
    // Set the hand
    int cards[10] = { ambassador, adventurer, council_room, feast, mine, 
                      remodel, smithy, village, baron, minion };
    struct gameState *state = newGame();
    int result;

    printf("=== AMBASSADOR UNIT TESTS\n");

    // Initialize game state for first round of tests
    initializeGame(2, cards, 1, state);
    state->hand[0][0]          = ambassador;
    state->hand[0][1]          = copper;
    state->handCount[0]        = 2;
    state->supplyCount[copper] = 0;
    state->numPlayers          = 1;

    // Test ambassador function
    result = ambassadorCardEffect(1, 1, 0, state, state->whoseTurn);

    // Run first set of tests
    describe("When a single card is selected in a one player game");
    assert("it returns successfully",
            result == 0);
    assert("it is sent to supply",
            state->supplyCount[copper] == 1);
    assert("it does not go to player's discard",
            state->discardCount[0] == 0);
    assert("it does not stay in player's hand",
            count_discard(copper, 0, state) == 0);

    // Reset the game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]          = ambassador;
    state->hand[0][1]          = copper;
    state->handCount[0]        = 2;
    state->supplyCount[copper] = 0;

    result = ambassadorCardEffect(1, 1, 0, state, state->whoseTurn);

    // Run second set of tests
    describe("When a single card is selected in a two player game");
    assert("it returns successfully",
            result == 0);
    assert("it sends one card to the other player",
            state->discardCount[1] == 1);
    assert("it does not leave a card in the supply",
            state->supplyCount[copper] == 0);

    // Reset the game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]          = ambassador;
    state->hand[0][1]          = copper;
    state->hand[0][2]          = copper;
    state->handCount[0]        = 3;
    state->supplyCount[copper] = 0;

    result = ambassadorCardEffect(1, 2, 0, state, state->whoseTurn);

    // Run second set of tests
    describe("When two cards are selected in a two player game");
    assert("it returns successfully",
            result == 0);
    assert("it sends one card to the other player",
            state->discardCount[1] == 1);
    assert("it leaves one card in the supply",
            state->supplyCount[copper] == 1);

    // Reset the game state
    initializeGame(2, cards, 1, state);
    state->hand[0][0]          = ambassador;
    state->hand[0][1]          = copper;
    state->hand[0][2]          = copper;
    state->handCount[0]        = 3;
    state->supplyCount[copper] = 0;

    // Run third set of tests
    describe("When attempting to discard incorrectly");
    result = ambassadorCardEffect(1, -1, 0, state, state->whoseTurn);
    assert("it does not allow discarding negative cards",
            result == -1);
    result = ambassadorCardEffect(1, 3, 0, state, state->whoseTurn);
    assert("it does not allow discarding more than 2 cards",
            result == -1);
    result = ambassadorCardEffect(0, 1, 0, state, state->whoseTurn);
    assert("it does not allow discarding the Ambassador card in play",
            result == -1);

    return 0;
}