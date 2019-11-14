#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TESTCARD "Tribute"

int main()
{	

	//set variables used to start game and for tribute card function
	int numPlayers,  seed,  currentPlayer,  nextPlayer;
	int tributeRevealedCards[2];
	int tributeCardFound;
	int randomCard1, randomCard2;
	int i, j;

	int treasureCardCount, victoryCardCount, actionCardCount;

	int c[27] = {curse, estate, duchy, province,
				copper, silver, gold,
				adventurer, council_room, feast, gardens,
				mine, remodel, smithy, village,
				baron, great_hall, minion, steward, 
				tribute, ambassador, cutpurse, embargo,
				outpost, salvager, sea_hag, treasure_map};

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	struct gameState G, testG;

	for(i = 0; i < 5000; i++)
	{
		//get random numbers for number of players and seed
		numPlayers = rand() % 3 + 2;
		seed = rand () % 5000;

		randomCard1 = rand() % 27;
		randomCard2 = rand() % 27;

		actionCardCount = 0;
		victoryCardCount = 0;
		treasureCardCount = 0;

		//initialize revealed cards to garbage values
		tributeRevealedCards[0] = c[randomCard1];
		tributeRevealedCards[1] = c[randomCard2];
		tributeCardFound = 0;

		//start game
		initializeGame(numPlayers, k, seed, &G);

		printf("--------------------Testing %s card on iteration %d-----------------------\n", TESTCARD, i + 1);

		memcpy(&testG, &G, sizeof(struct gameState));

		//set currentPlayer and nextPlayer
		currentPlayer = whoseTurn(&G);
		nextPlayer = currentPlayer + 1;

		//call tribute card function
		tributeRefactored(&testG, currentPlayer, nextPlayer, tributeRevealedCards);

		//test if player still has tribute card in hand
		for(j = 0; j < numHandCards(&testG); j++)
		{
			if(testG.hand[currentPlayer][j] == tribute)
			{
				tributeCardFound = 1;
			}
		}

		//if player has tribute card then test failed otherwise test passed
		if(tributeCardFound == 1)
		{
			printf("Test failed for not discarding tribute card after use.\n");
		}

		else
		{
			printf("Test passed for discarding tribute card after use.\n");
		}

		//test if nextPlayer discards two cards
		printf("Number of cards discarded for player to left: %d, Expected number of cards for player to left: %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer] + 2);

		if(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer] + 2)
		{
			printf("Test passed for player to left discarding revealed cards.\n");
		}

		else
		{
			printf("Test failed for player to left not discarding revealed cards.\n");
		}

		for(j = 0; j < 2; j++)
		{
			if (tributeRevealedCards[j] == copper || tributeRevealedCards[j] == silver || tributeRevealedCards[j] == gold)
        	{ 
        		treasureCardCount++;
        	}

        	else if (tributeRevealedCards[j] == estate || tributeRevealedCards[j] == duchy || tributeRevealedCards[j] == province || tributeRevealedCards[j] == gardens || tributeRevealedCards[j] == great_hall)
        	{ 
        		victoryCardCount++;
        	}
        	else
        	{ 
        		actionCardCount++;
        	}
        }

        if(treasureCardCount == 1)
        {
        	printf("Number of coins: %d, Expected number of coins: %d\n", testG.coins, G.coins + 2);

        	if(testG.coins == G.coins + 2)
        	{
        		printf("Test passed for adding two coins to player for one treasure card.\n");
        	}

        	else
        	{
        		printf("Test failed for not adding two coins to player for one treasure card.\n");
        	}
        }

        else if(treasureCardCount == 2)
        {
        	printf("Number of coins: %d, Expected number of coins: %d\n", testG.coins, G.coins + 4);

        	if(testG.coins == G.coins + 4)
        	{
        		printf("Test passed for adding 4 coins to player for two treasure cards.\n");
        	}

        	else 
        	{
        		printf("Test failed for not adding 4 coins to player for two treasure cards.\n");
        	}
        }

        else if(victoryCardCount == 1)
        {
        	printf("Number of cards in hand: %d, Expected number of cards in hand: %d\n", numHandCards(&testG), numHandCards(&G) + 2);

        	if(numHandCards(&testG) == numHandCards(&G) + 2)
        	{
        		printf("Test passed for adding two cards to player's hand for 1 victory card.\n");
        	}

        	else
        	{
        		printf("Test failed for not adding two cards to player's hand for 1 victory card.\n");
        	}
        }

        else if(victoryCardCount == 2)
        {
        	printf("Number of cards in hand: %d, Expected number of cards in hand: %d\n", numHandCards(&testG), numHandCards(&G) + 4);

        	if(numHandCards(&testG) == numHandCards(&G) + 4)
        	{
        		printf("Test passed for adding four cards to player's hand for 2 victory cards.\n");
        	}

        	else
        	{
        		printf("Test failed for not adding four cards to player's hand for 2 victory cards.\n");
        	}
        }

        else if(actionCardCount == 1)
        {
        	printf("Number of actions: %d, Expected number of actions: %d\n", testG.numActions, G.numActions + 2);

        	if(testG.numActions == G.numActions + 2)
        	{
        		printf("Test passed for adding 2 actions to player for one action card.\n");
        	}

        	else
        	{
        		printf("Test failed for not adding 2 actions to player for one action card.\n");
        	}
        }

        else if(actionCardCount == 2)
        {
        	printf("Number of actions: %d, Expected number of actions: %d\n", testG.numActions, G.numActions + 4);

        	if(testG.numActions == G.numActions + 4)
        	{
        		printf("Test passed for adding 4 actions to player for two action cards.\n");
        	}

        	else
        	{
        		printf("Test failed for not adding 4 actions to player for two action cards.\n");
        	}
        }

	}



	return 0;
}