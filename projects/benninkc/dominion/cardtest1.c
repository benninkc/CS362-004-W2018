/*********************************************************************
 ** Author: Casey Bennink ONID: benninkc
 ** Date: 2/4/18
 ** Description: Assignment 3 cardtest1.c
 ** test for Smithy
*********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(int argc, char const *argv[]) {
    int seed = 1024;
    int numPlayer = 3;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    int smy[MAX_HAND];
    int i;
    for (i = 0; i < MAX_HAND; i++)
    {
        smy[i] = smithy;
    }

    printf ("TESTING smithy card:\n");
    for (p = 0; p < numPlayer; p++) {

    	for (handCount = 0; handCount <= maxHandCount; handCount++) {
    		printf("Test player %d playing Smithy card, hand size: %d\n", p, handCount);
    		
    		memset(&G, 23, sizeof(struct gameState));
            r = initializeGame(numPlayer, k, seed, &G);
            G.whoseTurn = p;
            G.handCount[p] = handCount;
            memcpy(G.hand[p], smy, sizeof(int) * handCount);

            r = playCard(0, 0, 0, 0, &G);

            printf("G.handCount = %d, expected = %d\n", G.handCount[p], handCount + 2);

            if (G.handCount[p] == handCount + 2) {
            	printf("Smithy TEST PASSED\n");
            }
            else {
            	printf("Smith TEST FAILED\n");
            }
    	}
    }

	return 0;
}