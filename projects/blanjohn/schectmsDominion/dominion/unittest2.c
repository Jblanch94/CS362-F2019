#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define TESTCARD "Minion"

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

    //test for +1 action
    printf("TEST 1: Check for +1 action.\n");

    //copy state 
    memcpy(&testG, &G, sizeof(struct gameState));

    //doesnt matter what choice is +1 action should happen regardless
    choice1 = 0;
    choice2 = 0;

    //call function
    playMinion(&testG, handPos, currentPlayer, choice1, choice2);

    //print num actions and expected
    printf("number of actions: %d, Expected number of actions: %d\n", testG.numActions, G.numActions + 1);

    //test passed if added one action
    if(testG.numActions == G.numActions + 1) {
    	printf("Test passed checking for +1 action after minion card is played.\n");
    } else {
    	printf("Test failed checking for +1 action after minion card is played.\n");
    }

    printf("TEST 1 has completed.\n\n");


    //test if choice1 = 1 then add 2 coins to player
    printf("TEST 2: choice1 = 1 +2 coins.\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    choice1 = 1;

    playMinion(&testG, handPos, currentPlayer, choice1, choice2);

   	printf("Number of coins: %d, Expected Number of coins: %d\n", testG.coins, G.coins + 2);
   	if(testG.coins == G.coins + 2) {
   		printf("Test passed adding two coins for first choice.\n");
   	} else {
   		printf("Test failed for adding two coins for first choice.\n");
   	}

   	printf("TEST 2 has completed.\n\n");

   	//checks if the minion card was discarded and not any card from hand
   	printf("TEST 3: check if minion was discarded.\n");

   	memcpy(&testG, &G, sizeof(struct gameState));

   	playMinion(&testG, handPos, currentPlayer, choice1, choice2);

   	int numCards = numHandCards(&testG);
   	int found = 0;

   	printf("Number of cards in hand: %d, Expected number of cards in hand: %d\n", numCards, numHandCards(&G) - 1);

   	for(i = 0; i < 5; i++) {
   		if(testG.hand[currentPlayer][i] == minion) {
   			found = 1;

   		}
   	}

   	//if found minion card then test failed otherwise it passed
   	if(found == 1) {
   		printf("Test failed for not discarding minion card after used.\n");
   	} else {
   		printf("Test passed for  discarding minion card after used.\n");
   	}

   	printf("TEST 3 has completed.\n\n");

   	//checks if hand is discarded and checks hand count afterwards
   	printf("TEST 4: choice2 = 1 check if hand is discarded and 4 new cards are drawn.\n");

   	memcpy(&testG, &G, sizeof(struct gameState));

   	choice1 = 0;
   	choice2 = 1;

   	playMinion(&testG, handPos, currentPlayer, choice1, choice2);

   	
   	// test if cards were discarded
   	if(testG.discardCount[currentPlayer] != G.discardCount[currentPlayer]) {
   		printf("Test failed did not discard hand and draw new cards.\n");
   	} else {
   		printf("Test passed did discard hand and draw new cards.\n");
   	}

   	//test if four cards were drawn
   	printf("number of cards in hand: %d, expected number of cards in hand: %d\n", numHandCards(&testG), numHandCards(&G) - 1);

   	//passed if player has four cards
   	if(numHandCards(&testG) == numHandCards(&G) - 1) {
   		printf("Test passed with 4 cards in hand after redrawn.\n");
   	} else {
   		printf("Test failed with 4 cards not in hand after redrawn.\n");
   	}

   	printf("TEST 4 has completed.\n\n");

   	//same test as one above except for the next player
   	//only did it for next player since number of players is 2 but could have tested not matter the number of players
   	printf("TEST 5: choice2 = 1 check if hand is discarded and 4 cards redrawn for every  player.\n");


   	memcpy(&testG, &G, sizeof(struct gameState));

   	//currentPlayer = currentPlayer + 1;

    playMinion(&testG, handPos, currentPlayer, choice1, choice2);

   	if(testG.discardCount[currentPlayer] != G.discardCount[currentPlayer]) {
   		printf("Test failed did not discard hand and draw new cards.\n");
   	} else {
   		printf("Test passed did discard hand and draw new cards.\n");
   	}

   	printf("number of cards in hand: %d, expected number of cards in hand: %d\n", numHandCards(&testG), numHandCards(&G) - 1);

   	if(numHandCards(&testG) == numHandCards(&G) - 1) {
		printf("Test passed player has 4 cards in hand.\n");
	} else {
		printf("Test failed player does not have 4 cards in hand.\n");
	}

	printf("TEST 5 has completed.\n\n");

   	


    return 0;
}