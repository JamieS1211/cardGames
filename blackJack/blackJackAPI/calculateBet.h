//
// Created by Jamie on 20/07/2018.
//

#ifndef BLACKJACK_BLACKJACKAPI_CALCULATEBET_H
#define BLACKJACK_BLACKJACKAPI_CALCULATEBET_H

float calculateBet(float expectedValue, float minBet, float maxBet, float currentCash, float riskFactor);

float standardBetTrueCount(float trueCount, float minBet);

float standardBetExpectedValue(float expectedValue, float minBet);

#endif //BLACKJACK_BLACKJACKAPI_CALCULATEBET_H
