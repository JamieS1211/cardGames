//
// Created by Jamie on 28/12/2017.
//
void calculateChanceOfWin(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability *probabilityNodePointer);

void calculatePlayerHitScores(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability probabilityTree[3][23], int currentLayer);

void calculateProbabilities(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer);