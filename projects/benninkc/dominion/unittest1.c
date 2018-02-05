/*********************************************************************
 ** Author: Casey Bennink ONID: benninkc
 ** Date: 2/4/18
 ** Description: Assignment 3 unittest1.c
 ** unit test for discardCard function
*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"

int main(int argc, char const *argv[]) {
    int seed = 1024;
    int numPlayer = 3;
    int p, r, d, handCount, playedCount, playedResult, curFlag;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    int cards[MAX_HAND];
    int i;
    for (i = 0; i < MAX_HAND; i++)
    {
        cards[i] = adventurer;
    }

    printf ("TESTING discardCard():\n");
    for (p = 0; p < numPlayer; p++) {
    	for(handCount=1; handCount <= maxHandCount; handCount++) {
    		for(playedCount=0; playedCount <= 6; playedCount++) {
    			for(curFlag=0; curFlag < 4; curFlag++) {
    				printf("Test player %d with %d in hand, %d in played, and %d flag\n",p, handCount, playedCount, curFlag);
    				memset(&G, 23, sizeof(struct gameState));
    				r = initializeGame(numPlayer, k, seed, &G);

    				G.handCount[p] = handCount;

    				G.playedCardCount = playedCount;

    				int x;
    				for (x = 0; x < handCount; x++) {
    					G.hand[p][x] = k[x];
    				}
    				for (x = 0; x < playedCount; x++) {
    					G.playedCards[x] = k[x];
    				}

    				d = discardCard(handCount/2, p, &G, curFlag);

    				if (curFlag < 1) {
    					playedResult = playedCount + 1;
    				}
    				else {
    					playedResult = playedCount;
    				}

    				printf("G.handCount = %d, expected = %d\n", G.handCount[p], handCount - 1);
    				printf("G.playedCardCount = %d, expected = %d\n", G.playedCardCount, playedResult);

    				if (G.handCount[p] == handCount - 1 && G.playedCardCount == playedResult) {
    					printf("discard TEST PASSED\n");
    				}
    				else {
    					printf("discard TEST FAILED\n");
    				}

    			}
    		}
    	}
    
    }

	return 0;
}