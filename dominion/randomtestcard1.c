/********************************************************************
* Author: Brian Sprague
* Assignment 4
* randomtestcard1.c
********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int NUM_TESTS = 2000000;

/***********************
 * asserTrue
 * Returns 0 if condition is false, 1 if true.
 * Set opt to the following values for different conditions:
 *      -2: <
 *      -1: <=
 *      0: ==
 *      1: >=
 *      2: >
***********************/
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
    double result;
    int numPlayer;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState preGame, postGame;
    int seed = time(0);
    int choice;
    int hasEstate;

    srand(time(0));
    memset(&preGame, 23, sizeof(struct gameState));
    memset(&postGame, 23, sizeof(struct gameState));

    /***************************
     * Player sells an estate
     **************************/
    printf("*******************************\n");
    printf("randomcardtest1.c TESTS - Baron\n");
    printf("*******************************\n");

    for (i = 0; i < NUM_TESTS; i++)
    {
        printf("*******************************\n");
        printf("TEST %d:\n", i + 1);
        printf("*******************************\n");

        result = rand() % 255;
        printf("Result is: %f", result);
        if (result < 85)
        {
            numPlayer = 2;
        }

        else if (result <= 85 && result < 172)
        {
            numPlayer = 3;
        }

        else
        {
            numPlayer = MAX_PLAYERS;
        }
        
        printf("Number of players: %d\n", numPlayer);

        // init a new game
        initializeGame(numPlayer, k, seed, &postGame);

        // Add baron card to the player's hand at index 0
        postGame.hand[postGame.whoseTurn][0] = baron;

        // Set various amounts of estate cards in the supply
        postGame.supplyCount[estate] = (rand() % 13) - 6;

        //Copy contents of postGame to pregame
        memcpy(&preGame, &postGame, sizeof(struct gameState));

        result = rand() % 20;
        printf("Result is: %f", result);
        if (result >= 10)
        {
            choice = 1;
        }

        else
        {
            choice = 0;
        }

        printf("Player's choice: %d\n", choice);
        

        // Play the baron card
        playCard(0, choice, -1, -1, &postGame);

        // Find if there are any estate cards in the player's hand
        for (j = 0; j < preGame.handCount[preGame.whoseTurn]; j++)
        {
            if (preGame.hand[preGame.whoseTurn][j] == estate)
            {
                hasEstate = 1;
            }
        }

        // Player chooses to gain an estate
        if (choice == 0)
        {
            printf("Estate supplyCount test: ");
            assertTrue(2, preGame.supplyCount[estate], postGame.supplyCount[estate]);
            printf("Player's discardCount test: ");
            assertTrue(-2, preGame.discardCount[postGame.whoseTurn], postGame.discardCount[postGame.whoseTurn]);
            printf("Player's handCount test: ");
            assertTrue(0, preGame.handCount[postGame.whoseTurn], (postGame.handCount[postGame.whoseTurn] + 1));
        }

        // Player chooses to discard estate but doesn't have one
        else if (choice == 1 && hasEstate == 0)
        {
            printf("Estate supplyCount test: ");
            assertTrue(2, preGame.supplyCount[estate], postGame.supplyCount[estate]);
            printf("Player's discardCount test: ");
            assertTrue(-2, preGame.discardCount[postGame.whoseTurn], postGame.discardCount[postGame.whoseTurn]);
            printf("Player's handCount test: ");
            assertTrue(0, preGame.handCount[postGame.whoseTurn], (postGame.handCount[postGame.whoseTurn] + 1));
        }

        // Player chooses to discard estate and has one
        else if(choice == 1 && hasEstate == 1)
        {
            printf("Estate supplyCount test: ");
            assertTrue(2, preGame.supplyCount[estate], postGame.supplyCount[estate]);
            printf("Player's discardCount test: ");
            assertTrue(-2, preGame.discardCount[postGame.whoseTurn], postGame.discardCount[postGame.whoseTurn]);
            printf("Player's handCount test: ");
            assertTrue(0, preGame.handCount[postGame.whoseTurn], (postGame.handCount[postGame.whoseTurn] + 2));
        }
        printf("Player's numBuys test: ");
        assertTrue(-2, preGame.numBuys, postGame.numBuys);

        // Clear out the contents of the gameStates
        memset(&preGame, '\0', sizeof(struct gameState));
        memset(&postGame, '\0', sizeof(struct gameState));
    }

    printf("*******************************\n");
    printf("TESTS COMPLETE.\n");
    printf("*******************************\n");

    return 0;
}