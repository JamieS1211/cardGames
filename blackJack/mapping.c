//
// Created by Jamie on 19/07/2018.
//

#include <stdio.h>
#include "game/automateBlackJack.h"

void findMapping(int setsPerTest, int gamesPerSet) {
    int riskFactorSamplePoints = 11; //inclusive of min and max
    float riskFactorMin = 0;
    float riskFactorMax = 0.02;

    if (riskFactorSamplePoints< 2) {
        printf("The risk factor sample points was too low, defaulting to 10");
        riskFactorSamplePoints = 10;
    }

    float riskFactor;
    float riskFactorStep = (riskFactorMax - riskFactorMin) / (riskFactorSamplePoints - 1);




    int minBetSamplePoints = 11; //inclusive of min and max
    float minBetMin = 0;
    float minBetMax = 100;

    if (riskFactorSamplePoints< 2) {
        printf("The min bet sample points was too low, defaulting to 10");
        riskFactorSamplePoints = 10;
    }

    float minBet;
    float minBetStep = (minBetMax - minBetMin) / (minBetSamplePoints - 1);




    //Max bet is calculated as a scaler of the min bet
    int maxBetScalerSamplePoints = 11; //inclusive of min and max
    float maxBetScalerMin = 1;
    float maxBetScalerMax = 50;

    if (riskFactorSamplePoints< 2) {
        printf("The max bet scaler sample points was too low, defaulting to 10");
        riskFactorSamplePoints = 10;
    }

    float maxBetScaler, maxBet;
    float maxBetScalerStep = (maxBetScalerMax - maxBetScalerMin) / (maxBetScalerSamplePoints - 1);




    //Balance is calculated as a scaler of the min bet
    int balanceScalerSamplePoints = 11; //inclusive of min and max
    float balanceScalerMin = 10;
    float balanceScalerMax = 100;

    if (riskFactorSamplePoints< 2) {
        printf("The balance scaler sample points was too low, defaulting to 10");
        riskFactorSamplePoints = 10;
    }

    float balanceScaler, balance;
    float balanceScalerStep = (balanceScalerMax - balanceScalerMin) / (balanceScalerSamplePoints - 1);




    for (int i = 0; i < riskFactorSamplePoints; i++) {
        riskFactor = riskFactorMin + (i * riskFactorStep);
        //printf("RiskFactor: %f \n", riskFactor);

        for (int j = 0; j < minBetSamplePoints; j++) {
            minBet = minBetMin + (j * minBetStep);

            //Must remove occurrences where min bet is less then 0
            if (minBet > 0) {


                for (int k = 0; k < maxBetScalerSamplePoints; k++) {
                    maxBetScaler = maxBetScalerMin + (k * maxBetScalerStep);
                    maxBet = minBet * maxBetScaler;

                    for (int l = 0; l < balanceScalerSamplePoints; l++) {
                        balanceScaler = balanceScalerMin + (l * balanceScalerStep);
                        balance = minBet * balanceScaler;

                        automateBlackJack(setsPerTest, gamesPerSet, balance, minBet, maxBet, riskFactor);

                        //TODO should recieve response from automate blackjack so this can be checked to find the optimum for settings
                    }
                }


            }
        }
    }
}
