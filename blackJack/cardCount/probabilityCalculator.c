//
// Created by Jamie on 28/12/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../blackJackAPI/blackJack.h"
#include "../../cardAPI/simpleStack.h"
#include "../blackJackAPI/blackJackPlayer.h"
#include "../../cardAPI/player.h"

void printProbabilities(Probability **treePointer, int printOption) {
    /*
     * Print options
     * 0 - No output
     * 1 - Only hit or Stand advice
     * 2 - Hit and Stand advice and cumulative probabilities per layer
     * 3 - All text
     */

    int localLayersToCalculate = maxLayersDeepForScore(21);

    float cumulativeWin[localLayersToCalculate];
    float cumulativeDraw[localLayersToCalculate];
    float cumulativeLose[localLayersToCalculate];
    float lowestLose = 100;
    int bestChance = 0;

    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        int totalWays = 0;

        cumulativeWin[layer] = 0;
        cumulativeDraw[layer] = 0;
        cumulativeLose[layer] = 0;

        for (int score = 0; score < POSSIBLESCORES; score++) {
            totalWays += treePointer[layer][score].waysToAchieveScore;
        }


        if (printOption >= 2) {
            printf("\nLayer: %i \n", layer);

            printf("\t\t");
            if (printOption >= 3) {
                printf(" Chance");
            }

            printf("\t\t Win");
            printf("\t\t Draw");
            printf("\t\t Lose");

            if (printOption >= 3) {
                printf("\t\t Ways to get score \n");
            }

            printf("\n");
        }

        for (int score = 0; score < POSSIBLESCORES; score++) {

            if (treePointer[layer][score].waysToAchieveScore > 0) {
                if (printOption >= 3) {
                    if (score <= 21) {
                        printf("Score: %i", score);
                    } else {
                        printf("Bust:   ");
                    }
                }

                float percentOfGettingScore = ((float) treePointer[layer][score].waysToAchieveScore / totalWays) * 100;
                int waysOfGettingHere = treePointer[layer][score].waysToGetHere;
                float percentOfWin = (treePointer[layer][score].unscaledProbabilityWithScoreToWin / waysOfGettingHere) * 100;
                float percentOfDraw = (treePointer[layer][score].unscaledProbabilityWithScoreToDraw / waysOfGettingHere) * 100;
                float percentOfLose = (treePointer[layer][score].unscaledProbabilityWithScoreToLoose / waysOfGettingHere) * 100;

                if (printOption >= 3) {
                    printf("\t %f%%", percentOfGettingScore);
                    printf("\t %f%%", percentOfWin);
                    printf("\t %f%%", percentOfDraw);
                    printf("\t %f%% ", percentOfLose);
                    printf("\t %i\n", waysOfGettingHere);
                }
                
                cumulativeWin[layer] += percentOfGettingScore * percentOfWin;
                cumulativeDraw[layer] += percentOfGettingScore * percentOfDraw;
                cumulativeLose[layer] += percentOfGettingScore * percentOfLose;
            }
        }

        cumulativeWin[layer] /= 100;
        cumulativeDraw[layer] /= 100;
        cumulativeLose[layer] /= 100;

        if (printOption >= 2) {
            printf("\nCumulative probability:\t\t %f%%\t %f%%\t %f%% \n", cumulativeWin[layer], cumulativeDraw[layer],
                   cumulativeLose[layer]);
        }

        if (cumulativeLose[layer] < lowestLose) {
            lowestLose = cumulativeLose[layer];
            bestChance = layer;
        }

        if (cumulativeLose[layer] >= 99.9) { //100 but inclusive of floating point errors
            break;
        }
    }

    if (printOption >= 1) {
        if (bestChance == 0) {
            printf("\nYou should stand \n\n");
        } else {
            printf("\nYou should hit \n\n");
        }
    }
}

// A function that takes a player and dealer state and updates a probability tree with chance player wins / losses / draws with dealer provided player stands at this point

