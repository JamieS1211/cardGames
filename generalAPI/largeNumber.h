//
// Created by Jamie on 11/01/2018.
//

#define NumberOfValuesInSlot 10000

typedef struct largeNumber {
    int length;
    int *digits;
} LargeNumber;


/**
 * A function that initialises and returns a large number to a given length with value of 0
 * @param length        The length to initialise the large number
 * @return              The freshly initialised number
 */
LargeNumber initialiseLargeNumber(int length);

/**
 * A function that returns a copy of a large number
 * @param number        The large number to copy
 * @return              Copy of the large number
 */
LargeNumber getCopyOfLargeNumber(LargeNumber number);

/**
 * A function that prints a large number
 * @param number        The large number to print
 */
void printLargeNumber(LargeNumber number);

/**
 * A function to complete forwards and backwards carry operations on a large number
 * @param largeNumberPointer    Pointer to the large number to perform the carry operations
 */
void completeCarryAction(LargeNumber *largeNumberPointer);

/**
 * A function to remove the extra zeroes from the start of a large number
 * @param largeNumberPointer    Pointer to the large number to perform the trim operation
 */
void trimLargeNumber(LargeNumber *largeNumberPointer);

/**
 * A function to cast a integer to a large number
 * @param integer           The integer to cast to a large number
 * @return                  The large number representing the integer
 */
LargeNumber castLargeNumberFromInt(int integer);

/**
 * A function that adds two large numbers
 * @param a                 The first large number
 * @param b                 The second large number
 * @return                  The sum of the two large numbers
 */
LargeNumber addLargeNumbers(LargeNumber a, LargeNumber b);

/**
 * A function that subtracts two large numbers (smaller from larger)
 * @param a                 The first large number
 * @param b                 The second large number
 * @return                  The smaller number subtracted from the larger number
 */
LargeNumber subtractLargeNumbers(LargeNumber a, LargeNumber b);

/**
 * A function that multiplies two large numbers
 * @param a                 The first large number
 * @param b                 The second large number
 * @return                  The multiplication of the two large numbers
*/
LargeNumber multiplyLargeNumbers(LargeNumber a, LargeNumber b);

/**
 * A function that divides two large numbers (larger by smaller)
 * @param a                 The first large number
 * @param b                 The second large number
 * @return                  The larger number divided by the smaller number
*/
LargeNumber divideLargeNumbers(LargeNumber a, LargeNumber b);