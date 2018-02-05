/*********************************************************************
 ** Author: Casey Bennink ONID: benninkc
 ** Date: 2/4/18
 ** Description: Assignment 3 cardtest2.c
 ** test for Adventurer
*********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(int argc, char const *argv[]) {
    int i;
    int seed = 1024;
    int numPlayer = 3;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    int ads[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        ads[i] = adventurer;
    }

    printf ("TESTING adventurer card:\n");
    for (p = 0; p < numPlayer; p++) {
    	for (handCount = 1; handCount <= maxHandCount; handCount++) {
    		printf("Test player %d playing adventurer card, hand size: %d\n", p, handCount);
    		
    		memset(&G, 23, sizeof(struct gameState));
            r = initializeGame(numPlayer, k, seed, &G);
            G.whoseTurn = p;
            G.handCount[p] = handCount;
            memcpy(G.hand[p], ads, sizeof(int) * handCount);

            r = playCard(0, 0, 0, 0, &G);

            printf("G.handCount = %d, %d <= expected <= %d\n", G.handCount[p], handCount - 1, handCount + 1);

            if (G.handCount[p] >= handCount - 1 && G.handCount <= handCount + 1) {
            	printf("Adventurer TEST PASSED\n");
            }
            else {
            	printf("Adventurer TEST FAILED\n");
            }
    	}
    }


	return 0;
}