void calculateChanceOfWin(SimpleStack *simpleStackPointer, int *extraDealerCardsPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability **treePointer, int currentPlayerLayer, int currentDealerLayer, int numerator, int denominator, int currentBestPlayerScore) {
    updatePlayersScore(blackJackDealerPointer);
    int currentBestDealerScore = blackJackDealerPointer->score;
    if (currentBestDealerScore > 21) {
        currentBestDealerScore = 22;
    }

    float chance = (float) numerator / denominator;

    if (doesPlayerHaveBlackJack(blackJackPlayerPointer) && doesPlayerHaveBlackJack(blackJackDealerPointer)) {
        // Both have black jack
        treePointer[currentPlayerLayer][currentBestPlayerScore].unscaledProbabilityWithScoreToDraw += chance;
    } else if (doesPlayerHaveBlackJack(blackJackDealerPointer)) {
        // Dealer has black jack
        treePointer[currentPlayerLayer][currentBestPlayerScore].unscaledProbabilityWithScoreToLoose += chance;
    } else if (doesPlayerHaveBlackJack(blackJackPlayerPointer)) {
        // Player has black jack
        treePointer[currentPlayerLayer][currentBestPlayerScore].unscaledProbabilityWithScoreToWin += chance;
    } else if (currentBestPlayerScore > 21) {
        // Player gone bust
        treePointer[currentPlayerLayer][currentBestPlayerScore].unscaledProbabilityWithScoreToLoose += chance;
    } else if (currentBestDealerScore > 21) {
        // Dealer gone bust
        treePointer[currentPlayerLayer][currentBestPlayerScore].unscaledProbabilityWithScoreToWin += chance;
    } else if (currentBestDealerScore == currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and dealer has same score
        treePointer[currentPlayerLayer][currentBestPlayerScore].unscaledProbabilityWithScoreToDraw += chance;
    } else if (currentBestDealerScore > currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and player has better score
        treePointer[currentPlayerLayer][currentBestPlayerScore].unscaledProbabilityWithScoreToLoose += chance;
    } else if (currentBestDealerScore < currentBestPlayerScore && currentBestDealerScore >= 17) {
        // Dealer won't hit again and player has better score
        treePointer[currentPlayerLayer][currentBestPlayerScore].unscaledProbabilityWithScoreToWin += chance;
    } else {
        // Dealer will hit again and should re run this code giving them every possible card left in deck stack to deal.
        for (int cardID = ACE; cardID <= KING; cardID++) {
            if (simpleStackPointer->cardsCountsInStack[cardID] > 0) {
                //Order matters (because Ace can prevent further hitting if taken as 11) so can't force order
                numerator *= simpleStackPointer->cardsCountsInStack[cardID];
                denominator *= simpleStackPointer->cardsLeft;

                moveCardFromSimpleStackToBlackJackPlayer(simpleStackPointer, cardID, blackJackDealerPointer);
                updatePlayersScore(blackJackDealerPointer);

                calculateChanceOfWin(simpleStackPointer, extraDealerCardsPointer, blackJackPlayerPointer,
                                     blackJackDealerPointer,
                                     treePointer, currentPlayerLayer, currentDealerLayer + 1, numerator, denominator,
                                     currentBestPlayerScore);

                moveLastCardFromBlackJackPlayerToSimpleStack(simpleStackPointer, blackJackDealerPointer);

                numerator /= simpleStackPointer->cardsCountsInStack[cardID];
                denominator /= simpleStackPointer->cardsLeft;
            }
        }
    }
}

// A recursive function that builds up a pobability tree showing probabilities of outcomes

