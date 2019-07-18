/********************************************************************
* Author: Brian Sprague
* Assignment 3
* unittest5.c
********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

int main ()
{
    int numPlayers = 2;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);

    // init a new game
    initializeGame(numPlayers, kCards, seed, &G);
    G.whoseTurn = 0;
    G.hand[0][0] = mine;
    G.hand[0][1] = copper;
    G.handCount[0] = 2;

    playCard(0, G.hand[0][1], (G.hand[0][1] + 1), 0, &G);

    printf("Card in player's hand: %d\n", G.hand[0][0]);
    assert(G.hand[0][0] == 5);
    printf("Number of cards in player's hand: %d\n", G.handCount[0]);
    assert(G.handCount[0] == 1);

    return 0;
}