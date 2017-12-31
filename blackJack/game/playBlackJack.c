#include <stdio.h>

#include "../blackJack.h"
#include "../blackJackPlayer.h"
#include "../blackJackCard.h"
#include "../cardCount/probabilityCalculator.h"

#include "../../generalAPI/userInput.h"

#include "../../cardAPI/stack.h"
#include "../../cardAPI/player.h"

void playBlackJack() {

    DeckStack stack;
    initialiseFullStack(&stack, DECKSUSED);

    DeckStack usedStack;
    initialiseEmptyStack(&usedStack, DECKSUSED);


    BlackJackPlayer player;
    initialiseBlackJackPlayer(&player, "Player");

    BlackJackPlayer dealer;
    initialiseBlackJackPlayer(&dealer, "Dealer");

    int on = 1;

    while (on) {
        dealBlackJack(&stack, &usedStack, &player);
        dealBlackJack(&stack, &usedStack, &player);
        dealBlackJack(&stack, &usedStack, &dealer);

        int playerBust = 0;
        int dealerBust = 0;

        while (!playerBust && !doesPlayerHaveBlackJack(&player)) {

            printf("You have a score of score of: %i ", player.score);
            if (player.isScoreSoft) {
                printf("or %i", player.score - 10);
            }
            printf("\n");

            calculateProbabilities(&stack, &player, &dealer);

            printf("Would you like to hit or stand? \n"
                           "\t1: Hit \n"
                           "\t2: Stand \n");

            long option = getIntegerUserInput();

            if (option == 1) {
                dealBlackJack(&stack, &usedStack, &player);
                if (getPlayersBestScore(&player) > 21) {
                    playerBust = 1;
                    printf("\n \n \nPLAYER HAS GONE BUST \n");
                }
            } else if (option == 2) {
                break;
            } else {
                printf("What was entered was not a valid option, please try again. \n");
            }
        }

        if (!playerBust) {
            while (getPlayersBestScore(&dealer) < 17) {
                dealBlackJack(&stack, &usedStack, &dealer);
            }

            if (getPlayersBestScore(&dealer) > 21) {
                dealerBust = 1;
                printf("\n \n \nDEALER HAS GONE BUST \n");
            }
        }

        if (dealerBust) {
            printf("PLAYER WIN \n \n \n");
        } else if (playerBust) {
            printf("DEALER WIN \n \n \n");
        } else {

            if (doesPlayerHaveBlackJack(&player) && doesPlayerHaveBlackJack(&dealer)) {
                printf("\n \n \nDRAW \n \n \n");
            } else if (doesPlayerHaveBlackJack(&player)) {
                printf("\n \n \nPLAYER WIN \n \n \n");
            } else if (doesPlayerHaveBlackJack(&dealer)) {
                printf("\n \n \nDEALER WIN \n \n \n");
            } else {
                printf("Player has a score of: %i \n", getPlayersBestScore(&player));
                printf("Dealer has a score of: %i \n ", getPlayersBestScore(&dealer));

                if (getPlayersBestScore(&player) > getPlayersBestScore(&dealer)) {
                    printf("\n \n \nPLAYER WIN \n \n \n");
                } else if (getPlayersBestScore(&dealer) > getPlayersBestScore(&player)) {
                    printf("\n \n \nDEALER WIN \n \n \n");
                } else {
                    printf("\n \n \nDRAW \n \n \n");
                }
            }
        }

        for (int i = player.player.cardsInHand; i > 0; i--) {
            addCardToStack(&usedStack, getCardFromPlayer(&player.player, 0));
            removeCardFromBlackJackPlayersHand(&player, 0);
        }

        for (int i = dealer.player.cardsInHand; i > 0; i--) {
            addCardToStack(&usedStack, getCardFromPlayer(&dealer.player, 0));
            removeCardFromBlackJackPlayersHand(&dealer, 0);
        }

        while (1) {
            printf("Would you like to play another hand? \n"
                           "\t1: Yes \n"
                           "\t2: No \n");


            long option = getIntegerUserInput();

            if (option == 1) {
                break;
            } else if (option == 2) {
                on = 0;
                break;
            } else {
                printf("What was entered was not a valid option, please try again. \n");
            }
        }
    }

    return;
}