void calculatePlayerHitScores(SimpleStack *simpleStackPointer, int *extraCardsPointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer, Probability **treePointer, int currentLayer, int weight, int totalLayers) {
    //Current layer starts at 0 when called from other function

    int currentBestPlayerScore = blackJackPlayerPointer->score;
    int nextLayer = currentLayer + 1;

    if (currentBestPlayerScore > 21) {
        currentBestPlayerScore = 22;
    } else if (currentBestPlayerScore <= 21 && nextLayer < totalLayers) {
        for (int cardID = ACE; cardID <= TEN ; cardID++) {
            if (simpleStackPointer->cardsCountsInStack[cardID] > 0) {
                extraCardsPointer[currentLayer] = cardID;

                int validOrder = 1;

                for (int layer = 0; layer <= currentLayer - 1; layer++) { //should only run if 2 or more cards have been delt
                    if (extraCardsPointer[layer] > extraCardsPointer[layer + 1]) { // layer 0 must be smaller or equal to layer 1 card
                        validOrder = 0;
                        break;
                    }
                }

                if (validOrder) {
                    int waysToGetThisSetOfCards = 1;

                    weight *= (simpleStackPointer->cardsCountsInStack[cardID] * waysToGetThisSetOfCards);

                    moveCardFromSimpleStackToBlackJackPlayer(simpleStackPointer, cardID, blackJackPlayerPointer);
                    updatePlayersScore(blackJackPlayerPointer);

                    calculatePlayerHitScores(simpleStackPointer, extraCardsPointer, blackJackPlayerPointer,
                                             blackJackDealerPointer,
                                             treePointer, nextLayer, weight, totalLayers);

                    moveLastCardFromBlackJackPlayerToSimpleStack(simpleStackPointer, blackJackPlayerPointer);

                    weight /= (simpleStackPointer->cardsCountsInStack[cardID] * waysToGetThisSetOfCards);
                }
            }
        }
    }

    int *extraDealerCards = malloc(maxLayersDeepForScore(17) * sizeof(int));
    treePointer[currentLayer][currentBestPlayerScore].waysToGetHere++;
    calculateChanceOfWin(simpleStackPointer, extraDealerCards, blackJackPlayerPointer, blackJackDealerPointer,
                         treePointer, currentLayer, 0, 1, 1, currentBestPlayerScore);

    if (currentBestPlayerScore <= 21) {
        treePointer[currentLayer][currentBestPlayerScore].waysToAchieveScore += weight;

        if (currentLayer > 0) {
            treePointer[currentLayer][22].waysToAchieveScore -= weight;
        }
    }
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

    int localLayersToCalculate = maxLayersDeepForScore(21);

    // Simplify all 10 score cards into one slot
    for (int i = JACK; i <= KING; i++) {
        while (simpleStack.cardsCountsInStack[i] > 0) {
            simpleStack.cardsCountsInStack[10]++;
            simpleStack.cardsCountsInStack[i]--;
        }
    }

    Probability **tree = NULL;

    tree = malloc(localLayersToCalculate * POSSIBLESCORES * sizeof(Probability));

    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        tree[layer] = malloc(POSSIBLESCORES * sizeof(Probability));
    }


    int totalChancesInLayer = 1;
    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        for (int score = 0; score < POSSIBLESCORES; score++) {
            tree[layer][score].waysToAchieveScore = 0;
            tree[layer][score].unscaledProbabilityWithScoreToWin = 0;
            tree[layer][score].unscaledProbabilityWithScoreToDraw = 0;
            tree[layer][score].unscaledProbabilityWithScoreToLoose = 0;
            tree[layer][score].waysToGetHere = 0;
        }

        if (layer > 0) {
            totalChancesInLayer *= (simpleStack.cardsLeft + 1 - layer);
            tree[layer][22].waysToAchieveScore = totalChancesInLayer;
        }
    }

    int *extraCards = malloc(localLayersToCalculate * sizeof(int));
    calculatePlayerHitScores(&simpleStack, extraCards, blackJackPlayerPointer, blackJackDealerPointer, tree, 0, 1, localLayersToCalculate);
    free(extraCards);

    updatePlayersScore(blackJackPlayerPointer);
    updatePlayersScore(blackJackDealerPointer);

    printProbabilities(tree, PRINTOPTION);
    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        free(tree[layer]);
    }
    free(tree);
}

/**
 * A function that returns 1 if should stand and 0 if should hit
 * @param deckStackPointer
 * @param blackJackPlayerPointer
 * @param blackJackDealerPointer
 */
int shouldStand(DeckStack *deckStackPointer, SimpleStack *simpleStackPointer, ProbabilityTree *probabilityTreePointer,
                BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer) {
    /*
     * This value is amount of iterations deep that is relevant for calculations. Higher = better but longer
     * Value of 2 assesses current layer (standing) against next layer (hitting)
     * As cumulative odds of losing decrease to a point and then increase (AKA have one minimum) only 2 values are required
     * If next layer has higher cumulative chance of losing then we should stand
    */

    int localLayersToCalculate = 2; //This value is amount of iterations deep that is relevent for calculations. SHOULD ALWAYS BE 2 read above

    SimpleStack simpleStack;
    initialiseSimpleStackFromDeckStack(&simpleStack, deckStackPointer);

    // Simplify all 10 score cards into one slot
    for (int i = JACK; i <= KING; i++) {
        while (simpleStack.cardsCountsInStack[i] > 0) {
            simpleStack.cardsCountsInStack[10]++;
            simpleStack.cardsCountsInStack[i]--;
        }
    }

    int totalChancesInLayer = 1;
    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        for (int score = 0; score < POSSIBLESCORES; score++) {
            probabilityTreePointer->tree[layer][score].waysToAchieveScore = 0;
            probabilityTreePointer->tree[layer][score].unscaledProbabilityWithScoreToWin = 0;
            probabilityTreePointer->tree[layer][score].unscaledProbabilityWithScoreToDraw = 0;
            probabilityTreePointer->tree[layer][score].unscaledProbabilityWithScoreToLoose = 0;
            probabilityTreePointer->tree[layer][score].waysToGetHere = 0;
        }

        if (layer > 0) {
            totalChancesInLayer *= (simpleStack.cardsLeft + 1 - layer);
            probabilityTreePointer->tree[layer][22].waysToAchieveScore = totalChancesInLayer;
        }
    }

    //TODO work out why using simple stack pointer takes longer
    int *extraCards = malloc(localLayersToCalculate * sizeof(int));
    calculatePlayerHitScores(&simpleStack, extraCards, blackJackPlayerPointer, blackJackDealerPointer, probabilityTreePointer->tree, 0, 1, localLayersToCalculate);
    free(extraCards);

    updatePlayersScore(blackJackPlayerPointer);
    updatePlayersScore(blackJackDealerPointer);

    float cumulativeLose[localLayersToCalculate];
    float lowestLose = 100;
    int bestChance = 0;

    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        int totalWays = 0;

        cumulativeLose[layer] = 0;

        for (int score = 0; score < POSSIBLESCORES; score++) {
            totalWays += probabilityTreePointer->tree[layer][score].waysToAchieveScore;
        }

        for (int score = 0; score < POSSIBLESCORES; score++) {

            if (probabilityTreePointer->tree[layer][score].waysToAchieveScore > 0) {

                float percentOfGettingScore = ((float) probabilityTreePointer->tree[layer][score].waysToAchieveScore / totalWays) * 100;
                int waysOfGettingHere = probabilityTreePointer->tree[layer][score].waysToGetHere;
                float percentOfLose = (probabilityTreePointer->tree[layer][score].unscaledProbabilityWithScoreToLoose / waysOfGettingHere) * 100;

                cumulativeLose[layer] += percentOfGettingScore * percentOfLose;
            }
        }

        cumulativeLose[layer] /= 100;

        if (cumulativeLose[layer] < lowestLose) {
            lowestLose = cumulativeLose[layer];
            bestChance = layer;
        }
    }

    return bestChance == 0;
}

