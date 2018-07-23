//
// Created by Jamie on 21/12/2017.
//

#include <stdio.h>
#include <stdlib.h>

#include "api.h"

/**
 * A function to initialise a deck stack full of cards taking the pointer to the deck stack and number of decks
 * @param deckStackPointer              Pointer to deck stack
 * @param numberOfDecks                 Number of decks in stack
 */
void initialiseFullDeckStack(DeckStack *deckStackPointer, int numberOfDecks) {
    deckStackPointer->numberOfDecks = numberOfDecks;
    deckStackPointer->cardsLeft = deckStackPointer->numberOfDecks * NUMBER_OF_SUITS * NUMBER_OF_CARDS;
    deckStackPointer->cardsInStack = malloc(deckStackPointer->cardsLeft * sizeof(Card));

    int count = 0;
    for (int deck = 0; deck < numberOfDecks; deck++) {
        for (int cardID = 1; cardID <= NUMBER_OF_CARDS; cardID++) {
            for (int suit = 0; suit < NUMBER_OF_SUITS; suit++) {
                deckStackPointer->cardsInStack[count].cardID = cardID;
                deckStackPointer->cardsInStack[count].cardSuit = suit;
                count++;
            }
        }
    }
}

/**
 * A function to initialise a deck stack with no cards taking the pointer to the deck stack and number of decks
 * @param deckStackPointer              Pointer to deck stack
 * @param numberOfDecks                 Number of decks in stack
 */
void initialiseEmptyDeckStack(DeckStack *deckStackPointer, int numberOfDecks) {
    deckStackPointer->numberOfDecks = numberOfDecks;
    deckStackPointer->cardsLeft = 0;
    deckStackPointer->cardsInStack = NULL;
}

/**
 * A function to add a card to the deck stack
 * @param deckStackPointer              Pointer to deck stack
 * @param numberOfDecks                 Number of decks in stack
 */
void addCardToDeckStack(DeckStack *deckStackPointer, Card card) {
    deckStackPointer->cardsLeft++;
    deckStackPointer->cardsInStack = realloc(deckStackPointer->cardsInStack, deckStackPointer->cardsLeft * sizeof(Card));

    deckStackPointer->cardsInStack[deckStackPointer->cardsLeft - 1].cardSuit = card.cardSuit;
    deckStackPointer->cardsInStack[deckStackPointer->cardsLeft - 1].cardID = card.cardID;
}

/**
 * A function to return the card at that position in the given stack
 * @param deckStackPointer              Pointer to deck stack
 * @param position                      Position of card
 * @return card                         Card at the given position
 */
Card getCardFromDeckStack(DeckStack *deckStackPointer, int position) {
    Card card;
    card.cardSuit = deckStackPointer->cardsInStack[position].cardSuit;
    card.cardID = deckStackPointer->cardsInStack[position].cardID;

    return card;
}

/**
 * A function to return the position (first if multiple) of the given card in the stack
 *
 * @param deckStackPointer              Pointer to deck stack
 * @param card                          Card
 * @return                              Position of card, returns -1 if that card is not in players hand
 */
int findPositionOfDeckStacksCard(DeckStack *deckStackPointer, Card card) {
    for (int position = 0; position < deckStackPointer->cardsLeft; position++) {
        if (deckStackPointer->cardsInStack[position].cardID == card.cardID && deckStackPointer->cardsInStack[position].cardSuit == card.cardSuit) {
            return position;
        }
    }

    return -1;
}

/**
 * A function to remove a card from a given position from the deck stack
 * @param deckStackPointer              Pointer to deck stack
 * @param position                      Position of card
 */
void removeCardFromDeckStack(DeckStack *deckStackPointer, int position) {
    Card temp[deckStackPointer->cardsLeft];

    for (int i = 0; i < deckStackPointer->cardsLeft; i++) {
        temp[i].cardSuit = deckStackPointer->cardsInStack[i].cardSuit;
        temp[i].cardID = deckStackPointer->cardsInStack[i].cardID;
    }

    deckStackPointer->cardsLeft--;

    deckStackPointer->cardsInStack = realloc(deckStackPointer->cardsInStack, deckStackPointer->cardsLeft * sizeof(Card));

    for (int i = 0; i <= deckStackPointer->cardsLeft; i++) {
        if (i < position) {
            deckStackPointer->cardsInStack[i].cardSuit = temp[i].cardSuit;
            deckStackPointer->cardsInStack[i].cardID = temp[i].cardID;
        } else if (i > position) {
            deckStackPointer->cardsInStack[i - 1].cardSuit = temp[i].cardSuit;
            deckStackPointer->cardsInStack[i - 1].cardID = temp[i].cardID;
        }
    }
}

/**
 * A function to move all contents of a deck stack to another deck stack
 * @param deckStackPointerFrom              Pointer to deck stack for where cards are being moved from
 * @param deckStackPointerTo                Position to deck stack for where cards are being moved to
 */
void moveAllDeckStackContents(DeckStack *deckStackPointerFrom, DeckStack *deckStackPointerTo) {
    deckStackPointerTo->cardsInStack = realloc(deckStackPointerTo->cardsInStack, (deckStackPointerTo->cardsLeft + deckStackPointerFrom->cardsLeft) * sizeof(Card));

    for (int i = 0; i < deckStackPointerFrom->cardsLeft; i++) {
        deckStackPointerTo->cardsInStack[deckStackPointerTo->cardsLeft + i].cardSuit = deckStackPointerFrom->cardsInStack[i].cardSuit;
        deckStackPointerTo->cardsInStack[deckStackPointerTo->cardsLeft + i].cardID = deckStackPointerFrom->cardsInStack[i].cardID;
    }

    deckStackPointerTo->cardsLeft = deckStackPointerFrom->cardsLeft + deckStackPointerTo->cardsLeft;

    deckStackPointerFrom->cardsLeft = 0;
    deckStackPointerFrom->cardsInStack = realloc(deckStackPointerFrom->cardsInStack, deckStackPointerFrom->cardsLeft * sizeof(Card));
}