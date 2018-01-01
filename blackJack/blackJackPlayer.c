//
// Created by Jamie on 22/12/2017.
//

#include <stdio.h>
#include <stdlib.h>

#include "blackJack.h"

#include "../cardAPI/player.h"
#include "blackJackCard.h"
#include "../cardAPI/deckStack.h"
#include "../cardAPI/utilityFunctions.h"

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

    Card card;
    for (int i = 0; i < blackJackPlayerPointer->player.cardsInHand; i++) {
        card = getCardFromPlayer(&blackJackPlayerPointer->player, i);
        blackJackPlayerPointer->score += getCardValue(card);
        if (card.cardID == ACE) {
            aceCount++;
        }
    }

    if (aceCount > 0 && blackJackPlayerPointer->score <= 11) {
        blackJackPlayerPointer->score += 10;
        blackJackPlayerPointer->isScoreSoft = 1;
    } else {
        blackJackPlayerPointer->isScoreSoft = 0;
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
 * A function to return if a black jack player has a blackjack
 * @param blackJackPlayerPointer        Pointer to the black jack player
 * @return                              If the player has a black jack
 */
int doesPlayerHaveBlackJack(BlackJackPlayer *blackJackPlayerPointer) {
    return blackJackPlayerPointer->score == 21 && blackJackPlayerPointer->player.cardsInHand == 2;
}

/**
 * A function to move a card from a deck stack to a players hand
 * @param simpleStackPointer            Pointer to the stack
 * @param cardID                        Card in the stack to move
 * @param blackJackPlayerPointer        Pointer to the black jack player
 */
void moveCardFromSimpleStackToBlackJackPlayer(SimpleStack *simpleStackPointer, int cardID, BlackJackPlayer *blackJackPlayerPointer) {
    Card card;
    card.cardID = cardID;
    card.cardSuit = 0; //Place holder not used

    addCardToPlayer(&blackJackPlayerPointer->player, card);
    simpleStackPointer->cardsCountsInStack[cardID]--;
    simpleStackPointer->cardsLeft--;
}

/**
 * A function to move a card from a players hand to a deck stack
 * @param simpleStackPointer            Pointer to the stack
 * @param blackJackPlayerPointer        Pointer to the black jack player
 */
void moveLastCardFromBlackJackPlayerToSimpleStack(SimpleStack *simpleStackPointer, BlackJackPlayer *blackJackPlayerPointer) {
    Card card = getCardFromPlayer(&blackJackPlayerPointer->player, blackJackPlayerPointer->player.cardsInHand - 1);
    simpleStackPointer->cardsCountsInStack[card.cardID]++;
    simpleStackPointer->cardsLeft++;
    removeCardFromPlayersHand(&blackJackPlayerPointer->player, blackJackPlayerPointer->player.cardsInHand - 1);
}