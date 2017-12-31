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
 * @param card                              The card to get value of
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
 * @param stackPointer                      Pointer to the stack to deal from
 * @param usedStackPointer                  Pointer to the stack of used cards to shuffle from if needed
 * @param blackJackPlayerPointer            Pointer to the black jack player to deal to
 */
void dealBlackJack(DeckStack *stackPointer, DeckStack *usedStackPointer, BlackJackPlayer *blackJackPlayerPointer) {

    if (stackPointer->cardsLeft == 0) {
        for (int i = 0; i < usedStackPointer->cardsLeft; i++) {
            addCardToStack(stackPointer, getCardFromStack(usedStackPointer, i));
            removeCardFromStack(usedStackPointer, i);
        }
    }

    Card card = dealCard(stackPointer, &blackJackPlayerPointer->player);
    updatePlayersScore(blackJackPlayerPointer);

    char suit[120] = "";
    char cardName[120] = "";

    getCardSuitName(suit, card);
    getCardName(cardName, card);

    printf("Dealt card %s of %s to \"%s\" giving score of:", cardName, suit, blackJackPlayerPointer->player.playerName);

    for (int i = 0; i < blackJackPlayerPointer->differentScores; i++) {
        printf("  %i  ", blackJackPlayerPointer->scores[i]);
    }
    printf("\n");

}

/**
 * A function to specified card to a black jack player
 * @param stackPointer                      Pointer to the stack to deal from
 * @param usedStackPointer                  Pointer to the stack of used cards to shuffle from if needed
 * @param blackJackPlayerPointer            Pointer to the black jack player to deal to
 * @param card                              The card to give the player
 */
void giveBlackJackPlayerCard(DeckStack *stackPointer, DeckStack *usedStackPointer, BlackJackPlayer *blackJackPlayerPointer, Card card) {

    if (stackPointer->cardsLeft == 0) {
        for (int i = 0; i < usedStackPointer->cardsLeft; i++) {
            addCardToStack(stackPointer, getCardFromStack(usedStackPointer, i));
            removeCardFromStack(usedStackPointer, i);
        }
    }

    removeCardFromStack(stackPointer, findPositionOfStacksCard(stackPointer, card));
    addCardToPlayer(&blackJackPlayerPointer->player, card);
    updatePlayersScore(blackJackPlayerPointer);

    char suit[120] = "";
    char cardName[120] = "";

    getCardSuitName(suit, card);
    getCardName(cardName, card);

    printf("Dealt card %s of %s to \"%s\" giving score of:", cardName, suit, blackJackPlayerPointer->player.playerName);

    for (int i = 0; i < blackJackPlayerPointer->differentScores; i++) {
        printf("  %i  ", blackJackPlayerPointer->scores[i]);
    }
    printf("\n");
}