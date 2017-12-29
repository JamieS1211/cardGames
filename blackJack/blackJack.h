//
// Created by Jamie on 23/12/2017.
//

#include "../cardAPI/api.h"

#define DECKSUSED 1

typedef struct blackJackPlayer {
    Player player;
    int differentScores;
    int *scores;
} BlackJackPlayer;