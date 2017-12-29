//
// Created by Jamie on 28/12/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long getIntegerUserInput() {

    while (1) {
        char str[256] = {0x0};
        fgets(str, sizeof(str), stdin);
        char *ptr;
        long option = strtol(str, &ptr, 10);

        if (ptr[0] == '\n') {
            return option;
        } else {
            printf("You must enter a numbered value, please try again. \n");
        }
    }
}