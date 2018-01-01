//
// Created by Jamie on 23/12/2017.
//

#include "../cardAPI/api.h"

#define DECKSUSED 1

typedef struct blackJackPlayer {
    Player player;
    int isScoreSoft;
    int score;
} BlackJackPlayer;

typedef struct probability {
    int waysToAchieveScore;
    int waysWithScoreToWin;
    int waysWithScoreToDraw;
    int waysWithScoreToLoose;
} Probability;