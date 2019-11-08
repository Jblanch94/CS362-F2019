#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define TESTCARD "Ambassador"

int main() {

	//set up state so game can be initialzed with parameters needed for minion function
    struct gameState G, testG;
    int seed = 1000;
    int numPlayers = 2;
    int choice1, choice2;
    int handPos = 0;
    int i;
    int currentPlayer = whoseTurn(&G);
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room}; 

    //start game
    initializeGame(numPlayers, k, seed, &G);

    printf("-------------------------TESTING CARD: %s ------------------------\n", TESTCARD);

    //test if ambassador card was discarded
    printf("TEST 1: check if Ambassador card was discarded.\n");

    choice1 = 2;
    choice2 = 1;

    memcpy(&testG, &G, sizeof(struct gameState));

    ambassadorRefactored(choice1, choice2, &testG, handPos, currentPlayer);

    int numCards = numHandCards(&testG);
   	int found = 0;

   	for(i = 0; i < numCards; i++) {
   		if(testG.hand[currentPlayer][i] == ambassador) {
   			found = 1;

   		}
   	}

   	printf("Discard count: %d, expected discard count: %d\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + 1);

   	//if found minion card then test failed otherwise it passed
   	if(found == 1) {
   		printf("Test failed for not discarding ambassador card after used.\n");
   	} else {
   		printf("Test passed for  discarding ambassador card after used.\n");
   	}

   	printf("TEST 1 has completed.\n\n");


   	//check if both copies were placed in supply
   	printf("TEST 2: check if both copies were returned to supply.\n");

   	memcpy(&testG, &G, sizeof(struct gameState));

   	testG.hand[currentPlayer][0] = curse;
   	testG.hand[currentPlayer][2] = curse;
   	testG.hand[currentPlayer][4] = curse;

   	testG.hand[currentPlayer + 1][0] = estate;
   	testG.hand[currentPlayer + 1][1] = copper;
   	testG.hand[currentPlayer + 1][2] = silver;
   	testG.hand[currentPlayer + 1][3] = gold;
   	testG.hand[currentPlayer + 1][4] = copper;
   	

   	choice1 = 0;
   	choice2 = 2;

   	ambassadorRefactored(choice1, choice2, &testG, handPos, currentPlayer);

   	int count = 0;

   	printf("supply count of curse cards: %d, expected supply count of cursed cards: %d\n", supplyCount(0, &testG), supplyCount(0, &G) + 2);

   	//since returning curse cards we want the supply count of curse to be two greater
   	if(supplyCount(0, &testG) == supplyCount(0, &G) + 2) {
   		printf("Test passed for adding two cards to supply count.\n");
   	} else {
   		printf("Test failed for not adding two cards to supply count.\n");
   	}

   	for(i = 0; i < 6; i++) {
   		if(testG.hand[currentPlayer][i] == curse) {
   			count++;
   		}
   	}

   	printf("Number of curse cards: %d, expected number of curse cards: %d\n", count, 0);

   	if(count == 0) {
   		printf("Test passed player who played card has no curse cards.\n");
   	} else {
   		printf("Test failed for player who played card having more than 0 curse cards.\n");
   	}

   	count = 0;
   	for(i = 0; i < 6; i++) {
   		if(testG.hand[currentPlayer + 1][i] == curse) {
   			count++;
   		}
   	}

   	printf("Number of curse cards: %d, Expected number of curse cards: %d\n", count, 1);

   	if(count == 1) {
   		printf("Test passed where other players gain a copy of the card that was discarded.\n");
   	} else {
   		printf("Test failed where other players don't gain a copy of the card that was discarded.\n");
   	}

   	printf("TEST 2 has completed.\n\n");


   	//test to make sure if player who played card does not have enough copies that other players don't gain a copy
   	printf("TEST 3: check if player has no copies of card revealed that other players don't gain a copy.\n");

   	memcpy(&testG, &G, sizeof(struct gameState));

   	testG.hand[currentPlayer][0] = curse;
   	testG.hand[currentPlayer][1] = estate;
   	testG.hand[currentPlayer][2] = silver;
   	testG.hand[currentPlayer][3] = copper;
   	testG.hand[currentPlayer][4] = mine;

   	testG.hand[currentPlayer + 1][0] = estate;
   	testG.hand[currentPlayer + 1][1] = copper;
   	testG.hand[currentPlayer + 1][2] = silver;
   	testG.hand[currentPlayer + 1][3] = gold;
   	testG.hand[currentPlayer + 1][4] = copper;
   	

   	choice1 = 0;
   	choice2 = 0;

   	ambassadorRefactored(choice1, choice2, &testG, handPos, currentPlayer);

    count = 0;

   	printf("supply count of curse cards: %d, expected supply count of cursed cards: %d\n", supplyCount(0, &testG), supplyCount(0, &G) + 2);

   	if(supplyCount(0, &testG) == supplyCount(0, &G)) {
   		printf("Test passed for adding 0 cards to supply count.\n");
   	} else {
   		printf("Test failed for not adding 0 cards to supply count.\n");
   	}

   	for(i = 0; i < 6; i++) {
   		if(testG.hand[currentPlayer][i] == curse) {
   			count++;
   		}
   	}

   	printf("Number of curse cards for player who played card: %d, expected number of curse cards for player who played card: %d\n", count, 1);

   	if(count == 1) {
   		printf("Test passed has 1 curse cards.\n");
   	} else {
   		printf("Test failed for having curse not equal to one.\n");
   	}

   	count = 0;
   	for(i = 0; i < 6; i++) {
   		if(testG.hand[currentPlayer + 1][i] == curse) {
   			count++;
   		}
   	}

   	printf("Number of curse cards for next player: %d, Expected number of curse cards for next player: %d\n", count, 1);

   	if(count == 0) {
   		printf("Test passed where other players don't gain a copy of the card that was revealed.\n");
   	} else {
   		printf("Test failed where other players gain a copy of the card that was revealed.\n");
   	}

   	printf("TEST 3 has completed.\n\n");

   	//test if player tries to discard more than they should be allowed to
   	printf("TEST 4: testing for invalid number of cards to discard.\n");

   	memcpy(&testG, &G, sizeof(struct gameState));

   	currentPlayer = whoseTurn(&G);

   	choice1 = 0;
   	choice2 = 3;

   	testG.hand[currentPlayer][0] = copper;
   	testG.hand[currentPlayer][1] = copper;
   	testG.hand[currentPlayer][2] = copper;
   	testG.hand[currentPlayer][3] = copper;
   	testG.hand[currentPlayer][4] = copper;

   	int status = ambassadorRefactored(choice1, choice2, &testG, handPos, currentPlayer);

   	if(status == -1) {
   		printf("Test passed for error checking on number of cards that can discarded.\n");
   	} else {
   		printf("Test failed for allowing player to discard 3 cards when should only discard two cards.\n");
   	}

   	printf("TEST 4 has completed.\n");

   	return 0;

}