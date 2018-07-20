//
// Created by Jamie on 29/12/2017.
//

#include <stdio.h>

#include "generalAPI/userInput.h"
#include "blackJack/game/playBlackJack.h"
#include "blackJack/game/automateBlackJack.h"
#include "blackJack/cardCount/cardCountBlackJack.h"

int main() {

    setbuf(stdout, 0); //Required so CLion shows tezt output when running in debug mode


    while (1) {
        printf("Please select an option? \n"
                       "\t1: Play BlackJack \n"
                       "\t2: Card Count BlackJack \n"
                       "\t3: Automate BlackJack \n"
                       "\t4: Exit \n");


        long option = getIntegerUserInput();

        if (option == 1) {
            playBlackJack();
        } else if (option == 2) {
            cardCountBlackJack();
        } else if (option == 3) {
            automateBlackJack();
        } else if (option == 4) {
            printf("Program will exit. \n");
            break;
        } else {
            printf("What was entered was not a valid option, please try again. \n");
        }
    }
}