/*********************************************************************
 ** Author: Casey Bennink ONID: benninkc
 ** Date: 2/4/18
 ** Description: Assignment 3 cardtest3.c
 ** test for Village
*********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

int main(int argc, char const *argv[]) {
    int i;
    int seed = 1024;
    int numPlayer = 3;
    int p, r, handCount, correctActions;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    int vil[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        vil[i] = village;
    }

    printf ("TESTING village card:\n");
    for (p = 0; p < numPlayer; p++) {

    	for (handCount = 1; handCount <= maxHandCount; handCount++) {
    		printf("Test player %d playing Village card, hand size: %d\n", p, handCount);
    		
    		memset(&G, 23, sizeof(struct gameState));
            r = initializeGame(numPlayer, k, seed, &G);
            G.whoseTurn = p;
            G.handCount[p] = handCount;
            correctActions = G.numActions + 1;

            memcpy(G.hand[p], vil, sizeof(int) * handCount);

            r = playCard(0, 0, 0, 0, &G);

            printf("G.handCount = %d, expected = %d\n", G.handCount[p], handCount);
            printf("G.numActions = %d, expected = %d\n", G.numActions, correctActions);

            if (G.handCount[p] == handCount && G.numActions == correctActions) {
            	printf("Village TEST PASSED\n");
            }
            else {
            	printf("Village TEST FAILED\n");
            }
    	}
    }

	return 0;
}