/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include "math.h"
#include "testing/SimpleTest.h"
using namespace std;

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. n is positive.
 * To find divisors a loop iterates over the numbers from 1 to sqrt(n+1),
 * testing for a zero remainder from the division.
 * A divisor smaller than sqrt(n) must accompanied by a divisor
 * greater than sqrt(n). We measure the number of divisors
 * smaller than sqrt(n) as i. And find the accompanied divisors greater
 * than sqrt(n) from a loop iterates over the numbers from sqrt(n)+1 to n-1,
 * and countting the number of accompanied divisors as j.
 * if i == j, stop the loop. Add all divisors to total in the two loops.
 */
long smarterSum(long n) {
    /* TODO: Fill in this function. */
    long total = 0;
    int i = 0;         //i the number of divisors smaller than sqrt(n)
    int j = 0;         //j the number of accompanied divisors greater than sqrt(n)

    if (n <=1){
        return 0;
    }
    else{
        for (long divisor = 1; divisor < sqrt(n+1); divisor++) {
            if (n % divisor == 0) {
                total += divisor;
                i++;
            }
        }

        for (long rdivisor = sqrt(n)+1; rdivisor < n; rdivisor++) {
            if (n % rdivisor == 0) {
                total += rdivisor;
                j++;
                if (j==i-1){
                    break;
                }
            }
        }
    }

    return total;

}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfectSmarter(long n) {
    /* TODO: Fill in this function. */
    return (n != 0) && (n == smarterSum(n));
    //return false;
}

/*  This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfectsSmarter(long stop) {
     /* TODO: Fill in this function. */
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function takes one argument `n` and calculates the nth perfect number
 * by the method of Euclidean optimization. Here, n is positive.
 *
 * m = pow(2,k)-1, if the number m is a prime number, the number pow(2,k-1)*m is a perfect number.
 * To find nth perfect number, we first initialize the number k =1;
 * Calculte m = pow(2,k)-1; and use divisorSum(m) to make sure that m is a prime number or not.
 * if m is a prime number, we found that the number pow(2,k-1)*m is a perfect number
 * we use Nth in a loop the check whether Nth is equal to n,
 * if Nth == n, output found Nth perfect number.
 *
 */
long findNthPerfectEuclid(long n) {
    /* TODO: Fill in this function. */
    int Nth = 0;
    long m = 0;
    long NthperfectNumber =0;
    if (n <=0){
        cout << "ERROR: n should not smaller than 0" << endl;
        return 0;
    }
    else{
        for (int k = 1; Nth < n; k++){
             m = pow(2,k)-1;
            if (divisorSum(m) == 1){
               Nth++;
               NthperfectNumber = pow(2,k-1)*m;
               if (Nth == n){
                   cout << "Found " << Nth << "th perfect number: " << NthperfectNumber << endl;
               }
            }
        }
    }
    return NthperfectNumber;
}


/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10000, findPerfects(10000));
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
}

//TODO: add your student test cases here
STUDENT_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10, findPerfects(10));
    TIME_OPERATION(1000, findPerfects(1000));
    TIME_OPERATION(2000, findPerfects(2000));
    TIME_OPERATION(80000, findPerfects(80000));
}

STUDENT_TEST("Confirm -1 and -10000 are not perfect") {
    EXPECT(!isPerfect(-1));
    EXPECT(!isPerfect(-10000));
}

STUDENT_TEST("Confirm smarterSum of small inputs") {
    EXPECT_EQUAL(smarterSum(1), 0);
    EXPECT_EQUAL(smarterSum(6), 6);
    EXPECT_EQUAL(smarterSum(25), divisorSum(25));
    EXPECT_EQUAL(smarterSum(-6), divisorSum(-6));
    EXPECT_EQUAL(smarterSum(0), divisorSum(0));
}


STUDENT_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfectSmarter(6));
    EXPECT(isPerfectSmarter(28));
}

STUDENT_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfectSmarter(12));
    EXPECT(!isPerfectSmarter(98765));
}

STUDENT_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfectSmarter(0));
    EXPECT(!isPerfectSmarter(1));
}

STUDENT_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfectSmarter(33550336));
}

STUDENT_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(20000, findPerfectsSmarter(20000));
    TIME_OPERATION(40000, findPerfectsSmarter(40000));
    TIME_OPERATION(80000, findPerfectsSmarter(80000));
}


STUDENT_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
    TIME_OPERATION(80000, findPerfects(80000));
}

STUDENT_TEST("findNthPerfectEuclid(5) are perfect") {
    EXPECT(isPerfect(findNthPerfectEuclid(1)));
    EXPECT(isPerfect(findNthPerfectEuclid(5)));
}

STUDENT_TEST("findNthPerfectEuclid(0), and (-1) are not perfect") {
    EXPECT(!isPerfect(findNthPerfectEuclid(0)));
    EXPECT(!isPerfect(findNthPerfectEuclid(-1)));
}

STUDENT_TEST("Confirm findNthPerfectEuclid(n) of small inputs") {
    EXPECT_EQUAL(findNthPerfectEuclid(1), 6);
    EXPECT_EQUAL(findNthPerfectEuclid(2), 28);
    EXPECT_EQUAL(findNthPerfectEuclid(3), 496);
    EXPECT_EQUAL(findNthPerfectEuclid(4), 8128);
    EXPECT_EQUAL(findNthPerfectEuclid(5), 33550336);
}

