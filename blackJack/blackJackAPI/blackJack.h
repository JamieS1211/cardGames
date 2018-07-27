//
// Created by Jamie on 23/12/2017.
//

#ifndef BLACKJACK_BLACKJACKAPI_BLACKJACK_H
#define BLACKJACK_BLACKJACKAPI_BLACKJACK_H

#include "../../cardAPI/api.h"

#define DECKSUSED 1
#define LAYERSTOCALCULATE 2
#define POSSIBLESCORES 23

typedef struct blackJackPlayer {
    Player player;
    int isScoreSoft;
    int score;
} BlackJackPlayer;

typedef struct probability {
    unsigned long long waysToAchieveScore;
    unsigned long long waysWithScoreToWin;
    unsigned long long waysWithScoreToDraw;
    unsigned long long waysWithScoreToLoose;
} Probability;

typedef struct probabilityTree {
    Probability **tree;
} ProbabilityTree;

typedef struct currentChances {
    int shouldStand;
    float currentCumulativeWin;
    float currentCumulativeLose;
} CurrentChances;

#endif //BLACKJACK_BLACKJACKAPI_BLACKJACK_H