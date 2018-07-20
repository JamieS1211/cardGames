//
// Created by Jamie on 29/12/2017.
//

#include <stdio.h>

#include "generalAPI/userInput.h"
#include "blackJack/game/playBlackJack.h"
#include "blackJack/game/automateBlackJack.h"
#include "blackJack/cardCount/cardCountBlackJack.h"
#include "blackJack/mapping.h"

int main() {

    setbuf(stdout, 0); //Required so CLion shows tezt output when running in debug mode


    while (1) {
        printf("Please select an option? \n"
                       "\t1: Play BlackJack \n"
                       "\t2: Card Count BlackJack \n"
                       "\t3: Automate BlackJack \n"
                       "\t4: Run mapping \n"
                       "\t5: Exit \n");


        long option = getIntegerUserInput();

        if (option == 1) {
            playBlackJack();
        } else if (option == 2) {
            cardCountBlackJack();
        } else if (option == 3) {

            void automateBlackJack(int gamesSets, int gamesPerSet, float startBalance, float minBet, float maxBet, float riskFactor);

            int gameSets = 20;
            int gamesPerSet = 1000;

            float startBalance = 10000;
            float minBet = 0.1;
            float maxBet = 1000;

            //Lower value is less risk (values lower then 0.02 are required)
            float riskFactor = 0.005;

            automateBlackJack(gameSets, gamesPerSet, startBalance, minBet, maxBet, riskFactor);
        } else if (option == 4) {
            int setsPerTest = 1;
            int gamesPerSet = 1000;

            findMapping(setsPerTest, gamesPerSet);
        } else if (option == 5) {
            printf("Program will exit. \n");
            break;
        } else {
            printf("What was entered was not a valid option, please try again. \n");
        }
    }
}