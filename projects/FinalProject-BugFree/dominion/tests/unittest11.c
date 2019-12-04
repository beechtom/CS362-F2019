#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

const int choice1 = 0;
const int choice2 = 0;

int soft_assert(int expectedReturn, int actualReturn)
{
	if (expectedReturn != actualReturn)
	{
		fprintf(stderr, "Unit Test 11 (minion choice) failed:\n- Choice 1: %d\n- Choice 2: %d\n- Expected Return Value: %d\n- Actual Return Value: %d\n",
			choice1, choice2, expectedReturn, actualReturn);
		return 0;
	}

	return 1;
}

int main()
{
	// Initialize the game
	struct gameState* game = newGame();
	int numPlayers = 2;
	int k[10] = { adventurer, gardens, embargo, village, minion,
					mine, cutpurse, sea_hag, tribute, smithy };

	initializeGame(numPlayers, k, rand(), game);
	int currentPlayer = game->whoseTurn;

	// Test setup: Minion in hand
	game->hand[currentPlayer][0] = minion;

	// Prepare return values
	int expectedReturn = -1;
	int actualReturn;

	// Call playCard() with Minion
	actualReturn = playCard(0, choice1, choice2, 0, game);
	
	// Perform test
	soft_assert(expectedReturn, actualReturn);

	return 0;
}