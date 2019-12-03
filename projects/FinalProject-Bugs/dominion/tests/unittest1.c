#include "dominion.h"

void myAssert(int x, int y) {
	if (x == y) {
		printf("PASSED\n");
	} else {
		printf("FAILED\n");
	}
}

int main () {

	printf("Test 1. Mine discardCard:\n");
    int numPlayers = 2;
    int seed = 10;
    int coin_bonus = 0;
    
    //set your card array
    int k[10] = { ambassador, council_room, feast, tribute, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState cleanGame;
    struct gameState testGame;
    initializeGame(numPlayers, k, seed, &cleanGame);
    
    //********Test Trash and gain treasure**********
    printf("\nTest: Trash and gain treasure\n");
    memcpy(&testGame, &cleanGame, sizeof(struct gameState));
    testGame.hand[0][0] = mine;
    testGame.hand[0][1] = copper;
    cardEffect(mine, 1, silver, -1, &testGame, 0, &coin_bonus);

    //Assert discard pile doesn't have the "trashed" card
    printf("When a treaure card is trashed and a coin is gained\n");
    printf("the only card in the discard pile is Mine: ");
    myAssert(testGame.discard[0][0], mine);
    printf("the discard pile count isn't greater than 1: ");
    myAssert(testGame.discardCount[0], 1);

    return 0;
}


