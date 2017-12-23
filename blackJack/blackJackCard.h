//
// Created by Jamie on 21/12/2017.
//

/**
 * A function to return the maximum value of a card
 * @param card
 * @return
 */
int getCardMaxValue(Card card);

/**
 * A function to return the minimum value of a card
 * @param card
 * @return
 */
int getCardMinValue(Card card);

/**
 * A function to deal a random card to a black jack player
 * @param stack             Pointer to the stack to deal from
 * @param usedStack         Pointer to the stack of used cards to shuffle from if needed
 * @param player            Pointer to the black jack player to deal to
 */
void dealBlackJack(DeckStack *stack, DeckStack *usedStack, BlackJackPlayer *player);