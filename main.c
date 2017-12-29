//
// Created by Jamie on 29/12/2017.
//

#include <stdio.h>

#include "generalAPI/userInput.h"
#include "blackJack/game/playBlackJack.h"
#include "blackJack/cardCount/cardCountBlackJack.h"

int main() {
    while (1) {
        printf("Please select an option? \n"
                       "\t1: Play BlackJack \n"
                       "\t2: Card Count BlackJack \n"
                       "\t3: Exit \n");


        long option = getIntegerUserInput();

        if (option == 1) {
            playBlackJack();
        } else if (option == 2) {
            cardCountBlackJack();
        } else if (option == 3) {
            printf("Program will exit. \n");
            break;
        } else {
            printf("What was entered was not a valid option, please try again. \n");
        }
    }
}