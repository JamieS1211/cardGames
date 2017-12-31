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
 * A function to return the best score a black jack player has and if all scores make player bust the minimum score
 * @param blackJackPlayerPointer         Pointer to the black jack player
 * @return score                  The best score of the black jack player or lowest if bust
 */
int getPlayersBestScore(BlackJackPlayer *blackJackPlayerPointer);