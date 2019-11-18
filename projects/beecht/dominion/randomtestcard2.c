#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "unittest.h"
#include "dominion.h"

// MINION UNIT TESTS

int main() {
    // Seed the rng
    srand(time(0));

    // Set the hand
    struct gameState *before = newGame();
    struct gameState *after  = newGame();
    int results[15]          = {0};

    for (int test = 0; test < TEST_COUNT; test++) {
        // Initalize the state of the game ~randomly~
        initializeRandomGame(after, before, minion);

        int player  = before->whoseTurn;
        int choice1 = rand() % 2;
        int choice2 = rand() % 2;
        int handPos = rand() % before->handCount[player];

        // Run the card effect with ~random~ input
        int ret = card_effect_minion(choice1, choice2, handPos, after);

        // Record some important info, like the current player and Minion card count
        int minion_hand_before    = count_hand(minion, player, before);
        int minion_hand_after     = count_hand(minion, player, after);
        int minion_discard_before = count_discard(minion, player, before);
        int minion_discard_after  = count_discard(minion, player, after);

        // TEST 0: It should fail if the player does not have a Minion card
        if(minion_hand_before < 1 && ret != -1)
            results[0]++;
        
        // TEST 1: It should always discard the Minion card
        if(minion_hand_before > 0 &&
          (minion_hand_before - minion_hand_after != 1 ||
           minion_discard_after - minion_discard_before != 1))
            results[1]++;

        // TEST 2: It should always grant the player +1 action
        if(after->numActions - before->numActions != 1)
            results[2]++;

        // TEST 3: It should fail if player tries to gain coin and discard hand
        if(choice1 == true && choice2 == true && ret != -1)
            results[3]++;

        // SHARED TESTS: If the player chooses to gain +2 coins
        if (choice1) {
            // TEST 4: It should give the player +2 coins
            if(choice1 == true && after->coins - before->coins != 2)
                results[4]++;

            // TEST 5: It should not cause any player to draw more cards
            for (int i = 0; i < before->numPlayers; i++) {
                if(before->deckCount[i] != after->deckCount[i]) {
                    results[5]++;
                    break;
                }
            }
        }

        // SHARED TESTS: If the player chooses to discard their hand
        if (choice2) {
            // TEST 6: It should discard the player's entire hand
            if(after->discardCount[player] - before->discardCount[player] != before->handCount[player])
                results[6]++;
            
            // TEST 7: It should give the player +4 cards after discarding
            if(after->handCount[player] != 4)
                results[7]++;

            // TEST 8: It should draw 4 cards from the player's deck
            if(before->deckCount[player] - after->deckCount[player] != 4)
                results[8]++;

            // TEST 9: It should not give the player +2 coins
            if(after->coins != before->coins)
                results[9]++;

            for (int i = 0; i < before->numPlayers; i++) {
                // TEST 10: It should discard the hand of any player that had 5 or more cards
                if(before->handCount[i] >= 5 &&
                   after->discardCount[i] - before->discardCount[i] != before->handCount[i]) {
                    results[10]++;
                    break;
                }

                // TEST 11: It should cause any player that had 5 or more cards in hand to draw 4 cards
                if(before->handCount[i] >= 5 && after->handCount[i] != 4) {
                    results[11]++;
                    break;
                }

                // TEST 12: It should draw cards from the player's deck
                if(before->deckCount[i] - after->deckCount[i] != 4) {
                    results[12]++;
                    break;
                }
            }
        }
        
        // TEST 13: It should fail if trying to discard something other than Minion
        if(before->hand[player][handPos] != minion)
            results[13]++;

        // TEST 14: It should succeed if choosing ONE of the two choices and correctly indicating the minion card
        if (choice1 != choice2 && before->hand[player][handPos] == minion && ret != 0)
            results[14]++;
    }

    // Print the test results
    describe("When using the Minion card");
    assert("it fails if the player does not have a Minion card",
            results[0]);
    assert("it discards the Minion card",
            results[1]);
    assert("it grants the player +1 action",
            results[2]);
    assert("it fails if the player tries to select both options",
            results[3]);
    describe("\tand the player chooses +2 coins");
    assert("\tit gives the player +2 coins",
            results[4]);
    assert("\tit does not make players draw cards",
            results[5]);
    describe("\tand the player chooses to discard");
    assert("\tit discards the player's hand",
            results[6]);
    assert("\tit gives the player +4 cards",
            results[7]);
    assert("\tit draws cards from the player's deck",
            results[8]);
    assert("\tit doesn't give the player +2 coins",
            results[9]);
    assert("\tit discards the hand of any player with 5 or more cards",
            results[10]);
    assert("\tit gives +4 cards to any player that had 5 or more cards",
            results[11]);
    assert("\tit draws cards from the deck of any player that had 5 or more cards",
            results[12]);
    assert("it fails when trying to discard something other than Minion",
            results[13]);
    assert("it succeeds when choosing one of the two choices and correctly indicating the Minion",
            results[14]);
    printf("Total Tests: %d\n\n", TEST_COUNT);


    return 0;
}