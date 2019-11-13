#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TESTCARD "Minion"

int main()
{

	srand(time(NULL));
	int i, j;

	int numPlayers, seed, choice1, choice2, handPos, currentPlayer;

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	struct gameState G, testG;

	int minionCardFound = 0;

	for(i = 0; i < 10; i++)
	{
		numPlayers = rand() % 3 + 2;
		seed = rand () % 5000;
		choice1 = rand() % 2;

		if(choice1 == 1)
		{
			choice2 = 0;
		}

		else
		{
			choice2 = 1;
		}

		memcpy(&testG, &G, sizeof(struct gameState));
		handPos = 0;
		currentPlayer = whoseTurn(&G);


		printf("--------------------Testing %s card on iteration %d-----------------------\n", TESTCARD, i + 1);

		initializeGame(numPlayers, k, seed, &G);


		minionRefactored(choice1, choice2, &testG, handPos, currentPlayer);

		for(j = 0; j < numHandCards(&testG); j++)
		{
			if(testG.hand[currentPlayer][j] == minion)
			{
				minionCardFound = 1;
			}
		}

		if(minionCardFound == 1)
		{
			printf("Test passed for discarding minion card after used.\n");
		}

		else
		{
			printf("Test failed for not discarding minion card after used.\n");
		}

		printf("Number of actions: %d, Expected number of actions: %d\n", testG.numActions, G.numActions + 1);
	}

	minionCardFound = 0;

	return 0;
}