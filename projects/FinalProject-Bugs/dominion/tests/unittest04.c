#include "test_helpers.h"
#include "dominion.h"

// UNIT TESTS
// This file contains unit tests for the 'isGameOver loop' bug

int main() {
    int cards[10] = { curse, copper, silver, gold, estate,
                    duchy, province, feast, mine, treasure_map };
    struct gameState *state = newGame();
    int result;

    title("BUG #4: isGameOver loop");

    // Initialize game state and empty three supply piles, including the first
    // and last cards
    initializeGame(2, cards, 1, state);
    state->supplyCount[curse]        = 0; 
    state->supplyCount[copper]       = 0;
    state->supplyCount[treasure_map] = 0;

    // Run the first test
    result = isGameOver(state);

    describe("When three supply piles are empty, including the last card type");
    assert("it signals a game over",
            result == 1);
    

    // Initialize the new game state and empty two supply piles
    initializeGame(2, cards, 1, state);
    state->supplyCount[curse]  = 0;
    state->supplyCount[copper] = 0;

    // Run the second test
    result = isGameOver(state);

    describe("When fewer than three supply piles are empty");
    assert("it does not signal a game over",
            result == 0);

    return 0;
}