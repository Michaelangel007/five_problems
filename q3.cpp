/*
https://blog.svpino.com/2015/05/07/five-programming-problems-every-software-engineer-should-be-able-to-solve-in-less-than-1-hour
Problem 3

Write a function that computes the list of the first 100 Fibonacci numbers. By definition, the first two numbers in the Fibonacci sequence are 0 and 1, and each subsequent number is the sum of the previous two. As an example, here are the first 10 Fibonnaci numbers: 0, 1, 1, 2, 3, 5, 8, 13, 21, and 34.

F99 = 218,922,995,834,555,169,026

Solutions:

1. Use 128-bit number
2. Use a "big int"

*/

#include <stdio.h>
#include <stdint.h>
#include <string.h> // memcpy

// F0=0, F1=1
// signed   32-bit sum overflows pre sumF46 =              1,836,311,903
// unsigned 32-bit sum overflows pre sumF47 =              2,971,215,073
// signed   64-bit sum overflows pre sumF90 =  7,540,113,804,746,346,429
// unsigned 64-bit sum overflows pre sumF91 = 12,200,160,415,121,876,738
int fibonacci( int n )
{
    if (n < 2)
        return n;

    int fib1 = 0; // F0
    int fib2 = 1; // F1
    int sum     ; // Fn = Fn-1 + Fn-2

//printf( " %d, ", fib1 );
    for( int i = 1; i < n; i++ )
    {
//printf( "%d, ", fib2 );
        sum   = fib1 + fib2;
        fib1  = fib2;
        fib2  = sum;
    }
//printf( " = %d\n", sum );
    return sum;
}

int main()
{
    int n = 47;
    for( int i = 0; i < n; i++ )
        printf( "Fib #%d:  Sum: %d\n", i, fibonacci(i) );

    return 0;
}
