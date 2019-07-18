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
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);

    printf("*******************************\n");
    printf("cardtest3.c TESTS - endTurn\n");
    printf("*******************************\n");

    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        printf("*******************************\n");
        printf("TEST %d: %d Players.\n", i - 1, i);
        printf("*******************************\n");
        initializeGame(i, kCards, seed, &G);

        for (j = 0; j < i; j++)
        {
            printf("Current player: %d\n", G.whoseTurn + 1);
            assert(G.whoseTurn == j);
            endTurn(&G);
        }

        printf("Final player: %d\n", G.whoseTurn + 1);
        assert(G.whoseTurn == 0);

        memset(&G, '\0', sizeof(struct gameState));
    }
    
    printf("*******************************\n");
    printf("TESTS COMPLETE.\n");
    printf("*******************************\n");

    return 0;
}