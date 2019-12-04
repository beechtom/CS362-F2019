#include "dominion.h"
#include <stdio.h>
#include <string.h>

void myAssert(int x, int y) {
	if (x == y) {
		printf("PASSED\n");
	} else {
		printf("FAILED\n");
	}
}

int main () {

	printf("Test 7. Tribute array overrun:\n");
    int numPlayers = 2;
    int seed = 10;
    int coin_bonus = 0;

    //set your card array
    int k[10] = { ambassador, council_room, feast, tribute, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState cleanGame;
    struct gameState compareGame;
    struct gameState testGame;
    initializeGame(numPlayers, k, seed, &cleanGame);
    cleanGame.numActions = 0;
    
    //********Test Reveal two treasure cards**********
    printf("\nTest: Left player reveals two treaure cards\n");
    memcpy(&testGame, &cleanGame, sizeof(struct gameState));
    testGame.hand[0][0] = tribute;
    testGame.deckCount[1] = 2;
    testGame.deck[1][0] = copper;
    testGame.deck[1][1] = copper;
    cardEffect(tribute, -1, -1, -1, &testGame, 0, &coin_bonus);

    //Asserts
    printf("When nextPlayer reveals 2 treasure cards, assert\n");
    printf("CurrentPlayer coin count increased by 4: ");
    myAssert(testGame.coins, compareGame.coins + 4);
    printf("CurrentPlayer action count does not increase: ");
    myAssert(testGame.numActions, compareGame.numActions);

    return 0;
}

