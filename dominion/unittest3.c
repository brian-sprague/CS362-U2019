/********************************************************************
* Author: Brian Sprague
* Assignment 3
* unittest3.c
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

    // Run test for all configurations of players
    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("*******************************\n");
            printf("TEST %d\n", (i - 1));
            printf("*******************************\n");
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
                    for (h = 0; h < G.handCount[k]; h++)
                    {
                        printf("Before: %d || After: %d\n", playersCards[k][h], G.hand[k][h]);
                    }
                }

                else
                {
                    printf("Size of player %d's discard: %d -> %d\n", k, playersHandSize[k], G.discardCount[k]);
                    for (h = 0; h < G.discardCount[k]; h++)
                    {
                        printf("Before: %d || After: %d\n", playersCards[k][h], G.discard[k][h]);
                    }
                }
            }

            // Clear out the contents of gameState
            memset(&G, '\0', sizeof(struct gameState));
        }
    }

    return 0;
}