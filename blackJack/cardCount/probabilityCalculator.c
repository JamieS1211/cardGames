//
// Created by Jamie on 28/12/2017.
//

int layersDeep = 1;

#include <stdio.h>
#include <stdlib.h>
#include "../blackJack.h"
#include "../blackJackCard.h"
#include "../../cardAPI/deckStack.h"
#include "../blackJackPlayer.h"

void printProbabilities(Probability probabilityTree[3][23]) {
    for (int layer = 0; layer < 2; layer++) {
        printf("\nLayer: %i \n", layer);
        for (int i = 0; i < 23; i++) {
            if (i <= 21) {
                printf("Score: %i", i);
            } else {
                printf("Bust:    ");
            }
               printf("\t Chance: %i   \t Win: %i   \t Draw: %i   \t Lose: %i \n",
                   probabilityTree[layer][i].waysToAchieveScore,
                   probabilityTree[layer][i].waysWithScoreToWin,
                   probabilityTree[layer][i].waysWithScoreToDraw,
                   probabilityTree[layer][i].waysWithScoreToLoose);
        }
    }
}

// A function that takes a player and dealer state and updates a probability tree with chance player wins / losses / draws with dealer provided player stands at this point

void calculateChanceOfWin(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability *probabilityNodePointer) {

    int currentBestPlayerScore = blackJackPlayerPointer->score;
    if (currentBestPlayerScore > 21) {
        currentBestPlayerScore = 22;
    }

    int currentBestDealerScore = blackJackDealerPointer->score;
    if (currentBestDealerScore > 21) {
        currentBestDealerScore = 22;
    }


    if (doesPlayerHaveBlackJack(blackJackPlayerPointer) && doesPlayerHaveBlackJack(blackJackDealerPointer)) {
        // Both have black jack
        probabilityNodePointer->waysWithScoreToDraw++;
    } else if (doesPlayerHaveBlackJack(blackJackDealerPointer)) {
        // Dealer has black jack
        probabilityNodePointer->waysWithScoreToLoose++;
    } else if (doesPlayerHaveBlackJack(blackJackPlayerPointer)) {
        // Player has black jack
        probabilityNodePointer->waysWithScoreToWin++;
    } else if (currentBestPlayerScore > 21) {
        // Player gone bust
        probabilityNodePointer->waysWithScoreToLoose++;
    } else if (currentBestDealerScore > 21) {
        // Dealer gone bust
        probabilityNodePointer->waysWithScoreToWin++;
    } else if (currentBestDealerScore == currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and dealer has same score
        probabilityNodePointer->waysWithScoreToDraw++;
    } else if (currentBestDealerScore > currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and player has better score
        probabilityNodePointer->waysWithScoreToLoose++;
    } else if (currentBestDealerScore < currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and player has better score
        probabilityNodePointer->waysWithScoreToWin++;
    } else {
        // Dealer will hit again and should re run this code giving them every possible card left in deck stack to deal.
        for (int i = 0; i < deckStackPointer->cardsLeft; i++) {
            moveCardFromStackToBlackJackPlayer(deckStackPointer, i, blackJackDealerPointer);
            updatePlayersScore(blackJackDealerPointer);
            calculateChanceOfWin(deckStackPointer, blackJackPlayerPointer, blackJackDealerPointer, probabilityNodePointer);
            moveLastCardFromBlackJackPlayerToStack(deckStackPointer, blackJackDealerPointer);
            updatePlayersScore(blackJackDealerPointer);
        }
    }
}

// A recursive function that builds up a pobability tree showing probabilities of outcomes

void calculatePlayerHitScores(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability probabilityTree[3][23], int currentLayer) {
    int currentBestPlayerScore = blackJackPlayerPointer->score;
    int nextLayer = currentLayer + 1;

    if (currentBestPlayerScore > 21) {
        currentBestPlayerScore = 22;
    } else if (currentBestPlayerScore <= 21 && nextLayer <= 2) {
        for (int i = 0; i < deckStackPointer->cardsLeft ; i++) {
            moveCardFromStackToBlackJackPlayer(deckStackPointer, i, blackJackPlayerPointer);
            updatePlayersScore(blackJackPlayerPointer);

            calculatePlayerHitScores(deckStackPointer, blackJackPlayerPointer, blackJackDealerPointer, probabilityTree, nextLayer);

            moveLastCardFromBlackJackPlayerToStack(deckStackPointer, blackJackPlayerPointer);
        }
    }

    probabilityTree[currentLayer][currentBestPlayerScore].waysToAchieveScore++;
    //calculateChanceOfWin(stackPointer, blackJackPlayerPointer, blackJackDealerPointer, probabilityTree[currentBestPlayerScore]);
}

void calculateProbabilities(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer) {

    // An array of the amount of ways each best score can be achieved, 0 = score of 2, 1 = score of 3 ... 19 = score of 21, 20 = bust.

    int playerChances[21] = {0};

    for (int i = 0; i < deckStackPointer->cardsLeft; i++) {
        int score = blackJackPlayerPointer->score;
        Card card = deckStackPointer->cardsInStack[i];

        score += getCardValue(card);

        if (card.cardID == ACE && score < 12) {
            score += 10;
        }

        if (score > 21) {
            score = 22;
        }

        playerChances[score - 2]++;
    }

    printf("\n \n \n");
    for (int i = 0; i < 21; i++) {
        if (playerChances[i] != 0) {
            if (i == 20) {
                printf("The chance you hit and go bust is %i/%i \n", playerChances[i],
                       deckStackPointer->cardsLeft);
            }  else {
                printf("The chance you hit and have a best score of %i is %i/%i \n", i + 2, playerChances[i],
                       deckStackPointer->cardsLeft);
            }
        }
    }
    printf("\n \n \n");

    Probability probabilityTree[3][23];

    for (int layer = 0; layer < 3; layer++) {
        for (int score = 0; score <= 22; score++) {
            probabilityTree[layer][score].waysToAchieveScore = 0;
            probabilityTree[layer][score].waysWithScoreToWin = 0;
            probabilityTree[layer][score].waysWithScoreToDraw = 0;
            probabilityTree[layer][score].waysWithScoreToLoose = 0;
        }
    }

    calculatePlayerHitScores(deckStackPointer, blackJackPlayerPointer, blackJackDealerPointer, probabilityTree, 0);

    printProbabilities(probabilityTree);
}