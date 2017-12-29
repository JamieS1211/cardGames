//
// Created by Jamie on 21/12/2017.
//

#include <stdio.h>

#include "blackJack.h"

#include "../cardAPI/stack.h"
#include "../cardAPI/utilityFunctions.h"
#include "../cardAPI/player.h"
#include "blackJackPlayer.h"

/**
 * A function to return the maximum value of a card
 * @param card
 * @return
 */
int getCardValue(Card card) {
    switch (card.cardID) {
        case KING:
        case QUEEN:
        case JACK:
            return 10;

        default:
            return card.cardID;
    }
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
    updatePlayersScore(player);

    char suit[120] = "";
    char cardName[120] = "";

    getCardSuitName(suit, card);
    getCardName(cardName, card);

    printf("Dealt card %s of %s to \"%s\" giving score of:", cardName, suit, player->player.playerName);

    for (int i = 0; i < player->differentScores; i++) {
        printf("  %i  ", player->scores[i]);
    }
    printf("\n");

}

/**
 * A function to specified card to a black jack player
 * @param stack             Pointer to the stack to deal from
 * @param usedStack         Pointer to the stack of used cards to shuffle from if needed
 * @param player            Pointer to the black jack player to deal to
 * @param card              The card to give the player
 */
void giveBlackJackPlayerCard(DeckStack *stack, DeckStack *usedStack, BlackJackPlayer *player, Card card) {

    if (stack->cardsLeft == 0) {
        for (int i = 0; i < usedStack->cardsLeft; i++) {
            addCardToStack(stack, getCardFromStack(usedStack, i));
            removeCardFromStack(usedStack, i);
        }
    }

    removeCardFromStack(stack, findPositionOfStacksCard(stack, card));
    addCardToPlayer(&player->player, card);
    updatePlayersScore(player);

    char suit[120] = "";
    char cardName[120] = "";

    getCardSuitName(suit, card);
    getCardName(cardName, card);

    printf("Dealt card %s of %s to \"%s\" giving score of:", cardName, suit, player->player.playerName);

    for (int i = 0; i < player->differentScores; i++) {
        printf("  %i  ", player->scores[i]);
    }
    printf("\n");
}