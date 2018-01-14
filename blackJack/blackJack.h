//
// Created by Jamie on 23/12/2017.
//

#include "../cardAPI/api.h"

#define DECKSUSED 2

typedef struct blackJackPlayer {
    Player player;
    int isScoreSoft;
    int score;
} BlackJackPlayer;

typedef struct probability {
    float waysToAchieveScore;
    float waysWithScoreToWin;
    float waysWithScoreToDraw;
    float waysWithScoreToLoose;
} Probability;