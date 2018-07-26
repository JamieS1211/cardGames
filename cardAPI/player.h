//
// Created by Jamie on 21/12/2017.
//


#ifndef CARDAPI_PLAYER_H
#define CARDAPI_PLAYER_H

/**
 * A function to initialise a player with a given name and no memory to hold cards in hand
 * @param playerPointer         Pointer to the player
 * @param name                  Name of the player
 */
void initialisePlayerNoMemory(Player *playerPointer, char *name);

/**
 * A function to initialise a player with a given name and specified memory to hold cards in hand
 * @param playerPointer         Pointer to the player
 * @param name                  Name of the player
 */
void initialisePlayerSpecifiedMemory(Player *playerPointer, int maxCards, char *name);

/**
 * A function to return the card at that position in the given players hand
 * @param stack                 Pointer to the player
 * @param position              Position of card
 * @return card                 Card at the given position
 */
Card getCardFromPlayer(Player *playerPointer, int position);

/**
 * A function to add a card to a players hand
 * @param playerPointer        Pointer to the player
 * @param card          Pointer to the card
 */
void addCardToPlayerDynamicMemory(Player *playerPointer, Card card);

/**
 * A function to add a card to a players hand (WARNING STATIC MEMORY FUNCTION USE WITH CARE)
 * @param playerPointer        Pointer to the player
 * @param card          Pointer to the card
 */
void addCardToPlayerStaticMemory(Player *playerPointer, Card card);

/**
 * A function to add a card to a players hand
 * @param playerPointer        Pointer to the player
 * @param card          Pointer to the card
 */
void addCardToPlayerStaticMemory(Player *playerPointer, Card card);

/**
 * A function to return the position (first if multiple) of the given card in the given players hand
 *
 * @param playerPointer        Pointer to the player
 * @param card          Card
 * @return              Position of card, returns -1 if that card is not in players hand
 */
int findPositionOfPlayersCard(Player *playerPointer, Card card);

/**
* A function to remove a card from a given position from the players hand
* @param playerPointer                 Pointer to the player
* @param position               Position of card
*/
void removeCardFromPlayersHandDynamicMemory(Player *playerPointer, int position);

/**
* A function to remove a card from a given position from the players hand (WARNING STATIC MEMORY FUNCTION USE WITH CARE)
* @param playerPointer                 Pointer to the player
* @param position               Position of card
*/
void removeCardFromPlayersHandStaticMemory(Player *playerPointer, int position);

/**
 * A function to print out all the cards that a player has
 * @param player        The player
 */
void listCardsOfPlayer(Player player);


#endif //CARDAPI_PLAYER_H