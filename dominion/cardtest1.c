/********************************************************************
* Author: Brian Sprague
* Assignment 3
* cardtest1.c
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
    int i, j;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);
    int numEstates, numTreasure;

    printf("*******************************\n");
    printf("cardtest1.c TESTS - initializeGame\n");
    printf("*******************************\n");

    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        printf("*******************************\n");
        printf("TEST %d: %d Players.\n", i - 1, i);
        printf("*******************************\n");
        initializeGame(i, kCards, seed, &G);
        printf("Number of players: %d\n", G.numPlayers);
        assertTrue(G.numPlayers, i);
        printf("Number of curse cards: %d\n", G.supplyCount[curse]);
        if (i == 2)
        {
            assertTrue(G.supplyCount[curse], 10);
        }
        else if (i == 3)
        {
            assertTrue(G.supplyCount[curse], 20);
        }
        else
        {
            assertTrue(G.supplyCount[curse], 30);
        }

        printf("Number of estate cards: %d\n", G.supplyCount[estate]);
        printf("Number of duchy cards: %d\n", G.supplyCount[duchy]);
        printf("Number of province cards: %d\n", G.supplyCount[province]);
        if (i == 2)
        {
            assertTrue(G.supplyCount[estate], 8);
            assertTrue(G.supplyCount[duchy], 8);
            assertTrue(G.supplyCount[province], 8);
        }
        else
        {
            assertTrue(G.supplyCount[estate], 12);
            assertTrue(G.supplyCount[duchy], 12);
            assertTrue(G.supplyCount[province], 12);
        }

        printf("Number of copper cards: %d\n", G.supplyCount[copper]);
        printf("Number of silver cards: %d\n", G.supplyCount[silver]);
        printf("Number of gold cards: %d\n", G.supplyCount[gold]);
        assertTrue(G.supplyCount[copper], 60 - (7 * G.numPlayers));
        assertTrue(G.supplyCount[silver], 40);
        assertTrue(G.supplyCount[gold], 30);

        for (i = 0; i < G.numPlayers; i++)
        {
            numEstates = 0;
            numTreasure = 0;

            if(i == 0)
            {
                for (j = 0; j < G.deckCount[0]; j++)
                {
                    if (G.deck[i][j] == estate)
                    {
                        numEstates += 1;
                    }

                    else if (G.deck[i][j] == copper)
                    {
                        numTreasure += 1;
                    }
                }

                for (j = 0; j < G.handCount[0]; j++)
                {
                    if (G.hand[i][j] == estate)
                    {
                        numEstates += 1;
                    }

                    else if (G.hand[i][j] == copper)
                    {
                        numTreasure += 1;
                    }
                }

                printf("Amount of cards player %d has: %d\n", i, (G.deckCount[i] + G.handCount[i]));
                assertTrue((G.handCount[i] + G.deckCount[i]), 10);
                printf("Amount of cards player %d has in their hand: %d\n", i, G.handCount[i]);
                assertTrue(G.handCount[i], 5);
            }

            else
            {
                for (j = 0; j < 10; j++)
                {
                    if (G.deck[i][j] == estate)
                    {
                        numEstates += 1;
                    }

                    else if (G.deck[i][j] == copper)
                    {
                        numTreasure += 1;
                    }
                }

                printf("Amount of cards player %d has: %d\n", i, G.deckCount[i]);
                assertTrue(G.deckCount[i], 10);
            }
            
            
            printf("Player %d's # of estate cards: %d\n", i, numEstates);
            assertTrue(numEstates, 3);
            printf("Player %d's # of treasure cards: %d\n", i, numTreasure);
            assertTrue(numTreasure, 7);
        }
        
        memset(&G, '\0', sizeof(struct gameState));
    }

    printf("*******************************\n");
    printf("TEST COMPLETE.\n");
    printf("*******************************\n");

    return 0;
}