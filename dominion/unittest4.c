/********************************************************************
* Author: Brian Sprague
* Assignment 3
* unittest4.c
********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

int main ()
{
    int h, i, j, k;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);
    int playersCards[MAX_PLAYERS][MAX_HAND];
    int playersHandSize[MAX_PLAYERS];

    for (i = 0; i < 5; i++)
    {
        // init a new game
        initializeGame(i, kCards, seed, &G);
        G.whoseTurn = 0;
        G.hand[0][0] = tribute;
        G.handCount[0] = 1;

        if (i == 0) // single treasury card
        {
            G.hand[1][0] = copper;  // treasure / 4
            G.handCount[1] = 1;
        }

        else if (i == 1) // single victory card
        {
            G.hand[1][0] = estate;  // victory / 1
            G.handCount[1] = 1;
        }
        
        else if (i == 2) // single action card
        {
            G.hand[1][0] = feast;   // action / 9
            G.handCount[1] = 1;
        }

        else if (i == 3) // two victory cards
        {
            G.hand[1][0] = estate;  // victory / 1
            G.hand[1][1] = estate;  // victory / 1
            G.handCount[1] = 2;
        }
        
        else if (i == 4) // two action cards
        {
            G.hand[1][0] = feast;   // action / 9
            G.hand[1][1] = feast;   // action / 9
            G.handCount[1] = 2;
        }

        // Play tribute card
        playCard(0, 0, 0, 0, &G);

        printf("*******************************\n");
        printf("TEST: %d\n", i);
        printf("*******************************\n");

        if (i == 0) // Play treasury card card
        {
            printf("Size of player 0's discard: %d\n", G.discardCount[0]);
            // assert(G.discardCount[0] == 1);
        }

        else if ( i == 1 || i == 3) // Play victory card
        {
            printf("Size of player 0's discard: %d\n", G.discardCount[0]);
            // assert(G.discardCount[0] == 1);
            printf("Number of actions for player 0: %d\n", G.numActions);
            // assert(G.numActions == 3);
        }

        else if (i == 2 || i == 4)
        {
            printf("Size of player 0's discard: %d\n", G.discardCount[0]);
            // assert(G.discardCount[0] == 3);
        }
    }

    // Clear out the contents of gameState
    memset(&G, '\0', sizeof(struct gameState));

    return 0;
}