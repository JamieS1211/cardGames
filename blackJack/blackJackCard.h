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
 * @param stack             Pointer to the stack to deal from
 * @param usedStack         Pointer to the stack of used cards to shuffle from if needed
 * @param player            Pointer to the black jack player to deal to
 */
void dealBlackJack(DeckStack *stack, DeckStack *usedStack, BlackJackPlayer *player);

/**
 * A function to specified card to a black jack player
 * @param stack             Pointer to the stack to deal from
 * @param usedStack         Pointer to the stack of used cards to shuffle from if needed
 * @param player            Pointer to the black jack player to deal to
 * @param card              The card to give the player
 */
void giveBlackJackPlayerCard(DeckStack *stack, DeckStack *usedStack, BlackJackPlayer *player, Card card);