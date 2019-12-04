#include "test_helpers.h"
#include "dominion.h"

// UNIT TESTS
// This file contains unit tests for the 'Ambassador card count' bug

int main() {
    int cards[10] = { feast, mine, minion, tribute, ambassador,
                      smithy, steward, baron, remodel, adventurer };
    struct gameState *state = newGame();
    int result, player, card = ambassador, choice1, choice2, 
        choice3 = 0, handPos = 0, *bonus = NULL;

    title("BUG #10: Ambassador card count");

    // Initialize game state
    initializeGame(2, cards, 1, state);
    player                      = state->whoseTurn;
    choice1                     = estate;
    choice2                     = 2;
    state->numPlayers           = 1;
    state->supplyCount[choice1] = 0;
    state->hand[player][0]      = card;
    state->hand[player][1]      = choice1;
    state->hand[player][2]      = choice1;
    state->handCount[player]    = 3;

    // Run the tests
    result = cardEffect(card, choice1, choice2, choice3, state, handPos, bonus);

    describe("When the player has two copies of a card and returns them to the supply");
    assert("it returns successfully",
            result == 0);
    assert("it adds the cards to the supply",
            state->supplyCount[choice1] == 2);
    assert("it removes the cards from the player's hand",
            count_hand(choice1, player, state) == 0);

    // Initialize game state
    initializeGame(2, cards, 1, state);
    player                      = state->whoseTurn;
    choice1                     = estate;
    choice2                     = 2;
    state->numPlayers           = 1;
    state->supplyCount[choice1] = 0;
    state->hand[player][0]      = card;
    state->hand[player][1]      = choice1;
    state->handCount[player]    = 2;

    // Run the tests
    result = cardEffect(card, choice1, choice2, choice3, state, handPos, bonus);

    describe("When the player has one copy of a card and tries to return it to the supply");
    assert("it returns unsuccessfully",
            result == -1);
    assert("it does not add the card to the supply",
            state->supplyCount[choice1] == 0);
    assert("it does not remove the card from the player's hand",
            count_hand(choice1, player, state) == 1);

    return 0;
}