//
// Created by Jamie on 20/07/2018.
//

float calculateBet(float expectedValue, float minBet, float maxBet, float currentCash, float riskFactor) {
    float bet;

    bet = expectedValue * (currentCash * riskFactor);

    if (expectedValue < minBet) {
        bet = minBet;
    } else if (expectedValue > maxBet) {
        bet = maxBet;
    }

    return bet;
}