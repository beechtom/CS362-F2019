#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "unittest.h"
#include "dominion.h"

// BARON UNIT TESTS

int main() {
    // Seed the rng
    srand(time(0));

    // Set the hand
    struct gameState *state       = newGame();
    struct gameState *state_start = newGame();
    int results[14]               = {0};

    for (int test = 0; test < TEST_COUNT; test++) {
        int choice1 = rand() % 2;

        // Initalize the state of the game ~randomly~
        initializeRandomGame(state, state_start, baron);

        // Run the card effect with ~random~ input
        int ret = card_effect_baron(choice1, state);

        // Record some important info, like the current player and card count for
        // baron and estate cards
        int player               = state_start->whoseTurn;
        int estate_hand_start    = count_hand(estate, player, state_start);
        int estate_discard_start = count_discard(estate, player, state_start);
        int baron_hand_start     = count_hand(estate, player, state_start);
        int baron_discard_start  = count_discard(estate, player, state_start);
        int estate_hand          = count_hand(estate, player, state);
        int estate_discard       = count_discard(estate, player, state);
        int baron_hand           = count_hand(baron, player, state);
        int baron_discard        = count_discard(baron, player, state);

        // TEST 0: Baron should never affect other players
        for (int i = 0; i < state_start->numPlayers; i++) {
            if (i != player) {
                if (state->handCount[i]    != state_start->handCount[i] ||
                    state->deckCount[i]    != state_start->deckCount[i] ||
                    state->discardCount[i] != state_start->discardCount[i]) {
                    results[0]++;
                }
                for (int j = 0; j < state->handCount[i]; j++) {
                    if (state->hand[i][j] != state_start->hand[i][j]) {
                        results[0]++;
                    }
                }
                for (int j = 0; j < state->deckCount[i]; j++) {
                    if (state->deck[i][j] != state_start->deck[i][j]) {
                        results[0]++;
                    }
                }
                for (int j = 0; j < state->discardCount[i]; j++) {
                    if (state->discard[i][j] != state_start->discard[i][j]) {
                        results[0]++;
                    }
                }
            }
        }

        // TEST 1: It should not affect the player's deck
        if (state->deckCount[player] != state_start->deckCount[player])
            results[1]++;

        // TEST 2: It should not increase the player's discard by > 2
        if (state->discardCount[player] - state_start->discardCount[player] > 2)
            results[2]++;

        // TEST 3: It should always discard the Baron
        if (baron_discard - baron_discard_start != 1 || baron_hand_start - baron_hand != 1)
            results[3]++;

        // TEST 4: It should not affect actions
        if (state->numActions > state_start->numActions)
            results[4]++;

        // TEST 5: Player should always gain +1 buy
        if (state->numBuys - state_start->numBuys != 1)
            results[5]++;

        // TEST 6: It should always gain an Estate if not discarding an estate
        if (choice1 == false && estate_discard - estate_discard_start != 1)
            results[6]++;

        // TEST 7: It should never change the number of Estates in hand if player chooses not to discard
        if (choice1 == false && estate_hand != estate_hand_start)
            results[7]++;

        // TEST 8: It should always gain +4 coin if discarding an estate
        if (choice1 == true && estate_hand_start > 0 && state->coins - state_start->coins != 4)
            results[8]++;

        // TEST 9: The player should never gain coins if not discarding an estate
        if ((choice1 == false || (choice1 == true && estate_hand < estate_hand_start)) && state->coins != state_start->coins)
            results[9]++;
        
        // TEST 10: It should always discard ONE Estate if player has one in hand and chooses to discard
        if (choice1 == true && estate_hand_start > 0 && estate_hand - estate_hand_start != 1)
            results[10]++;

        // TEST 11: It should always fail if player has no Estate and tries to discard one
        if (choice1 == true && estate_hand_start == 0 && ret != 1)
            results[11]++;

        // TEST 12: It should always fail if player does not have a Baron card
        if (baron_hand_start < 1 && ret == 0)
            results[12]++;

        // TEST 13: It should always succeed otherwise
        if ((choice1 == false || (choice1 == true && estate_hand_start > 0)) && ret != 0)
            results[13]++;
    }

    // Print the test results
    describe("When using the Baron card");
    assert("it never affects another player's state",
            results[0]);
    assert("it never affects the player's deck",
            results[1]);
    assert("it never increases the player's deck by more than 2 cards",
            results[2]);
    assert("it discards the Baron after playing it",
            results[3]);
    assert("it does not affect the player's number of actions",
            results[4]);
    assert("it gives the player +1 buys",
            results[5]);
    assert("it causes the player to gain an Estate if they do not discard an Estate",
            results[6]);
    assert("it doesn't change the number of Estates in hand if player does not discard",
            results[7]);
    assert("it causes the player to gain +4 coin if discarding an Estate",
            results[8]);
    assert("it doesn't affect the player's coins when not discarding an Estate",
            results[9]);
    assert("it only discards one Estate if the player has one in hand and discards",
            results[10]);
    assert("it fails if the player has no Estates and tries to discard one",
            results[11]);
    assert("it fails if the player does not have a Baron card",
            results[12]);
    assert("it succeeds when player does not discard or chooses to discard and has an Estate",
            results[13]);
    printf("Total Tests: %d\n\n", TEST_COUNT);

    return 0;
}