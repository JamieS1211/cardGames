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

void automateBlackJack() {

    srand((unsigned int) time(NULL));

    for (int totalTimes = 0; totalTimes < 20; totalTimes++) {

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


        int gamesToPlay = 10000;


        float startBalance = 500;
        float minBet = 0.1;
        float maxBet = 1000;

        float percentOfBalanceForMaxBet = 17.5;
        float expectedValueOffset = -7;
        float expectedValueMultiplier = 24;


        float balance = startBalance;
        for (int i = 0; i < gamesToPlay; i++) {
            //TODO correct for real occurances
            if (deckStack.cardsLeft < 5) {
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


                float expectedValue = getExpectedValueOfHand(&deckStack);
                //float expectedValueReal = getRealExpectedValueOfHand(&deckStack, &player, &dealer);
                float bet = minBet * (expectedValue + expectedValueOffset) * expectedValueMultiplier;

                if (bet > balance * (percentOfBalanceForMaxBet / 100)) {
                    bet = balance * (percentOfBalanceForMaxBet / 100);
                }

                if (bet > maxBet) {
                    bet = maxBet;
                } else if (bet < minBet) {
                    bet = minBet;
                }

                if (bet > balance) {
                    bet = balance;
                }

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
                    removeCardFromBlackJackPlayersHand(&player, 0);
                }

                for (int i = dealer.player.cardsInHand; i > 0; i--) {
                    addCardToDeckStack(&usedDeckStack, getCardFromPlayer(&dealer.player, 0));
                    removeCardFromBlackJackPlayersHand(&dealer, 0);
                }
            } else {
                srand((unsigned int) i);
                break;
            }
        }

        printf("\nIn %i games, using the advised strategy the player won %i times, dealer won %i times and there was %i draws.\n",
               gamesToPlay, playerWins, dealerWins, draws);
        printf("Starting with $%g the player ended with $%g multiplying their money by %g \n", startBalance,
               balance, balance / startBalance);
    }

    printf("\n\n");
}