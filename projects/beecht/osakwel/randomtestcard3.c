#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "unittest.h"
#include "dominion.h"

enum TYPE { ACTION = 0, TREASURE, VICTORY };

// MINION UNIT TESTS

int main() {
    // Seed the rng
    srand(time(0));

    // Set the hand
    struct gameState *before = newGame();
    struct gameState *after  = newGame();
    int results[10]          = {0};

    for (int test = 0; test < TEST_COUNT; test++) {
        // Initalize the state of the game ~randomly~
        initializeRandomGame(after, before, tribute);

        int next_player             = (after->whoseTurn + 1) % after->numPlayers;
        int tributeRevealedCards[2] = {-1, -1};

        // Run the card effect with ~random~ input
        int ret = tributeCardEffect(after, next_player, after->whoseTurn, tributeRevealedCards);

        // Record some important info, like the current player and next player's deck
        int player                 = before->whoseTurn;
        int tribute_hand_before    = count_hand(tribute, player, before);
        int tribute_hand_after     = count_hand(tribute, player, after);
        int tribute_discard_before = count_discard(tribute, player, before);
        int tribute_discard_after  = count_discard(tribute, player, after);
        int next                   = (player + 1) % before->numPlayers;
        int next_deck_before       = before->deckCount[next];
        int next_card[2]           = { before->deck[next][next_deck_before - 1],
                                       before->deck[next][next_deck_before - 2] };

        // Record the next card types for easy reference
        int next_type[2];
        for (int i = 0; i < 2; i++) {
            if (next_card[i] >= copper && next_card[i] <= gold)
                next_type[i] = TREASURE;
            else if (next_card[i] >= curse && next_card[i] <= great_hall)
                next_type[i] = VICTORY;
            else
                next_type[i] = ACTION;
        }

        // TEST 0: It should fail if the player does not have a Tribute card
        if (tribute_hand_before < 1 && ret != -1)
            results[0]++;

        // TEST 1: It should always discard the Tribute card
        if(tribute_hand_before > 0 &&
          (tribute_hand_before - tribute_hand_after != 1 ||
           tribute_discard_after - tribute_discard_before != 1))
            results[1]++;

        // TEST 2: It should fail when the next player has an empty deck and discard
        if (before->discardCount[next] + before->deckCount[next] == 0 && ret != -1)
            results[2]++;

        // TEST 3: It discards the revealed cards
        if (count_discard(next_card[0], next, after) - count_discard(next_card[0], next, before) != 1 ||
            count_discard(next_card[1], next, after) - count_discard(next_card[1], next, before) != 1)
            results[3]++;

        // TEST 4: It gives +4 actions for 2 revealed action cards
        if (next_type[0] == ACTION && next_type[1] == ACTION &&
            after->numActions - before->numActions != 4)
            results[4]++;

        // TEST 5: It gives +4 coins for 2 revealed treasure cards
        if (next_type[0] == TREASURE && next_type[1] == TREASURE &&
            after->coins - before->coins != 4)
            results[5]++;

        // TEST 6: It gives +4 cards for 2 revealed victory cards
        if (next_type[0] == VICTORY && next_type[1] == VICTORY &&
            before->deckCount[player] - after->deckCount[player] != 4)
            results[6]++;

        // TEST 7: It ignores 2 identical cards
        if (next_card[0] == next_card[1] && (
            after->numActions - before->numActions > 2 ||
            after->coins - before->coins > 2 ||
            before->deckCount[player] - after->deckCount[player] > 2))
            results[7]++;

        // TEST 8: It gives separate bonuses for different card types
        if (next_type[0] == ACTION && next_type[1] == TREASURE && (
            after->coins - before->coins != 2 || after->numActions - before->numActions != 2))
            results[8]++;

        // TEST 9: It should succeed if the player has a Tribute card and next player has cards to reveal
        if (tribute_hand_before > 0 && before->discardCount[next] + before->deckCount[next] == 0 && ret != 0)
            results[9]++;
    }

    // Print the test results
    describe("When using the Tribute card");
    assert_random("it fails if the player does not have a Tribute card",
            results[0]);
    assert_random("it discards the Tribute card",
            results[1]);
    assert_random("it fails if the player to the left has an empty discard and deck",
            results[2]);
    assert_random("it discards the revealed cards",
            results[3]);
    assert_random("it gives +4 actions for 2 revealed action cards",
            results[4]);
    assert_random("it gives +4 coins for 2 revealed treasure cards",
            results[5]);
    assert_random("it gives +4 cards for 2 revealed victory cards",
            results[6]);
    assert_random("it ignores 2 identical revealed cards",
            results[7]);
    assert_random("it gives separate bonuses for different card types",
            results[8]);
    assert_random("it succeeds if the player has a Tribute card and the player to the left has cards to reveal",
            results[9]);
    printf("Total Tests: %d\n\n", TEST_COUNT);

    return 0;
}