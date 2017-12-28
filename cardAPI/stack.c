//
// Created by Jamie on 21/12/2017.
//

#include <stdio.h>
#include <stdlib.h>

#include "api.h"

/**
 * A function to initialise a deck stack full of cards taking the pointer to the deck stack and number of decks
 * @param stack                 Pointer to stack
 * @param numberOfDecks         Number of decks in stack
 */
void initialiseFullStack(DeckStack *stack, int numberOfDecks) {
    stack->numberOfDecks = numberOfDecks;
    stack->cardsLeft = stack->numberOfDecks * NUMBER_OF_SUITS * NUMBER_OF_CARDS;
    stack->cardsInStack = malloc(stack->cardsLeft * sizeof(Card));

    int count = 0;
    for (int deck = 0; deck < numberOfDecks; deck++) {
        for (int cardID = 1; cardID <= NUMBER_OF_CARDS; cardID++) {
            for (int suit = 0; suit < NUMBER_OF_SUITS; suit++) {
                stack->cardsInStack[count].cardID = cardID;
                stack->cardsInStack[count].cardSuit = suit;
                count++;
            }
        }
    }
}

/**
 * A function to initialise a deck stack with no cards taking the pointer to the deck stack and number of decks
 * @param stack                 Pointer to stack
 * @param numberOfDecks         Number of decks in stack
 */
void initialiseEmptyStack(DeckStack *stack, int numberOfDecks) {
    stack->numberOfDecks = numberOfDecks;
    stack->cardsLeft = 0;
    stack->cardsInStack = NULL;
}

/**
 * A function to add a card to the deck stack
 * @param stack                 Pointer to stack
 * @param numberOfDecks         Number of decks in stack
 */
void addCardToStack(DeckStack *stack, Card card) {
    stack->cardsLeft++;
    stack->cardsInStack = realloc(stack->cardsInStack, stack->cardsLeft * sizeof(Card));

    stack->cardsInStack[stack->cardsLeft - 1].cardSuit = card.cardSuit;
    stack->cardsInStack[stack->cardsLeft - 1].cardID = card.cardID;
}

/**
 * A function to return the card at that position in the given stack
 * @param stack                 Pointer to the stack
 * @param position              Position of card
 * @return card                 Card at the given position
 */
Card getCardFromStack(DeckStack *stack, int position) {
    Card card;
    card.cardSuit = stack->cardsInStack[position].cardSuit;
    card.cardID = stack->cardsInStack[position ].cardID;

    return card;
}

/**
 * A function to return the position (first if multiple) of the given card in the stack
 *
 * @param stack         Pointer to the stack
 * @param card          Card
 * @return              Position of card, returns -1 if that card is not in players hand
 */
int findPositionOfStacksCard(DeckStack *stack, Card card) {
    for (int position = 0; position < stack->cardsLeft; position++) {
        if (stack->cardsInStack[position].cardID == card.cardID && stack->cardsInStack[position].cardSuit == card.cardSuit) {
            return position;
        }
    }

    return -1;
}

/**
 * A function to remove a card from a given position from the deck stack
 * @param deckStack              Pointer to the stack
 * @param position               Position of card
 */
void removeCardFromStack(DeckStack *stack, int position) {
    Card temp[stack->cardsLeft];

    for (int i = 0; i < stack->cardsLeft; i++) {
        temp[i].cardSuit = stack->cardsInStack[i].cardSuit;
        temp[i].cardID = stack->cardsInStack[i].cardID;
    }

    stack->cardsLeft--;

    realloc(stack->cardsInStack, stack->cardsLeft * sizeof(Card));

    for (int i = 0; i <= stack->cardsLeft; i++) {
        if (i < position) {
            stack->cardsInStack[i].cardSuit = temp[i].cardSuit;
            stack->cardsInStack[i].cardID = temp[i].cardID;
        } else if (i > position) {
            stack->cardsInStack[i - 1].cardSuit = temp[i].cardSuit;
            stack->cardsInStack[i - 1].cardID = temp[i].cardID;
        }
    }
}