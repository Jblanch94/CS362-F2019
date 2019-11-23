#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define TESTCARD "Tribute"

int main ()
{
	//set up state so game can be initialzed with parameters needed for minion function
    struct gameState G, testG;
    int seed = 1000;
    int numPlayers = 2;
    int i;
    int found = 0;
    int currentPlayer = whoseTurn(&G);
    int nextPlayer = currentPlayer + 1;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room}; 
    int revealedCards[2];  

    //start game
    initializeGame(numPlayers, k, seed, &G);

    printf("-------------------------TESTING CARD: %s ------------------------\n", TESTCARD);

    //check if tribute card was discarded
    printf("TEST 1: Check if tribute card was discarded.\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    //get number of cards in hand
    int numCards = numHandCards(&testG);

    //call tribute card function
    playTribute(&testG, nextPlayer, currentPlayer);

    //if find tribute card in hand then it was not discarded so test failed otherwise passed
    for(i = 0; i < numCards; i++) 
    {
    	if(testG.hand[currentPlayer][i] == tribute)
    	{
    		found = 1;
    	}
    }

    if(found == 1)
    {
    	printf("Test failed did not discard tribute card.\n");
    }
    else 
    {
    	printf("Test passed did discard tribute card.\n");
    }

    printf("TEST 1 has completed.\n\n");


    //test if one of the revealed cards is coin card player gets +2 coins
    printf("TEST 2: check if revealed card is coin type that you gain +2 coins.\n");

    memcpy(&testG, &G, sizeof(struct gameState));


    playTribute(&testG, nextPlayer, currentPlayer);

    revealedCards[0] = copper;

    printf("Number of coins: %d, Expected number of coins: %d\n", testG.coins, G.coins + 2);

    if(testG.coins == G.coins + 2)
    {
    	printf("Test passed for 1 revealed card of coin type added two coins to player.\n");
    }
    else 
    {
    	printf("Test failed did not add two coins to player for revealed card of coin type.\n");
    }

    printf("TEST 2 has completed.\n\n");


    //test for two different named coin cards player gets +4 coins
    printf("TEST 3: check if two revealed cards of different names yields +4 coins.\n");


    memcpy(&testG, &G, sizeof(struct gameState));

    playTribute(&testG, nextPlayer, currentPlayer);

    revealedCards[0] = copper;
    revealedCards[1] = silver;

    printf("Number of coins: %d, Expected number of coins: %d\n", testG.coins, G.coins + 4);

    if(testG.coins == G.coins + 4)
    {
    	printf("Test passed added four coins to player when revealed two coin type cards of different names.\n");
    }
    else 
    {
    	printf("Test failed did not add four coins to player when revealed two coin type cards of different names.\n");
    }


    printf("TEST 3 has completed.\n\n");

    //test if no coin cards that player gets +0 coins
    printf("TEST 4: check if neither of the revealed cards are coin types and make sure player does not get any coins.\n");

    initializeGame(numPlayers, k, seed, &G);

    memcpy(&testG, &G, sizeof(struct gameState));


    playTribute(&testG, nextPlayer, currentPlayer);

    revealedCards[0] = estate;
    revealedCards[1] = gardens;

    printf("Number of coins: %d, Expected number of coins: %d\n", testG.coins, G.coins);

    if(testG.coins == G.coins)
    {
    	printf("Test passed for not adding any coins to player when no coin type cards were revealed.\n");
    }
    else 
    {
    	printf("Test failed for adding coins to player when no coin type cards were revealed.\n");
    }

   printf("TEST 4 has completed.\n\n");

   //test if 1 action card revealed player gets +2 action
   printf("TEST 5: check if number of actions increases by 2 for an action type card revealed.\n");

   memcpy(&testG, &G, sizeof(struct gameState));

   playTribute(&testG, nextPlayer, currentPlayer);

   revealedCards[0] = baron;
   revealedCards[1] = estate;

   printf("Number of actions: %d, Expected number of actions: %d\n", testG.numActions, G.numActions + 2);

   if(testG.numActions == G.numActions + 2)
   {
   	printf("Test passed for increasing number of actions by 2 for given player.\n");
   }
   else
   {
   	printf("Test failed for not increasing number of actions by 2 for given player.\n");
   }

   printf("TEST 5 has completed.\n\n");

   //test for two different action cards revealed yields +4 action for player
   printf("TEST 6: check if two different action cards revealed yields +4 action.\n");

   memcpy(&testG, &G, sizeof(struct gameState));

   playTribute(&testG, nextPlayer, currentPlayer);

  revealedCards[0] = baron;
  revealedCards[1] = mine;


   printf("Number of actions: %d, Expected number of actions: %d\n", testG.numActions, G.numActions  + 4);

   if(testG.numActions == G.numActions + 4)
   {
   	printf("Test passed for adding 4 actions to player for two revealed action cards of different names.\n");
   }
   else
   {
   	printf("Test failed for not adding 4 actions to player for two revealed action cards of different names.\n");
   }


   printf("TEST 6 has completed.\n\n");

   //test for no action cards revealed player does not gain any action
   printf("TEST 7: check if no action cards revealed player does not gain any action.\n");

   memcpy(&testG, &G, sizeof(struct gameState));

   playTribute(&testG, nextPlayer, currentPlayer);

   revealedCards[0] = copper;
   revealedCards[1] = copper;

   printf("Number of actions: %d, Expected number of actions: %d\n", testG.numActions, G.numActions);

   if(testG.numActions == G.numActions)
   {
   	printf("Test passed for not rewarding player with any actions for no revealed action cards.\n");
   }

   else
   {
   	printf("Test failed for rewarding player with actions for no revealed action cards.\n");
   }


   printf("TEST 7 has completed.\n\n");

   //test if player draws two cards if one revealed card is a victory card
   printf("TEST 8: check if revealed card has one victory that player draws two cards.\n");
   
   memcpy(&testG, &G, sizeof(struct gameState));

   playTribute(&testG, nextPlayer, currentPlayer);

   revealedCards[0] = estate;
   revealedCards[1] = copper;

   //check if added one card to hand, should be same since discarded tribute card then add one card to hand should be 5
   printf("Number of cards in hand: %d, Expected number of cards in hand: %d\n", numHandCards(&testG), numHandCards(&G));

   if(numHandCards(&testG) == numHandCards(&G)) {
   	printf("Test passed for adding one card to hand.\n");
   } else {
   		printf("Test failed for not adding exactly one card to hand.\n");
   }


   printf("TEST 8 has completed.\n\n");

   //test if player draws four cards for two different named victory cards
   printf("TEST 9: check if 2 victory yields player drawing four cards.\n");

   memcpy(&testG, &G, sizeof(struct gameState));

   playTribute(&testG, nextPlayer, currentPlayer);

    revealedCards[0] = estate;
    revealedCards[1] = province;

   printf("Number of cards in hand: %d, Expected number of cards in hand: %d\n", numHandCards(&testG), numHandCards(&G) + 3);

   if(numHandCards(&testG) == numHandCards(&G)) {
   	printf("Test passed for adding two cards to player's hand.\n");
   } else {
   	printf("Test failed for not adding exactly two cards to player's hand.\n");
   }


   printf("TEST 9 has completed.\n\n");

   //test if 2 victory cards with same name yield +2 cards 
   printf("TEST 10: check if 2 victory cards with same name yield draw of 2 cards.\n");

   memcpy(&testG, &G, sizeof(struct gameState));


   playTribute(&testG, nextPlayer, currentPlayer);

   revealedCards[0] = estate;
   revealedCards[1] = estate;

   printf("Number of cards in hand: %d, Expected number of cards in hand: %d\n", numHandCards(&testG), numHandCards(&G) + 1);

   if(numHandCards(&testG) == numHandCards(&G) + 1)
   {
   		printf("Test passed for adding two cards to player's hand.\n");
   }

   else 
   {
   		printf("Test failed for not adding two cards to player's hand.\n");
   }


   printf("TEST 10 has completed.\n");


   //test if no victory cards that player does not gain any cards
   printf("TEST 11: check if no victory cards does not add cards to player's hand.\n");

   memcpy(&testG, &G, sizeof(struct gameState));


   playTribute(&testG, nextPlayer, currentPlayer);

   revealedCards[0] = copper;
   revealedCards[1] = gold;

   printf("Number of cards in hand: %d, Expected number of cards in hand: %d\n", numHandCards(&testG), numHandCards(&G) - 1);

   if(numHandCards(&testG) == numHandCards(&G) - 1) {
   	printf("Test passed for not adding any cards to player's hand.\n");
   } else {
   	printf("Test failed for adding cards to player's hand.\n");
   }


   printf("TEST 11 has completed.\n\n");

   printf("TEST 12: check if player to left discarded two cards.\n");

   memcpy(&testG, &G, sizeof(struct gameState));

   playTribute(&testG, nextPlayer, currentPlayer);

   revealedCards[0] = copper;
   revealedCards[1] = silver;

   printf("Number of cards discarded for left player: %d, Expected number of cards discarded for left: %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer] + 2);

   if(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer] + 2) {
   	printf("Test passed for discarding top 2 cards.\n");
   } else {
   	printf("Test failed for not discarding top 2 cards.\n");
   }

   printf("TEST 12 has completed.\n\n");


    return 0;
}