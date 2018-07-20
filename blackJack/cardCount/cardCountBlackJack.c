//
// Created by Jamie on 23/12/2017.
//

#include <stdio.h>
#include "../blackJackAPI/blackJack.h"
#include "../blackJackAPI/blackJackPlayer.h"

#include "../../cardAPI/deckStack.h"
#include "../../cardAPI/player.h"
#include "../../cardAPI/utilityFunctions.h"
#include "../blackJackAPI/blackJackCard.h"
#include "../../generalAPI/userInput.h"
#include "probabilityCalculator.h"

void cardCountBlackJack() {

    DeckStack deckStack;
    initialiseFullDeckStack(&deckStack, 1);

    DeckStack usedDeckStack;
    initialiseEmptyDeckStack(&usedDeckStack, 1);


    BlackJackPlayer player;
    initialiseBlackJackPlayer(&player, "Player");

    BlackJackPlayer dealer;
    initialiseBlackJackPlayer(&dealer, "Dealer");

    int on = 1;

    while (on) {


        printf("Please enter the players first card \n");
        giveBlackJackPlayerCard(&deckStack, &usedDeckStack, &player, getCardDealt());

        printf("Please enter the players second card \n");
        giveBlackJackPlayerCard(&deckStack, &usedDeckStack, &player, getCardDealt());

        printf("Please enter the dealers first card \n");
        giveBlackJackPlayerCard(&deckStack, &usedDeckStack, &dealer, getCardDealt());

        calculateProbabilities(&deckStack, &player, &dealer);

        int playersTurn = 1;
        while (playersTurn) {
            while (1) {
                printf("Did you hit? \n"
                               "\t1: Yes \n"
                               "\t2: No \n");


                long option = getIntegerUserInput();

                if (option == 1) {
                    printf("Please enter the card you just got from hitting \n");
                    giveBlackJackPlayerCard(&deckStack, &usedDeckStack, &player, getCardDealt());
                    break;
                } else if (option == 2) {
                    playersTurn = 0;
                    break;
                } else {
                    printf("What was entered was not a valid option, please try again. \n");
                }
            }
        }

        int dealersTurn = 1;
        while (dealersTurn) {
            while (1) {
                printf("Did the dealer take another card? \n"
                               "\t1: Yes \n"
                               "\t2: No \n");


                long option = getIntegerUserInput();

                if (option == 1) {
                    printf("Please enter the card the dealer just got from hitting \n");
                    giveBlackJackPlayerCard(&deckStack, &usedDeckStack, &dealer, getCardDealt());
                    break;
                } else if (option == 2) {
                    dealersTurn = 0;
                    break;
                } else {
                    printf("What was entered was not a valid option, please try again. \n");
                }
            }
        }

        for (int i = player.player.cardsInHand; i > 0; i--) {
            addCardToDeckStack(&usedDeckStack, getCardFromPlayer(&player.player, 0));
            removeCardFromBlackJackPlayersHand(&player, 0, 0);
        }

        for (int i = dealer.player.cardsInHand; i > 0; i--) {
            addCardToDeckStack(&usedDeckStack, getCardFromPlayer(&dealer.player, 0));
            removeCardFromBlackJackPlayersHand(&dealer, 0, 0);
        }

        updatePlayersScore(&player);
        updatePlayersScore(&dealer);


        while (1) {
            printf("Calculate next hand? \n"
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