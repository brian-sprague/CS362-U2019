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
    int numPlayers = 2;
    int i;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);

    // Test drawing from deck

    initializeGame(numPlayers, kCards, seed, &G);
    
    drawCard(0, &G);
    printf("Size of the player's hand: %d\n", G.handCount[0]);
    assert(G.handCount[0] == 6);
    printf("Size of player's discard: %d\n", G.discardCount[0]);
    assert(G.discardCount[0] == 0);
    printf("Size of player's deck: %d\n", G.deckCount[0]);
    assert(G.deckCount[0] == 4);

    memset(&G, '\0', sizeof(struct gameState));

    // Test empty deck, moving cards from discard

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
    assert(G.handCount[0] == 1);
    printf("Size of player's discard: %d\n", G.discardCount[0]);
    assert(G.discardCount[0] == 0);
    printf("Size of player's deck: %d\n", G.deckCount[0]);
    assert(G.deckCount[0] == 9);
    
    return 0;
}