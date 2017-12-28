//
// Created by Jamie on 21/12/2017.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "api.h"
#include "player.h"
#include "utilityFunctions.h"

/**
 * A function to initialise a player with a given name
 * @param player        Pointer to the player
 * @param name          Name of the player
 */
void initialisePlayer(Player *player, char name[120]) {
    strcpy(player->playerName, name);

    player->cardsInHand = 0;

    player->cardsDealt = NULL;
}

/**
 * A function to return the card at that position in the given players hand
 * @param stack                 Pointer to the player
 * @param position              Position of card
 * @return card                 Card at the given position
 */
Card getCardFromPlayer(Player *player, int position) {
    Card card;
    card.cardSuit = player->cardsDealt[position].cardSuit;
    card.cardID = player->cardsDealt[position].cardID;

    return card;
}

/**
 * A function to add a card to a players hand
 * @param player        Pointer to the player
 * @param card          Pointer to the card
 */
void addCardToPlayer(Player *player, Card card) {
    player->cardsInHand++;

    player->cardsDealt = realloc(player->cardsDealt, player->cardsInHand * sizeof(Card));

    player->cardsDealt[player->cardsInHand - 1].cardID = card.cardID;
    player->cardsDealt[player->cardsInHand - 1].cardSuit = card.cardSuit;
}

/**
 * A function to return the position (first if multiple) of the given card in the given players hand
 *
 * @param player        Pointer to the player
 * @param card          Card
 * @return              Position of card, returns -1 if that card is not in players hand
 */
int findPositionOfPlayersCard(Player *player, Card card) {
    for (int position = 0; position < player->cardsInHand; position++) {
        if (player->cardsDealt[position].cardID == card.cardID && player->cardsDealt[position].cardSuit == card.cardSuit) {
            return position;
        }
    }

    return -1;
}

/**
* A function to remove a card from a given position from the players hand
* @param player                 Pointer to the player
* @param position               Position of card
*/
void removeCardFromPlayersHand(Player *player, int position) {
    Card temp[player->cardsInHand];

    for (int i = 0; i < player->cardsInHand; i++) {
        temp[i].cardSuit = player->cardsDealt[i].cardSuit;
        temp[i].cardID = player->cardsDealt[i].cardID;
    }

    player->cardsInHand--;

    realloc(player->cardsDealt, player->cardsInHand * sizeof(Card));

    for (int i = 0; i <= player->cardsInHand; i++) {
        if (i < position) {
            player->cardsDealt[i].cardSuit = temp[i].cardSuit;
            player->cardsDealt[i].cardID = temp[i].cardID;
        } else if (i > position) {
            player->cardsDealt[i - 1].cardSuit = temp[i].cardSuit;
            player->cardsDealt[i - 1].cardID = temp[i].cardID;
        }
    }
}

/**
 * A function to print out all the cards that a player has
 * @param player        The player
 */
void listCardsOfPlayer(Player player) {
    if (player.cardsInHand > 0) {
        for (int i = 0; i < player.cardsInHand; i++) {
            char suit[12] = "";
            char cardName[12] = "";

            getCardSuitName(suit, player.cardsDealt[i]);
            getCardName(cardName, player.cardsDealt[i]);

            printf("Player \"%s\" has %s of %s \n", player.playerName, cardName, suit);
        }
    } else {
        printf("Player \"%s\" has no cards \n", player.playerName);
    }
}