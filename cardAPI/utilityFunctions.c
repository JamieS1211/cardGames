//
// Created by Jamie on 21/12/2017.
//

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "api.h"
#include "deckStack.h"
#include "player.h"
#include "../generalAPI/userInput.h"

/**
 * A function that updates a pointer to a character array and pointer to a card and updates the character array to be the suit of the card
 * @param suitPointer               Pointer to character array to store suit of card
 * @param card                      The card
 */
void getCardSuitName(char *suitPointer, Card card) {
    switch (card.cardSuit) {
        case HEART:
            strcpy(suitPointer, "Hearts");
            break;
        case DIAMOND:
            strcpy(suitPointer, "Diamonds");
            break;
        case CLUB:
            strcpy(suitPointer, "Clubs");
            break;
        case SPADE:
            strcpy(suitPointer, "Spades");
            break;
        default:
            strcpy(suitPointer, "?");
    }
}

/**
 * A function that updates a pointer to a character array and pointer to a card and updates the character array to be the name of the card
 * @param cardNamePointer           Pointer to character array to store name of card
 * @param card                      The card
 */
void getCardName(char *cardNamePointer, Card card) {
    switch (card.cardID) {
        case ACE:
            strcpy(cardNamePointer, "Ace");
            break;
        case TWO:
            strcpy(cardNamePointer, "Two");
            break;
        case THREE:
            strcpy(cardNamePointer, "Three");
            break;
        case FOUR:
            strcpy(cardNamePointer, "Four");
            break;
        case FIVE:
            strcpy(cardNamePointer, "Five");
            break;
        case SIX:
            strcpy(cardNamePointer, "Six");
            break;
        case SEVEN:
            strcpy(cardNamePointer, "Seven");
            break;
        case EIGHT:
            strcpy(cardNamePointer, "Eight");
            break;
        case NINE:
            strcpy(cardNamePointer, "Nine");
            break;
        case TEN:
            strcpy(cardNamePointer, "Ten");
            break;
        case JACK:
            strcpy(cardNamePointer, "Jack");
            break;
        case QUEEN:
            strcpy(cardNamePointer, "Queen");
            break;
        case KING:
            strcpy(cardNamePointer, "King");
            break;
        default:
            strcpy(cardNamePointer, "?");
    }
}

/**
 * A function that takes a stack of cards and a player and deals a random card from that stack to the player returning the card that was dealt
 *
 * @param stackPointer          Stack of cards to deal from
 * @param playerPointer         Player to deal card to
 * @return                      Card that was dealt to player
 */
Card dealCardDynamicMemory(DeckStack *stackPointer, Player *playerPointer) {
    int cardPosition = rand() % stackPointer->cardsLeft;

    Card card = getCardFromDeckStack(stackPointer, cardPosition);
    removeCardFromDeckStack(stackPointer, cardPosition);

    addCardToPlayerDynamicMemory(playerPointer, card);

    return card;
}

/**
 * A function that takes a stack of cards and a player and deals a random card from that stack to the player returning the card that was dealt (WARNING STATIC MEMORY FUNCTION USE WITH CARE)
 *
 * @param stackPointer          Stack of cards to deal from
 * @param playerPointer         Player to deal card to
 * @return                      Card that was dealt to player
 */
Card dealCardStaticMemory(DeckStack *stackPointer, Player *playerPointer) {
    int cardPosition = rand() % stackPointer->cardsLeft;

    Card card = getCardFromDeckStack(stackPointer, cardPosition);
    removeCardFromDeckStack(stackPointer, cardPosition);

    addCardToPlayerDynamicMemory(playerPointer, card);

    return card;
}

/**
 * A function to request user input for a specific card
 * @return              The card the user specified
 */
Card getCardDealt() {
    Card card;

    while (1) {
        printf("Please enter the suit of the card: \n"
                       "\t1: Heart \n"
                       "\t2: Diamond \n"
                       "\t3: Spade \n"
                       "\t4: Club \n");
        long option = getIntegerUserInput();

        if (option > 0 && option <= 4) {
            card.cardSuit = option - 1;
            break;
        } else {
            printf("What was entered was not a valid option, please try again. \n");
        }
    }

    while (1) {
        printf("Please enter the card number of the card: \n"
                       "\t1: Ace \n"
                       "\t2: Two \n"
                       "\t3: Three \n"
                       "\t4: Four \n"
                       "\t5: Five \n"
                       "\t6: Six \n"
                       "\t7: Seven \n"
                       "\t8: Eight \n"
                       "\t9: Nine \n"
                       "\t10: Ten \n"
                       "\t11: Jack \n"
                       "\t12: Queen \n"
                       "\t13: King \n");
        long option = getIntegerUserInput();

        if (option > 0 && option <= 13) {
            card.cardID = option;
            break;
        } else {
            printf("What was entered was not a valid option, please try again. \n");
        }
    }

    return card;
}