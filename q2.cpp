/*
Write a function that combines two lists by alternatingly taking elements. For example: given the two lists [a, b, c] and [1, 2, 3], the function should return [a, 1, b, 2, c, 3].
*/
#include <stdio.h>
#include <string.h>

struct list
{
    size_t _size;
    char  *_data;

    list( size_t size = 0, const char *init = NULL )
    {
        _data = 0;
        _size = size;
        if( size )
            alloc( size );
        if( init )
            memcpy( _data, init, size );
    }

    ~list()
    {
        free();
    }

    void alloc( size_t size )
    {
        _size = size;
        _data = new char [ size ];
    }

    void free()
    {
        delete [] _data;
    }

    void dump() const
    {
        printf( "Size: %u: ", (unsigned) _size );
        print();
    }

    void print() const
    {
        for( size_t i = 0; i < _size; i++ )
            printf( "%c, ", _data[ i ] );
        printf( "\n" );
    }

    friend void add( list & sum, const list & lhs, const list & rhs )
    {
//lhs.dump();
//rhs.dump();
        if( sum._size )
            sum.free();

        sum.alloc( lhs._size + rhs._size );

        for( size_t i = 0; i < lhs._size; i++ )
        {
            sum._data[ i*2 + 0 ] = lhs._data[ i ];
            sum._data[ i*2 + 1 ] = rhs._data[ i ];
        }
//sum.dump();
    }
};

int main()
{
    list a( 3, "abc" );
    list b( 3, "123" );
    list c;

    add( c, a, b );
    c.print();

    return 0;
}
