/*********************************************************************
 ** Author: Casey Bennink ONID: benninkc
 ** Date: 2/4/18
 ** Description: Assignment 3 unittest4.c
 ** unit test for gainCard
*********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main() 
{
    int seed = 1024;
    int numPlayer = 4;
    int p;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    struct gameState G;
	int fCount, dkCount, dscCount, hCount, sCount, supplyPos;

    printf ("TESTING gainCard\n");
    for (p = 0; p < numPlayer; p++) {
        for (supplyPos = 0; supplyPos < treasure_map+1; supplyPos++)  {
			#if (NOISY_TEST == 1)
				printf("Test player %d with %d supply position.\n", p, supplyPos);
			#endif

            memset(&G, 23, sizeof(struct gameState));
            initializeGame(numPlayer, k, seed, &G);
				
			dkCount = 50, hCount = 5, dscCount = 0, sCount = 100;

            G.deckCount[p] = dkCount;
			G.handCount[p] = hCount;
			G.discardCount[p] = dscCount;
			G.supplyCount[supplyPos] = sCount;

			fCount = 0;
			dscCount++;
			sCount--;

			gainCard(supplyPos, &G, fCount, p);

			#if (NOISY_TEST == 1)
				printf("discard count = %d, expected = %d\n", G.discardCount[p], dscCount);
				printf("supply count = %d, expected = %d\n", G.supplyCount[supplyPos], sCount);
			#endif
			assert(G.discardCount[p] == dscCount);
			assert(G.supplyCount[supplyPos] == sCount);

			fCount = 1;
			dkCount++;
			sCount--;

			gainCard(supplyPos, &G, fCount, p);

			#if (NOISY_TEST == 1)
				printf("deck count = %d, expected = %d\n", G.deckCount[p], dkCount);
				printf("supply count = %d, expected = %d\n", G.supplyCount[supplyPos], sCount);
			#endif
			assert(G.deckCount[p] == dkCount);
			assert(G.supplyCount[supplyPos] == sCount);

			fCount = 2;
			hCount++;
			sCount--;

			gainCard(supplyPos, &G, fCount, p);

			#if (NOISY_TEST == 1)
				printf("hand count = %d, expected = %d\n", G.handCount[p], hCount);
				printf("supply count = %d, expected = %d\n", G.supplyCount[supplyPos], sCount);
			#endif
			assert(G.handCount[p] == hCount);
			assert(G.supplyCount[supplyPos] == sCount);
               
			puts("");
        }
    }

    printf("TESTS PASSED\n");

    return 0;
}