//
// Created by Jamie on 23/12/2017.
//

#ifndef BLACKJACK_BLACKJACKAPI_BLACKJACK_H
#define BLACKJACK_BLACKJACKAPI_BLACKJACK_H

#include "../../cardAPI/api.h"

#define DECKSUSED 1

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

#endif //BLACKJACK_BLACKJACKAPI_BLACKJACK_H