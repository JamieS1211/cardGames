//
// Created by Jamie on 28/12/2017.
//

int layersDeep = 2;

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../blackJack.h"
#include "../blackJackCard.h"
#include "../../cardAPI/deckStack.h"
#include "../../cardAPI/simpleStack.h"
#include "../blackJackPlayer.h"

void printProbabilities(Probability probabilityTree[3][23]) {
    for (int layer = 0; layer <= layersDeep; layer++) {
        int totalWays = 0;
        int totalWaysForDealerPlay = 0;

        for (int i = 0; i < 23; i++) {
            totalWays += probabilityTree[layer][i].waysToAchieveScore;
            totalWaysForDealerPlay += probabilityTree[layer][i].waysWithScoreToWin;
            totalWaysForDealerPlay += probabilityTree[layer][i].waysWithScoreToDraw;
            totalWaysForDealerPlay += probabilityTree[layer][i].waysWithScoreToLoose;
        }


        printf("\nLayer: %i \n", layer);

        printf("\t\t\t\t Chance");
        printf("\t\t\t Win");
        printf("\t\t\t Draw");
        printf("\t\t\t Lose \n");

        for (int i = 0; i < 23; i++) {
            if (i <= 21) {
                printf("Score: %i", i);
            } else {
                printf("Bust:   ");
            }


            float percentOfGettingScore = ((float)probabilityTree[layer][i].waysToAchieveScore / totalWays) * 100;
            float percentOfWin = ((float)probabilityTree[layer][i].waysWithScoreToWin / totalWaysForDealerPlay) * 100;
            float percentOfDraw = ((float)probabilityTree[layer][i].waysWithScoreToDraw / totalWaysForDealerPlay) * 100;
            float percentOfLose = ((float)probabilityTree[layer][i].waysWithScoreToLoose / totalWaysForDealerPlay) * 100;

            printf("\t\t %f%%", percentOfGettingScore);
            printf("\t\t %f%%", percentOfWin);
            printf("\t\t %f%%", percentOfDraw);
            printf("\t\t %f%% \n", percentOfLose);
        }
    }
}

// A function that takes a player and dealer state and updates a probability tree with chance player wins / losses / draws with dealer provided player stands at this point

void calculateChanceOfWin(SimpleStack *simpleStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability probabilityTree[3][23], int currentLayer, int weight, int currentBestPlayerScore) {

    updatePlayersScore(blackJackDealerPointer);
    int currentBestDealerScore = blackJackDealerPointer->score;
    if (currentBestDealerScore > 21) {
        currentBestDealerScore = 22;
    }


    if (doesPlayerHaveBlackJack(blackJackPlayerPointer) && doesPlayerHaveBlackJack(blackJackDealerPointer)) {
        // Both have black jack
        probabilityTree[currentLayer][currentBestPlayerScore].waysWithScoreToDraw += weight;
    } else if (doesPlayerHaveBlackJack(blackJackDealerPointer)) {
        // Dealer has black jack
        probabilityTree[currentLayer][currentBestPlayerScore].waysWithScoreToLoose += weight;
    } else if (doesPlayerHaveBlackJack(blackJackPlayerPointer)) {
        // Player has black jack
        probabilityTree[currentLayer][currentBestPlayerScore].waysWithScoreToWin += weight;
    } else if (currentBestPlayerScore > 21) {
        // Player gone bust
        probabilityTree[currentLayer][currentBestPlayerScore].waysWithScoreToLoose += weight;
    } else if (currentBestDealerScore > 21) {
        // Dealer gone bust
        probabilityTree[currentLayer][currentBestPlayerScore].waysWithScoreToWin += weight;
    } else if (currentBestDealerScore == currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and dealer has same score
        probabilityTree[currentLayer][currentBestPlayerScore].waysWithScoreToDraw += weight;
    } else if (currentBestDealerScore > currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and player has better score
        probabilityTree[currentLayer][currentBestPlayerScore].waysWithScoreToLoose += weight;
    } else if (currentBestDealerScore < currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and player has better score
        probabilityTree[currentLayer][currentBestPlayerScore].waysWithScoreToWin += weight;
    } else {
        // Dealer will hit again and should re run this code giving them every possible card left in deck stack to deal.
        for (int cardID = 1; cardID <= NUMBER_OF_CARDS ; cardID++) {
            if (simpleStackPointer->cardsCountsInStack[cardID] > 0) {
                weight *= simpleStackPointer->cardsCountsInStack[cardID];

                moveCardFromSimpleStackToBlackJackPlayer(simpleStackPointer, cardID, blackJackDealerPointer);
                updatePlayersScore(blackJackDealerPointer);

                calculateChanceOfWin(simpleStackPointer, blackJackPlayerPointer, blackJackDealerPointer,
                                         probabilityTree, currentLayer, weight, currentBestPlayerScore);

                moveLastCardFromBlackJackPlayerToSimpleStack(simpleStackPointer, blackJackDealerPointer);

                weight /= simpleStackPointer->cardsCountsInStack[cardID];
            }
        }
    }
}

