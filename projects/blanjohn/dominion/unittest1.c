#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define TESTCARD "Baron"

int main() {

	//define states and initialize game
	struct gameState G, testG;
	int seed = 1000;
	int numPlayers = 2;
	int choice1 = 1;
	int currentPlayer = whoseTurn(&G);
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	//initialize game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("-------------------------TESTING CARD: %s ------------------------\n", TESTCARD);

	//check if the number of buys were increased
	printf("TEST 1: Check for +1 buy\n");
	printf("---------------------------------------------------------------------\n");

	memcpy(&testG, &G, sizeof(struct gameState));


	//after the expected should be 2
	int expectedNumBuys = 2;

	//call baron function
	baronRefactored(choice1, &testG, currentPlayer);

	//print the actual number of buys and the expected number of buys
	printf("num buys: %d, expected num buys: %d\n", testG.numBuys, expectedNumBuys);

	//print if the test passed or failed
	if(testG.numBuys == expectedNumBuys) {
		printf("Test passed for increasing number of buys\n");
	} else {
		printf("Test failed for increasing number of buys\n");
	}
	printf("----------------------------------------------------------------------\n");

	/*set choice to 1 anything over 0 
	check to make sure 4 coins are increased if estate is discarded 
	check to make sure estate is discarded */
	printf("TEST 2: choice1 = 1 -> discard estate and check number of coins increased by 4\n");

	//copy state over for another test
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	int coinsAdded = 4;
	int handCards = numHandCards(&testG);
	int i;
	int found = 0;

	//since testing for discarding estate make sure estate card is in hand
	testG.hand[currentPlayer][2] = estate;

	baronRefactored(choice1, &testG, currentPlayer);

	//find estate card in hand test for number of coins and number of cards in hand 
	for(i = 0; i < handCards; i++) {
		if(testG.hand[currentPlayer][i] == estate) {
			found = 1;

			//testing to see if coins are added to player
			printf("Found estate card and will be adding 4 coins to player.\n");
			printf("number of coins: %d, expected number of coins: %d\n",testG.coins, G.coins + coinsAdded);

			if(testG.coins == G.coins + coinsAdded) {
				printf("Test passed for adding 4 coins to player.\n");
			} else {
				printf("Test failed for adding 4 coins to player.\n");
			}

		}
	}


	printf("----------------------------------------------------------------------\n");

	//test if no estate card found then no coins should be give to player and no card should be discarded
	printf("TEST 3: choice1 = 1 -> if no estate there is no coins added to player and no card should be discarded\n");

	memcpy(&testG, &G, sizeof(struct gameState));

	//since we dont want estate in hand make sure it is not
	testG.hand[currentPlayer][0] = minion;
	testG.hand[currentPlayer][1] = baron;
	testG.hand[currentPlayer][2] = mine;
	testG.hand[currentPlayer][3] = copper;
	testG.hand[currentPlayer][4] = silver;


	baronRefactored(choice1, &testG, currentPlayer);

	found = 0;

	for(i = 0; i < numHandCards(&testG); i++) {
		if(testG.hand[currentPlayer][i] == estate) {
			found = 1;
		}
	}

	//test for coins and cards in hand when no estate in hand
	if(found == 0) {
		printf("number of coins: %d, expected number of coins: %d\n", testG.coins, G.coins);
		if(testG.coins == G.coins) {
			printf("Test passed for adding 0 coins to player when no estate card was found.\n");
		} else if(testG.coins == G.coins + 4) {
			printf("Test failed for adding 4 coins to player when no estate card was found.\n");
		}

		printf("Hand count: %d, expected Hand count: %d\n", numHandCards(&testG), numHandCards(&G));
		if(numHandCards(&testG) == numHandCards(&G)) {
			printf("Test passed for not discarding estate card when it was not found.\n");
		} else if(numHandCards(&testG) == numHandCards(&G)  + 1) {
			printf("Test failed.\n");
		}
	}


	printf("----------------------------------------------------------------------\n");

	//test for gain in estate card and decrease in supply count of estate cards
	printf("TEST 4: choice1 = 0 -> check for gain in estate card and decrease in supply count of estate cards.\n");
	printf("----------------------------------------------------------------------\n");

	memcpy(&testG, &G, sizeof(struct gameState));
	found = 0;	
	choice1 = 0;
	int count = 0;
	baronRefactored(choice1, &testG, currentPlayer);

	//get number of cards in hand
	handCards = numHandCards(&testG);

	//test for adding estate card to hand and get number of cards in hand
	for(i = 0; i < handCards; i++) {
		if(testG.hand[currentPlayer][i] == estate) {
			count++;
		}
	}

	if(count == 1)
	{
		printf("Test passed for adding estate to player's hand.\n");
	}

	else 
	{
		printf("Test failed for not adding estate to player's hand.\n");
	}

	//check to see if estate supply count was decremented
	printf("Estate supply count: %d, expected Estate supply count: %d\n", testG.supplyCount[estate], G.supplyCount[estate] - 1);
	if(testG.supplyCount[estate] == G.supplyCount[estate] - 1) {
		printf("Test passed for taking one estate card away from estate supply count.\n");
	} else {
		printf("Test failed .\n");
	}

	printf("TEST 4 has completed.\n\n");

	printf("TEST 5: check if baron card was discarded.\n");

	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 0;
	found = 0;

	baronRefactored(choice1, &testG, currentPlayer);

	for(i = 0; i < numHandCards(&testG); i++)
	{
		if(testG.hand[currentPlayer][i] == baron)
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


	printf("--------------------------TESTING COMPLETE-----------------------------------------------------------\n");


	return 0;
}