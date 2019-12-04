#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

const int numActions = 2;

int soft_assert(int expectedActions, int actualActions)
{
	if (expectedActions != actualActions)
	{
		fprintf(stderr, "Unit Test 9 (tribute duplicates) failed:\n- Duplicate Revealed: Minion\n- Expected Actions: %d\n- Actual Actions: %d\n",
			expectedActions, actualActions);
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
	int nextPlayer = (currentPlayer + 1) % numPlayers;

	// Test setup: current actions, next player's top 2 cards in deck
	game->numActions = numActions;
	game->hand[currentPlayer][0] = tribute;
	game->deck[nextPlayer][game->deckCount[nextPlayer]++] = minion;
	game->deck[nextPlayer][game->deckCount[nextPlayer]++] = minion;

	// Call playCard() for Tribute
	playCard(0, 0, 0, 0, game);

	// Prepare actions
	// Player loses 1 by playing Tribute, then gains 2 ONCE for revealing Minion
	int expectedActions = numActions + 1;
	int actualActions = game->numActions;

	// Perform test
	soft_assert(expectedActions, actualActions);

	return 0;
}