//
// Created by Jamie on 19/07/2018.
//

#include <stdio.h>
#include <afxres.h>
#include "game/automateBlackJack.h"

void findMapping(int setsPerTest, int gamesPerSet) {
    int riskFactorSamplePoints = 11; //inclusive of min and max
    float riskFactorMin = 0;
    float riskFactorMax = 0.02;

    if (riskFactorSamplePoints < 2) {
        printf("The risk factor sample points was too low, defaulting to 10");
        riskFactorSamplePoints = 10;
    }

    float riskFactor;
    float riskFactorStep = (riskFactorMax - riskFactorMin) / (riskFactorSamplePoints - 1);


    int minBetSamplePoints = 11; //inclusive of min and max
    float minBetMin = 0;
    float minBetMax = 100;

    if (riskFactorSamplePoints < 2) {
        printf("The min bet sample points was too low, defaulting to 10");
        riskFactorSamplePoints = 10;
    }

    float minBet;
    float minBetStep = (minBetMax - minBetMin) / (minBetSamplePoints - 1);




    //Max bet is calculated as a Scalar of the min bet
    int maxBetScalarSamplePoints = 11; //inclusive of min and max
    float maxBetScalarMin = 5;
    float maxBetScalarMax = 50;

    if (riskFactorSamplePoints < 2) {
        printf("The max bet scalar sample points was too low, defaulting to 10");
        riskFactorSamplePoints = 10;
    }

    float maxBetScalar, maxBet;
    float maxBetScalarStep = (maxBetScalarMax - maxBetScalarMin) / (maxBetScalarSamplePoints - 1);




    //Balance is calculated as a Scalar of the min bet
    int balanceScalarSamplePoints = 11; //inclusive of min and max
    float balanceScalarMin = 10;
    float balanceScalarMax = 100;

    if (riskFactorSamplePoints < 2) {
        printf("The balance scalar sample points was too low, defaulting to 10");
        riskFactorSamplePoints = 10;
    }

    float balanceScalar, balance;
    float balanceScalarStep = (balanceScalarMax - balanceScalarMin) / (balanceScalarSamplePoints - 1);


    for (int j = 0; j < minBetSamplePoints; j++) {
        minBet = minBetMin + (j * minBetStep);

        //Must remove occurrences where min bet is less then 0
        if (minBet > 0) {


            for (int k = 0; k < maxBetScalarSamplePoints; k++) {
                maxBetScalar = maxBetScalarMin + (k * maxBetScalarStep);
                maxBet = minBet * maxBetScalar;

                for (int l = 0; l < balanceScalarSamplePoints; l++) {
                    balanceScalar = balanceScalarMin + (l * balanceScalarStep);
                    balance = minBet * balanceScalar;

                    for (int i = 0; i < riskFactorSamplePoints; i++) {
                        riskFactor = riskFactorMin + (i * riskFactorStep);
                        printf("RiskFactor: %f \n", riskFactor);

                        automateBlackJack(setsPerTest, gamesPerSet, balance, minBet, maxBet, riskFactor);

                        //TODO should receive response from automate blackjack so this can be checked to find the optimum for settings
                    }
                }
            }
        }

        //Sleep(1000);
    }
}
