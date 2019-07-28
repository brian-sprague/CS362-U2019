/********************************************************************
* Author: Brian Sprague
* Assignment 4
* randomtesrcard3.c
********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

int NUM_TESTS = 200000;

int assertTrue(int opt, int val1, int val2)
{
    if (opt == -2)
    {
        if (val1 < val2)
        {
            printf("TEST PASSES.\n");
            return 1;
        }

        else
        {
            printf("TEST FAILS.\n");
            return 0;
        }
    }

    else if(opt == -1)
    {
        if (val1 <= val2)
        {
            printf("TEST PASSES.\n");
            return 1;
        }

        else
        {
            printf("TEST FAILS.\n");
            return 0;
        }
    }

    else if(opt == 0)
    {
        if (val1 == val2)
        {
            printf("TEST PASSES.\n");
            return 1;
        }

        else
        {
            printf("TEST FAILS.\n");
            return 0;
        }
    }

    else if(opt == 1)
    {
        if (val1 >= val2)
        {
            printf("TEST PASSES.\n");
            return 1;
        }

        else
        {
            printf("TEST FAILS.\n");
            return 0;
        }
    }

    else if(opt == 2)
    {
        if (val1 > val2)
        {
            printf("TEST PASSES.\n");
            return 1;
        }

        else
        {
            printf("TEST FAILS.\n");
            return 0;
        }
    }

    else
    {
        printf("Invalid value entered for opt. Please change.\n");
        exit(1);
    }
}

int main ()
{
    int i, j;
    int numPlayers = 2;
    int kCards[10] = {adventurer, council_room, feast, steward, mine,
                 remodel, copper, village, baron, great_hall};
    struct gameState preGame, postGame;
    int seed = time(0);
    int card, numDrawCards;

    srand(time(0));
    memset(&preGame, 23, sizeof(struct gameState));
    memset(&postGame, 23, sizeof(struct gameState));


    printf("*******************************\n");
    printf("randomtesrcard3.c TESTS - Tribute\n");
    printf("*******************************\n");

    for (i = 0; i < NUM_TESTS; i++)
    {
        // init a new game
        initializeGame(numPlayers, kCards, seed, &postGame);
        postGame.hand[0][0] = tribute;

        // Set the opposing player's deck
        postGame.deckCount[1] = rand() % MAX_DECK;
        for (j = 0; j < postGame.deckCount[1]; j++)
        {
            card = rand() % 10;
            postGame.deck[1][j] = kCards[card];

        }

        numDrawCards = rand() % MAX_HAND;
        for (j = 0; j < numDrawCards; j++)
        {
            drawCard(1, &postGame);
        }

        //Copy contents of postGame to pregame
        memcpy(&preGame, &postGame, sizeof(struct gameState));

        // Play tribute card
        playCard(0, 0, 0, 0, &G);

        printf("*******************************\n");
        printf("TEST: %d\n", i + 1);
        printf("*******************************\n");

        if (postGame.discardCount[1] == 2) // Revealed single card
        {
            // Played action card
            if (postGame.discard[1][2] >= 7)
            printf("Player 1's numActions: %d\n", postGame.numActions);
            assertTrue(0, preGame.numActions, postGame.numActions - 2);

            // Played victory card
            else if (postGame.discard[1][2] <= 3)
            printf("Player 1's handCount: %d\n", postGame.handCount[0]);
            assertTrue(0, preGame.handCount[0], postGame.handCount[0] - 2);

            else
            {
                printf("Player 1's numActions: %d\n", postGame.numActions);
                assertTrue(0, preGame.numActions, postGame.numActions);
                printf("Player 1's handCount: %d\n", postGame.handCount[0]);
                assertTrue(0, preGame.handCount[0], postGame.handCount[0]);
            }
            
        }

        else if (postGame.discardCount[1] == 3) // Revealed two cards
        {
            // Played action card
            if (postGame.discard[1][3] >= 7)
            printf("Player 1's numActions: %d\n", postGame.numActions);
            assertTrue(0, preGame.numActions, postGame.numActions - 2);

            // Played victory card
            else if (postGame.discard[1][3] <= 3)
            printf("Player 1's handCount: %d\n", postGame.handCount[0]);
            assertTrue(0, preGame.handCount[0], postGame.handCount[0] - 2);

            else
            {
                printf("Player 1's numActions: %d\n", postGame.numActions);
                assertTrue(0, preGame.numActions, postGame.numActions);
                printf("Player 1's handCount: %d\n", postGame.handCount[0]);
                assertTrue(0, preGame.handCount[0], postGame.handCount[0]);
            }

            // Played action card
            if (postGame.discard[1][2] >= 7)
            printf("Player 1's numActions: %d\n", postGame.numActions);
            assertTrue(0, preGame.numActions, postGame.numActions - 2);

            // Played victory card
            else if (postGame.discard[1][2] <= 3)
            printf("Player 1's handCount: %d\n", postGame.handCount[0]);
            assertTrue(0, preGame.handCount[0], postGame.handCount[0] - 2);

            else
            {
                printf("Player 1's numActions: %d\n", postGame.numActions);
                assertTrue(0, preGame.numActions, postGame.numActions);
                printf("Player 1's handCount: %d\n", postGame.handCount[0]);
                assertTrue(0, preGame.handCount[0], postGame.handCount[0]);
            }
        }

        // Revealed no cards
        else
        {
            printf("Player 1's numActions: %d\n", postGame.numActions);
            assertTrue(0, preGame.numActions, postGame.numActions);
            printf("Player 1's handCount: %d\n", postGame.handCount[0]);
            assertTrue(0, preGame.handCount[0], postGame.handCount[0]);
        }
        

        // Clear out the contents of gameState
        memset(&postGame, '\0', sizeof(struct gameState));
        memset(&preGame, '\0', sizeof(struct gameState));
    }

    printf("*******************************\n");
    printf("TESTS COMPLETE.\n");
    printf("*******************************\n");

    return 0;
}