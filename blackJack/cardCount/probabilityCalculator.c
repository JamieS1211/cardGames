//
// Created by Jamie on 28/12/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include "../blackJack.h"
#include "../blackJackCard.h"
#include "../../cardAPI/stack.h"
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
                   probabilityTree[layer][i].numberOfWaysToAchieveScore,
                   probabilityTree[layer][i].numberOfWaysWithScoreToWin,
                   probabilityTree[layer][i].numberOfWaysWithScoreToDraw,
                   probabilityTree[layer][i].numberOfWaysWithScoreToLoose);
        }
    }
}

// A function that takes a player and dealer state and updates a probability tree with chance player wins / losses / draws with dealer provided player stands at this point

void calculateChanceOfWin(DeckStack *stackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability *probabilityNodePointer) {

    int currentBestPlayerScore = getPlayersBestScore(blackJackPlayerPointer);
    if (currentBestPlayerScore > 21) {
        currentBestPlayerScore = 22;
    }

    int currentBestDealerScore = getPlayersBestScore(blackJackDealerPointer);
    if (currentBestDealerScore > 21) {
        currentBestDealerScore = 22;
    }


    if (doesPlayerHaveBlackJack(blackJackPlayerPointer) && doesPlayerHaveBlackJack(blackJackDealerPointer)) {
        // Both have black jack
        probabilityNodePointer->numberOfWaysWithScoreToDraw++;
    } else if (doesPlayerHaveBlackJack(blackJackDealerPointer)) {
        // Dealer has black jack
        probabilityNodePointer->numberOfWaysWithScoreToLoose++;
    } else if (doesPlayerHaveBlackJack(blackJackPlayerPointer)) {
        // Player has black jack
        probabilityNodePointer->numberOfWaysWithScoreToWin++;
    } else if (currentBestPlayerScore > 21) {
        // Player gone bust
        probabilityNodePointer->numberOfWaysWithScoreToLoose++;
    } else if (currentBestDealerScore > 21) {
        // Dealer gone bust
        probabilityNodePointer->numberOfWaysWithScoreToWin++;
    } else if (currentBestDealerScore == currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and dealer has same score
        probabilityNodePointer->numberOfWaysWithScoreToDraw++;
    } else if (currentBestDealerScore > currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and player has better score
        probabilityNodePointer->numberOfWaysWithScoreToLoose++;
    } else if (currentBestDealerScore < currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and player has better score
        probabilityNodePointer->numberOfWaysWithScoreToWin++;
    } else {
        // Dealer will hit again and should re run this code giving them every possible card left in deck stack to deal.
        for (int i = 0; i < stackPointer->cardsLeft; i++) {
            moveCardFromStackToBlackJackPlayer(stackPointer, i, blackJackDealerPointer);
            calculateChanceOfWin(stackPointer, blackJackPlayerPointer, blackJackDealerPointer, probabilityNodePointer);
            moveLastCardFromBlackJackPlayerToStack(stackPointer, blackJackDealerPointer);
        }
    }
}

// A recursive function that builds up a pobability tree showing probabilities of outcomes

void calculatePlayerHitScores(DeckStack *stackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability probabilityTree[5][22], int currentLayer) {

    int currentBestPlayerScore = getPlayersBestScore(blackJackPlayerPointer);
    if (currentBestPlayerScore > 21) {
        currentBestPlayerScore = 22;
    }

    probabilityTree[currentLayer][currentBestPlayerScore].numberOfWaysToAchieveScore++;
    //calculateChanceOfWin(stackPointer, blackJackPlayerPointer, blackJackDealerPointer, probabilityTree[currentBestPlayerScore]);


    if (currentBestPlayerScore <= 21 && currentLayer <= 1) {
        for (int i = stackPointer->cardsLeft - 1; i >= 0 ; i--) {
            moveCardFromStackToBlackJackPlayer(stackPointer, i, blackJackPlayerPointer);
            calculatePlayerHitScores(stackPointer, blackJackPlayerPointer, blackJackDealerPointer, probabilityTree, currentLayer + 1);
            moveLastCardFromBlackJackPlayerToStack(stackPointer, blackJackPlayerPointer);
        }
    }
}

void calculateProbabilities(DeckStack *stackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer) {

    // An array of the amount of ways each best score can be achieved, 0 = score of 2, 1 = score of 3 ... 19 = score of 21, 20 = bust.
    /*
    int playerChances[21] = {0};

    for (int i = 0; i < stackPointer->cardsLeft; i++) {
        int score = getPlayersBestScore(blackJackPlayerPointer);
        Card card = stackPointer->cardsInStack[i];

        score += getCardValue(card);

        if (card.cardID == ACE && score < 12) {
            score += 10;
        }

        if (score > 21) {
            score = 22;
        }

        playerChances[score - 2] = playerChances[score - 2] + 1;
    }

    printf("\n \n \n");
    for (int i = 0; i < 21; i++) {
        if (playerChances[i] != 0) {
            if (i == 20) {
                printf("The chance you hit and go bust is %i/%i \n", playerChances[i],
                       stackPointer->cardsLeft);
            }  else {
                printf("The chance you hit and have a best score of %i is %i/%i \n", i + 2, playerChances[i],
                       stackPointer->cardsLeft);
            }
        }
    }
    printf("\n \n \n");
     */

    int differentScores = 23;
    int layers = 3;
    Probability probabilityTree[layers][differentScores];

    for (int layer = 0; layer < layers; layer++) {
        for (int i = 0; i < differentScores; i++) {
            probabilityTree[layer][i].numberOfWaysToAchieveScore = 0;
            probabilityTree[layer][i].numberOfWaysWithScoreToWin = 0;
            probabilityTree[layer][i].numberOfWaysWithScoreToDraw = 0;
            probabilityTree[layer][i].numberOfWaysWithScoreToLoose = 0;
        }
    }

    calculatePlayerHitScores(stackPointer, blackJackPlayerPointer, blackJackDealerPointer, probabilityTree, 0);

    printProbabilities(probabilityTree);
}