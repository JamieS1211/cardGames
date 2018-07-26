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
 * A function to initialise a player with a given name and no memory to hold cards in hand
 * @param playerPointer         Pointer to the player
 * @param name                  Name of the player
 */
void initialisePlayerNoMemory(Player *playerPointer, char *name) {
    strcpy(playerPointer->playerName, name);

    playerPointer->cardsInHand = 0;

    playerPointer->cardsDealt = NULL;
}

/**
 * A function to initialise a player with a given name and specified memory to hold cards in hand
 * @param playerPointer         Pointer to the player
 * @param name                  Name of the player
 */
void initialisePlayerSpecifiedMemory(Player *playerPointer, int maxCards, char *name) {
    strcpy(playerPointer->playerName, name);

    playerPointer->cardsInHand = 0;

    playerPointer->cardsDealt = malloc(maxCards * sizeof(Card));
}

/**
 * A function to return the card at that position in the given players hand
 * @param stack                 Pointer to the player
 * @param position              Position of card
 * @return card                 Card at the given position
 */
Card getCardFromPlayer(Player *playerPointer, int position) {
    Card card;
    card.cardSuit = playerPointer->cardsDealt[position].cardSuit;
    card.cardID = playerPointer->cardsDealt[position].cardID;

    return card;
}

/**
 * A function to add a card to a players hand
 * @param playerPointer         Pointer to the player
 * @param card                  Pointer to the card
 */
void addCardToPlayerDynamicMemory(Player *playerPointer, Card card) {
    playerPointer->cardsInHand++;

    playerPointer->cardsDealt = realloc(playerPointer->cardsDealt, playerPointer->cardsInHand * sizeof(Card));

    playerPointer->cardsDealt[playerPointer->cardsInHand - 1].cardID = card.cardID;
    playerPointer->cardsDealt[playerPointer->cardsInHand - 1].cardSuit = card.cardSuit;
}

/**
 * A function to add a card to a players hand (WARNING STATIC MEMORY FUNCTION USE WITH CARE)
 * @param playerPointer         Pointer to the player
 * @param card                  Pointer to the card
 */
void addCardToPlayerStaticMemory(Player *playerPointer, Card card) {
    playerPointer->cardsInHand++;

    playerPointer->cardsDealt[playerPointer->cardsInHand - 1].cardID = card.cardID;
    playerPointer->cardsDealt[playerPointer->cardsInHand - 1].cardSuit = card.cardSuit;
}

/**
 * A function to return the position (first if multiple) of the given card in the given players hand
 *
 * @param playerPointer         Pointer to the player
 * @param card                  Card
 * @return                      Position of card, returns -1 if that card is not in players hand
 */
int findPositionOfPlayersCard(Player *playerPointer, Card card) {
    for (int position = 0; position < playerPointer->cardsInHand; position++) {
        if (playerPointer->cardsDealt[position].cardID == card.cardID && playerPointer->cardsDealt[position].cardSuit == card.cardSuit) {
            return position;
        }
    }

    return -1;
}

/**
* A function to remove a card from a given position from the players hand
* @param playerPointer              Pointer to the player
* @param position                   Position of card
*/
void removeCardFromPlayersHandDynamicMemory(Player *playerPointer, int position) {
    Card temp[playerPointer->cardsInHand];

    for (int i = 0; i < playerPointer->cardsInHand; i++) {
        temp[i].cardSuit = playerPointer->cardsDealt[i].cardSuit;
        temp[i].cardID = playerPointer->cardsDealt[i].cardID;
    }

    playerPointer->cardsInHand--;

    playerPointer->cardsDealt = realloc(playerPointer->cardsDealt, playerPointer->cardsInHand * sizeof(Card));

    for (int i = 0; i <= playerPointer->cardsInHand; i++) {
        if (i < position) {
            playerPointer->cardsDealt[i].cardSuit = temp[i].cardSuit;
            playerPointer->cardsDealt[i].cardID = temp[i].cardID;
        } else if (i > position) {
            playerPointer->cardsDealt[i - 1].cardSuit = temp[i].cardSuit;
            playerPointer->cardsDealt[i - 1].cardID = temp[i].cardID;
        }
    }
}

/**
* A function to remove a card from a given position from the players hand (WARNING STATIC MEMORY FUNCTION USE WITH CARE)
* @param playerPointer              Pointer to the player
* @param position                   Position of card
*/
void removeCardFromPlayersHandStaticMemory(Player *playerPointer, int position) {
    Card temp[playerPointer->cardsInHand];

    for (int i = 0; i < playerPointer->cardsInHand; i++) {
        temp[i].cardSuit = playerPointer->cardsDealt[i].cardSuit;
        temp[i].cardID = playerPointer->cardsDealt[i].cardID;
    }

    playerPointer->cardsInHand--;

    for (int i = 0; i <= playerPointer->cardsInHand; i++) {
        if (i < position) {
            playerPointer->cardsDealt[i].cardSuit = temp[i].cardSuit;
            playerPointer->cardsDealt[i].cardID = temp[i].cardID;
        } else if (i > position) {
            playerPointer->cardsDealt[i - 1].cardSuit = temp[i].cardSuit;
            playerPointer->cardsDealt[i - 1].cardID = temp[i].cardID;
        }
    }
}

/**
 * A function to print out all the cards that a player has
 * @param player                       The player
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