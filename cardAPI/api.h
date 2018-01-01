//
// Created by Jamie on 20/12/2017.
//

#define NUMBER_OF_SUITS 4
#define NUMBER_OF_CARDS 13

#define NOT_IN_DECK 0
#define IN_DECK 1

#define HEART 0
#define DIAMOND 1
#define SPADE 2
#define CLUB 3

#define ACE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define TEN 10
#define JACK 11
#define QUEEN 12
#define KING 13


typedef struct card {
    int cardSuit;
    int cardID;
} Card;

typedef struct deckStack {
    int numberOfDecks;
    int cardsLeft;
    Card *cardsInStack;
} DeckStack;

typedef struct simpleStack {
    int cardsLeft;
    int cardsCountsInStack[NUMBER_OF_CARDS + 1];
} SimpleStack;

typedef struct player {
    char playerName[120];
    int cardsInHand;
    Card *cardsDealt;
} Player;