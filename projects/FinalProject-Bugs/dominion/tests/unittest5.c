#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

const int numHandEstates = 4;
const int numDeckEstates = 8;
const int numDiscardEstates = 2;

// Always returns the same value as condition
int soft_assert(int expectedScore, int actualScore)
{
	if (expectedScore != actualScore)
	{
		fprintf(stderr, "Unit Test 5 (scoreFor deck count) failed:\n- Estates in Hand/Deck/Discard: %d/%d/%d\n- Expected Score: %d\n- Actual Score: %d\n",
			numHandEstates, numDeckEstates, numDiscardEstates, expectedScore, actualScore);
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
	game->deckCount[currentPlayer] = 0;
	game->discardCount[currentPlayer] = 0;

	// Player has Estates
	for (i = 0; i < numHandEstates; i++)
		game->hand[currentPlayer][game->handCount[currentPlayer]++] = estate;
	for (i = 0; i < numDeckEstates; i++)
		game->deck[currentPlayer][game->deckCount[currentPlayer]++] = estate;
	for (i = 0; i < numDiscardEstates; i++)
		game->discard[currentPlayer][game->discardCount[currentPlayer]++] = estate;

	// Prepare scores
	int expectedScore = numHandEstates + numDeckEstates + numDiscardEstates;
	int actualScore = scoreFor(currentPlayer, game);

	// Perform test
	soft_assert(expectedScore, actualScore);
	
	return 0;
}