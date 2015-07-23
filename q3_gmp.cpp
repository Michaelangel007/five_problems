/*
g++ q3_gmp.cpp -I/usr/local/include -L/usr/local/lib -lgmp
https://blog.svpino.com/2015/05/07/five-programming-problems-every-software-engineer-should-be-able-to-solve-in-less-than-1-hour
Problem 3

Write a function that computes the list of the first 100 Fibonacci numbers. By definition, the first two numbers in the Fibonacci sequence are 0 and 1, and each subsequent number is the sum of the previous two. As an example, here are the first 10 Fibonnaci numbers: 0, 1, 1, 2, 3, 5, 8, 13, 21, and 34.

F99 = 218,922,995,834,555,169,026

Solutions:

1. Use 128-bit number
2. Use a "big int"
   a) GMP
   b) custom big int

*/

#include <stdio.h>
#include <stdint.h>
#include <string.h> // memcpy
#include <gmp.h>

void fibonacci_gmp( int n, mpz_t result )
{
    mpz_t fib1;
    mpz_t fib2;

    mpz_init( fib1   );
    mpz_init( fib2   );

    mpz_set_ui(fib1, 0);
    mpz_set_ui(fib2, 1);

    if( n == 0 ) { mpz_set( result, fib1 ); goto end; }
    if( n == 1 ) { mpz_set( result, fib2 ); goto end; }

    for( int i = 1; i < n; i++ )
    {
        mpz_add( result, fib1, fib2 ); // sum  = fib1 + fib2
        mpz_set( fib1  , fib2       ); // fib1 = fib2;
        mpz_set( fib2  , result     ); // fib2 = sum;
    }
end:
    mpz_clear( fib1 );
    mpz_clear( fib2 );
}

int main()
{
    mpz_t result;
    mpz_init( result );

    int n = 100;
    for( int i = 0; i < n; i++ )
    {
        fibonacci_gmp(i, result );
        printf( "Fib #%2d:  Sum: %s\n", i, mpz_get_str( NULL, 10, result ) );
    }

    mpz_clear( result );
    return 0;
}

