//
// Created by Jamie on 01/01/2018.
//

#include "api.h"
#include "deckStack.h"

/**
 * A function to initialise a simple stack from a deck stack
 * @param simpleStackPointer            Pointer to simple stack
 * @param deckStackPointer              Pointer to deck stack
 */
void initialiseSimpleStackFromDeckStack(SimpleStack *simpleStackPointer, DeckStack *deckStackPointer) {
    simpleStackPointer->cardsLeft = deckStackPointer->cardsLeft;

    for (int i = 0; i <= NUMBER_OF_CARDS; i++) {
        simpleStackPointer->cardsCountsInStack[i] = 0;
    }

    for (int i = 0; i < deckStackPointer->cardsLeft; i++) {
        simpleStackPointer->cardsCountsInStack[getCardFromDeckStack(deckStackPointer, i).cardID]++;
    }
}