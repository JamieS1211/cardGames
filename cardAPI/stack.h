//
// Created by Jamie on 21/12/2017.
//

/**
 * A function to initialise a deck stack full of cards taking the pointer to the deck stack and number of decks
 * @param stackPointer                 Pointer to stack
 * @param numberOfDecks         Number of decks in stack
 */
void initialiseFullStack(DeckStack *stackPointer, int numberOfDecks);

/**
 * A function to initialise a deck stack with no cards taking the pointer to the deck stack and number of decks
 * @param stackPointer                 Pointer to stack
 * @param numberOfDecks         Number of decks in stack
 */
void initialiseEmptyStack(DeckStack *stackPointer, int numberOfDecks);

/**
 * A function to add a card to the deck stack
 * @param stackPointer                 Pointer to stack
 * @param numberOfDecks         Number of decks in stack
 */
void addCardToStack(DeckStack *stackPointer, Card card);

/**
 * A function to return the card at that position in the given stack
 * @param stackPointer                 Pointer to the stack
 * @param position              Position of card
 * @return card                 Card at the given position
 */
Card getCardFromStack(DeckStack *stackPointer, int position);

/**
 * A function to return the position (first if multiple) of the given card in the stack
 *
 * @param stackPointer         Pointer to the stack
 * @param card          Card
 * @return              Position of card, returns -1 if that card is not in players hand
 */
int findPositionOfStacksCard(DeckStack *stackPointer, Card card);

/**
 * A function to remove a card from a given position from the deck stack
 * @param deckStack              Pointer to the stack
 * @param position               Position of card
 */
void removeCardFromStack(DeckStack *stackPointer, int position);