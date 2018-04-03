//
// Created by Jamie on 11/01/2018.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "largeNumber.h"

/**
 * A function that initialises and returns a large number to a given length with value of 0
 * @param length        The length to initialise the large number
 * @return              The freshly initialised number
 */
LargeNumber initialiseLargeNumber(int length) {
    LargeNumber number;
    number.length = length;

    number.digits = malloc(number.length * sizeof(int));
    for (int i = 0; i < number.length; i++) {
        number.digits[i] = 0;
    }

    return number;
}

/**
 * A function that returns a copy of a large number
 * @param number        The large number to copy
 * @return              Copy of the large number
 */
LargeNumber getCopyOfLargeNumber(LargeNumber number) {
    LargeNumber copy = initialiseLargeNumber(number.length);

    copy.digits = malloc(copy.length * sizeof(int));

    for (int i = 0; i < copy.length; i++) {
        copy.digits[i] = number.digits[i];
    }

    return copy;
}

/**
 * A function that prints a large number
 * @param number        The large number to print
 */
void printLargeNumber(LargeNumber number) {
    for (int digit = number.length - 1; digit >= 0; digit--) {
        printf("%i", number.digits[digit]);
    }
}

/**
 * A function to complete forwards and backwards carry operations on a large number
 * @param largeNumberPointer    Pointer to the large number to perform the carry operations
 */
void completeCarryAction(LargeNumber *largeNumberPointer) {
    for (int digit = 0; digit < largeNumberPointer->length; digit++) {
        if (largeNumberPointer->digits[digit] >= NumberOfValuesInSlot) {

            // If not enough space add more
            if (digit + 1 >= largeNumberPointer->length) {
                largeNumberPointer->length = digit + 2;
                largeNumberPointer->digits = realloc(largeNumberPointer->digits, largeNumberPointer->length * sizeof(int));
                largeNumberPointer->digits[digit + 1] = 0;
            }

            largeNumberPointer->digits[digit + 1] += ((largeNumberPointer->digits[digit] - (largeNumberPointer->digits[digit] % NumberOfValuesInSlot)) /
                                             NumberOfValuesInSlot);
            largeNumberPointer->digits[digit] %= NumberOfValuesInSlot;

        } if (largeNumberPointer->digits[digit] < 0 && largeNumberPointer->length > digit + 1) {
            int adjustment = ((largeNumberPointer->digits[digit] * - 1) / NumberOfValuesInSlot) + 1;
            largeNumberPointer->digits[digit + 1] -= adjustment;
            largeNumberPointer->digits[digit] += NumberOfValuesInSlot * adjustment;
        }
    }

    trimLargeNumber(largeNumberPointer);
}

/**
 * A function to remove the extra zeroes from the start of a large number
 * @param largeNumberPointer    Pointer to the large number to perform the trim operation
 */
void trimLargeNumber(LargeNumber *largeNumberPointer) {
    for (int digit = largeNumberPointer->length - 1; digit >= 0; digit--) {
        if (largeNumberPointer->digits[digit] > 0) {
            largeNumberPointer->length = digit + 1;
            largeNumberPointer->digits = realloc(largeNumberPointer->digits, largeNumberPointer->length * sizeof(int));
            break;
        }
    }
}

/**
 * A function to cast a integer to a large number
 * @param integer           The integer to cast to a large number
 * @return                  The large number representing the integer
 */
LargeNumber castLargeNumberFromInt(int integer) {
    LargeNumber output;

    output.length = (logl(integer) / logl(NumberOfValuesInSlot)) + 1;
    output.digits = malloc(output.length * sizeof(int));

    for (int i = 0; i < output.length; i++) {
        output.digits[i] = integer % NumberOfValuesInSlot;
        integer /= NumberOfValuesInSlot;
    }

    return output;
}

/**
 * A function that takes two large numbers and returns if the first is larger then second
 * @param a                 The first large number
 * @param b                 The second large number
 * @return                  If the first is bigger then second (1) [if equal (2)] if second bigger (0)
 */
