//
// Created by Jamie on 28/12/2017.
//

#include <stdio.h>
#include "../blackJack.h"
#include "../blackJackCard.h"
#include "../../cardAPI/stack.h"
#include "../blackJackPlayer.h"

void calculateProbabilities(DeckStack *stack, BlackJackPlayer *player) {

    // An array of the amount of ways each best score can be achieved, 0 = score of 2, 1 = score of 3 ... 19 = score of 21, 20 = bust.
    int playerChances[21] = {0};

    for (int i = 0; i < stack->cardsLeft; i++) {
        int score = getPlayersBestScore(player);
        Card card = stack->cardsInStack[i];

        score += getCardValue(card);

        if (card.cardID == ACE && score < 12) {
            score += 10;
        }

        if (score > 21) {
            score = 22;
        }

        playerChances[score - 2] = playerChances[score - 2] + 1;
    }

    printf("\n \n \n");
    for (int i = 0; i < 21; i++) {
        if (playerChances[i] != 0) {
            if (i == 20) {
                printf("The chance you hit and go bust is %i/%i \n", playerChances[i],
                       stack->cardsLeft);
            }  else {
                printf("The chance you hit and have a best score of %i is %i/%i \n", i + 2, playerChances[i],
                       stack->cardsLeft);
            }
        }
    }
    printf("\n \n \n");
}