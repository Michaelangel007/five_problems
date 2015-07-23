/*
Problem 1

Write three functions that compute the sum of the numbers in a given list using a for-loop, a while-loop, and recursion.
*/
#include <stdio.h>

int sum1( int n, int data[] )
{
    int sum = 0;

    for( int i = 0; i <  n; i++ )
        sum += data[i];

    return sum;
}

int sum2( int n, int data[] )
{
   int sum = 0;

    while( n --> 0 )
        sum += data[n];

    return sum;
}

int sum3( int n, int data[] )
{
    if( n < 0 )
        return 0;

    return data[ n-1 ] +  sum3( n-1, data );
}

int main()
{
    int DATA[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
    int SIZE   = sizeof( DATA ) / sizeof( DATA[0] );

    int s1 = sum1( SIZE, DATA );
    printf( "Sum: %d\n", s1 );

    int s2 = sum2( SIZE, DATA );
    printf( "Sum: %d\n", s2 );

    int s3 = sum3( SIZE, DATA );
    printf( "Sum: %d\n", s3 );

    return 0;
}
