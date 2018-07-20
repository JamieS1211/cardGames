//
// Created by Jamie on 21/12/2017.
//

#ifndef BLACKJACK_BLACKJACKAPI_BLACKJACKCARD_H
#define BLACKJACK_BLACKJACKAPI_BLACKJACKCARD_H

/**
 * A function to return the maximum value of a card
 * @param card
 * @return
 */
int getCardValue(Card card);

/**
 * A function to deal a random card to a black jack player
 * @param deckStackPointer                  Pointer to the deck stack to deal from
 * @param usedDeckStackPointer              Pointer to the deck stack of used cards to shuffle from if needed
 * @param blackJackPlayerPointer            Pointer to the black jack player to deal to
 * @param silent                            Should this be done silently without printing output
 */
void dealBlackJack(DeckStack *deckStackPointer, DeckStack *usedDeckStackPointer, BlackJackPlayer *blackJackPlayerPointer, int silent);

/**
 * A function to specified card to a black jack player
 * @param deckStackPointer             Pointer to the stack to deal from
 * @param usedDeckStackPointer         Pointer to the stack of used cards to shuffle from if needed
 * @param blackJackPlayerPointer            Pointer to the black jack player to deal to
 * @param card              The card to give the player
 */
void giveBlackJackPlayerCard(DeckStack *deckStackPointer, DeckStack *usedDeckStackPointer, BlackJackPlayer *blackJackPlayerPointer, Card card);


#endif //BLACKJACK_BLACKJACKAPI_BLACKJACKCARD_H
