//
// Created by Jamie on 22/12/2017.
//

#include "blackJack.h"

#include "../cardAPI/player.h"

/**
 * A function to initialise a black jack player with a given name
 * @param blackJackPlayer        Pointer to the black jack player
 * @param name                   Name of the black jack player
 */
void initialiseBlackJackPlayer(BlackJackPlayer *blackJackPlayer, char name[120]) {
    initialisePlayer(&blackJackPlayer->player, name);

    blackJackPlayer->scoreMax = 0;
    blackJackPlayer->scoreMin = 0;
}

/**
 * A function to print out all the cards that a black jack player has
 * @param blackJackPlayer        Pointer to the black jack player
 */
void listCardsOfBlackJackPlayer(BlackJackPlayer *blackJackPlayer) {
    listCardsOfPlayer(blackJackPlayer->player);
}