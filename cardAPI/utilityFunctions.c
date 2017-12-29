//
// Created by Jamie on 21/12/2017.
//

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "api.h"
#include "stack.h"
#include "player.h"
#include "../generalAPI/userInput.h"

/**
 * A function that updates a pointer to a character array and pointer to a card and updates the character array to be the suit of the card
 * @param cardName          Pointer to character array to store suit of card
 * @param card              The card
 */
void getCardSuitName(char *suit, Card card) {
    switch (card.cardSuit) {
        case HEART:
            strcpy(suit, "Hearts");
            break;
        case DIAMOND:
            strcpy(suit, "Diamonds");
            break;
        case CLUB:
            strcpy(suit, "Clubs");
            break;
        case SPADE:
            strcpy(suit, "Spades");
            break;
        default:
            strcpy(suit, "?");
    }
}

/**
 * A function that updates a pointer to a character array and pointer to a card and updates the character array to be the name of the card
 * @param cardName          Pointer to character array to store name of card
 * @param card              The card
 */
void getCardName(char *cardName, Card card) {
    switch (card.cardID) {
        case ACE:
            strcpy(cardName, "Ace");
            break;
        case TWO:
            strcpy(cardName, "Two");
            break;
        case THREE:
            strcpy(cardName, "Three");
            break;
        case FOUR:
            strcpy(cardName, "Four");
            break;
        case FIVE:
            strcpy(cardName, "Five");
            break;
        case SIX:
            strcpy(cardName, "Six");
            break;
        case SEVEN:
            strcpy(cardName, "Seven");
            break;
        case EIGHT:
            strcpy(cardName, "Eight");
            break;
        case NINE:
            strcpy(cardName, "Nine");
            break;
        case TEN:
            strcpy(cardName, "Ten");
            break;
        case JACK:
            strcpy(cardName, "Jack");
            break;
        case QUEEN:
            strcpy(cardName, "Queen");
            break;
        case KING:
            strcpy(cardName, "King");
            break;
        default:
            strcpy(cardName, "?");
    }
}

/**
 * A function that takes a stack of cards and a player and deals a random card from that stack to the player returning the card that was dealt
 *
 * @param stack         Stack of cards to deal from
 * @param player        Player to deal card to
 * @return              Card that was dealt to player
 */
Card dealCard(DeckStack *stack, Player *player) {
    srand((unsigned int) time(NULL));

    int cardPosition = rand() % stack->cardsLeft;

    Card card = getCardFromStack(stack, cardPosition);
    removeCardFromStack(stack, cardPosition);

    addCardToPlayer(player, card);

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