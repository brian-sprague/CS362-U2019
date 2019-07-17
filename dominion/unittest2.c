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
    int i, j, h;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);
    int playersCards[MAX_PLAYERS][MAX_HAND];
    int playersHandSize[MAX_PLAYERS];

    // Run test for all configurations of players
    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        printf("*******************************\n");
        printf("TEST %d\n", (i - 1));
        printf("*******************************\n");
        // init a new game
        initializeGame(i, k, seed, &G);

        // Save the player's hand and handsize
        for (j = 0; j < G.handCount[0]; j++)
        {
            playersCards[0][j] = G.hand[0][j];
        }
        playersHandSize[0] = G.handCount[0];

        G.hand[0][0] = minion;

        // Call drawCards x5 for all other players until they have 5
        for (j = 1; j < i; j++)
        {
            // Give even mnumbered players 4 cards
            if (j % 2 == 0)
            {
                for (h = 0; h < 4; h++)
                {
                    drawCard(j, &G);
                }
            }

            // Give everyone else 5 cards
            else
            {
                for (h = 0; h < 5; h++)
                {
                    drawCard(j, &G);
                }
            }
            
            // Save the player's hand and handsize
            for (h = 0; h < G.handCount[0]; h++)
            {
                playersCards[j][h] = G.hand[j][h];
            }
            playersHandSize[j] = G.handCount[j];
        }

        // Play minion card
        playCard(0, 0, 1, 0, &G);

        // Check the player's hands
        for (j = 0; j < i; j++)
        {
            printf("-------------------------------\n");
            printf("PLAYER %d\n", j);
            printf("-------------------------------\n");

            // check starting player's hand
            if (j == 0)
            {
                printf("Size of player %d's hand was: %d\n", j, playersHandSize[j]);
                printf("Size of player %d's hand is: %d\n", j, G.handCount[j]);
                // assert(G.handCount[j] == 4);
            }

            else if (j % 2 == 0)
            {
                printf("Size of player %d's hand: %d -> %d\n", j, playersHandSize[j], G.handCount[j]);
                // assert(G.handCount[j] == playersHandSize[j]);
                for (h = 0; h < G.handCount[j]; h++)
                {
                    printf("Expected: %d || Found: %d\n", playersCards[j][h], G.hand[j][h]);
                    // assert(playersCards[j][h] == G.hand[j][h]);
                }
            }

            else
            {
                printf("Size of player %d's hand: %d -> %d\n", j, playersHandSize[j], G.handCount[j]);
                // assert(G.handCount[j] < playersHandSize[j]);
                for (h = 0; h < G.handCount[j]; h++)
                {
                    printf("Expected: %d || Found: %d\n", playersCards[j][h], G.hand[j][h]);
                }
            }
        }

        // Clear out the contents of gameState
        memset(&G, '\0', sizeof(struct gameState));
    }

    return 0;
}