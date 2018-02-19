/*********************************************************************
 ** Author: Casey Bennink ONID: benninkc
 ** Date: 2/4/18
 ** Description: Assignment 4 randomcardtest2.c
 ** test for Village
*********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rngs.h"

int cardEffectFails = 0;
int discardCardFails = 0;
int drawCardFails = 0;
int numActionsFails = 0;
int deckHandCountFails = 0;

void checkVillage(int p, struct gameState *post)
{
	int r, s, x;
	int bonus = 0;
	
	struct gameState pre;
	
	memcpy(&pre, post, sizeof(struct gameState));
	
	r = cardEffect(village, 0, 0, 0, post, 0, &bonus);
	
	s = drawCard(p, &pre);
	
	pre.numActions++;
	pre.numActions++;

	x = discardCard(0, p, &pre, 0);
	
	int postHC = post->handCount[p];
	int postDC = post->deckCount[p];
	int preHC = pre.handCount[p];
	int preDC = pre.deckCount[p];
	
	if (pre.numActions != post->numActions)
	{
		numActionsFails++;
	}
	
	if (s == -1 && pre.deckCount[p] != 0)
	{
		drawCardFails++;
	}
	
	if (!(r == 0 && x == 0))
	{
		if (r)
		{
			cardEffectFails++;
		}
		if (x)
		{
			discardCardFails++;
		}
	}
	
	if (!(postHC == preHC && postDC == preDC))
	{
		deckHandCountFails++;
	}
	
}
	
	
int main()
{
	printf("Village Random Test\n");
	int iterations = 10000;
	int i, n, player, deckCount, handCount, discardCount;
	struct gameState G;
	srand(time(NULL));
	
	for (n = 0; n < iterations; n++)
	{
		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = floor(Random() * 256);
		}
		
		G.numActions = 1;
		G.playedCardCount = floor(Random() * (MAX_DECK-1));
		player = floor(Random() * MAX_PLAYERS);
		G.deckCount[player] = floor(Random() * MAX_DECK);
		G.handCount[player] = floor(Random() * MAX_HAND);
		G.discardCount[player] = floor(Random() * MAX_DECK);
		G.whoseTurn = player;
		
		checkVillage(player, &G);
	}
	int totalFails = cardEffectFails + discardCardFails + drawCardFails + deckHandCountFails + numActionsFails;
	printf("Tests passed: %d\n", iterations - totalFails);
	printf("Tests failed: %d\n", totalFails);
	
	if (totalFails == 0)
	{
		printf("All random Village tests PASSED!");
	}
	else
	{
		printf("Failures:\n");
		printf("drawCard failed: %d\n", drawCardFails);
		printf("cardEffect failed: %d\n", cardEffectFails);
		printf("discardCard failed: %d\n", discardCardFails);
		printf("numActions failed %d\n", numActionsFails);
		printf("Hand/Deck fails: %d\n", deckHandCountFails);
	}
	
	return 0;
}
	
	
	