// A recursive function that builds up a pobability tree showing probabilities of outcomes

void calculatePlayerHitScores(SimpleStack *simpleStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability probabilityTree[3][23], int currentLayer, int weight) {
    int currentBestPlayerScore = blackJackPlayerPointer->score;
    int nextLayer = currentLayer + 1;

    if (currentBestPlayerScore > 21) {
        currentBestPlayerScore = 22;
    } else if (currentBestPlayerScore <= 21 && nextLayer <= layersDeep) {
        for (int cardID = 1; cardID <= NUMBER_OF_CARDS ; cardID++) {
            if (simpleStackPointer->cardsCountsInStack[cardID] > 0) {
                weight *= simpleStackPointer->cardsCountsInStack[cardID];

                moveCardFromSimpleStackToBlackJackPlayer(simpleStackPointer, cardID, blackJackPlayerPointer);
                updatePlayersScore(blackJackPlayerPointer);

                calculatePlayerHitScores(simpleStackPointer, blackJackPlayerPointer, blackJackDealerPointer,
                                         probabilityTree, nextLayer, weight);

                moveLastCardFromBlackJackPlayerToSimpleStack(simpleStackPointer, blackJackPlayerPointer);

                weight /= simpleStackPointer->cardsCountsInStack[cardID];
            }
        }
    }

    calculateChanceOfWin(simpleStackPointer, blackJackPlayerPointer, blackJackDealerPointer, probabilityTree, currentLayer, weight, currentBestPlayerScore);
    probabilityTree[currentLayer][currentBestPlayerScore].waysToAchieveScore += weight;
}

void calculateProbabilities(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer) {
    SimpleStack simpleStack;
    initialiseSimpleStackFromDeckStack(&simpleStack, deckStackPointer);

    // Simplify all 10 score cards into one slot
    for (int i = JACK; i <= KING; i++) {
        while (simpleStack.cardsCountsInStack[i] > 0) {
            simpleStack.cardsCountsInStack[10]++;
            simpleStack.cardsCountsInStack[i]--;
        }
    }

    Probability probabilityTree[3][23];
    for (int layer = 0; layer <= layersDeep; layer++) {
        for (int score = 0; score < 23; score++) {
            probabilityTree[layer][score].waysToAchieveScore = 0;
            probabilityTree[layer][score].waysWithScoreToWin = 0;
            probabilityTree[layer][score].waysWithScoreToDraw = 0;
            probabilityTree[layer][score].waysWithScoreToLoose = 0;
        }
    }

    calculatePlayerHitScores(&simpleStack, blackJackPlayerPointer, blackJackDealerPointer, probabilityTree, 0, 1);

    printProbabilities(probabilityTree);
}