/********************************************************************
* Author: Brian Sprague
* Assignment 3
* cardtest3.c
********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

int main ()
{
    int i, j;
    int numPlayers;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);
    int refDeck[MAX_DECK];
    int sameCards = 0;

    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        initializeGame(numPlayers, kCards, seed, &G);

        for (j = 0; j < numPlayers; j++)
        {
            print(" Current player: %d\n", (j + 1));
            assert(G.whoseTurn == j);
            endTurn(&G);
        }

        print(" Current player: %d\n", (j + 1));
        assert(G.whoseTurn == j);

        memset(&G, '\0', sizeof(struct gameState));
    }
    
    return 0;
}