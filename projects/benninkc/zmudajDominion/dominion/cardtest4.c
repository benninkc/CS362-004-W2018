/*********************************************************************
 ** Author: Casey Bennink ONID: benninkc
 ** Date: 2/4/18
 ** Description: Assignment 3 cardtest4.c
 ** test for Salvager
*********************************************************************/
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
    int p, r, handCount, correctBuys, correctCoins, toTrash;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    int salv[11];
    salv[0] = salvager;
    for (i = 1; i < 11; i++)
    {
        salv[i] = k[i - 1];
    }

    printf ("TESTING Salvager card:\n");
    for (p = 0; p < numPlayer; p++) {
    	for (handCount = 2; handCount <= 11; handCount++) {
    		for(toTrash = 1; toTrash < handCount; toTrash++){
    			printf("Test player %d playing Salvager card, hand size: %d, hand to trash: %d\n", p, handCount, toTrash);
    		
    			memset(&G, 23, sizeof(struct gameState));
        	    r = initializeGame(numPlayer, k, seed, &G);
        	    G.whoseTurn = p;
        	    G.handCount[p] = handCount;
        	    correctBuys = G.numBuys + 1;
        	    correctCoins = G.coins + getCost(salv[toTrash]);

        	    memcpy(G.hand[p], salv, sizeof(int) * handCount);

        	    r = playCard(0, toTrash, 0, 0, &G);

        	    printf("numBuys = %d, expected = %d\n", G.numBuys, correctBuys);
        	    printf("coins = %d, expected = %d\n", G.coins, correctCoins);

        	    if (G.numBuys == correctBuys + 2 && G.coins == correctCoins) {
        	    	printf("The Salvager TEST PASSED\n");
        	    }
        	    else {
        	    	printf("Salvager TEST FAILED\n");
        	    }
        	}
    	}
    }
	

	return 0;
}