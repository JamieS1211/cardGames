//
// Created by Jamie on 21/12/2017.
//

/**
 * A function to return the maximum value of a card
 * @param card
 * @return
 */
int getCardValue(Card card);

/**
 * A function to deal a random card to a black jack player
 * @param stackPointer             Pointer to the stack to deal from
 * @param usedStackPointer         Pointer to the stack of used cards to shuffle from if needed
 * @param blackJackPlayerPointer            Pointer to the black jack player to deal to
 */
void dealBlackJack(DeckStack *stackPointer, DeckStack *usedStackPointer, BlackJackPlayer *blackJackPlayerPointer);

/**
 * A function to specified card to a black jack player
 * @param stackPointer             Pointer to the stack to deal from
 * @param usedStackPointer         Pointer to the stack of used cards to shuffle from if needed
 * @param blackJackPlayerPointer            Pointer to the black jack player to deal to
 * @param card              The card to give the player
 */
void giveBlackJackPlayerCard(DeckStack *stackPointer, DeckStack *usedStackPointer, BlackJackPlayer *blackJackPlayerPointer, Card card);