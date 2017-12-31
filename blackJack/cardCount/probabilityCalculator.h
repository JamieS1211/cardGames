//
// Created by Jamie on 28/12/2017.
//

void printProbabilities(Probability **probabilityTree);

// A function that takes a player and dealer state and updates a probability tree with chance player wins / losses / draws with dealer provided player stands at this point

void calculateChanceOfWin(DeckStack *stackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability *probabilityNodePointer);

// A recursive function that builds up a pobability tree showing probabilities of outcomes

void calculatePlayerHitScores(DeckStack *stackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability **probabilityTree, int currentLayer);

void calculateProbabilities(DeckStack *stackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer);