/********************************************************************
* Author: Brian Sprague
* Assignment 3
* unittest3.c
********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

void assertTrue(int val1, int val2)
{
    if (val1 == val2)
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
    int h, i, j, k;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);
    int playersCards[MAX_PLAYERS][MAX_HAND];
    int playersHandSize[MAX_PLAYERS];

    printf("*******************************\n");
    printf("unittest3.c TESTS - Ambassador\n");
    printf("*******************************\n");

    // Run test for all configurations of players
    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        for (j = 0; j < 3; j++)
        {
            // init a new game
            initializeGame(i, kCards, seed, &G);
            G.whoseTurn = 0;
            G.hand[0][0] = ambassador;
            G.hand[0][1] = copper;
            G.hand[0][2] = copper;
            G.hand[0][3] = copper;
            G.handCount[0] = 4;

            // Save the player's hand and handsize
            for (k = 0; k < G.numPlayers; k++)
            {
                for (h = 0; h < G.handCount[0]; h++)
                {
                    if (k == 0)
                    {
                        playersHandSize[k] = G.handCount[k];
                        playersCards[k][h] = G.hand[k][h];
                    }

                    else
                    {
                        playersHandSize[k] = G.discardCount[k];
                        playersCards[k][h] = G.discard[k][h];
                    }
                }
            }

            printf("*******************************\n");
            printf("TEST: %d players, %d coppers selected\n", i, j);
            printf("*******************************\n");
            // Play ambassador card
            playCard(0, 1, j, 0, &G);

            for (k = 0; k < i; k++)
            {
                printf("-------------------------------\n");
                printf("PLAYER %d\n", k);
                printf("-------------------------------\n");

                if (k == 0)
                {
                    printf("Size of player %d's hand: %d -> %d\n", k, playersHandSize[k], G.handCount[k]);
                    assertTrue(G.handCount[k], (2 - j));
                    for (h = 0; h < G.handCount[k]; h++)
                    {
                        printf("Before: %d || After: %d\n", playersCards[k][h], G.hand[k][h]);
                    }
                }

                else
                {
                    printf("Size of player %d's discard: %d -> %d\n", k, playersHandSize[k], G.discardCount[k]);
                    assertTrue(G.discardCount[k], 1);
                    for (h = 0; h < G.discardCount[k]; h++)
                    {
                        printf("Before: %d || After: %d\n", playersCards[k][h], G.discard[k][h]);
                        assertTrue(G.discard[k][h], copper);
                    }
                }
            }

            // Clear out the contents of gameState
            memset(&G, '\0', sizeof(struct gameState));
        }
    }

    printf("*******************************\n");
    printf("TESTS COMPLETE.\n");
    printf("*******************************\n");

    return 0;
}