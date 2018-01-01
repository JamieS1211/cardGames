//
// Created by Jamie on 22/12/2017.
//

/**
 * A function to initialise a black jack player with a given name
 * @param blackJackPlayerPointer        Pointer to the black jack player
 * @param name                   Name of the black jack player
 */
void initialiseBlackJackPlayer(BlackJackPlayer *blackJackPlayerPointer, char name[120]);

/**
 * A function to print out all the cards that a black jack player has
 * @param blackJackPlayerPointer        Pointer to the black jack player
 */
void listCardsOfBlackJackPlayer(BlackJackPlayer *blackJackPlayerPointer);

/**
 * A function to remove a card from a black jack player
 * @param blackJackPlayerPointer       Pointer to the black jack player
 * @param position              Position
 */
void removeCardFromBlackJackPlayersHand(BlackJackPlayer *blackJackPlayerPointer, int position);

/**
 * A function to read all cards a black jack player has and store all the possible scores
 * @param blackJackPlayerPointer        Pointer to the black jack player
 */
void updatePlayersScore(BlackJackPlayer *blackJackPlayerPointer);

/**
 * A function to return if a black jack player has a blackjack
 * @param blackJackPlayerPointer        Pointer to the black jack player
 * @return                              If the player has a black jack
 */
int doesPlayerHaveBlackJack(BlackJackPlayer *blackJackPlayerPointer);

/**
 * A function to move a card from a deck stack to a players hand
 * @param deckStackPointer                  Pointer to the stack
 * @param cardPosition                  Position of the card in the stack to move
 * @param blackJackPlayerPointer        Pointer to the black jack player
 */
void moveCardFromStackToBlackJackPlayer(DeckStack *deckStackPointer, int cardPosition, BlackJackPlayer *blackJackPlayerPointer);

/**
 * A function to move a card from a players hand to a deck stack
 * @param deckStackPointer                  Pointer to the stack
 * @param blackJackPlayerPointer        Pointer to the black jack player
 */
void moveLastCardFromBlackJackPlayerToStack(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer);