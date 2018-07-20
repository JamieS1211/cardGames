//
// Created by Jamie on 28/12/2017.
//

int layersToCalculate = 2;
int possibleScores = 23;

#include <stdio.h>
#include <stdlib.h>
#include "../blackJackAPI/blackJack.h"
#include "../../cardAPI/simpleStack.h"
#include "../blackJackAPI/blackJackPlayer.h"
#include "../../cardAPI/player.h"

void printProbabilities(Probability **treePointer) {

    float cumulativeWin[layersToCalculate];
    float cumulativeDraw[layersToCalculate];
    float cumulativeLose[layersToCalculate];

    for (int layer = 0; layer < layersToCalculate; layer++) {
        int totalWays = 0;

        cumulativeWin[layer] = 0;
        cumulativeDraw[layer] = 0;
        cumulativeLose[layer] = 0;

        for (int score = 0; score < possibleScores; score++) {
            totalWays += treePointer[layer][score].waysToAchieveScore;
        }


        printf("\nLayer: %i \n", layer);

        printf("\t\t\t\t Chance");
        printf("\t\t\t Win");
        printf("\t\t\t Draw");
        printf("\t\t\t Lose \n");

        for (int score = 0; score < possibleScores; score++) {

            if (treePointer[layer][score].waysToAchieveScore > 0) {
                if (score <= 21) {
                    printf("Score: %i", score);
                } else {
                    printf("Bust:   ");
                }

                int totalWaysForDealerPlay = 0;

                totalWaysForDealerPlay += treePointer[layer][score].waysWithScoreToWin
                                          + treePointer[layer][score].waysWithScoreToDraw
                                          + treePointer[layer][score].waysWithScoreToLoose;

                float percentOfGettingScore = ((float) treePointer[layer][score].waysToAchieveScore / totalWays) * 100;
                float percentOfWin =
                        ((float) treePointer[layer][score].waysWithScoreToWin / totalWaysForDealerPlay) * 100;
                float percentOfDraw =
                        ((float) treePointer[layer][score].waysWithScoreToDraw / totalWaysForDealerPlay) * 100;
                float percentOfLose =
                        ((float) treePointer[layer][score].waysWithScoreToLoose / totalWaysForDealerPlay) * 100;

                printf("\t\t %f%%", percentOfGettingScore);
                printf("\t\t %f%%", percentOfWin);
                printf("\t\t %f%%", percentOfDraw);
                printf("\t\t %f%% \n", percentOfLose);
                
                cumulativeWin[layer] += percentOfGettingScore * percentOfWin;
                cumulativeDraw[layer] += percentOfGettingScore * percentOfDraw;
                cumulativeLose[layer] += percentOfGettingScore * percentOfLose;
            }
        }

        cumulativeWin[layer] /= 100;
        cumulativeDraw[layer] /= 100;
        cumulativeLose[layer] /= 100;

        printf("\nCumulative probability:\t\t\t %f%%\t\t %f%%\t\t %f%% \n", cumulativeWin[layer], cumulativeDraw[layer], cumulativeLose[layer]);
    }

    float lowestLose = 100;
    int bestChance = 0;
    //TODO when is the probability improvement worth the risk of going bust from hitting?
    for (int layer = 0; layer < layersToCalculate; layer++) {
        if (cumulativeLose[layer] < lowestLose) {
            lowestLose = cumulativeLose[layer];
            bestChance = layer;
        }
    }

    printf("\n\n\nTo minimise your chance of losing you should hit %i times \n\n", bestChance);
}

// A function that takes a player and dealer state and updates a probability tree with chance player wins / losses / draws with dealer provided player stands at this point

void calculateChanceOfWin(SimpleStack *simpleStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability **treePointer, int currentLayer, int weight, int currentBestPlayerScore) {

    updatePlayersScore(blackJackDealerPointer);
    int currentBestDealerScore = blackJackDealerPointer->score;
    if (currentBestDealerScore > 21) {
        currentBestDealerScore = 22;
    }


    if (doesPlayerHaveBlackJack(blackJackPlayerPointer) && doesPlayerHaveBlackJack(blackJackDealerPointer)) {
        // Both have black jack
        treePointer[currentLayer][currentBestPlayerScore].waysWithScoreToDraw += weight;
    } else if (doesPlayerHaveBlackJack(blackJackDealerPointer)) {
        // Dealer has black jack
        treePointer[currentLayer][currentBestPlayerScore].waysWithScoreToLoose += weight;
    } else if (doesPlayerHaveBlackJack(blackJackPlayerPointer)) {
        // Player has black jack
        treePointer [currentLayer][currentBestPlayerScore].waysWithScoreToWin += weight;
    } else if (currentBestPlayerScore > 21) {
        // Player gone bust
        treePointer [currentLayer][currentBestPlayerScore].waysWithScoreToLoose += weight;
    } else if (currentBestDealerScore > 21) {
        // Dealer gone bust
        treePointer[currentLayer][currentBestPlayerScore].waysWithScoreToWin += weight;
    } else if (currentBestDealerScore == currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and dealer has same score
        treePointer[currentLayer][currentBestPlayerScore].waysWithScoreToDraw += weight;
    } else if (currentBestDealerScore > currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and player has better score
        treePointer[currentLayer][currentBestPlayerScore].waysWithScoreToLoose += weight;
    } else if (currentBestDealerScore < currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and player has better score
        treePointer[currentLayer][currentBestPlayerScore].waysWithScoreToWin += weight;
    } else {
        // Dealer will hit again and should re run this code giving them every possible card left in deck stack to deal.
        for (int cardID = 1; cardID <= NUMBER_OF_CARDS ; cardID++) {
            if (simpleStackPointer->cardsCountsInStack[cardID] > 0) {
                weight *= simpleStackPointer->cardsCountsInStack[cardID];

                moveCardFromSimpleStackToBlackJackPlayer(simpleStackPointer, cardID, blackJackDealerPointer);
                updatePlayersScore(blackJackDealerPointer);

                calculateChanceOfWin(simpleStackPointer, blackJackPlayerPointer, blackJackDealerPointer,
                                         treePointer, currentLayer, weight, currentBestPlayerScore);

                moveLastCardFromBlackJackPlayerToSimpleStack(simpleStackPointer, blackJackDealerPointer);

                weight /= simpleStackPointer->cardsCountsInStack[cardID];
            }
        }
    }
}

// A recursive function that builds up a pobability tree showing probabilities of outcomes

void calculatePlayerHitScores(SimpleStack *simpleStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability **treePointer, int currentLayer, int weight, int totalLayers) {
    int currentBestPlayerScore = blackJackPlayerPointer->score;
    int nextLayer = currentLayer + 1;

    if (currentBestPlayerScore > 21) {
        currentBestPlayerScore = 22;
    } else if (currentBestPlayerScore <= 21 && nextLayer < totalLayers) {
        for (int cardID = 1; cardID <= NUMBER_OF_CARDS ; cardID++) {
            if (simpleStackPointer->cardsCountsInStack[cardID] > 0) {
                weight *= simpleStackPointer->cardsCountsInStack[cardID];

                moveCardFromSimpleStackToBlackJackPlayer(simpleStackPointer, cardID, blackJackPlayerPointer);
                updatePlayersScore(blackJackPlayerPointer);

                calculatePlayerHitScores(simpleStackPointer, blackJackPlayerPointer, blackJackDealerPointer,
                                         treePointer, nextLayer, weight, totalLayers);

                moveLastCardFromBlackJackPlayerToSimpleStack(simpleStackPointer, blackJackPlayerPointer);

                weight /= simpleStackPointer->cardsCountsInStack[cardID];
            }
        }
    }

    calculateChanceOfWin(simpleStackPointer, blackJackPlayerPointer, blackJackDealerPointer, treePointer, currentLayer, weight, currentBestPlayerScore);
    treePointer[currentLayer][currentBestPlayerScore].waysToAchieveScore += weight;
}

/**
 * A function that print the probability tree of the state of deck, player and dealer
 * @param deckStackPointer
 * @param blackJackPlayerPointer
 * @param blackJackDealerPointer
 */
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

    Probability **tree = NULL;

    tree = malloc(layersToCalculate * possibleScores * sizeof(Probability));

    for (int layer = 0; layer < layersToCalculate; layer++) {
        tree[layer] = malloc(possibleScores * sizeof(Probability));
    }


    for (int layer = 0; layer < layersToCalculate; layer++) {
        for (int score = 0; score < possibleScores; score++) {
            tree[layer][score].waysToAchieveScore = 0;
            tree[layer][score].waysWithScoreToWin = 0;
            tree[layer][score].waysWithScoreToDraw = 0;
            tree[layer][score].waysWithScoreToLoose = 0;
        }
    }

    calculatePlayerHitScores(&simpleStack, blackJackPlayerPointer, blackJackDealerPointer, tree, 0, 1, layersToCalculate);
    updatePlayersScore(blackJackPlayerPointer);
    updatePlayersScore(blackJackDealerPointer);

    printProbabilities(tree);
    for (int layer = 0; layer < layersToCalculate; layer++) {
        free(tree[layer]);
    }
    free(tree);
}

/**
 * A function that returns 1 if should stand and 0 if should hit
 * @param simpleStackPointer
 * @param blackJackPlayerPointer
 * @param blackJackDealerPointer
 */
int standSimpleStack(SimpleStack *simpleStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer) {
    int localLayersToCalculate = 2; //TODO this value is amount of iterations deep that is relevent for calculations. Higher = better but longer


    // Simplify all 10 score cards into one slot
    for (int i = JACK; i <= KING; i++) {
        while (simpleStackPointer->cardsCountsInStack[i] > 0) {
            simpleStackPointer->cardsCountsInStack[10]++;
            simpleStackPointer->cardsCountsInStack[i]--;
        }
    }

    Probability **tree = NULL;

    tree = malloc(localLayersToCalculate * possibleScores * sizeof(Probability));

    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        tree[layer] = malloc(possibleScores * sizeof(Probability));
    }


    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        for (int score = 0; score < possibleScores; score++) {
            tree[layer][score].waysToAchieveScore = 0;
            tree[layer][score].waysWithScoreToWin = 0;
            tree[layer][score].waysWithScoreToDraw = 0;
            tree[layer][score].waysWithScoreToLoose = 0;
        }
    }

    calculatePlayerHitScores(simpleStackPointer, blackJackPlayerPointer, blackJackDealerPointer, tree, 0, 1, localLayersToCalculate);
    updatePlayersScore(blackJackPlayerPointer);
    updatePlayersScore(blackJackDealerPointer);


    float cumulativeWin[localLayersToCalculate];
    float cumulativeDraw[localLayersToCalculate];
    float cumulativeLose[localLayersToCalculate];

    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        int totalWays = 0;

        cumulativeWin[layer] = 0;
        cumulativeDraw[layer] = 0;
        cumulativeLose[layer] = 0;

        for (int score = 0; score < possibleScores; score++) {
            totalWays += tree[layer][score].waysToAchieveScore;
        }

        for (int score = 0; score < possibleScores; score++) {

            if (tree[layer][score].waysToAchieveScore > 0) {

                int totalWaysForDealerPlay = 0;

                totalWaysForDealerPlay += tree[layer][score].waysWithScoreToWin
                                          + tree[layer][score].waysWithScoreToDraw
                                          + tree[layer][score].waysWithScoreToLoose;

                float percentOfGettingScore = ((float) tree[layer][score].waysToAchieveScore / totalWays) * 100;
                float percentOfWin =
                        ((float) tree[layer][score].waysWithScoreToWin / totalWaysForDealerPlay) * 100;
                float percentOfDraw =
                        ((float) tree[layer][score].waysWithScoreToDraw / totalWaysForDealerPlay) * 100;
                float percentOfLose =
                        ((float) tree[layer][score].waysWithScoreToLoose / totalWaysForDealerPlay) * 100;

                cumulativeWin[layer] += percentOfGettingScore * percentOfWin;
                cumulativeDraw[layer] += percentOfGettingScore * percentOfDraw;
                cumulativeLose[layer] += percentOfGettingScore * percentOfLose;
            }
        }

        cumulativeWin[layer] /= 100;
        cumulativeDraw[layer] /= 100;
        cumulativeLose[layer] /= 100;
    }

    float lowestLose = 100;
    int bestChance = 0;
    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        if (cumulativeLose[layer] < lowestLose) {
            lowestLose = cumulativeLose[layer];
            bestChance = layer;
        }
    }

    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        free(tree[layer]);
    }
    free(tree);

    return bestChance == 0;
}

/**
 * A function that returns 1 if should stand and 0 if should hit
 * @param deckStackPointer
 * @param blackJackPlayerPointer
 * @param blackJackDealerPointer
 */
int stand(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer) {

    SimpleStack simpleStack;
    initialiseSimpleStackFromDeckStack(&simpleStack, deckStackPointer);

    return standSimpleStack(&simpleStack, blackJackPlayerPointer, blackJackDealerPointer);
}

float getExpectedValueOfNextHand(DeckStack *deckStackPointer) {
    //TODO accurately find this value
    float runningCount = 0;

    for (int i = 0; i < deckStackPointer->cardsLeft; i++) {
        switch (deckStackPointer->cardsInStack[i].cardID) {
            case KING:
            case QUEEN:
            case JACK:
            case TEN:
            case ACE:
                runningCount++;
                break;
            case TWO:
            case THREE:
            case FOUR:
            case FIVE:
            case SIX:
                runningCount--;
                break;
        }
    }

    float decksLeft = (float) deckStackPointer->cardsLeft / 52;
    float trueCount = runningCount / decksLeft;

    return (trueCount - 1) / 2;
}

float getRealExpectedValueOfNextHand(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer,
                                     BlackJackPlayer *blackJackDealerPointer) {

    SimpleStack simpleStack;
    initialiseSimpleStackFromDeckStack(&simpleStack, deckStackPointer);

    // Simplify all 10 score cards into one slot
    for (int i = JACK; i <= KING; i++) {
        while (simpleStack.cardsCountsInStack[i] > 0) {
            simpleStack.cardsCountsInStack[10]++;
            simpleStack.cardsCountsInStack[i]--;
        }
    }

    float totalWin = 0;
    float totalDraw = 0;
    float totalLose = 0;

    int weight = 1;


    // For every card remaining deal to user
    // Then follow computer directions to hit or stand using first 2 cards.
    // When computer sa

    Card dynamicCard;
    dynamicCard.cardSuit = 0;

    for (int i = 0; i < 10; i++) {
        // Deal 1st card to player
        if (simpleStack.cardsCountsInStack[i] > 0) {
            weight *= simpleStack.cardsCountsInStack[i];
            simpleStack.cardsCountsInStack[i]--;
            simpleStack.cardsLeft--;

            dynamicCard.cardID = i;
            addCardToPlayer(&blackJackPlayerPointer->player, dynamicCard);
            updatePlayersScore(blackJackPlayerPointer);

            for (int j = 0; j < 10; j++) {
                // Deal 2nd card to player
                if (simpleStack.cardsCountsInStack[j] > 0) {
                    weight *= simpleStack.cardsCountsInStack[j];
                    simpleStack.cardsCountsInStack[j]--;
                    simpleStack.cardsLeft--;

                    dynamicCard.cardID = j;
                    addCardToPlayer(&blackJackPlayerPointer->player, dynamicCard);
                    updatePlayersScore(blackJackPlayerPointer);

                    for (int k = 0; k < 10; k++) {
                        // Deal 3rd card to dealer
                        if (simpleStack.cardsCountsInStack[k] > 0) {
                            weight *= simpleStack.cardsCountsInStack[k];
                            simpleStack.cardsCountsInStack[k]--;
                            simpleStack.cardsLeft--;

                            dynamicCard.cardID = k;
                            addCardToPlayer(&blackJackDealerPointer->player, dynamicCard);
                            updatePlayersScore(blackJackDealerPointer);

                            // Dealt first 3 cards


                            //TODO Check if hit or stand, when stand work out probability of win lose and draw


                            // Un-deal cards

                            removeCardFromBlackJackPlayersHand(blackJackDealerPointer, blackJackDealerPointer->player.cardsInHand - 1, 1);

                            simpleStack.cardsCountsInStack[k]++;
                            weight /= simpleStack.cardsCountsInStack[k];
                            simpleStack.cardsLeft++;
                        }
                    }

                    removeCardFromBlackJackPlayersHand(blackJackPlayerPointer, blackJackPlayerPointer->player.cardsInHand - 1, 1);

                    simpleStack.cardsCountsInStack[j]++;
                    weight /= simpleStack.cardsCountsInStack[j];
                    simpleStack.cardsLeft++;
                }
            }

            removeCardFromBlackJackPlayersHand(blackJackPlayerPointer, blackJackPlayerPointer->player.cardsInHand - 1, 1);

            simpleStack.cardsCountsInStack[i]++;
            weight /= simpleStack.cardsCountsInStack[i];
            simpleStack.cardsLeft++;
        }
    }

    int totalHands =
            deckStackPointer->cardsLeft * (deckStackPointer->cardsLeft - 1) * (deckStackPointer->cardsLeft - 2);

    return (totalWin - totalLose) / totalHands;
}
