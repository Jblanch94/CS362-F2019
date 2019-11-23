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

	//set variables to be used for initializeGame and cardEffect
	int numPlayers, seed, choice1, choice2, handPos, currentPlayer;

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	struct gameState G, testG;

	//boolean used to see if player still has minion card
	int minionCardFound = 0;

	for(i = 0; i < 1000; i++)
	{
		//rng for number of players, seed and choice1 and choice2
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



		printf("--------------------Testing %s card on iteration %d-----------------------\n", TESTCARD, i + 1);

		//start game
		initializeGame(numPlayers, k, seed, &G);

		//copy of state of game used for testing
		memcpy(&testG, &G, sizeof(struct gameState));
		handPos = 0;
		currentPlayer = whoseTurn(&G);

		//call minion function
		playMinion(&testG, handPos, currentPlayer, choice1, choice2);

		//check if player has minion card in hand
		for(j = 0; j < numHandCards(&testG); j++)
		{
			if(testG.hand[currentPlayer][j] == minion)
			{
				minionCardFound = 1;
			}
		}

		/* test if player has minion card
		if found then test failed otherwise test passed */
		if(minionCardFound == 1)
		{
			printf("Test failed for not discarding minion card after used.\n");
		}

		else
		{
			printf("Test passed for discarding minion card after used.\n");
		}

		//test if number of actions were incremented 
		printf("Number of actions: %d, Expected number of actions: %d\n", testG.numActions, G.numActions + 1);

		//test passed if numActions incremented otherwise test failed
		if(testG.numActions == G.numActions + 1)
		{
			printf("Test passed for giving player +1 action.\n");
		}

		else
		{
			printf("Test failed for not giving player +1 action.\n");
		}

		/* if player chose to gain 2 coins test
		if player gained two coins, test passed if they gained coins 
		otherwise test failed.*/
		if(choice1 == 1)
		{
			printf("Number of coins: %d, Expected number of coins: %d\n", testG.coins, G.coins + 2);

			if(testG.coins == G.coins + 2)
			{
				printf("Test passed for adding two coins to player after choosing first option.\n");
			}

			else
			{
				printf("Test failed for not adding two coins to player after choosing first option.\n");
			}
		}

		/*if player chose to discard hand and redraw test 
		if the discardCount was increased and if they 
		are holding 4 cards now. */
		if(choice2 == 1)
		{
			printf("Number of cards discarded: %d, Expected number of cards discarded: %d\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + 4);
			printf("Number of cards in hand: %d, Expected number of cards in hand: %d\n", numHandCards(&testG), 4);

			if(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + 4)
			{
				printf("Test passed for discarding hand.\n");
			}

			else
			{
				printf("Test failed for not discarding hand.\n");
			}

			if(numHandCards(&testG) == 4)
			{
				printf("Test passed for drawing four cards.\n");
			}

			else
			{
				printf("Test failed for not drawing exactly four cards.\n");
			}
		}
	}

	//reset boolean for use again in next iteration
	minionCardFound = 0;

	return 0;
}