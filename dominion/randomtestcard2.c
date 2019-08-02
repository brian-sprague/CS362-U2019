/********************************************************************
* Author: Brian Sprague
* Assignment 4
* randomcardtest2.c
********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

int NUM_TESTS = 2000000;

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
    int i, j, h;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState preGame, postGame;
    int seed = time(0);
    int numPlayer, numCards;
    int choice1, choice2;
    double result;

    srand(time(0));
    memset(&preGame, 23, sizeof(struct gameState));
    memset(&postGame, 23, sizeof(struct gameState));

    printf("*******************************\n");
    printf("randomtestcard2.c TESTS - Minion\n");
    printf("*******************************\n");

    // Run test for all configurations of players
    for (i = 0; i < NUM_TESTS; i++)
    {
        printf("*******************************\n");
        printf("TEST %d\n", i + 1);
        printf("*******************************\n");

        result = rand() % 255;
        // printf("Result is: %d", result);
        if (result < 85)
        {
            numPlayer = 2;
        }

        else if (result >= 85 && result < 172)
        {
            numPlayer = 3;
        }

        else
        {
            numPlayer = MAX_PLAYERS;
        }

        // init a new game
        initializeGame(numPlayer, k, seed, &postGame);

        // Call drawCard a random amount of times between 0 and 9
        for (j = 1; j < postGame.numPlayers; j++)
        {
            numCards = rand() % 10;
            for (h = 0; h < numCards; h++)
            {
                drawCard(j, &postGame);
            }
        }

        // Add baron card to the player's hand at index 0
        postGame.hand[postGame.whoseTurn][0] = minion;

        //Copy contents of postGame to pregame
        memcpy(&preGame, &postGame, sizeof(struct gameState));

        //Set choice1 to either 1 or 0
        result = rand() % 20;
        printf("result is: %d\n", choice1);
        if (result >= 10)
        {
            choice1 = 1;
        }

        else
        {
            choice1 = 0;
        }

        // Set choice1 to either 1 or 0
        result = rand() % 20;
        printf("result is: %d\n", choice2);
        if (result >= 10)
        {
            choice2 = 1;
        }

        else
        {
            choice2 = 0;
        }

        // Play minion card
        playCard(0, choice1, choice2, 0, &postGame);

        
        

        // Player chooses to gain coins
        if (choice1 == 1 || (choice1 == 0 && choice2 == 0))
        {
            printf("Player 1's discardCount test: ");
            assertTrue(0, preGame.discardCount[postGame.whoseTurn], postGame.discardCount[postGame.whoseTurn] - 1);
            printf("Player 1's handCount test: ");
            assertTrue(0, preGame.handCount[postGame.whoseTurn], (postGame.handCount[postGame.whoseTurn] + 1) + 1);
            
            for (j = 1; j < postGame.numPlayers; j++)
            {
                printf("Player %d's discardCount test: ", j + 1);
                assertTrue(0, preGame.discardCount[j], postGame.discardCount[j]);
                printf("Player %d's handCount test: ", j + 1);
                assertTrue(0, preGame.handCount[j], postGame.handCount[j]);              
            }
        }

        // Player chooses to discard hand and force all other players
        // with 5 or more cards to discard their hands
        else if (choice2 == 1)
        {
            printf("Player 1's discardCount test: ");
            assertTrue(0, postGame.discardCount[postGame.whoseTurn], preGame.discardCount[postGame.whoseTurn] + preGame.handCount[postGame.whoseTurn]);
            printf("Player 1's handCount test: ");
            assertTrue(0, postGame.handCount[postGame.whoseTurn], 4);

            for (j = 1; j < postGame.numPlayers; j++)
            {
                if (preGame.handCount[j] >= 5)
                {
                    printf("Player %d's discardCount test: ", j + 1);
                    assertTrue(0, preGame.discardCount[j], postGame.discardCount[j] - preGame.handCount[j]);
                    printf("Player %d's handCount test: ", j + 1);
                    assertTrue(0, postGame.handCount[j], 4);
                }

                else
                {
                    printf("Player %d's discardCount test: ", j + 1);
                    assertTrue(0, preGame.discardCount[j], postGame.discardCount[j]);
                    printf("Player %d's handCount test: ", j + 1);
                    assertTrue(0, preGame.handCount[j], postGame.handCount[j]);
                }                
            }
        }

        printf("Player 1's numActions test: ");
        assertTrue(0, preGame.numActions, postGame.numActions - 1);

        // Clear out the contents of the gameStates
        memset(&preGame, '\0', sizeof(struct gameState));
        memset(&postGame, '\0', sizeof(struct gameState));
    }

    printf("*******************************\n");
    printf("TESTS COMPLETE.\n");
    printf("*******************************\n");


    return 0;
}