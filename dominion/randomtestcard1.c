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

int NUM_TESTS = 20000;

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
    int numPlayer;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState preGame, postGame;
    int seed = time(0);
    int choice;
    int hasEstate;

    memset(&preGame, 23, sizeof(struct gameState));
    memset(&postGame, 23, sizeof(struct gameState));
    SelectStream(2);
    PutSeed(3);

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

        numPlayer = floor(Random() * MAX_PLAYERS);
        printf("Number of players: %d\n", numPlayer);

        if (numPlayer < 2 || numPlayer > MAX_PLAYERS)
        {
            continue;
        }
        else
        {

            // init a new game
            initializeGame(numPlayer, k, seed, &postGame);
            printf("Called initializeGame.\n");

            // Add baron card to the player's hand at index 0
            postGame.hand[postGame.whoseTurn][0] = baron;
            printf("Added baron card.\n");

            //Copy contents of postGame to pregame
            memcpy(&preGame, &postGame, sizeof(struct gameState));
            printf("Called memcpy.\n");

            choice = floor(Random() * 2);
            if (choice >= 1)
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
    }

    printf("*******************************\n");
    printf("TESTS COMPLETE.\n");
    printf("*******************************\n");

    return 0;
}