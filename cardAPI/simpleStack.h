//
// Created by Jamie on 01/01/2018.
//


#ifndef CARDAPI_SIMPLESTACK_H
#define CARDAPI_SIMPLESTACK_H

#include "api.h"

/**
 * A function to initialise a simple stack from a deck stack
 * @param simpleStackPointer            Pointer to simple stack
 * @param deckStackPointer              Pointer to deck stack
 */
void initialiseSimpleStackFromDeckStack(SimpleStack *simpleStackPointer, DeckStack *deckStackPointer);


#endif //CARDAPI_SIMPLESTACK_H