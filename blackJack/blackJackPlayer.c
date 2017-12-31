//
// Created by Jamie on 22/12/2017.
//

#include <stdio.h>
#include <stdlib.h>

#include "blackJack.h"

#include "../cardAPI/player.h"
#include "blackJackCard.h"

/**
 * A function to initialise a black jack player with a given name
 * @param blackJackPlayerPointer        Pointer to the black jack player
 * @param name                          Name of the black jack player
 */
void initialiseBlackJackPlayer(BlackJackPlayer *blackJackPlayerPointer, char name[120]) {
    initialisePlayer(&blackJackPlayerPointer->player, name);

    blackJackPlayerPointer->scores = NULL;
    blackJackPlayerPointer->differentScores = 1;
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
    int differentScores = 1;
    int baseScore = 0;

    for (int i = 0; i < blackJackPlayerPointer->player.cardsInHand; i++) {
        baseScore += getCardValue(blackJackPlayerPointer->player.cardsDealt[i]);
        if (blackJackPlayerPointer->player.cardsDealt[i].cardID == ACE) {
            differentScores++;
        }
    }

    blackJackPlayerPointer->differentScores = differentScores;
    blackJackPlayerPointer->scores = realloc(blackJackPlayerPointer->scores, differentScores * sizeof(int));
    for (int i = 0; i < differentScores; i++) {
        blackJackPlayerPointer->scores[i] = baseScore + (10 * i);
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
    for (int i = blackJackPlayerPointer->differentScores - 1; i >= 0; i--) {
        if (blackJackPlayerPointer->scores[i] <= 21) {
            return blackJackPlayerPointer->scores[i];
        }
    }

    return blackJackPlayerPointer->scores[0];
}