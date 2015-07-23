/*
    g++ -Wall -Wextra q4_int.cpp

https://blog.svpino.com/2015/05/07/five-programming-problems-every-software-engineer-should-be-able-to-solve-in-less-than-1-hour

Problem 4

Write a function that given a list of non negative integers, arranges them such that they form the largest possible number. For example, given [50, 2, 1, 9], the largest formed number is 95021.

Note: The author's solution doesn't even work
https://blog.svpino.com/2015/05/08/solution-to-problem-4
*/
#include <stdio.h>

// http://stackoverflow.com/questions/3068397/finding-the-length-of-an-integer-in-c
// Equivalent to: 1 + log10(x)
int num_digits( int x )
{
    int digits = 1;
    while( x >= 10 )
    {
        digits++;
        x /= 10;
    }
    return digits;
}

// Note: will overflow on 21! as largest 64-bit is 20! = 18,446,744,073,709,551,615
// For GMP solution: http://stackoverflow.com/questions/19230573/cannot-calculate-factorials-bigger-than-20-how-to-do-so
int factorial( int n )
{
    int result = 1; // mpz_set_ui( result, 1 );
    if( n < 2 )
        return result;
    while( n > 1 )
    {
        result *= n; // mpz_mul_ui(result, result, n)
        n--;
    }
    return result;
}

int largest_combination( size_t size, int data[] )
{
    int *aComb = new int[ size ]; // temp set
    int  nComb = factorial( size );
    int  nBest = 0;

printf( "Combinations: %u\n", nComb );

    // There are n! combinations
    // Enumerate each factoradic -- see https://en.wikipedia.org/wiki/Factorial_number_system
    for( int iComb = 0; iComb < nComb; iComb++ )
    {
        // Reset temp set
        for( size_t t = 0; t < size; t++ ) // memcpy()
            aComb[ t ] = data[ t ];

        int base = size;
printf( "Combination: #%u\n", iComb );

        int x = iComb;
        int digit;
        int concat = 0;

        // convert factoradic to actual combination
        for( size_t iDigit = 0; iDigit < size; iDigit++    )
        {
            digit = x % base;
            x    /=     base;
            base--;

            int n     = aComb[ digit ];
            int nTens = num_digits( n );
            for( int iTens = 0; iTens < nTens; iTens++ )
                concat *= 10;
            concat += n;
printf( " [%u]: %3u -> sum: %u\n", digit, n, concat );
            // combination: remove this element from the set
            aComb[ digit ] = aComb[ base ];
        }
printf( "Concatenation: %u\n", concat );
        if( nBest < concat )
            nBest = concat;
    }

    delete [] aComb;
    return nBest;
}

int main()
{
    //int  DATA[] = { 50,  2,   1, 9 }; // 9+50+2+1
    //int  DATA[] = {  5, 50,  56    }; // 56+5+50
    //int  DATA[] = {420, 42, 423    }; // 42+423+420
      int  DATA[] = { 52,  5,   3    }; // 5+52+3
    //int  DATA[] = {  1,  2,   3    }; // 3+2+1
    size_t SIZE   = sizeof( DATA ) / sizeof( DATA[0] );

    int n = largest_combination( SIZE, DATA );
    printf( "Largest: %d\n", n );

    return 0;
}


