//
// Created by Jamie on 23/12/2017.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "../blackJackAPI/blackJack.h"
#include "../blackJackAPI/blackJackPlayer.h"
#include "../blackJackAPI/blackJackCard.h"
#include "../cardCount/probabilityCalculator.h"

#include "../../generalAPI/userInput.h"

#include "../../cardAPI/deckStack.h"
#include "../../cardAPI/player.h"
#include "../blackJackAPI/calculateBet.h"

void automateBlackJack(int gamesSets, int gamesPerSet, float startBalance, float minBet, float maxBet, float riskFactor) {

    srand((unsigned int) time(NULL));

    for (int set = 0; set < gamesSets; set++) {

        DeckStack deckStack;
        initialiseFullDeckStack(&deckStack, DECKSUSED);

        DeckStack usedDeckStack;
        initialiseEmptyDeckStack(&usedDeckStack, DECKSUSED);


        BlackJackPlayer player;
        initialiseBlackJackPlayer(&player, "Player");

        BlackJackPlayer dealer;
        initialiseBlackJackPlayer(&dealer, "Dealer");

        srand((unsigned int) time(NULL));

        int playerWins = 0;
        int dealerWins = 0;
        int draws = 0;

        float balance = startBalance;
        for (int i = 0; i < gamesPerSet; i++) {
            float cardRemainingPercent = usedDeckStack.cardsLeft / (DECKSUSED * NUMBER_OF_SUITS * NUMBER_OF_CARDS) * 100;
            if (cardRemainingPercent < 40) {
                for (int i = 0; i < usedDeckStack.cardsLeft; i++) {
                    addCardToDeckStack(&deckStack, getCardFromDeckStack(&usedDeckStack, i));
                    removeCardFromDeckStack(&usedDeckStack, i);
                }
            }

            if (balance >= minBet) {

                if (deckStack.cardsLeft == 0) {
                    for (int i = 0; i < usedDeckStack.cardsLeft; i++) {
                        addCardToDeckStack(&deckStack, getCardFromDeckStack(&usedDeckStack, i));
                        removeCardFromDeckStack(&usedDeckStack, i);
                    }
                }


                float expectedValue = getExpectedValueOfNextHandRunningCount(&deckStack);
                //float expectedValueReal = getExpectedValueOfNextHandReal(&deckStack, &player, &dealer);
                float bet = calculateBet(expectedValue, minBet, maxBet, balance, riskFactor);

                dealBlackJack(&deckStack, &usedDeckStack, &player, 1);
                dealBlackJack(&deckStack, &usedDeckStack, &player, 1);
                dealBlackJack(&deckStack, &usedDeckStack, &dealer, 1);

                int playerBust = 0;
                int dealerBust = 0;

                while (!playerBust && !doesPlayerHaveBlackJack(&player)) {

                    if (stand(&deckStack, &player, &dealer)) {
                        break;
                    } else {
                        dealBlackJack(&deckStack, &usedDeckStack, &player, 1);
                        if (player.score > 21) {
                            playerBust = 1;
                        }
                    }
                }

                if (!playerBust && !doesPlayerHaveBlackJack(&player)) {
                    while (dealer.score < 17) {
                        dealBlackJack(&deckStack, &usedDeckStack, &dealer, 1);
                    }

                    if (dealer.score > 21) {
                        dealerBust = 1;
                    }
                }

                if (dealerBust) {
                    playerWins++;
                    balance += bet;
                } else if (playerBust) {
                    dealerWins++;
                    balance -= bet;
                } else {

                    if (doesPlayerHaveBlackJack(&player) && doesPlayerHaveBlackJack(&dealer)) {
                        draws++;
                    } else if (doesPlayerHaveBlackJack(&player)) {
                        playerWins++;
                        balance += bet;
                    } else if (doesPlayerHaveBlackJack(&dealer)) {
                        dealerWins++;
                        balance -= bet;
                    } else {
                        if (player.score > dealer.score) {
                            playerWins++;
                            balance += bet;
                        } else if (dealer.score > player.score) {
                            dealerWins++;
                            balance -= bet;
                        } else {
                            draws++;
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

            } else {
                srand((unsigned int) i);
                break;
            }
        }

        printf("\nIn %i games, using the advised strategy the player won %i times, dealer won %i times and there was %i draws.\n",
               gamesPerSet, playerWins, dealerWins, draws);
        printf("Starting with $%g the player ended with $%g multiplying their money by %g \n", startBalance,
               balance, balance / startBalance);
        printf("Settings for games: MinBet: %g  MaxBet: %g  RiskFactor: %g\n", minBet, maxBet, riskFactor);
    }

    printf("\n\n");
}