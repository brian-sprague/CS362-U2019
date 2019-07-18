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
    int i, j;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);
    int numEstates, numTreasure;

    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        initializeGame(i, kCards, seed, &G);
        printf("Number of players: %d\n", G.numPlayers);
        assert(G.numPlayers == i);
        printf("Number of curse cards: %d\n", G.supplyCount[curse]);
        if (i == 2)
        {
            assert(G.supplyCount[curse] == 10);
        }
        else if (i == 3)
        {
            assert(G.supplyCount[curse] == 20);
        }
        else
        {
            assert(G.supplyCount[curse] == 30);
        }

        

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
                assert((G.handCount[i] + G.deckCount[i]) == 10);
                printf("Amount of cards player %d has in their hand: %d\n", i, G.handCount[i]);
                assert(G.handCount[i] == 5);
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
                assert(G.deckCount[i] == 10);
            }
            
            
            printf("Player %d's # of estate cards: %d\n", i, numEstates);
            assert(numEstates == 3);
            printf("Player %d's # of treasure cards: %d\n", i, numTreasure);
            assert(numTreasure == 7);
        }
        
        
    }

    return 0;
}