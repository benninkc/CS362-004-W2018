/*********************************************************************
 ** Author: Casey Bennink ONID: benninkc
 ** Date: 2/4/18
 ** Description: Assignment 4 randomtestcard2.c
 ** test for smithy
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
int deckHandCountFails = 0;

void checkSmithyCard(int p, struct gameState *post)
{
	int r, s, t, u, v;
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	int bonus = 0;
	
	r = cardEffect(smithy, 0, 0, 0, post, 0, &bonus);
	s = drawCard(p, &pre);
	t = drawCard(p, &pre);
	u = drawCard(p, &pre);
	
	v = discardCard(0, p, &pre, 0);
	
	int postHC = post->handCount[p];
	int postDC = post->deckCount[p];
	int preHC = pre.handCount[p];
	int preDC = pre.deckCount[p];
	
	if (s == -1 && pre.deckCount[p] != 0)
	{
		drawCardFails++;
	}
	if (t == -1 && pre.deckCount[p] != 0)
	{
		drawCardFails++;
	}
	if (u == -1 && pre.deckCount[p] != 0)
	{
		drawCardFails++;
	}
	
	if (!(r == 0 && v == 0))
	{
		if(r)
		{
			cardEffectFails++;
		}
		if (v)
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
	printf("Smithy random test\n");
	int iterations = 10000;
	int i, n, player;
	struct gameState G;
	srand(time(NULL));
	
	for (n = 0; n < iterations; n++)
	{
		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = floor(Random() * 256);
		}
	player = floor(Random() * MAX_PLAYERS);
	G.deckCount[player] = floor(Random() * MAX_DECK);
	G.discardCount[player] = floor(Random() * MAX_DECK);
	G.handCount[player] = floor(Random() * MAX_HAND);
	G.playedCardCount = floor(Random() * (MAX_DECK - 1));
	G.whoseTurn = player;
	checkSmithyCard(player, &G);
	}
	int totalFails = cardEffectFails + deckHandCountFails + drawCardFails + deckHandCountFails;
	printf("Failed Tests: %d\n", totalFails);
	if (totalFails == 0)
	{
		printf("All Smithy tests passed\n");
	}
	else
	{
		printf("Failures:\n");
		printf("drawCard failed: %d\n", drawCardFails);
		printf("cardEffect failed: %d\n", cardEffectFails);
		printf("discardCard failed: %d\n", discardCardFails);
		printf("Hand/Deck fails: %d\n", deckHandCountFails);
	}
	
	return 0;
}