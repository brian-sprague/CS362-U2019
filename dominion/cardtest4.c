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
    int i;
    int numPlayers = 2;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int seed = time(0);
    int players[MAX_PLAYERS];

    printf("*******************************\n");
    printf("cardtest4.c TESTS - getWinners\n");
    printf("*******************************\n");
    printf("*******************************\n");
    printf("TEST 1: Player 1 wins outright.\n");
    printf("*******************************\n");

    // First player wins outright
    initializeGame(numPlayers, kCards, seed, &G);

    G.hand[0][0] = province;
    G.hand[0][1] = province;
    G.hand[0][2] = province;
    G.hand[0][3] = province;
    G.hand[0][4] = province;
    G.handCount[0] = 5;

    G.deck[0][0] = province;
    G.deck[0][1] = province;
    G.deck[0][2] = province;
    G.deck[0][3] = province;
    G.deck[0][4] = province;
    G.deckCount[0] = 5;

    G.discard[0][0] = province;
    G.discard[0][1] = province;
    G.discard[0][2] = province;
    G.discard[0][3] = province;
    G.discard[0][4] = province;
    G.discardCount[0] = 5;

    G.hand[1][0] = curse;
    G.hand[1][1] = estate;
    G.hand[1][2] = duchy;
    G.hand[1][3] = province;
    G.hand[1][4] = great_hall;
    G.hand[1][5] = gardens;
    G.handCount[1] = 6;

    G.deck[1][0] = curse;
    G.deck[1][1] = estate;
    G.deck[1][2] = duchy;
    G.deck[1][3] = province;
    G.deck[1][4] = great_hall;
    G.deck[1][5] = gardens;
    G.deckCount[1] = 6;

    G.discard[1][0] = curse;
    G.discard[1][1] = estate;
    G.discard[1][2] = duchy;
    G.discard[1][3] = province;
    G.discard[1][4] = great_hall;
    G.discard[1][5] = gardens;
    G.discardCount[1] = 6;

    getWinners(players, &G);

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (players[i] == 1)
        {
            printf("Player %d wins!\n", (i + 1));
        }
    }

    assert(players[0] == 1);
    memset(&G, '\0', sizeof(struct gameState));
    printf("*******************************\n");
    printf("TEST 2: Player 2 wins due to not having as many turns.\n");
    printf("*******************************\n");

    // Second player wins due to not having as many turns
    initializeGame(numPlayers, kCards, seed, &G);

    G.hand[0][0] = province;
    G.hand[0][1] = province;
    G.hand[0][2] = province;
    G.hand[0][3] = province;
    G.hand[0][4] = province;
    G.handCount[0] = 5;

    G.deck[0][0] = province;
    G.deck[0][1] = province;
    G.deck[0][2] = province;
    G.deck[0][3] = province;
    G.deck[0][4] = province;
    G.deckCount[0] = 5;

    G.discard[0][0] = province;
    G.discard[0][1] = province;
    G.discard[0][2] = province;
    G.discard[0][3] = province;
    G.discard[0][4] = province;
    G.discardCount[0] = 5;

    G.hand[1][0] = province;
    G.hand[1][1] = province;
    G.hand[1][2] = province;
    G.hand[1][3] = province;
    G.hand[1][4] = province;
    G.handCount[1] = 5;

    G.deck[1][0] = province;
    G.deck[1][1] = province;
    G.deck[1][2] = province;
    G.deck[1][3] = province;
    G.deck[1][4] = province;
    G.deckCount[1] = 5;

    G.discard[1][0] = province;
    G.discard[1][1] = province;
    G.discard[1][2] = province;
    G.discard[1][3] = province;
    G.discard[1][4] = province;
    G.discardCount[1] = 5;

    getWinners(players, &G);

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (players[i] == 1)
        {
            printf("Player %d wins!\n", (i + 1));
        }
    }

    assert(players[1] == 1);

    printf("*******************************\n");
    printf("TESTS COMPLETE.\n");
    printf("*******************************\n");
    
    return 0;
}