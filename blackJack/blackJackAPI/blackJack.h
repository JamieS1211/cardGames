//
// Created by Jamie on 23/12/2017.
//

#ifndef BLACKJACK_BLACKJACKAPI_BLACKJACK_H
#define BLACKJACK_BLACKJACKAPI_BLACKJACK_H

#include "../../cardAPI/api.h"

#define PRINTOPTION 0

#define DECKSUSED 1
#define POSSIBLESCORES 23

typedef struct blackJackPlayer {
    Player player;
    int isScoreSoft;
    int score;
} BlackJackPlayer;

typedef struct probability {
    unsigned long long waysToAchieveScore;
    float unscaledProbabilityWithScoreToWin;
    float unscaledProbabilityWithScoreToDraw;
    float unscaledProbabilityWithScoreToLoose;
    int waysToGetHere;
} Probability;

typedef struct probabilityTree {
    Probability **tree;
} ProbabilityTree;

#endif //BLACKJACK_BLACKJACKAPI_BLACKJACK_H