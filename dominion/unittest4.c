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
    int i;
    int numPlayers = 2;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);

    for (i = 0; i < 7; i++)
    {
        // init a new game
        initializeGame(numPlayers, kCards, seed, &G);
        G.whoseTurn = 0;
        G.hand[0][0] = tribute;
        G.handCount[0] = 1;

        if (i == 0) // single treasury card
        {
            G.deck[1][0] = copper;  // treasure / 4
            G.deckCount[1] = 1;
        }

        else if (i == 1) // single victory card
        {
            G.deck[1][0] = estate;  // victory / 1
            G.deckCount[1] = 1;
        }
        
        else if (i == 2) // single action card
        {
            G.deck[1][0] = feast;   // action / 9
            G.deckCount[1] = 1;
        }

        else if (i == 3) // two victory cards
        {
            G.deck[1][0] = estate;  // victory / 1
            G.deck[1][1] = estate;  // victory / 1
            G.deckCount[1] = 2;
        }
        
        else if (i == 4) // two action cards
        {
            G.deck[1][0] = feast;   // action / 9
            G.deck[1][1] = feast;   // action / 9
            G.deckCount[1] = 2;
        }

        else if (i == 5)
        {
            G.discard[1][0] = estate;
            G.discardCount[1] = 1;
            G.deckCount[1] = 0;
        }

        else if (i == 6)
        {
            G.discard[1][0] = estate;
            G.discardCount[1] = 1;
            G.deckCount[1] = 0;
        }

        // Play tribute card
        playCard(0, 0, 0, 0, &G);

        printf("*******************************\n");
        printf("TEST: %d\n", i);
        printf("*******************************\n");

        if (i == 0) // Play treasury card card
        {
            printf("Size of player 0's deck: %d\n", G.deckCount[0]);
            // assert(G.discardCount[0] == 1);
        }

        else if ( i == 1 || i == 3) // Play victory card
        {
            printf("Size of player 0's deck: %d\n", G.deckCount[0]);
            // assert(G.discardCount[0] == 1);
        }

        else if (i == 2 || i == 4)
        {
            printf("Size of player 0's deck: %d\n", G.deckCount[0]);
            // assert(G.discardCount[0] == 3);
            printf("Number of actions for player 0: %d\n", G.numActions);
            // assert(G.numActions == 3);
        }

        // Clear out the contents of gameState
        memset(&G, '\0', sizeof(struct gameState));
    }

    return 0;
}