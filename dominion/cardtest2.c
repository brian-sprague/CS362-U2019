/********************************************************************
* Author: Brian Sprague
* Assignment 3
* cardtest1.c
********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

int main ()
{
    int i, j, k;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);
    int refDeck[MAX_DECK];
    int sameCards = 0;
    
    initializeGame(2, kCards, seed, &G);

    k = 0;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 5; j++)
        {
            G.deck[0][k] = kCards[i];
            refDeck[k] = kCards[i];
            k++;
        }
    }

    shuffle(0, &G);

    for (i = 2; i < MAX_DECK; i++)
    {
        if (G.deck[0][i] == refDeck[i] && G.deck[0][i-1] == refDeck[i-1] && G.deck[0][i-2] == refDeck[i-2])
        {
            sameCards++;
        }
    }

    printf("Amount of 3-card sequences from the old deck to new deck: %d / 500\n", sameCards);
    // assert(sameCards <= 200);


    return 0;
}