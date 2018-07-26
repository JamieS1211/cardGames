//
// Created by Jamie on 21/12/2017.
//

#include <stdio.h>

#include "blackJack.h"

#include "../../cardAPI/deckStack.h"
#include "../../cardAPI/utilityFunctions.h"
#include "../../cardAPI/player.h"
#include "blackJackPlayer.h"

/**
 * A function to return the minimum value of a card
 * @param card                              The card to get value of
 * @return
 */
int getCardValue(Card card) {
    switch (card.cardID) {
        case KING:
        case QUEEN:
        case JACK:
            return 10;

        default:
            return card.cardID;
    }
}

/**
 * A function to deal a random card to a black jack player
 * @param deckStackPointer                  Pointer to the deck stack to deal from
 * @param simpleDeckStackPointer            Pointer to the simple form of the deck stack to deal from
 * @param blackJackPlayerPointer            Pointer to the black jack player to deal to
 * @param silent                            Should this be done silently without printing output
 */
void dealBlackJack(DeckStack *deckStackPointer, SimpleStack *simpleDeckStackPointer, BlackJackPlayer *blackJackPlayerPointer, int silent) {

    if (deckStackPointer->cardsLeft == 0) {
        printf("ERROR: No more cards to deal \n");
        return;
    }

    Card card = dealCardStaticMemory(deckStackPointer, &blackJackPlayerPointer->player);
    updatePlayersScore(blackJackPlayerPointer);

    simpleDeckStackPointer->cardsLeft--;
    if (card.cardID >= JACK) {
        simpleDeckStackPointer->cardsCountsInStack[TEN]--;
    } else {
        simpleDeckStackPointer->cardsCountsInStack[card.cardID]--;
    }

    if (!silent) {
        char suit[120] = "";
        char cardName[120] = "";

        getCardSuitName(suit, card);
        getCardName(cardName, card);

        printf("Dealt card %s of %s to \"%s\" giving score of: %i ", cardName, suit,
               blackJackPlayerPointer->player.playerName, blackJackPlayerPointer->score);

        if (blackJackPlayerPointer->isScoreSoft) {
            printf("or %i", blackJackPlayerPointer->score - 10);
        }
        printf("\n");
    }

}

/**
 * A function to specified card to a black jack player
 * @param deckStackPointer                  Pointer to the stack to deal from
 * @param usedDeckStackPointer              Pointer to the stack of used cards to shuffle from if needed
 * @param blackJackPlayerPointer            Pointer to the black jack player to deal to
 * @param card                              The card to give the player
 */
void giveBlackJackPlayerCard(DeckStack *deckStackPointer, DeckStack *usedDeckStackPointer, BlackJackPlayer *blackJackPlayerPointer, Card card) {

    if (deckStackPointer->cardsLeft == 0) {
        for (int i = 0; i < usedDeckStackPointer->cardsLeft; i++) {
            addCardToDeckStack(deckStackPointer, getCardFromDeckStack(usedDeckStackPointer, i));
            removeCardFromDeckStack(usedDeckStackPointer, i);
        }
    }

    removeCardFromDeckStack(deckStackPointer, findPositionOfDeckStacksCard(deckStackPointer, card));
    addCardToPlayerStaticMemory(&blackJackPlayerPointer->player, card);
    updatePlayersScore(blackJackPlayerPointer);

    char suit[120] = "";
    char cardName[120] = "";

    getCardSuitName(suit, card);
    getCardName(cardName, card);

    printf("Dealt card %s of %s to \"%s\" giving score of: %i ", cardName, suit, blackJackPlayerPointer->player.playerName, blackJackPlayerPointer->score);

    if (blackJackPlayerPointer->isScoreSoft) {
        printf("or %i", blackJackPlayerPointer->score - 10);
    }
    printf("\n");
}