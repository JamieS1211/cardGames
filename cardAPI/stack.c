//
// Created by Jamie on 21/12/2017.
//

#include <stdio.h>
#include <stdlib.h>

#include "api.h"

/**
 * A function to initialise a deck stack full of cards taking the pointer to the deck stack and number of decks
 * @param stackPointer                  Pointer to stack
 * @param numberOfDecks                 Number of decks in stack
 */
void initialiseFullStack(DeckStack *stackPointer, int numberOfDecks) {
    stackPointer->numberOfDecks = numberOfDecks;
    stackPointer->cardsLeft = stackPointer->numberOfDecks * NUMBER_OF_SUITS * NUMBER_OF_CARDS;
    stackPointer->cardsInStack = malloc(stackPointer->cardsLeft * sizeof(Card));

    int count = 0;
    for (int deck = 0; deck < numberOfDecks; deck++) {
        for (int cardID = 1; cardID <= NUMBER_OF_CARDS; cardID++) {
            for (int suit = 0; suit < NUMBER_OF_SUITS; suit++) {
                stackPointer->cardsInStack[count].cardID = cardID;
                stackPointer->cardsInStack[count].cardSuit = suit;
                count++;
            }
        }
    }
}

/**
 * A function to initialise a deck stack with no cards taking the pointer to the deck stack and number of decks
 * @param stackPointer                  Pointer to stack
 * @param numberOfDecks                 Number of decks in stack
 */
void initialiseEmptyStack(DeckStack *stackPointer, int numberOfDecks) {
    stackPointer->numberOfDecks = numberOfDecks;
    stackPointer->cardsLeft = 0;
    stackPointer->cardsInStack = NULL;
}

/**
 * A function to add a card to the deck stack
 * @param stackPointer                  Pointer to stack
 * @param numberOfDecks                 Number of decks in stack
 */
void addCardToStack(DeckStack *stackPointer, Card card) {
    stackPointer->cardsLeft++;
    stackPointer->cardsInStack = realloc(stackPointer->cardsInStack, stackPointer->cardsLeft * sizeof(Card));

    stackPointer->cardsInStack[stackPointer->cardsLeft - 1].cardSuit = card.cardSuit;
    stackPointer->cardsInStack[stackPointer->cardsLeft - 1].cardID = card.cardID;
}

/**
 * A function to return the card at that position in the given stack
 * @param stackPointer                  Pointer to the stack
 * @param position                      Position of card
 * @return card                         Card at the given position
 */
Card getCardFromStack(DeckStack *stackPointer, int position) {
    Card card;
    card.cardSuit = stackPointer->cardsInStack[position].cardSuit;
    card.cardID = stackPointer->cardsInStack[position ].cardID;

    return card;
}

/**
 * A function to return the position (first if multiple) of the given card in the stack
 *
 * @param stackPointer                  Pointer to the stack
 * @param card                          Card
 * @return                              Position of card, returns -1 if that card is not in players hand
 */
int findPositionOfStacksCard(DeckStack *stackPointer, Card card) {
    for (int position = 0; position < stackPointer->cardsLeft; position++) {
        if (stackPointer->cardsInStack[position].cardID == card.cardID && stackPointer->cardsInStack[position].cardSuit == card.cardSuit) {
            return position;
        }
    }

    return -1;
}

/**
 * A function to remove a card from a given position from the deck stack
 * @param stackPointer                  Pointer to the stack
 * @param position                      Position of card
 */
void removeCardFromStack(DeckStack *stackPointer, int position) {
    Card temp[stackPointer->cardsLeft];

    for (int i = 0; i < stackPointer->cardsLeft; i++) {
        temp[i].cardSuit = stackPointer->cardsInStack[i].cardSuit;
        temp[i].cardID = stackPointer->cardsInStack[i].cardID;
    }

    stackPointer->cardsLeft--;

    realloc(stackPointer->cardsInStack, stackPointer->cardsLeft * sizeof(Card));

    for (int i = 0; i <= stackPointer->cardsLeft; i++) {
        if (i < position) {
            stackPointer->cardsInStack[i].cardSuit = temp[i].cardSuit;
            stackPointer->cardsInStack[i].cardID = temp[i].cardID;
        } else if (i > position) {
            stackPointer->cardsInStack[i - 1].cardSuit = temp[i].cardSuit;
            stackPointer->cardsInStack[i - 1].cardID = temp[i].cardID;
        }
    }
}