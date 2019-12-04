#include "dominion.h"
#include <stdio.h>
#include <string.h>
#include "dominion_helpers.h"

void myAssert(int x, int y) {
	if (x == y) {
		printf("PASSED\n");
	} else {
		printf("FAILED\n");
	}
}

void myAssertGreater(int x, int y) {
    if (x >= y) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
}

int main () {

	printf("Test 3. Remodel if-statement:\n");
    int numPlayers = 2;
    int seed = 10;
    int coin_bonus = 0;
    

    //set your card array
    int k[10] = { ambassador, council_room, feast, tribute, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState cleanGame;
    struct gameState testGame;
    initializeGame(numPlayers, k, seed, &cleanGame);
    
    //********Test Gained card cost more**********
    printf("\nTest: Discard Silver and gain Mine\n");
    memcpy(&testGame, &cleanGame, sizeof(struct gameState));
    testGame.hand[0][0] = remodel;
    testGame.hand[0][1] = silver;
    int cardToBeTrashed = testGame.hand[0][1];
    cardEffect(remodel, 1, mine, -1, &testGame, 0, &coin_bonus);

    //Asserts
    printf("When player trashes silver card costing 3, assert\n");
    printf("Card gained has cost greater than trashed card: ");
    myAssertGreater(getCost(testGame.hand[0][1]), getCost(cardToBeTrashed));

    return 0;
}
