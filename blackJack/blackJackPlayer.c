//
// Created by Jamie on 22/12/2017.
//

#include <stdio.h>
#include <stdlib.h>

#include "blackJack.h"

#include "../cardAPI/player.h"
#include "blackJackCard.h"
#include "../cardAPI/stack.h"

/**
 * A function to initialise a black jack player with a given name
 * @param blackJackPlayerPointer        Pointer to the black jack player
 * @param name                          Name of the black jack player
 */
void initialiseBlackJackPlayer(BlackJackPlayer *blackJackPlayerPointer, char name[120]) {
    initialisePlayer(&blackJackPlayerPointer->player, name);

    blackJackPlayerPointer->score = 0;
    blackJackPlayerPointer->isScoreSoft = 0;
}

/**
 * A function to print out all the cards that a black jack player has
 * @param blackJackPlayerPointer        Pointer to the black jack player
 */
void listCardsOfBlackJackPlayer(BlackJackPlayer *blackJackPlayerPointer) {
    listCardsOfPlayer(blackJackPlayerPointer->player);
}

/**
 * A function to read all cards a black jack player has and store all the possible scores
 * @param blackJackPlayerPointer        Pointer to the black jack player
 */
void updatePlayersScore(BlackJackPlayer *blackJackPlayerPointer) {
    blackJackPlayerPointer->score = 0;
    int aceCount = 0;

    for (int i = 0; i < blackJackPlayerPointer->player.cardsInHand; i++) {
        blackJackPlayerPointer->score += getCardValue(blackJackPlayerPointer->player.cardsDealt[i]);
        if (blackJackPlayerPointer->player.cardsDealt[i].cardID == ACE) {
            aceCount++;
        }
    }

    if (aceCount > 0 && blackJackPlayerPointer->score + 10 <= 21) {
        blackJackPlayerPointer->score += 10;
        blackJackPlayerPointer->isScoreSoft = 1;
    }
}

/**
 * A function to remove a card from a black jack player
 * @param blackJackPlayerPointer        Pointer to the black jack player
 * @param position                      Position
 */
void removeCardFromBlackJackPlayersHand(BlackJackPlayer *blackJackPlayerPointer, int position) {
    removeCardFromPlayersHand(&blackJackPlayerPointer->player, position);
    updatePlayersScore(blackJackPlayerPointer);
}

/**
 * A function to return the best score a black jack player has and if all scores make player bust the minimum score
 * @param blackJackPlayerPointer         Pointer to the black jack player
 * @return score                         The best score of the black jack player or lowest if bust
 */
int getPlayersBestScore(BlackJackPlayer *blackJackPlayerPointer) {
    updatePlayersScore(blackJackPlayerPointer);
    return blackJackPlayerPointer->score;
}

/**
 * A function to return if a black jack player has a blackjack
 * @param blackJackPlayerPointer        Pointer to the black jack player
 * @return                              If the player has a black jack
 */
int doesPlayerHaveBlackJack(BlackJackPlayer *blackJackPlayerPointer) {
    return blackJackPlayerPointer->score == 21 && blackJackPlayerPointer->player.cardsInHand == 2;
}

/**
 * A function to move a card from a deck stack to a players hand
 * @param stackPointer                  Pointer to the stack
 * @param cardPosition                  Position of the card in the stack to move
 * @param blackJackPlayerPointer        Pointer to the black jack player
 */
void moveCardFromStackToBlackJackPlayer(DeckStack *stackPointer, int cardPosition, BlackJackPlayer *blackJackPlayerPointer) {
    addCardToPlayer(&blackJackPlayerPointer->player, getCardFromStack(stackPointer, cardPosition));
    removeCardFromStack(stackPointer, cardPosition);
}

/**
 * A function to move a card from a players hand to a deck stack
 * @param stackPointer                  Pointer to the stack
 * @param blackJackPlayerPointer        Pointer to the black jack player
 */
void moveLastCardFromBlackJackPlayerToStack(DeckStack *stackPointer, BlackJackPlayer *blackJackPlayerPointer) {
    int playersHandPosition = blackJackPlayerPointer->player.cardsInHand - 1;
    addCardToStack(stackPointer, getCardFromPlayer(&blackJackPlayerPointer->player, playersHandPosition));
    removeCardFromPlayersHand(&blackJackPlayerPointer->player, playersHandPosition);
}