#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

const int numHandCoppers = 3;

int soft_assert(int expectedCoins, int actualCoins)
{
	if (expectedCoins != actualCoins)
	{
		fprintf(stderr, "Unit Test 8 (bonus coins) failed:\n- Coppers in Hand: %d\n- Card Played: Minion (+2 Coins)\n- Expected Coins: %d\n- Actual Coins: %d\n",
			numHandCoppers, expectedCoins, actualCoins);
		return 0;
	}

	return 1;
}

int main()
{
	int i;
	// Initialize the game
	struct gameState* game = newGame();
	int numPlayers = 2;
	int k[10] = { adventurer, gardens, embargo, village, minion,
					mine, cutpurse, sea_hag, tribute, smithy };

	initializeGame(numPlayers, k, rand(), game);
	int currentPlayer = game->whoseTurn;

	// Test setup
	game->handCount[currentPlayer] = 0;

	// Player will play Minion for 2 Coins
	game->hand[currentPlayer][game->handCount[currentPlayer]++] = minion;

	// While holding 4 Coppers in hand
	for (i = 0; i < numHandCoppers; i++)
		game->hand[currentPlayer][game->handCount[currentPlayer]++] = copper;

	// Call playCard() for Minion
	playCard(0, 1, 0, 0, game);

	// Prepare coins
	int expectedCoins = numHandCoppers + 2;
	int actualCoins = game->coins;
	
	// Perform test
	soft_assert(expectedCoins, actualCoins);

	return 0;
}