#include "test_helpers.h"
#include "dominion.h"

// UNIT TESTS
// This file contains unit tests for the 'Mine switch statement' bug

int main() {
    int cards[10] = { feast, mine, minion, tribute, ambassador,
                      smithy, steward, baron, remodel, adventurer };
    struct gameState *state = newGame();
    int result, player, card = mine, choice1, choice2, 
        choice3 = 0, handPos = 0, *bonus = NULL;

    title("BUG #2: Mine switch statement");

    // Initialize game state
    initializeGame(2, cards, 1, state);
    player                       = state->whoseTurn;
    choice1                      = 1;
    choice2                      = gold;
    state->hand[player][0]       = card;
    state->hand[player][choice1] = copper;
    state->handCount[player]     = 2;
    state->supplyCount[choice2]  = 1;
    state->discard[player][0]    = -1;
    state->discardCount[player]  = 0;

    // Run the tests
    result = cardEffect(card, choice1, choice2, choice3, state, handPos, bonus);

    describe("When the player trashes a treasure and gains another treasure worth > 3 coins more");
    assert("it returns unsuccessfully",
            result == -1);
    assert("it does not add the more expensive treasure to the player's hand",
            count_hand(choice2, player, state) == 0);
    assert("it does not remove the more expensive treasure from the supply",
            state->supplyCount[choice2] == 1);
    assert("it does not trash treasure from the player's hand",
            count_hand(copper, player, state) == 1);

    // Initialize game state
    initializeGame(2, cards, 1, state);
    player                       = state->whoseTurn;
    choice1                      = 1;
    choice2                      = copper;
    state->hand[player][0]       = card;
    state->hand[player][choice1] = silver;
    state->handCount[player]     = 2;
    state->supplyCount[choice2]  = 1;
    state->discard[player][0]    = -1;
    state->discardCount[player]  = 0;

    // Run the tests
    result = cardEffect(card, choice1, choice2, choice3, state, handPos, bonus);

    describe("When the player trashes a treasure and gains another treasure worth less");
    assert("it returns successfully",
            result == 0);
    assert("it adds the less expensive treasure to the player's hand",
            count_hand(choice2, player, state) == 1);
    assert("it removes the less expensive treasure from the supply",
            state->supplyCount[choice2] == 0);
    assert("it trashes the treasure from the player's hand",
            count_hand(silver, player, state) == 0);

    // Initialize game state
    initializeGame(2, cards, 1, state);
    player                       = state->whoseTurn;
    choice1                      = 1;
    choice2                      = copper;
    state->hand[player][0]       = card;
    state->hand[player][choice1] = choice2;
    state->handCount[player]     = 2;
    state->supplyCount[choice2]  = 1;
    state->discard[player][0]    = -1;
    state->discardCount[player]  = 0;

    // Run the tests
    result = cardEffect(card, choice1, choice2, choice3, state, handPos, bonus);

    describe("When the player trashes a treasure and gains another treasure worth the same");
    assert("it returns successfully",
            result == 0);
    assert("it adds the treasure to the player's hand",
            count_hand(choice2, player, state) == 1);
    assert("it removes the treasure from the supply",
            state->supplyCount[choice2] == 0);


    return 0;
}