/*

Combinations: 24
Combination: #0
 [0]:  50 -> sum: 50
 [0]:   9 -> sum: 509
 [0]:   1 -> sum: 5091
 [0]:   2 -> sum: 50912
Concatenation: 50912
Combination: #1
 [1]:   2 -> sum: 2
 [0]:  50 -> sum: 250
 [0]:   1 -> sum: 2501
 [0]:   9 -> sum: 25019
Concatenation: 25019
Combination: #2
 [2]:   1 -> sum: 1
 [0]:  50 -> sum: 150
 [0]:   9 -> sum: 1509
 [0]:   2 -> sum: 15092
Concatenation: 15092
Combination: #3
 [3]:   9 -> sum: 9
 [0]:  50 -> sum: 950
 [0]:   1 -> sum: 9501
 [0]:   2 -> sum: 95012
Concatenation: 95012
Combination: #4
 [0]:  50 -> sum: 50
 [1]:   2 -> sum: 502
 [0]:   9 -> sum: 5029
 [0]:   1 -> sum: 50291
Concatenation: 50291
Combination: #5
 [1]:   2 -> sum: 2
 [1]:   9 -> sum: 29
 [0]:  50 -> sum: 2950
 [0]:   1 -> sum: 29501
Concatenation: 29501
Combination: #6
 [2]:   1 -> sum: 1
 [1]:   2 -> sum: 12
 [0]:  50 -> sum: 1250
 [0]:   9 -> sum: 12509
Concatenation: 12509
Combination: #7
 [3]:   9 -> sum: 9
 [1]:   2 -> sum: 92
 [0]:  50 -> sum: 9250
 [0]:   1 -> sum: 92501
Concatenation: 92501
Combination: #8
 [0]:  50 -> sum: 50
 [2]:   1 -> sum: 501
 [0]:   9 -> sum: 5019
 [0]:   2 -> sum: 50192
Concatenation: 50192
Combination: #9
 [1]:   2 -> sum: 2
 [2]:   1 -> sum: 21
 [0]:  50 -> sum: 2150
 [0]:   9 -> sum: 21509
Concatenation: 21509
Combination: #10
 [2]:   1 -> sum: 1
 [2]:   9 -> sum: 19
 [0]:  50 -> sum: 1950
 [0]:   2 -> sum: 19502
Concatenation: 19502
Combination: #11
 [3]:   9 -> sum: 9
 [2]:   1 -> sum: 91
 [0]:  50 -> sum: 9150
 [0]:   2 -> sum: 91502
Concatenation: 91502
Combination: #12
 [0]:  50 -> sum: 50
 [0]:   9 -> sum: 509
 [1]:   2 -> sum: 5092
 [0]:   1 -> sum: 50921
Concatenation: 50921
Combination: #13
 [1]:   2 -> sum: 2
 [0]:  50 -> sum: 250
 [1]:   9 -> sum: 2509
 [0]:   1 -> sum: 25091
Concatenation: 25091
Combination: #14
 [2]:   1 -> sum: 1
 [0]:  50 -> sum: 150
 [1]:   2 -> sum: 1502
 [0]:   9 -> sum: 15029
Concatenation: 15029
Combination: #15
 [3]:   9 -> sum: 9
 [0]:  50 -> sum: 950
 [1]:   2 -> sum: 9502
 [0]:   1 -> sum: 95021
Concatenation: 95021
Combination: #16
 [0]:  50 -> sum: 50
 [1]:   2 -> sum: 502
 [1]:   1 -> sum: 5021
 [0]:   9 -> sum: 50219
Concatenation: 50219
Combination: #17
 [1]:   2 -> sum: 2
 [1]:   9 -> sum: 29
 [1]:   1 -> sum: 291
 [0]:  50 -> sum: 29150
Concatenation: 29150
Combination: #18
 [2]:   1 -> sum: 1
 [1]:   2 -> sum: 12
 [1]:   9 -> sum: 129
 [0]:  50 -> sum: 12950
Concatenation: 12950
Combination: #19
 [3]:   9 -> sum: 9
 [1]:   2 -> sum: 92
 [1]:   1 -> sum: 921
 [0]:  50 -> sum: 92150
Concatenation: 92150
Combination: #20
 [0]:  50 -> sum: 50
 [2]:   1 -> sum: 501
 [1]:   2 -> sum: 5012
 [0]:   9 -> sum: 50129
Concatenation: 50129
Combination: #21
 [1]:   2 -> sum: 2
 [2]:   1 -> sum: 21
 [1]:   9 -> sum: 219
 [0]:  50 -> sum: 21950
Concatenation: 21950
Combination: #22
 [2]:   1 -> sum: 1
 [2]:   9 -> sum: 19
 [1]:   2 -> sum: 192
 [0]:  50 -> sum: 19250
Concatenation: 19250
Combination: #23
 [3]:   9 -> sum: 9
 [2]:   1 -> sum: 91
 [1]:   2 -> sum: 912
 [0]:  50 -> sum: 91250
Concatenation: 91250
Largest: 95021


Combinations: 6
Combination: #0
 [0]:   5 -> sum: 5
 [0]:  56 -> sum: 556
 [0]:  50 -> sum: 55650
Concatenation: 55650
Combination: #1
 [1]:  50 -> sum: 50
 [0]:   5 -> sum: 505
 [0]:  56 -> sum: 50556
Concatenation: 50556
Combination: #2
 [2]:  56 -> sum: 56
 [0]:   5 -> sum: 565
 [0]:  50 -> sum: 56550
Concatenation: 56550
Combination: #3
 [0]:   5 -> sum: 5
 [1]:  50 -> sum: 550
 [0]:  56 -> sum: 55056
Concatenation: 55056
Combination: #4
 [1]:  50 -> sum: 50
 [1]:  56 -> sum: 5056
 [0]:   5 -> sum: 50565
Concatenation: 50565
Combination: #5
 [2]:  56 -> sum: 56
 [1]:  50 -> sum: 5650
 [0]:   5 -> sum: 56505
Concatenation: 56505
Largest: 56550




Combinations: 6
Combination: #0
 [0]: 420 -> sum: 420
 [0]: 423 -> sum: 420423
 [0]:  42 -> sum: 42042342
Concatenation: 42042342
Combination: #1
 [1]:  42 -> sum: 42
 [0]: 420 -> sum: 42420
 [0]: 423 -> sum: 42420423
Concatenation: 42420423
Combination: #2
 [2]: 423 -> sum: 423
 [0]: 420 -> sum: 423420
 [0]:  42 -> sum: 42342042
Concatenation: 42342042
Combination: #3
 [0]: 420 -> sum: 420
 [1]:  42 -> sum: 42042
 [0]: 423 -> sum: 42042423
Concatenation: 42042423
Combination: #4
 [1]:  42 -> sum: 42
 [1]: 423 -> sum: 42423
 [0]: 420 -> sum: 42423420
Concatenation: 42423420
Combination: #5
 [2]: 423 -> sum: 423
 [1]:  42 -> sum: 42342
 [0]: 420 -> sum: 42342420
Concatenation: 42342420
Largest: 42423420



Combinations: 6
Combination: #0
 [0]:  52 -> sum: 52
 [0]:   3 -> sum: 523
 [0]:   5 -> sum: 5235
Concatenation: 5235
Combination: #1
 [1]:   5 -> sum: 5
 [0]:  52 -> sum: 552
 [0]:   3 -> sum: 5523
Concatenation: 5523
Combination: #2
 [2]:   3 -> sum: 3
 [0]:  52 -> sum: 352
 [0]:   5 -> sum: 3525
Concatenation: 3525
Combination: #3
 [0]:  52 -> sum: 52
 [1]:   5 -> sum: 525
 [0]:   3 -> sum: 5253
Concatenation: 5253
Combination: #4
 [1]:   5 -> sum: 5
 [1]:   3 -> sum: 53
 [0]:  52 -> sum: 5352
Concatenation: 5352
Combination: #5
 [2]:   3 -> sum: 3
 [1]:   5 -> sum: 35
 [0]:  52 -> sum: 3552
Concatenation: 3552
Largest: 5523


Combinations: 6
Combination: #0
 [0]:   1 -> sum: 1
 [0]:   3 -> sum: 13
 [0]:   2 -> sum: 132
Concatenation: 132
Combination: #1
 [1]:   2 -> sum: 2
 [0]:   1 -> sum: 21
 [0]:   3 -> sum: 213
Concatenation: 213
Combination: #2
 [2]:   3 -> sum: 3
 [0]:   1 -> sum: 31
 [0]:   2 -> sum: 312
Concatenation: 312
Combination: #3
 [0]:   1 -> sum: 1
 [1]:   2 -> sum: 12
 [0]:   3 -> sum: 123
Concatenation: 123
Combination: #4
 [1]:   2 -> sum: 2
 [1]:   3 -> sum: 23
 [0]:   1 -> sum: 231
Concatenation: 231
Combination: #5
 [2]:   3 -> sum: 3
 [1]:   2 -> sum: 32
 [0]:   1 -> sum: 321
Concatenation: 321
Largest: 321

*/

