//
// Created by Jamie on 21/12/2017.
//

/**
 * A function to initialise a player with a given name
 * @param playerPointer        Pointer to the player
 * @param name          Name of the player
 */
void initialisePlayer(Player *playerPointer, char name[120]);

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
void addCardToPlayer(Player *playerPointer, Card card);

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
void removeCardFromPlayersHand(Player *playerPointer, int position);

/**
 * A function to print out all the cards that a player has
 * @param player        The player
 */
void listCardsOfPlayer(Player player);