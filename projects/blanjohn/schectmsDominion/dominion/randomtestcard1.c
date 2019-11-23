#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TESTCARD "Baron"

int main ()
{
	srand(time(NULL));

	int i, j, m;

	int estateCount = 0;

	int numPlayers, choice1, seed;
	int currentPlayer = 0;
	struct gameState G, testG;

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	int found = 0;
	int estateFound = 0;

	for(i = 0; i < 2000; i++)
	{
		//generate random number between 2 and 4 for number of players
		 numPlayers = rand() % 3 + 2;

		 //generate random choice for input that is 0 or 1
		 choice1 = rand() % 2;

		 //generate random seed for input
		 seed = rand () % 5000;
		
		initializeGame(numPlayers, k, seed, &G);

		printf("--------------------Testing %s card on iteration %d-----------------------\n", TESTCARD, i + 1);

		// copy state into a test variable
		memcpy(&testG, &G, sizeof(struct gameState));

		//initialize the current player
		currentPlayer = whoseTurn(&G);

		//loop through hand before function call to find out how many estates were found
		for(m = 0; m < G.handCount[currentPlayer]; m++)
		{
			if(G.hand[currentPlayer][m] == estate)
			{
				estateCount++;
			}
		}

		//call baron card function
		playBaron(&testG, choice1, currentPlayer);

		// test for increase in number of buys
		printf("Number of buys: %d, Expected number of buys: %d\n", testG.numBuys, G.numBuys + 1);

		if(testG.numBuys == G.numBuys + 1)
		{
			printf("Test passed for adding one buy to the player.\n");
		}

		else
		{
			printf("Test failed for not adding one buy to the player.\n");
		}

		//test for discarding baron card after use
		for(j = 0; j < numHandCards(&testG); j++)
		{
			if(testG.hand[currentPlayer][j] == baron)
			{
				found = 1;
			}
		}

		if(found == 1)
		{
			printf("Test failed for not discarding baron card after use.\n");
		}

		else 
		{
			printf("Test passed for discarding baron card after use.\n");
		}

		//test if player has estate that they gain 4 coins
		if(estateCount >= 1)
		{
			printf("Number of coins: %d, Expected number of coins: %d\n", testG.coins, G.coins + 4);

			if(testG.coins == G.coins + 4)
			{
				printf("Test passed for adding 4 coins to player when they had an estate card in hand.\n");
			}

			else
			{
				printf("Test failed for not adding 4 coins to player when they had an estate card in hand.\n");
			}
		}

		//test if player has no estates they gain an estate
		if(estateCount == 0)
		{
			for(j = 0; j < numHandCards(&testG); j++)
			{
				if(testG.hand[currentPlayer][j] == estate)
				{
					estateFound = 1;
				}
			}

			if(estateFound == 1)
			{
				printf("Test passed for adding estate to player when they had none.\n");
			}

			else
			{
				printf("Test failed for not adding estate to player when they had none.\n");
			}
		}

		//reset variables used for reuse
		found = 0;

		estateFound = 0;

		estateCount = 0;
	}


	return 0;
}