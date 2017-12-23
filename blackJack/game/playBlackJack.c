#include <stdio.h>

#include "../blackJack.h"
#include "../blackJackPlayer.h"
#include "../blackJackCard.h"

#include "../../cardAPI/stack.h"
#include "../../cardAPI/player.h"

int main() {

    DeckStack stack;
    initialiseFullStack(&stack, 1);

    DeckStack usedStack;
    initialiseEmptyStack(&usedStack, 1);


    BlackJackPlayer player;
    initialiseBlackJackPlayer(&player, "Player");

    BlackJackPlayer dealer;
    initialiseBlackJackPlayer(&dealer, "Dealer");

    for (int j = 0; j < 1000; j++) {

        dealBlackJack(&stack, &usedStack, &player);
        dealBlackJack(&stack, &usedStack, &player);
        dealBlackJack(&stack, &usedStack, &dealer);

        int playerBust = 0;
        int dealerBust = 0;

        while (!playerBust) {

            if (player.scoreMax == player.scoreMin || (player.scoreMax > 21 && player.scoreMin <= 21)) {
                printf("You have a score of %i\n", player.scoreMin);
            } else {
                printf("You have a score of %i or %i\n", player.scoreMax, player.scoreMin);
            }

            printf("Would you like to hit or stand? \n"
                           "\t1: Hit \n"
                           "\t2: Stand \n");
            int option;

            //TODO change to strtol to prevent crashes / spam etc.
            scanf("%i", &option);

            if (option == 1) {
                dealBlackJack(&stack, &usedStack, &player);
                if (player.scoreMax > 21 && player.scoreMin > 21) {
                    playerBust = 1;
                    printf("\n \n \nPLAYER HAS GONE BUST WITH A SCORE OF %i \n", player.scoreMin);
                }
            } else if (option == 2) {
                break;
            } else {
                printf("What was entered was not a valid option, please try again. \n");
            }
        }

        if (!playerBust) {
            while (dealer.scoreMax < 17 || (dealer.scoreMax > 21 && dealer.scoreMin < 17)) {
                dealBlackJack(&stack, &usedStack, &dealer);
            }

            if (dealer.scoreMax > 21 && dealer.scoreMin > 21) {
                dealerBust = 1;
                printf("\n \n \nDEALER HAS GONE BUST WITH A SCORE OF %i \n", dealer.scoreMin);
            }
        }

        if (dealerBust) {
            printf("\n \n \nPLAYER WIN \n \n \n");
        } else if (playerBust) {
            printf("\n \n \nDEALER WIN \n \n \n");
        } else {
            int dealerScoreUsed;

            int playerScoreUsed;
            if (player.scoreMax <= 21) {
                playerScoreUsed = player.scoreMax;
            } else {
                playerScoreUsed = player.scoreMin;
            }

            if (dealer.scoreMax <= 21) {
                dealerScoreUsed = dealer.scoreMax;
            } else {
                dealerScoreUsed = dealer.scoreMin;
            }

            printf("Player has a score of: %i \n", playerScoreUsed);
            printf("Dealer has a score of: %i \n ", dealerScoreUsed);

            if (playerScoreUsed > dealerScoreUsed) {
                printf("\n \n \nPLAYER WIN \n \n \n");
            } else if (dealerScoreUsed > playerScoreUsed) {
                printf("\n \n \nDEALER WIN \n \n \n");
            } else {
                printf("\n \n \nDRAW \n \n \n");
            }
        }


        //TODO find out why remove card from players hand is not working in this case
        for (int i = 0; i < player.player.cardsInHand; i++) {
            addCardToStack(&usedStack, getCardFromPlayer(&player.player, 0));
            removeCardFromPlayersHand(&player.player, 0);
        }

        for (int i = 0; i < dealer.player.cardsInHand; i++) {
            addCardToStack(&usedStack, getCardFromPlayer(&dealer.player, 0));
            removeCardFromPlayersHand(&dealer.player, 0);
        }
    }

    return 0;
}