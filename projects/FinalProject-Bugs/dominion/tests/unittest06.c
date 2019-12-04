#include "test_helpers.h"
#include "dominion.h"

// UNIT TESTS
// This file contains unit tests for the 'Feast coin count' bug

int main() {
    int cards[10] = { feast, mine, minion, tribute, ambassador,
                      smithy, steward, baron, remodel, adventurer };
    struct gameState *state = newGame();
    int result, player, card = feast, choice1, choice2 = 0, 
        choice3 = 0, handPos = 0, *bonus = NULL;

    title("BUG #6: Feast coin count");

    // Initialize game state
    initializeGame(2, cards, 1, state);
    player                      = state->whoseTurn;
    choice1                     = duchy;
    state->supplyCount[choice1] = 1;
    state->hand[player][0]      = card;
    state->handCount[player]    = 1;
    state->coins                = 0;
    state->discard[player][0]   = -1;
    state->discardCount[player] = 0;

    // Run the tests
    result = cardEffect(card, choice1, choice2, choice3, state, handPos, bonus);

    describe("When the player uses Feast and gains a card worth 5 coins");
    assert("it returns successfully",
            result == 0);
    assert("it removes the gained card from the supply pile",
            state->supplyCount[choice1] == 0);
    assert("it adds the gained card to the discard",
            state->discard[player][0] == choice1 && state->discardCount[player] == 1);
    assert("it does not affect the user's coin count",
            state->coins == 0);

    return 0;
}