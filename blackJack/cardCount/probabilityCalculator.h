//
// Created by Jamie on 28/12/2017.
//

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
int stand(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer);

/**
 * A function that returns the expected value of the next hand
 * @param deckStackPointer
 * @return
 */
float getExpectedValueOfHand(DeckStack *deckStackPointer);


float getRealExpectedValueOfHand(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer);