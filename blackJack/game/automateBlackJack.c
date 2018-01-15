#include <stdio.h>

#include "../blackJackAPI/blackJack.h"
#include "../blackJackAPI/blackJackPlayer.h"
#include "../blackJackAPI/blackJackCard.h"
#include "../cardCount/probabilityCalculator.h"

#include "../../generalAPI/userInput.h"

#include "../../cardAPI/deckStack.h"
#include "../../cardAPI/player.h"

void automateBlackJack() {

    DeckStack deckStack;
    initialiseFullDeckStack(&deckStack, DECKSUSED);

    DeckStack usedDeckStack;
    initialiseEmptyDeckStack(&usedDeckStack, DECKSUSED);


    BlackJackPlayer player;
    initialiseBlackJackPlayer(&player, "Player");

    BlackJackPlayer dealer;
    initialiseBlackJackPlayer(&dealer, "Dealer");

    int playerWins = 0;
    int dealerWins = 0;
    int draws = 0;
    int gamesToPlay = 1000000;

    for (int i = 0; i < gamesToPlay; i++) {
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
        } else if (playerBust) {
            dealerWins++;
        } else {

            if (doesPlayerHaveBlackJack(&player) && doesPlayerHaveBlackJack(&dealer)) {
                draws++;
            } else if (doesPlayerHaveBlackJack(&player)) {
                playerWins++;
            } else if (doesPlayerHaveBlackJack(&dealer)) {
                dealerWins++;
            } else {
                if (player.score > dealer.score) {
                    playerWins++;
                } else if (dealer.score > player.score) {
                    dealerWins++;
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
    }

    printf("\n\nIn %i games, using the advised strategy the player won %i times, dealer won %i times and there was %i draws.\n\n", gamesToPlay, playerWins, dealerWins, draws);
}