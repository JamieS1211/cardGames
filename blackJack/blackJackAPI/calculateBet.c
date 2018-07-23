//
// Created by Jamie on 20/07/2018.
//

#import "calculateBet.h"

float calculateBet(float expectedValue, float minBet, float maxBet, float currentCash, float riskFactor) {

    return standardBetExpectedValue(expectedValue, minBet);

    float bet;

    float maxAllowableBet = maxBet;
    if (currentCash * riskFactor < maxBet) {
        maxAllowableBet = currentCash * riskFactor;
    }

    //Chance of winning multiplied by how much cash you have. Bounded by min and mex betting values.
    bet = minBet + (expectedValue * (maxAllowableBet - minBet));

    if (bet > maxBet) {
        bet = maxBet;
    } else if (bet < minBet){
        bet = minBet;
    }

    return bet;
}

float standardBetTrueCount(float trueCount, float minBet) {
    return (trueCount - 1) * minBet;
}

float standardBetExpectedValue(float expectedValue, float minBet) {
    float trueCount = (expectedValue * 2) + 1;

    return (trueCount - 1) * minBet;
}