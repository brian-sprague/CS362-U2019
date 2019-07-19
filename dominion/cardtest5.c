/********************************************************************
* Author: Brian Sprague
* Assignment 3
* cardtest3.c
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
    int numPlayers = 2;
    int i;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);

    // Test drawing from deck

    printf("*******************************\n");
    printf("cardtest5.c TESTS - drawCard\n");
    printf("*******************************\n");
    printf("*******************************\n");
    printf("TEST 1: Player draws from deck.\n");
    printf("*******************************\n");

    initializeGame(numPlayers, kCards, seed, &G);
    
    drawCard(0, &G);
    printf("Size of the player's hand: %d\n", G.handCount[0]);
    assertTrue(G.handCount[0], 6);
    printf("Size of player's discard: %d\n", G.discardCount[0]);
    assertTrue(G.discardCount[0], 0);
    printf("Size of player's deck: %d\n", G.deckCount[0]);
    assertTrue(G.deckCount[0], 4);

    memset(&G, '\0', sizeof(struct gameState));

    // Test empty deck, moving cards from discard

    printf("*******************************\n");
    printf("TEST 2: Player draws from empty deck.\n");
    printf("*******************************\n");

    initializeGame(numPlayers, kCards, seed, &G);

    // Move cards in hand to discard
    for (i = 0; i < 5; i++)
    {
        G.discard[0][i] = G.hand[0][i];
        G.discardCount[0]++;
        G.hand[0][i] = -1;
        G.handCount[0]--;
    }

    // Move cards in deck to discard
    for (i = 0; i < 5; i++)
    {
        G.discard[0][i] = G.deck[0][i];
        G.discardCount[0]++;
        G.deck[0][i] = -1;
        G.deckCount[0]--;
    }
    
    drawCard(0, &G);
    printf("Size of the player's hand: %d\n", G.handCount[0]);
    assertTrue(G.handCount[0], 1);
    printf("Size of player's discard: %d\n", G.discardCount[0]);
    assertTrue(G.discardCount[0], 0);
    printf("Size of player's deck: %d\n", G.deckCount[0]);
    assertTrue(G.deckCount[0], 9);

    printf("*******************************\n");
    printf("TESTS COMPLETE.\n");
    printf("*******************************\n");
    
    return 0;
}