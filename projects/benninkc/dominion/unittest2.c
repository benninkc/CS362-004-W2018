/*********************************************************************
 ** Author: Casey Bennink ONID: benninkc
 ** Date: 2/4/18
 ** Description: Assignment 3 unittest2.c
 ** unit test for whoseTurn function
*********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(int argc, char const *argv[]) {
    int seed = 1024;
    int curPlayer;
    int numPlayer = 3;
    int p, r, turnRes, corRes;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    printf ("TESTING whoseTurn\n");
    for (p = 0; p < numPlayer; p++)	{
    		for (curPlayer = 0; curPlayer <= numPlayer; curPlayer++) {
    				printf("Testing %d players with player %d's turn\n", p, curPlayer);
    				memset(&G, 23, sizeof(struct gameState));
    				r = initializeGame(p, k, seed, &G);

    				if (curPlayer == numPlayer) {
    					G.whoseTurn = 0;
    				}
    				else {
    					G.whoseTurn = curPlayer;
    				}
    				

    				turnRes = whoseTurn(&G);
    				if (curPlayer == numPlayer) {
    					corRes = 0;
    					printf("turn =  %d, expected = %d \n", turnRes, corRes);
    				}
    				else {
    					corRes = curPlayer;
    					printf("turn =  %d, expected = %d \n", turnRes, corRes);
					}
    				if (turnRes == corRes) {
    					printf("whoseTurn TEST PASSED\n");
    				}
    				else {
    					printf("whoseTurn TEST FAILED\n");
    				}
    		}
    }

	return 0;
}