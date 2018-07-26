//
// Created by Jamie on 20/07/2018.
//

#import "calculateBet.h"

//TODO FIND OPTIMUM SETTINGS
float calculateBet(float expectedValue, float minBet, float maxBet, float currentCash, float riskFactor) {
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

float standardBetExpectedValue(float trueCount, float minBet, float maxBet) {

    float bet = (trueCount - 1) * minBet;

    if (bet < minBet) {
        bet = minBet;
    }

    if (bet > maxBet) {
        bet = maxBet;
    }

    return bet;
}