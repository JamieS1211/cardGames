//
// Created by Jamie on 29/12/2017.
//

#include <stdio.h>
#include <omp.h>
#include <afxres.h>
#include <gmp.h>

#include "generalAPI/userInput.h"
#include "blackJack/game/playBlackJack.h"
#include "blackJack/game/automateBlackJack.h"
#include "blackJack/cardCount/cardCountBlackJack.h"
#include "blackJack/mapping.h"

int main() {

    setbuf(stdout, 0); //Required so CLion shows "printf" output when running in debug mode


    //GMP example
    /*
    mpz_t x,y,result;

    mpz_init_set_str(x, "7612058254738945", 10);
    mpz_init_set_str(y, "9263591128439081", 10);
    mpz_init(result);

    mpz_mul(result, x, y);
    gmp_printf("    %Zd\n"
               "*\n"
               "    %Zd\n"
               "--------------------\n"
               "%Zd\n", x, y, result);

    // free used memory
    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(result);

    return 0;*/

    //Multi-threading example
    /*
    double start, end;
    double runTime;
    start = omp_get_wtime();
    int num = 1,primes = 0;

    int limit = 100000;

    #pragma omp parallel for schedule(dynamic) reduction(+ : primes)
    for (num = 1; num <= limit; num++) {
        int i = 2;
        while(i <= num) {
            if(num % i == 0)
                break;
            i++;
        }
        if(i == num)
            primes++;
    }

    end = omp_get_wtime();
    runTime = end - start;
    printf("This machine calculated all %d prime numbers under %d in %g seconds\n",primes,limit,runTime);

    return 0;*/


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
            int gameSets = 1;
            int gamesPerSet = 1000;

            float startBalance = 10000;
            float minBet = 25;
            float maxBet = 1000;

            //Lower value is less risk (values lower then 0.02 are required)
            float riskFactor = 0.007;

            automateBlackJack(gameSets, gamesPerSet, startBalance, minBet, maxBet, riskFactor);
        } else if (option == 4) {
            int setsPerTest = 1;
            int gamesPerSet = 100000;

            findMapping(setsPerTest, gamesPerSet);
        } else if (option == 5) {
            printf("Program will exit. \n");
            break;
        } else {
            printf("What was entered was not a valid option, please try again. \n");
        }
    }
}