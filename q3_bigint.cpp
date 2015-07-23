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
#include <stdlib.h> // exit

// BigInt in base 10
struct bigint
{
    size_t _size;
    char  *_data;

    bigint( int n, size_t size = 32 ) {
        _size = size;
        _data = new char[ size + 1 ];
        _data[ size ] = 0;
        memset( _data, '0', size );
        if( n )
            init( n );
    }

    bigint& operator =( const bigint & rhs )
    {
        memcpy( _data, rhs._data, _size );
        return *this;
    }

    void init( int n )
    {
        char *p = _data + _size - 1;
        while( n >= 10 )
        {
            *p-- = '0' + (n %  10);
                          n /= 10;
        }
        *p = '0' + n;
    }

    char* print()
    {
        char *p = _data;
        char *e = _data + _size - 1;
        while ((p < e) && (*p == '0'))
            p++;
        return p;
    }

    bigint& operator += ( const bigint & rhs )
    {
        char *src   = rhs._data + rhs._size - 1;
        char *dst   =     _data +     _size - 1;
        char  carry = 0;

        while (dst > _data)
        {
            carry = (*src - '0') + (*dst - '0') + carry;
            if( carry >= 10 )
            {
                *dst = '0' + (carry %  10);
                              carry /= 10;
            }
            else
            {
                *dst = '0' + carry;
                carry = 0;
            }

            src--;
            dst--;
        }
        return *this;
    }
};



char* sprint_u128( __uint128_t x )
{
    static char buffer[64];
    /* */  char*p = buffer + sizeof(buffer) - 1;
    *p-- = 0;
    if( !x )
    {
        *p = '0';
        return p;
    }

    while( x > 0 )
    {
        *p-- = "0123456789"[x % 10];
        x /= 10;
    }
    return p+1;
}

// F0=0, F1=1
// signed   32-bit sum overflows pre sumF46 =              1,836,311,903
// unsigned 32-bit sum overflows pre sumF47 =              2,971,215,073
// signed   64-bit sum overflows pre sumF90 =  7,540,113,804,746,346,429
// unsigned 64-bit sum overflows pre sumF91 = 12,200,160,415,121,876,738
__uint128_t fibonacci_int( int n )
{
    if( n < 2)
        return n;

    __uint128_t fib1 = 0; // F0
    __uint128_t fib2 = 1; // F1
    __uint128_t temp = 0; // Fn = Fn-1 + Fn-2
    __uint128_t sum     ;

    for( int i = 1; i < n; i++ )
    {
        sum  = fib1 + fib2;
        fib1 = fib2;
        fib2 = sum;
    }
    return sum;
}

bigint fibonacci_big( int n )
{
    bigint fib1( 0 );
    bigint fib2( 1 );
    bigint sum ( 0 );

    if( n == 0 ) return fib1;
    if( n == 1 ) return fib2;

    for( int i = 1; i < n; i++ )
    {
        sum  = fib1;
        sum += fib2;
        fib1 = fib2;
        fib2 = sum;
    }
    return sum;
}


int fib( int n )
{
    if (n < 2)
        return n;

    int fib1 = 0; // F0
    int fib2 = 1; // F1
    int sum     ; // Fn = Fn-1 + Fn-2

printf( " %d, ", fib1 );
    for( int i = 1; i < n; i++ )
    {
printf( "%d, ", fib2 );
        sum   = fib1 + fib2;
        fib1  = fib2;
        fib2  = sum;
    }
printf( " = %d\n", sum );
    return sum;
}

int main()
{
    int n = 10;

    //int f = fib( n );
    //printf( "Fib #%d: %d\n", n, f );
    //for( int i = 0; i < 10; i++ )
    //    printf( "Fib #%d:  Sum: %d\n", i, fib(i) );

    //int i = 7;
    //printf( "Fib #%d: %s\n", i, fibonacci_big(i).print() );

    for( int i = 0; i < 100; i++ )
        printf( "Fib #%2d:  Sum: %s\n", i, fibonacci_big(i).print() );

//    bigint t( 1 );
//    printf( "%s\n", t.print() );

#if 0
    bool s32 = 0;
    bool u32 = 0;
    bool s64 = 0;
    bool u64 = 0;

    for( int i = 0; i < 100; i++ )
    {
        __uint128_t sum = fibonacci_int( i );

if( !s32 && (sum > ((__uint128_t)1ULL) << 31)) { s32 = 1; printf( " @ Fib s32: #%d\n", i ); }
if( !u32 && (sum > ((__uint128_t)1ULL) << 32)) { u32 = 1; printf( " @ Fib u32: #%d\n", i ); }
if( !s64 && (sum > ((__uint128_t)1ULL) << 63)) { s64 = 1; printf( " @ Fib s64: #%d\n", i ); }
if( !u64 && (sum > ((__uint128_t)1ULL) << 64)) { u64 = 1; printf( " @ Fib u64: #%d\n", i ); }

        printf( "Fib #%d: %s\n", i, sprint_u128( sum ) );
    }
#endif

    return 0;
}
