/*********************************************************************
 ** Author: Casey Bennink ONID: benninkc
 ** Date: 2/4/18
 ** Description: Assignment 4 randomtestadventurer.c
 ** test for adventurer
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
int shuffleFails = 0;
int drawCardFails = 0;
int deckHandCountFails = 0;
int treasureCountFails = 0;

void checkAdventurerCard(int p, struct gameState *post)
{
	int PostTreasureCount = 0;
	int PreTreasureCount = 0;
	int temphand[MAX_HAND];
	int drawntreasure = 0;
	int cardDrawn = 0;
	
	struct gameState pre;
	int card = 0;
	int bonus = 0;
	int r, s, t, i;
	int z = 0;
	memcpy(&pre,post,sizeof(struct gameState));
	
	r = cardEffect(adventurer, 0, 0, 0, post, 0, &bonus);
	
	if (r)
	{
		cardEffectFails++;
	}
	
	while(drawntreasure < 2)
	{
		if (pre.deckCount[p] < 1)
		{
			s = shuffle(p, &pre);
			if (s == -1 && pre.deckCount[p] >=1)
			{
				shuffleFails++;
			}
		}
		t = drawCard(p, &pre);
		if (t == -1 && pre.deckCount[p] != 0)
		{
			drawCardFails++;
		}
		cardDrawn = pre.hand[p][pre.handCount[p] -1];
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		{
			drawntreasure++;
		}
		else
		{
			temphand[z] = cardDrawn;
			pre.handCount[p]--;
			z++;
		}
	}
	while(z -1 >= 0)
	{
		pre.discard[p][pre.discardCount[p]++] = temphand[z-1];
		z = z-1;
	}
	
	for (i = 0; i < post->handCount[p]; i++)
	{
		card = post->hand[p][i];
		if (card == copper || card == silver || card == gold)
		{
			PostTreasureCount++;
		}
	}
	if (PostTreasureCount != PreTreasureCount)
	{
		treasureCountFails++;
	}
	
	int postHC = post->handCount[p];
	int postDC = post->deckCount[p];
	int postDCC = post->discardCount[p];
	int preHC = pre.handCount[p];
	int preDC = pre.deckCount[p];
	int preDCC = pre.discardCount[p];
	
	if(!(postHC == preHC && postDC == preDC && postDCC == preDCC))
	{
		deckHandCountFails++;
	}
}
	
int main()
{
	printf("Adventurer Random Test\n");
	int iterations = 10000;
	int i, n, player;
	int treasures[] = {copper, silver, gold};
	int numTreasures;
	struct gameState G;
	srand(time(NULL));
	int min = 3;
	
	for (n = 0; n < iterations; n++)
	{
		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = floor(Random() * 256);
		}
		
		player = floor(Random() * MAX_PLAYERS);
		G.deckCount[player] = floor(Random() * ((MAX_DECK - min) + 1) + min);
		numTreasures = floor(Random() * ((G.deckCount[player] - min) + 1) + min);
		
		for (i = 0; i < numTreasures; i++)
		{
			G.deck[player][i] = treasures[rand() %3];
		}
		G.discardCount[player] = 0;
		G.handCount[player] = floor(Random() * ((MAX_HAND - min) + 1) + min);
		G.whoseTurn = player;
		
		checkAdventurerCard(player, &G);
	}
	
	int totalFails = cardEffectFails = cardEffectFails + drawCardFails + shuffleFails + deckHandCountFails + treasureCountFails;
	
	
	if (totalFails == 0)
	{
		printf("All random Village tests PASSED!");
	}
	else
	{
		printf("Failures:\n");
		printf("drawCard failed: %d\n", drawCardFails);
		printf("cardEffect failed: %d\n", cardEffectFails);
		printf("shuffle failed: %d\n", shuffleFails);
		printf("treasure count failed %d\n", treasureCountFails);
		printf("Hand/Deck fails: %d\n", deckHandCountFails);
	}
	
	return 0;
}