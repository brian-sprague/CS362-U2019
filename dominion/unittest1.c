/********************************************************************
* Author: Brian Sprague
* Assignment 3
* unittest1.c
********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

int main ()
{
    int i;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);

    memset(&G, 23, sizeof(struct gameState));

    /***************************
     * Player sells an estate
     **************************/

    // init a new game
    initializeGame(numPlayer, k, seed, &G);

    // Clear out hand and add baron and estate cards to player's hand
    for (i = 0; i < 5; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }
    G.hand[G.whoseTurn][0] = baron;
    G.hand[G.whoseTurn][1] = estate;
    G.handCount[G.whoseTurn] = 2;
    G.coins = 0;

    // Play the baron card
    playCard(0, 1, -1, -1, &G);

    printf("*******************************\n");
    printf("TEST 1: Player sells an estate.\n");
    printf("*******************************\n");
    printf("Player's hand where there should be an estate: %d\n",  G.hand[G.whoseTurn][1]);
    // assert( G.hand[G.whoseTurn][1] == -1);
    printf("Player's coins: %d\n",  G.coins);
    // assert( G.coins == 4);
    printf("Player's numBuys: %d\n",  G.numBuys);
    // assert( G.numBuys == 2);

    // Clear out the contents of gameState
    memset(&G, '\0', sizeof(struct gameState));

    /*************************************
     * Player chooses to draw an estate
     *************************************/

    // init a new game
    initializeGame(numPlayer, k, seed, &G);

    // Clear out hand and add baron and estate cards to player's hand
    for (i = 0; i < 5; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }
    G.hand[G.whoseTurn][0] = baron;
    G.handCount[G.whoseTurn] = 1;
    G.coins = 0;

    // Play the baron card
    playCard(0, 0, -1, -1, &G);

    printf("*******************************\n");
    printf("TEST 2: Player chooses to draw an estate.\n");
    printf("*******************************\n");
    printf("Player's discard where there should be an estate: %d\n", G.discard[G.whoseTurn][G.discardCount[G.whoseTurn]]);
    // assert( G.discard[G.whoseTurn][G.discardCount[G.whoseTurn]] == estate);
    printf("Player's coins: %d\n",  G.coins);
    // assert( G.coins == 0);
    printf("Player's numBuys: %d\n",  G.numBuys);
    // assert( G.numBuys == 2);

    // Clear out the contents of gameState
    memset(&G, '\0', sizeof(struct gameState));


    /*************************************
     * Player chooses to sell an estate
     * without having an estate
     *************************************/

    // init a new game
    initializeGame(numPlayer, k, seed, &G);

    // Clear out hand and add baron and estate cards to player's hand
    for (i = 0; i < 5; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }
    G.hand[G.whoseTurn][0] = baron;
    G.hand[G.whoseTurn][1] = -1;
    G.handCount[G.whoseTurn] = 1;
    G.coins = 0;

    // Play the baron card
    playCard(0, 1, -1, -1, &G);

    printf("*******************************\n");
    printf("TEST 3: Player chooses to sell an estate but has to draw an estate.\n");
    printf("*******************************\n");
    printf("Player's discard where there should be an estate: %d\n",  G.discard[G.whoseTurn][G.discardCount[G.whoseTurn]]);
    // assert( G.discard[G.whoseTurn][G.discardCount[G.whoseTurn]] == estate);
    printf("Player's coins: %d\n",  G.coins);
    // assert( G.coins == 0);
    printf("Player's numBuys: %d\n",  G.numBuys);
    // assert( G.numBuys == 2);


    return 0;
}