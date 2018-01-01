//
// Created by Jamie on 21/12/2017.
//

/**
 * A function to initialise a deck stack full of cards taking the pointer to the deck stack and number of decks
 * @param deckStackPointer                 Pointer to stack
 * @param numberOfDecks         Number of decks in stack
 */
void initialiseFullDeckStack(DeckStack *deckStackPointer, int numberOfDecks);

/**
 * A function to initialise a deck stack with no cards taking the pointer to the deck stack and number of decks
 * @param deckStackPointer                 Pointer to stack
 * @param numberOfDecks         Number of decks in stack
 */
void initialiseEmptyDeckStack(DeckStack *deckStackPointer, int numberOfDecks);

/**
 * A function to add a card to the deck stack
 * @param deckStackPointer                 Pointer to stack
 * @param numberOfDecks         Number of decks in stack
 */
void addCardToDeckStack(DeckStack *deckStackPointer, Card card);

/**
 * A function to return the card at that position in the given stack
 * @param deckStackPointer                 Pointer to the stack
 * @param position              Position of card
 * @return card                 Card at the given position
 */
Card getCardFromDeckStack(DeckStack *deckStackPointer, int position);

/**
 * A function to return the position (first if multiple) of the given card in the stack
 *
 * @param deckStackPointer         Pointer to the stack
 * @param card          Card
 * @return              Position of card, returns -1 if that card is not in players hand
 */
int findPositionOfDeckStacksCard(DeckStack *deckStackPointer, Card card);

/**
 * A function to remove a card from a given position from the deck stack
 * @param deckStack              Pointer to the stack
 * @param position               Position of card
 */
void removeCardFromDeckStack(DeckStack *deckStackPointer, int position);