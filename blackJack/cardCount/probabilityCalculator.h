//
// Created by Jamie on 28/12/2017.
//

#ifndef BLACKJACK_CARDCOUNT_PROBABILITYCALCULATOR_H
#define BLACKJACK_CARDCOUNT_PROBABILITYCALCULATOR_H

/**
 * A function that print the probability tree of the state of deck, player and dealer
 * @param deckStackPointer
 * @param blackJackPlayerPointer
 * @param blackJackDealerPointer
 */
void calculateProbabilities(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer);

/**
 * A function that returns 1 if should stand and 0 if should hit
 * @param deckStackPointer
 * @param blackJackPlayerPointer
 * @param blackJackDealerPointer
 */
int shouldStand(DeckStack *deckStackPointer, SimpleStack *simpleStackPointer, ProbabilityTree *probabilityTreePointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer);

/**
 * A function that returns the expected value of the next hand
 * @param deckStackPointer
 * @return
 */
float getTrueCount(DeckStack *deckStackPointer);


float getExpectedValueOfNextHandReal(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer,
                                     BlackJackPlayer *blackJackDealerPointer);


int factorial(int i);

int maxLayersDeepForScore(int score);

#endif //BLACKJACK_CARDCOUNT_PROBABILITYCALCULATOR_H