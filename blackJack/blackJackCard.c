//
// Created by Jamie on 21/12/2017.
//

#include <stdio.h>

#include "blackJack.h"

#include "../cardAPI/stack.h"
#include "../cardAPI/utilityFunctions.h"

/**
 * A function to return the maximum value of a card
 * @param card
 * @return
 */
int getCardMaxValue(Card card) {
    switch (card.cardID) {
        case ACE:
            return 11;

        case KING:
        case QUEEN:
        case JACK:
            return 10;

        default:
            return card.cardID;
    }
}

/**
 * A function to return the minimum value of a card
 * @param card
 * @return
 */
int getCardMinValue(Card card) {

    if (card.cardID == ACE) {
        return 1;
    }

    return getCardMaxValue(card);
}

/**
 * A function to deal a random card to a black jack player
 * @param stack             Pointer to the stack to deal from
 * @param usedStack         Pointer to the stack of used cards to shuffle from if needed
 * @param player            Pointer to the black jack player to deal to
 */
void dealBlackJack(DeckStack *stack, DeckStack *usedStack, BlackJackPlayer *player) {

    if (stack->cardsLeft == 0) {
        for (int i = 0; i < usedStack->cardsLeft; i++) {
            addCardToStack(stack, getCardFromStack(usedStack, i));
            removeCardFromStack(usedStack, i);
        }
    }

    Card card = dealCard(stack, &player->player);

    player->scoreMax += getCardMaxValue(card);
    player->scoreMin += getCardMinValue(card);

    char suit[120] = "";
    char cardName[120] = "";

    getCardSuitName(suit, card);
    getCardName(cardName, card);

    if (player->scoreMax == player->scoreMin || (player->scoreMax > 21 && player->scoreMin <= 21)) {
        printf("Dealt card %s of %s to \"%s\" giving score of %i\n", cardName, suit, player->player.playerName, player->scoreMin);
    } else {
        printf("Dealt card %s of %s to \"%s\" giving score of %i or %i\n", cardName, suit, player->player.playerName, player->scoreMax, player->scoreMin);
    }
}