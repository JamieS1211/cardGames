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
 * @param blackJackPlayer        Pointer to the black jack player
 * @param name                   Name of the black jack player
 */
void initialiseBlackJackPlayer(BlackJackPlayer *blackJackPlayer, char name[120]) {
    initialisePlayer(&blackJackPlayer->player, name);

    blackJackPlayer->scores = NULL;
    blackJackPlayer->differentScores = 1;
}

/**
 * A function to print out all the cards that a black jack player has
 * @param blackJackPlayer        Pointer to the black jack player
 */
void listCardsOfBlackJackPlayer(BlackJackPlayer *blackJackPlayer) {
    listCardsOfPlayer(blackJackPlayer->player);
}

/**
 * A function to read all cards a black jack player has and store all the possible scores
 * @param blackJackPlayer        Pointer to the black jack player
 */
void updatePlayersScore(BlackJackPlayer *blackJackPlayer) {
    int differentScores = 1;
    int baseScore = 0;

    for (int i = 0; i < blackJackPlayer->player.cardsInHand; i++) {
        baseScore += getCardValue(blackJackPlayer->player.cardsDealt[i]);
        if (blackJackPlayer->player.cardsDealt[i].cardID == ACE) {
            differentScores++;
        }
    }

    blackJackPlayer->differentScores = differentScores;
    blackJackPlayer->scores = realloc(blackJackPlayer->scores, differentScores * sizeof(int));
    for (int i = 0; i < differentScores; i++) {
        blackJackPlayer->scores[i] = baseScore + (10 * i);
    }
}

/**
 * A function to remove a card from a black jack player
 * @param blackJackPlayer       Pointer to the black jack player
 * @param position              Position
 */
void removeCardFromBlackJackPlayersHand(BlackJackPlayer *blackJackPlayer, int position) {
    removeCardFromPlayersHand(&blackJackPlayer->player, position);
    updatePlayersScore(blackJackPlayer);
}

/**
 * A function to return the best score a black jack player has and if all scores make player bust the minimum score
 * @param blackJackPlayer         Pointer to the black jack player
 * @return score                  The best score of the black jack player or lowest if bust
 */
int getPlayersBestScore(BlackJackPlayer *blackJackPlayer) {
    for (int i = blackJackPlayer->differentScores - 1; i >= 0; i--) {
        if (blackJackPlayer->scores[i] <= 21) {
            return blackJackPlayer->scores[i];
        }
    }

    return 22;
}