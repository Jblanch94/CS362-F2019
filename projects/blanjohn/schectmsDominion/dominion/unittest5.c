#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define TESTCARD "Mine"

int main ()
{
	//set up state so game can be initialzed with parameters needed for minion function
    struct gameState G, testG;
    int seed = 1000;
    int numPlayers = 2;
    int i;
    int found = 0;
    int status;
    int currentPlayer = whoseTurn(&G);
    int handPos = 0;
    int choice1 = 0;
    int choice2 = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};   

    //set up game
    initializeGame(numPlayers, k, seed, &G);

    printf("-------------------------TESTING CARD: %s ------------------------\n", TESTCARD);

    memcpy(&testG, &G, sizeof(struct gameState));

    //test to make sure mine card was discarded
    printf("TEST 1: check if mine card was discarded.\n");

    playMine(&testG, currentPlayer, choice1, choice2, handPos);

    for(i = 0; i < numHandCards(&testG); i++)
    {
    	if(testG.hand[currentPlayer][i] == mine)
    	{
    		found = 1;
    	}
    }

    if(found == 1)
    {
    	printf("Test passed for discarding mine card.\n");
    } 

    else 
    {
    	printf("Test failed for not discarding mine card.\n");
    }

    printf("TEST 1 has completed.\n\n");

    //test that player gains a treasure card up to +3 of the one discarded
    printf("TEST 2: check if player gains a treasure card up to +3.\n");

    memcpy(&testG, &G, sizeof(struct gameState)); 

    choice1 = 0;
    choice2 = silver;
    found = 0;

    playMine(&testG, currentPlayer, choice1, choice2, handPos);

    testG.hand[currentPlayer][0] = copper;
    testG.hand[currentPlayer][1] = estate;
    testG.hand[currentPlayer][2] = mine;
    testG.hand[currentPlayer][3] = duchy;
    testG.hand[currentPlayer][4] = curse;  

    for(i = 0; i < numHandCards(&testG); i++)
    {
    	if(testG.hand[currentPlayer][i] == silver)
    	{
    		found = 1;
    	}
    }

    if(found == 1)
    {
    	printf("Test passed for adding treasure card up to +3 of the one discarded.\n");
    }

    else
    {
    	printf("Test failed for not adding treasure card up to +3 of the one discarded.\n");
    }

    printf("TEST 2 has completed.\n\n");

    //test if card selected is more than +3 than card discarded will be allowed or not
    printf("TEST 3: check if card more than +3 will not be allowed.\n");

    memcpy(&testG, &G, sizeof(struct gameState));
 

    choice1 = 0;
    choice2 = gold;

    playMine(&testG, currentPlayer, choice1, choice2, handPos);

    testG.hand[currentPlayer][0] = copper;
    testG.hand[currentPlayer][1] = estate;
    testG.hand[currentPlayer][2] = mine;
    testG.hand[currentPlayer][3] = duchy;
    testG.hand[currentPlayer][4] = curse;

   	for(i = 0; i < numHandCards(&testG); i++)
   	{
   		if(testG.hand[currentPlayer][i] == gold)
   		{
   			found = 1;
   		}
   	}

   	if(found == 1)
   	{
   		printf("Test failed for adding treasure card that is +3 more than card discarded.\n");
   	}

   	else 
   	{
   		printf("Test passed for not adding treasure card that is +3 more than card discarded.\n");
   	}

   	printf("TEST 3 has completed.\n\n");

   	//test if selected treasure card was trashed
   	printf("TEST 4: check if treasure card selected was discarded.\n");

   	memcpy(&testG, &G, sizeof(struct gameState));


   	choice1 = 0;
   	choice2 = silver;
   	found = 0;

   	playMine(&testG, currentPlayer, choice1, choice2, handPos);

    testG.hand[currentPlayer][0] = copper;
    testG.hand[currentPlayer][1] = estate;
    testG.hand[currentPlayer][2] = mine;
    testG.hand[currentPlayer][3] = duchy;
    testG.hand[currentPlayer][4] = curse; 


   	for(i = 0; i < numHandCards(&testG); i++)
   	{
   		if(testG.hand[currentPlayer][i] == copper)
   		{
   			found = 1;
   		}
   	}

   	if(found == 0 && (testG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + 1))
   	{
   		printf("Test passed for trashing selected treasure card.\n");
   	}

   	else 
   	{
   		printf("Test failed for not trashing selected trasure card.\n");
   	}


   	printf("TEST 4 has completed.\n\n");

   	//test for error checking if the selected was not between copper and gold
   	printf("TEST 5: check if a card selected is not between copper and gold.\n");

   	memcpy(&testG, &G, sizeof(struct gameState));

   	choice1 = curse;
   	choice2 = silver;
   	found = 0;

   	status = playMine(&testG, currentPlayer, choice1, choice2, handPos);

    testG.hand[currentPlayer][0] = copper;
    testG.hand[currentPlayer][1] = estate;
    testG.hand[currentPlayer][2] = mine;
    testG.hand[currentPlayer][3] = duchy;
    testG.hand[currentPlayer][4] = curse; 

   	if(status == -1)
   	{
   		printf("Test passed for not allowing a choice that is not between copper and gold.\n");
   	}

   	else
   	{
   		printf("Test failed for allowing a choice that is not between copper and gold.\n");
   	}

   	printf("TEST 5 has completed.\n\n");

   	//test if invalid card choice, i.e. does not exist throws error or not
   	printf("TEST 6: check if invalid choice throws error.\n");

   	memcpy(&testG, &G, sizeof(struct gameState));

   	choice1 = copper;
   	choice2 = 100;
   	found = 0;

   	status = playMine(&testG, currentPlayer, choice1, choice2, handPos);

   	if(status == -1)
   	{
   		printf("Test passed for not allowing an invalid choice to pass.\n");
   	}

   	else
   	{
   		printf("Test failed for not throwing error for invalid choice.\n");
   	}

   	printf("TEST 6 has completed.\n\n");


    return 0;
}