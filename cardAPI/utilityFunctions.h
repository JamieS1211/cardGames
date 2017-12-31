//
// Created by Jamie on 21/12/2017.
//

/**
 * A function that updates a pointer to a character array and pointer to a card and updates the character array to be the suit of the card
 * @param cardName          Pointer to character array to store suit of card
 * @param card              The card
 */
void getCardSuitName(char *suitPointer, Card card);

/**
 * A function that updates a pointer to a character array and pointer to a card and updates the character array to be the name of the card
 * @param cardNamePointer          Pointer to character array to store name of card
 * @param card              The card
 */
void getCardName(char *cardNamePointer, Card card);

/**
 * A function that takes a stack of cards and a player and deals a random card from that stack to the player returning the card that was dealt
 *
 * @param stackPointer         Stack of cards to deal from
 * @param playerPointer        Player to deal card to
 * @return              Card that was dealt to player
 */
Card dealCard(DeckStack *stackPointer, Player *playerPointer);

/**
 * A function to request user input for a specific card
 * @return              The card the user specified
 */
Card getCardDealt();