float getTrueCount(DeckStack *deckStackPointer) {
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

    return trueCount;
}

float getExpectedValueOfNextHandReal(DeckStack *deckStackPointer, BlackJackPlayer *blackJackPlayerPointer,
                                     BlackJackPlayer *blackJackDealerPointer) {
    /* Expectation
     * Can be +tive or - tive
     * Represents decimal percent of bet you expect to win by betting
     * -0.03 means you expect to lose 3% of your bet from betting
     * this can be considered to be a multiplier of (100 - E)% for each bet
     * This is given by:
     * (chance of winning * value of winning) - (chance of losing * value of losing)
    */

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

    Card firstCard, secondCard, thirdCard;
    firstCard.cardSuit = 0;
    secondCard.cardSuit = 0;
    thirdCard.cardSuit = 0;

    for (int i = 0; i < 10; i++) {
        // Deal 1st card to player
        if (simpleStack.cardsCountsInStack[i] > 0) {
            weight *= simpleStack.cardsCountsInStack[i];
            simpleStack.cardsCountsInStack[i]--;
            simpleStack.cardsLeft--;

            firstCard.cardID = i;
            addCardToPlayerStaticMemory(&blackJackPlayerPointer->player, firstCard);

            for (int j = i; j < 10; j++) {
                // Deal 2nd card to player
                if (simpleStack.cardsCountsInStack[j] > 0) {
                    weight *= simpleStack.cardsCountsInStack[j];
                    simpleStack.cardsCountsInStack[j]--;
                    simpleStack.cardsLeft--;

                    secondCard.cardID = j;
                    addCardToPlayerStaticMemory(&blackJackPlayerPointer->player, secondCard);

                    if (i != j) {
                        weight *= 2; //Corrects weights for occurrences that can happen in 2 ways
                    }


                    updatePlayersScore(blackJackPlayerPointer);

                    for (int k = 0; k < 10; k++) {
                        // Deal 3rd card to dealer
                        if (simpleStack.cardsCountsInStack[k] > 0) {
                            weight *= simpleStack.cardsCountsInStack[k];
                            simpleStack.cardsCountsInStack[k]--;
                            simpleStack.cardsLeft--;

                            thirdCard.cardID = k;
                            addCardToPlayerStaticMemory(&blackJackDealerPointer->player, thirdCard);
                            updatePlayersScore(blackJackDealerPointer);

                            // Dealt first 3 cards


                            //TODO Check if hit or stand, when stand work out probability of win lose and draw. If hit we must then simulate once for every card the player could recieve. If stand we must find percentage of win draw and loss


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

                    if (i != j) {
                        weight /= 2; //Corrects weights for occurrences that can happen in 2 ways
                    }
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

int factorial(int i) {
    if (i > 1) {
        return i * factorial(i - 1);
    } else if (i == 1) {
        return 1;
    } else {
        return 0;
    }
}

int maxLayersDeepForScore(int score) {
    int maxLayers = 0;
    for (int cardID = ACE; cardID <= KING; cardID++) {
        for (int i = 0; i < DECKSUSED * NUMBER_OF_SUITS; i++) {
            if (score < 0) {
                return maxLayers;
            } else {
                score -= cardID;
                maxLayers++;
            }
        }
    }

    return maxLayers;
}