/********************************************************************
* Author: Brian Sprague
* Assignment 3
* cardtest2.c
********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

void assertTrue(int val1, int val2)
{
    if (val1 < val2)
    {
        printf("TEST PASSES.\n");
    }

    else
    {
        printf("TEST FAILS.\n");
    }
}

int main ()
{
    int i, j, k;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);
    int refDeck[MAX_DECK];
    int sameCards = 0;

    printf("*******************************\n");
    printf("cardtest2.c TEST - shuffle\n");
    printf("*******************************\n");
    printf("*******************************\n");
    printf("TEST: Cards should be in new order after shuffling.\n");
    printf("*******************************\n");
    
    initializeGame(2, kCards, seed, &G);

    k = 0;
    for (i = 0; i < 25; i++)
    {
        for (j = 0; j < 20; j++)
        {
            G.deck[0][k] = i;
            G.deckCount[0]++;
            refDeck[k] = i;
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
    assertTrue(sameCards, 200);

    printf("*******************************\n");
    printf("TEST COMPLETE.\n");
    printf("*******************************\n");

    return 0;
}