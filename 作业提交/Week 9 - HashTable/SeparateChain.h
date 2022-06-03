#ifndef separate_chain
#define separate_chain

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

int nextPrime (int N)
{
    if (N % 2 == 0)
        ++N;
    int i;
    bool NotPrime = false;
    for (; ; N += 2){
        NotPrime = true;
        for (i = 3; i*i <= N; i+=2)
            if (N % i == 0)
            {
                NotPrime = true;
                break;
            }
        if (!NotPrime)
            return N;
    }
}

template <typename T>
class Hash
{
  public:
    explicit Hash( int size = 200000 ) : currentSize{ 0 }
      { theLists.resize( 200000 ); }

    bool contains( const T & x ) const
    {
        auto & whichList = theLists[ myhash( x ) ];
        return find( begin( whichList ), end( whichList ), x ) != end( whichList );
    }

    void makeEmpty( )
    {
        for( auto & thisList : theLists )
            thisList.clear( );
    }

    bool insert( const T & x )
    {
        auto & whichList = theLists[ myhash( x ) ];
        if( find( begin( whichList ), end( whichList ), x ) != end( whichList) )
            return false;
        whichList.push_back( x );

        if( ++currentSize > theLists.size( ) )
            rehash( );

        return true;
    }
    
    bool insert( T && x )
    {
        auto & whichList = theLists[ myhash( x ) ];      
        if( find( begin( whichList ), end( whichList ), x ) != end( whichList ) )
            return false;
        whichList.push_back( std::move( x ) );

        if( ++currentSize > theLists.size( ) )
            rehash( );

        return true;
    }

    bool remove( const T & x )
    {
        auto & whichList = theLists[ myhash( x ) ];
        auto itr = find( begin( whichList ), end( whichList ), x );

        if( itr == end( whichList ) )
            return false;

        whichList.erase( itr );
        --currentSize;
        return true;
    }

  private:
    vector<list<T>> theLists;   //动态数组，里面全是链表
    int  currentSize;

    void rehash( )
    {
        vector<list<T>> oldLists = theLists;

            // 创建新的散列
        theLists.resize( nextPrime( 2 * theLists.size( ) ) );
        for( auto & thisList : theLists )
            thisList.clear( );

            // Copy table over
        currentSize = 0;
        for( auto & thisList : oldLists )
            for( auto & x : thisList )
                insert( std::move( x ) );
    }

    size_t myhash( const T & x ) const
    {
        static hash<T> hf;
        return hf( x ) % theLists.size( );
    }
};

#endif