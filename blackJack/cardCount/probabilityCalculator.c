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

void printProbabilities(Probability **treePointer) {

    float cumulativeWin[LAYERSTOCALCULATE];
    float cumulativeDraw[LAYERSTOCALCULATE];
    float cumulativeLose[LAYERSTOCALCULATE];

    for (int layer = 0; layer < LAYERSTOCALCULATE; layer++) {
        int totalWays = 0;

        cumulativeWin[layer] = 0;
        cumulativeDraw[layer] = 0;
        cumulativeLose[layer] = 0;

        for (int score = 0; score < POSSIBLESCORES; score++) {
            totalWays += treePointer[layer][score].waysToAchieveScore;
        }


        printf("\nLayer: %i \n", layer);

        printf("\t\t\t\t Chance");
        printf("\t\t\t Win");
        printf("\t\t\t Draw");
        printf("\t\t\t Lose \n");

        for (int score = 0; score < POSSIBLESCORES; score++) {

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
    //TODO optimise function to only do each order of cards once

    int currentBestPlayerScore = blackJackPlayerPointer->score;
    int nextLayer = currentLayer + 1;

    if (currentBestPlayerScore > 21) {
        currentBestPlayerScore = 22;
    } else if (currentBestPlayerScore <= 21 && nextLayer < totalLayers) {
        for (int cardID = 1; cardID <= TEN ; cardID++) {
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

    tree = malloc(LAYERSTOCALCULATE * POSSIBLESCORES * sizeof(Probability));

    for (int layer = 0; layer < LAYERSTOCALCULATE; layer++) {
        tree[layer] = malloc(POSSIBLESCORES * sizeof(Probability));
    }


    for (int layer = 0; layer < LAYERSTOCALCULATE; layer++) {
        for (int score = 0; score < POSSIBLESCORES; score++) {
            tree[layer][score].waysToAchieveScore = 0;
            tree[layer][score].waysWithScoreToWin = 0;
            tree[layer][score].waysWithScoreToDraw = 0;
            tree[layer][score].waysWithScoreToLoose = 0;
        }
    }

    calculatePlayerHitScores(&simpleStack, blackJackPlayerPointer, blackJackDealerPointer, tree, 0, 1, LAYERSTOCALCULATE);
    updatePlayersScore(blackJackPlayerPointer);
    updatePlayersScore(blackJackDealerPointer);

    printProbabilities(tree);
    for (int layer = 0; layer < LAYERSTOCALCULATE; layer++) {
        free(tree[layer]);
    }
    free(tree);
}

/**
 * A function that returns a current chances object that advises if a player should stand and what their current win and lose chances are
 * @param deckStackPointer
 * @param blackJackPlayerPointer
 * @param blackJackDealerPointer
 */
CurrentChances shouldStand(DeckStack *deckStackPointer, SimpleStack *simpleStackPointer, ProbabilityTree *probabilityTreePointer,
                BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer) {
    /*
     * This value is amount of iterations deep that is relevant for calculations. Higher = better but longer
     * Value of 2 assesses current layer (standing) against next layer (hitting)
     * As cumulative odds of losing decrease to a point and then increase (AKA have one minimum) only 2 values are required
     * If next layer has higher cumulative chance of losing then we should stand
    */

    int localLayersToCalculate = 2; //TODO this value is amount of iterations deep that is relevent for calculations. Higher = better but longer
    int possibleScores = POSSIBLESCORES;

    SimpleStack simpleStack;
    initialiseSimpleStackFromDeckStack(&simpleStack, deckStackPointer);

    // Simplify all 10 score cards into one slot
    for (int i = JACK; i <= KING; i++) {
        while (simpleStack.cardsCountsInStack[i] > 0) {
            simpleStack.cardsCountsInStack[10]++;
            simpleStack.cardsCountsInStack[i]--;
        }
    }

    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        for (int score = 0; score < possibleScores; score++) {
            probabilityTreePointer->tree[layer][score].waysToAchieveScore = 0;
            probabilityTreePointer->tree[layer][score].waysWithScoreToWin = 0;
            probabilityTreePointer->tree[layer][score].waysWithScoreToDraw = 0;
            probabilityTreePointer->tree[layer][score].waysWithScoreToLoose = 0;
        }
    }

    //TODO work out why using simple stack pointer takes longer
    calculatePlayerHitScores(&simpleStack, blackJackPlayerPointer, blackJackDealerPointer, probabilityTreePointer->tree, 0, 1, localLayersToCalculate);

    updatePlayersScore(blackJackPlayerPointer);
    updatePlayersScore(blackJackDealerPointer);

    CurrentChances currentChances;
    float cumulativeWin[localLayersToCalculate];
    float cumulativeLose[localLayersToCalculate];

    float lowestLose = 100;
    int bestChance = 0;

    for (int layer = 0; layer < localLayersToCalculate; layer++) {
        int totalWays = 0;

        cumulativeWin[layer] = 0;
        cumulativeLose[layer] = 0;

        for (int score = 0; score < possibleScores; score++) {
            totalWays += probabilityTreePointer->tree[layer][score].waysToAchieveScore;
        }

        for (int score = 0; score < possibleScores; score++) {

            if (probabilityTreePointer->tree[layer][score].waysToAchieveScore > 0) {

                int totalWaysForDealerPlay = 0;

                totalWaysForDealerPlay += probabilityTreePointer->tree[layer][score].waysWithScoreToWin
                                          + probabilityTreePointer->tree[layer][score].waysWithScoreToDraw
                                          + probabilityTreePointer->tree[layer][score].waysWithScoreToLoose;

                float percentOfGettingScore = ((float) probabilityTreePointer->tree[layer][score].waysToAchieveScore / totalWays) * 100;
                float percentOfWin = ((float) probabilityTreePointer->tree[layer][score].waysWithScoreToWin / totalWaysForDealerPlay) * 100;
                float percentOfLose = ((float) probabilityTreePointer->tree[layer][score].waysWithScoreToLoose / totalWaysForDealerPlay) * 100;

                cumulativeWin[layer] += percentOfGettingScore * percentOfWin;
                cumulativeLose[layer] += percentOfGettingScore * percentOfLose;
            }
        }

        cumulativeWin[layer] /= 100;
        cumulativeLose[layer] /= 100;

        if (cumulativeLose[layer] < lowestLose) {
            lowestLose = cumulativeLose[layer];
            bestChance = layer;
        }
    }

    currentChances.shouldStand = (bestChance == 0);
    currentChances.currentCumulativeWin = cumulativeWin[0];
    currentChances.currentCumulativeLose = cumulativeLose[0];

    return currentChances;
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

float getExpectedValueOfNextHand(DeckStack *deckStackPointer, ProbabilityTree *probabilityTreePointer, BlackJackPlayer *blackJackPlayerPointer, BlackJackPlayer *blackJackDealerPointer) {
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

    CurrentChances currentChances;
    int totalStartingHands =
            deckStackPointer->cardsLeft * (deckStackPointer->cardsLeft - 1) * (deckStackPointer->cardsLeft - 2);
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
                        //Only do in ascending order, total ways to organise is factorial of different cards
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

                            float setupCumulativeWin = 0;
                            float setupCumulativeLose = 0;

                            /// Dealt first 3 cards


                            currentChances = shouldStand(deckStackPointer, &simpleStack,
                                                         probabilityTreePointer,
                                                         blackJackPlayerPointer,
                                                         blackJackDealerPointer);

                            if (currentChances.shouldStand == 0) { //If you should hit at least once
                                int timesHit = 1;
                                int *hitCards = NULL;
                                int correctOrder;
                                int differentCards;

                                float weightFraction;

                                while () {//TODO work out contents so that every path is exhausted
                                    hitCards = realloc(hitCards, timesHit * sizeof(int));
                                    correctOrder = 1;

                                    while (!nBitCounterAddOne(timesHit, hitCards, 10)) {
                                        //Deal next card (in every way possible)

                                        //card IDs are values - 1 of hitCards contents
                                        //hitCards[0] + 1 is the cardID of the 1st hit card

                                        for (int cardPosition = 0; cardPosition < timesHit - 1; cardPosition++) {
                                            if (hitCards[cardPosition] > hitCards[cardPosition + 1]) {
                                                correctOrder = 0;
                                            }
                                        }

                                        if (correctOrder) {
                                            //Valid order to deal cards

                                            int enoughOfAllCardsToDeal = 1;

                                            //TODO chance enough of all cards to deal to be 0 if there is not enough of a certain card to deal that possibility

                                            if (enoughOfAllCardsToDeal) {
                                                //Deal the hits cards
                                                currentChances = shouldStand(deckStackPointer, &simpleStack,
                                                                             probabilityTreePointer,
                                                                             blackJackPlayerPointer,
                                                                             blackJackDealerPointer);
                                                //Undeal the hits cards

                                                if (currentChances.shouldStand == 1) {

                                                    for (int cardType = ACE; cardType <= TEN; cardType++) {
                                                        for (int cardPosition = 0;
                                                             cardPosition < timesHit; cardPosition++) {
                                                            if (hitCards[cardPosition] == cardType) {
                                                                differentCards++;
                                                                break;
                                                            }
                                                        }
                                                    }

                                                    weightFraction = factorial(differentCards) * waysToGetTheseCards * 10^hits;

                                                    setupCumulativeWin = currentChances.currentCumulativeLose * weightFraction;
                                                    setupCumulativeLose = currentChances.currentCumulativeLose * weightFraction;

                                                    if (hitCards[timesHit - 1] == TEN) {
                                                        //Go up a level
                                                        timesHit--;
                                                        break;
                                                    }

                                                } else {
                                                    //Go deeper
                                                    timesHit++;
                                                    break;
                                                }

                                            }
                                        }

                                    }
                                }
                            } else {
                                setupCumulativeWin = currentChances.currentCumulativeWin;
                                setupCumulativeLose = currentChances.currentCumulativeLose;
                            }

                            float chanceOfGettingFirst3Cards = (weight / totalStartingHands);
                            totalWin +=  chanceOfGettingFirst3Cards * setupCumulativeWin;
                            totalLose += chanceOfGettingFirst3Cards * setupCumulativeLose;

                            /// Un-deal first 3 cards

                            removeCardFromBlackJackPlayersHand(blackJackDealerPointer,
                                                               blackJackDealerPointer->player.cardsInHand - 1, 1);

                            simpleStack.cardsCountsInStack[k]++;
                            weight /= simpleStack.cardsCountsInStack[k];
                            simpleStack.cardsLeft++;
                        }
                    }

                    removeCardFromBlackJackPlayersHand(blackJackPlayerPointer,
                                                       blackJackPlayerPointer->player.cardsInHand - 1, 1);

                    simpleStack.cardsCountsInStack[j]++;
                    weight /= simpleStack.cardsCountsInStack[j];
                    simpleStack.cardsLeft++;

                    if (i != j) {
                        //Only do in ascending order, total ways to organise is factorial of different cards
                        weight /= 2; //Corrects weights for occurrences that can happen in 2 ways
                    }
                }
            }

            removeCardFromBlackJackPlayersHand(blackJackPlayerPointer, blackJackPlayerPointer->player.cardsInHand - 1,
                                               1);

            simpleStack.cardsCountsInStack[i]++;
            weight /= simpleStack.cardsCountsInStack[i];
            simpleStack.cardsLeft++;
        }
    }

    return 0;
}

/**
 * Counter function that takes bits in a counter, pointer to the counter and base of counting and then returns 1 if the counter has finished and if not returns 0 and increments the counter by 1
 *
 * @param bits      Bits in the counter
 * @param p         Pointer to counter
 * @param base      Base of counting
 * @return          If the counter has finished
 */
int nBitCounterAddOne(int bits, int *p, int base) {
    int finished = 1;
    for (int i = 0; i < bits; i++) {
        if (p[i] < base - 1) {
            finished = 0;
            break;
        }
    }

    if (finished) {
        return finished;
    }

    p[0] = p[0] + 1;

    for (int i = 0; i < bits; i++) {
        if (p[i] >= base) {
            if (i < bits - 1 && p[i + 1] < base) {
                p[i + 1] = p[i + 1] + 1;
                p[i] = 0;
            }
        }
    }

    return 0;
}
