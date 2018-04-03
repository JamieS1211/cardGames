#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../blackJackAPI/blackJack.h"
#include "../blackJackAPI/blackJackPlayer.h"
#include "../blackJackAPI/blackJackCard.h"
#include "../cardCount/probabilityCalculator.h"

#include "../../generalAPI/userInput.h"

#include "../../cardAPI/deckStack.h"
#include "../../cardAPI/player.h"

void playBlackJack() {


    srand((unsigned int) time(NULL));

    DeckStack deckStack;
    initialiseFullDeckStack(&deckStack, DECKSUSED);

    DeckStack usedDeckStack;
    initialiseEmptyDeckStack(&usedDeckStack, DECKSUSED);


    BlackJackPlayer player;
    initialiseBlackJackPlayer(&player, "Player");

    BlackJackPlayer dealer;
    initialiseBlackJackPlayer(&dealer, "Dealer");

    int on = 1;

    while (on) {
        dealBlackJack(&deckStack, &usedDeckStack, &player, 0);
        dealBlackJack(&deckStack, &usedDeckStack, &player, 0);
        dealBlackJack(&deckStack, &usedDeckStack, &dealer, 0);

        int playerBust = 0;
        int dealerBust = 0;

        while (!playerBust && !doesPlayerHaveBlackJack(&player)) {

            printf("You have a score of score of: %i ", player.score);
            if (player.isScoreSoft) {
                printf("or %i", player.score - 10);
            }
            printf("\n");

            calculateProbabilities(&deckStack, &player, &dealer);

            printf("Would you like to hit or stand? \n"
                           "\t1: Hit \n"
                           "\t2: Stand \n");

            long option = getIntegerUserInput();

            if (option == 1) {
                dealBlackJack(&deckStack, &usedDeckStack, &player, 0);
                if (player.score > 21) {
                    playerBust = 1;
                    printf("\n \n \nPLAYER HAS GONE BUST \n");
                }
            } else if (option == 2) {
                break;
            } else {
                printf("What was entered was not a valid option, please try again. \n");
            }
        }

        if (!playerBust && !doesPlayerHaveBlackJack(&player)) {
            while (dealer.score < 17) {
                dealBlackJack(&deckStack, &usedDeckStack, &dealer, 0);
            }

            if (dealer.score > 21) {
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
                printf("Player has a score of: %i \n", player.score);
                printf("Dealer has a score of: %i \n ", dealer.score);

                if (player.score > dealer.score) {
                    printf("\n \n \nPLAYER WIN \n \n \n");
                } else if (dealer.score > player.score) {
                    printf("\n \n \nDEALER WIN \n \n \n");
                } else {
                    printf("\n \n \nDRAW \n \n \n");
                }
            }
        }

        for (int i = player.player.cardsInHand; i > 0; i--) {
            addCardToDeckStack(&usedDeckStack, getCardFromPlayer(&player.player, 0));
            removeCardFromBlackJackPlayersHand(&player, 0);
        }

        for (int i = dealer.player.cardsInHand; i > 0; i--) {
            addCardToDeckStack(&usedDeckStack, getCardFromPlayer(&dealer.player, 0));
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
}