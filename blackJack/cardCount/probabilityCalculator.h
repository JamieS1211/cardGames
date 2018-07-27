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
 * A function that returns a current chances object that advises if a player should stand and what their current win and lose chances are
 * @param deckStackPointer
 * @param blackJackPlayerPointer
 * @param blackJackDealerPointer
 */
CurrentChances shouldStand(DeckStack *deckStackPointer, SimpleStack *simpleStackPointer, ProbabilityTree *probabilityTreePointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer);

/**
 * A function that returns the expected value of the next hand
 * @param deckStackPointer
 * @return
 */
float getTrueCount(DeckStack *deckStackPointer);


float getExpectedValueOfNextHand(DeckStack *deckStackPointer, ProbabilityTree *probabilityTreePointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer);

/**
 * Counter function that takes bits in a counter, pointer to the counter and base of counting and then returns 1 if the counter has finished and if not returns 0 and increments the counter by 1
 *
 * @param bits      Bits in the counter
 * @param p         Pointer to counter
 * @param base      Base of counting
 * @return          If the counter has finished
 */
int nBitCounterAddOne(int bits, int *p, int base);

#endif //BLACKJACK_CARDCOUNT_PROBABILITYCALCULATOR_H