int isFirstBiggerThanSecond(LargeNumber a, LargeNumber b) {
    if (a.length > b.length) {
        return 1;
    } else if (a.length < b.length) {
        return 0;
    } else {

        for (int i = a.length - 1; i >= 0; i--) {
            if (a.digits[i] > b.digits[i]) {
                return 1;
            } else if (a.digits[i] < b.digits[i]) {
                return 0;
            }
        }

        return 2;
    }
}

/**
 * A function that adds two large numbers
 * @param a                 The first large number
 * @param b                 The second large number
 * @return                  The sum of the two large numbers
 */
LargeNumber addLargeNumbers(LargeNumber a, LargeNumber b) {
    LargeNumber output = getCopyOfLargeNumber(a);
    LargeNumber smallerNumber = getCopyOfLargeNumber(b);

    if (isFirstBiggerThanSecond(a, b) == 0) {
        output = getCopyOfLargeNumber(b);
        smallerNumber = getCopyOfLargeNumber(a);
    }

    for (int digit = 0; digit < smallerNumber.length; digit++) {
        output.digits[digit] += smallerNumber.digits[digit];
    }

    completeCarryAction(&output);

    return output;
}

/**
 * A function that subtracts two large numbers (smaller from larger)
 * @param a                 The first large number
 * @param b                 The second large number
 * @return                  The smaller number subtracted from the larger number
 */
LargeNumber subtractLargeNumbers(LargeNumber a, LargeNumber b) {
    LargeNumber output = getCopyOfLargeNumber(a);
    LargeNumber smallerNumber = getCopyOfLargeNumber(b);

    if (isFirstBiggerThanSecond(a, b) == 0) {
        output = getCopyOfLargeNumber(b);
        smallerNumber = getCopyOfLargeNumber(a);
    }

    for (int digit = 0; digit < smallerNumber.length; digit++) {
        output.digits[digit] -= smallerNumber.digits[digit];
    }

    completeCarryAction(&output);

    return output;
}

/**
 * A function that multiplies two large numbers
 * @param a                 The first large number
 * @param b                 The second large number
 * @return                  The multiplication of the two large numbers
*/
LargeNumber multiplyLargeNumbers(LargeNumber a, LargeNumber b) {

    LargeNumber largerNumber = getCopyOfLargeNumber(a);
    LargeNumber smallerNumber = getCopyOfLargeNumber(b);

    if (isFirstBiggerThanSecond(a, b) == 0) {
        largerNumber = getCopyOfLargeNumber(b);
        smallerNumber = getCopyOfLargeNumber(a);
    }

    LargeNumber output = initialiseLargeNumber(largerNumber.length + smallerNumber.length);

    for (int smallDigit = 0; smallDigit < smallerNumber.length; smallDigit++) {
        for (int largeDigit = 0; largeDigit < largerNumber.length; largeDigit++) {
            output.digits[largeDigit + smallDigit] += largerNumber.digits[largeDigit] * smallerNumber.digits[smallDigit];
        }

        completeCarryAction(&output);
    }

    trimLargeNumber(&output);

    return output;
}


//TODO URGENT - Optimise so that it is not iterative subtraction
/**
 * A function that divides two large numbers (larger by smaller)
 * @param a                 The first large number
 * @param b                 The second large number
 * @return                  The larger number divided by the smaller number
*/
LargeNumber divideLargeNumbers(LargeNumber a, LargeNumber b) {
    LargeNumber largerNumber = getCopyOfLargeNumber(a);
    LargeNumber smallerNumber = getCopyOfLargeNumber(b);

    if (isFirstBiggerThanSecond(a, b) == 0) {
        largerNumber = getCopyOfLargeNumber(b);
        smallerNumber = getCopyOfLargeNumber(a);
    }

    LargeNumber output = initialiseLargeNumber(largerNumber.length + smallerNumber.length);

    while (isFirstBiggerThanSecond(largerNumber, smallerNumber) != 0) {
        largerNumber = subtractLargeNumbers(largerNumber, smallerNumber);
        output = addLargeNumbers(output, castLargeNumberFromInt(1));
    }

    return output;
}