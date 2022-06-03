#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

#include <iostream>
#include <vector>
#include <initializer_list>
#include "dsexceptions.h"
#include "sim_iobtr.h"
using namespace std;

namespace DSAA
{

template <typename T>
class Bqueue
{

private:
    struct BinomialNode
    {
        T    data;
        BinomialNode *lch;
        BinomialNode *nch;

        BinomialNode( const T & e, BinomialNode *lt=nullptr, BinomialNode *rt=nullptr )
          : data{ e }, lch{ lt }, nch{ rt } { }
        
        BinomialNode( T && e, BinomialNode *lt=nullptr, BinomialNode *rt=nullptr )
          : data{ std::move( e ) }, lch{ lt }, nch{ rt } { }
    };

public:
    typedef  BinomialNode    node_type;
    typedef  node_type*      node_ptr;
    typedef  T               value_type;
    typedef  unsigned long   size_type;


private:
    const static int DEFAULT_TREES = 1;
    vector<node_ptr> theTrees;  // An array of tree roots
    int currentSize;                  // Number of items in the priority queue
    
    /***********************************************************************************************
     * Find index of tree containing the smallest item in the priority queue.
     * The priority queue must not be empty.
     * Return the index of tree containing the smallest item.
     ***********************************************************************************************/
    int findMinIndex( ) const
    {
        int i;
        int minIndex;

        // 跳过空树
        for( i = 0; theTrees[ i ] == nullptr; ++i )
            ;

        // 当遇到第一棵非空树的时候开始记录下其堆顶，并且往后不断的跳过空树或者比较堆顶
        for( minIndex = i; i < theTrees.size( ); ++i )
            if( theTrees[ i ] != nullptr &&
                theTrees[ i ]->data < theTrees[ minIndex ]->data )
                minIndex = i;

        return minIndex;
    }

    /***********************************************************************************************
     * Return the capacity.
     * 实际上这是一个等比数列，并且等比为2，所以根据公式容易知道所含有的元素个数
     ***********************************************************************************************/
    int capacity( ) const
      { return ( 1 << theTrees.size() ) - 1; }

    /***********************************************************************************************
     * Return the result of merging equal-sized t1 and t2.
     ***********************************************************************************************/
    node_ptr combineTrees( node_ptr t1, node_ptr t2 )
    {
        if( t2->data < t1->data )
            return combineTrees( t2, t1 );
        t2->nch = t1->lch;
        t1->lch = t2;
        return t1;
    }

    /*********************************************************
     * Make a binomial tree logically empty, and free memory.
     *********************************************************/
    void makeEmpty( node_ptr & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->lch );
            makeEmpty( t->nch );
            delete t;
            t = nullptr;
        }
    }

    /*********************************************************
     * Internal method to clone subtree.
     *********************************************************/
    node_ptr clone( node_ptr t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new node_type{ t->data, clone( t->lch ), clone( t->nch ) };
    }




public:
/******************************** 基础函数 *********************************/
    Bqueue( ) : theTrees( DEFAULT_TREES )
    {
        for( auto & root : theTrees )
            root = nullptr;
        currentSize = 0;
    }

    Bqueue( const T & item ) : theTrees( 1 ), currentSize{ 1 }
      { theTrees[ 0 ] = new node_type{ item, nullptr, nullptr }; }

    Bqueue( const Bqueue & rhs )
      : theTrees( rhs.theTrees.size( ) ),currentSize{ rhs.currentSize }
    { 
        for( int i = 0; i < rhs.theTrees.size( ); ++i )
            theTrees[ i ] = clone( rhs.theTrees[ i ] );
    }

    Bqueue( Bqueue && rhs )
      : theTrees{ std::move( rhs.theTrees ) }, currentSize{ rhs.currentSize }
    {}

    Bqueue(const std::initializer_list<value_type> &v):theTrees(1),currentSize(0)
    {
        for( auto & root : theTrees )
            root = nullptr;

        std::cout<<"test!!"<<endl;

        for(auto it : v)
            insert(it);
    }

    ~Bqueue()
      { makeEmpty(); }

    
public:
    /******************************************************************************
     * Deep copy.
     ******************************************************************************/
    Bqueue & operator=( const Bqueue & rhs )
    {
        Bqueue copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /******************************************************************************
     * Move.
     ******************************************************************************/
    Bqueue & operator=( Bqueue && rhs )
    {
        std::swap( currentSize, rhs.currentSize );
        std::swap( theTrees, rhs.theTrees );
        
        return *this;
    }

    Bqueue & operator=(const initializer_list<value_type> &v)
    {
        for(auto it : v)
            insert(it);
    }
    
    /******************************************************************************
     * Return true if empty; false otherwise.
     ******************************************************************************/
    bool isEmpty( ) const
      { return currentSize == 0; }

    int size() const
        {return currentSize;}

    /******************************************************************************
     * Returns minimum item.
     * Throws UnderflowException if empty.
     ******************************************************************************/
    const value_type & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };

        return theTrees[ findMinIndex( ) ]->data;
    }
    
    /******************************************************************************
     * Insert item x into the priority queue; allows duplicates.
     ******************************************************************************/
    void insert( const value_type & x )
      { Bqueue oneItem(x); merge( oneItem ); }

    void insert( value_type && x )
      { Bqueue oneItem(std::move( x )); merge( oneItem ); }
    
    /******************************************************************************
     * Remove the smallest item from the priority queue.
     * Throws UnderflowException if empty.
     ******************************************************************************/
    void deleteMin( )
    {
        value_type x;
        deleteMin( x );
    }
    void deleteMin( value_type & minItem )
    {
        if( isEmpty( ) )
            throw UnderflowException{ };

        int minIndex = findMinIndex( );
        minItem = theTrees[ minIndex ]->data;

        BinomialNode *oldRoot = theTrees[ minIndex ];
        BinomialNode *deletedTree = oldRoot->lch;
        delete oldRoot;

        // Construct H''
        Bqueue deletedQueue;
        deletedQueue.theTrees.resize( minIndex + 1 );
        deletedQueue.currentSize = ( 1 << minIndex ) - 1;
        for( int j = minIndex - 1; j >= 0; --j )
        {
            deletedQueue.theTrees[ j ] = deletedTree;
            deletedTree = deletedTree->nch;
            deletedQueue.theTrees[ j ]->nch = nullptr;
        }

        // Construct H'
        theTrees[ minIndex ] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;

        merge( deletedQueue );
    }

    /******************************************************************************
     * Make the priority queue logically empty.
     ******************************************************************************/
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & root : theTrees )
            makeEmpty( root );
    }

    /******************************************************************************
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     * Exercise 6.35 needed to make this operation more efficient.
     ******************************************************************************/
    void merge( Bqueue & rhs )
    {
        if( this == &rhs )    // Avoid aliasing problems
            return;

        currentSize += rhs.currentSize;

        if( currentSize > capacity( ) )
        {
            int oldNumTrees = theTrees.size( );
            int newNumTrees = max( theTrees.size( ), rhs.theTrees.size( ) ) + 1;
            theTrees.resize( newNumTrees );
            for( int i = oldNumTrees; i < newNumTrees; ++i )
                theTrees[ i ] = nullptr;
        }

        BinomialNode *carry = nullptr;
        for( int i = 0, j = 1; j <= currentSize; ++i, j *= 2 )
        {
            BinomialNode *t1 = theTrees[ i ];
            BinomialNode *t2 = i < rhs.theTrees.size( ) ? rhs.theTrees[ i ] : nullptr;

            int whichCase = t1 == nullptr ? 0 : 1;
            whichCase += t2 == nullptr ? 0 : 2;
            whichCase += carry == nullptr ? 0 : 4;

            switch( whichCase )
            {
              case 0: /* No trees */
              case 1: /* Only this */
                break;
              case 2: /* Only rhs */
                theTrees[ i ] = t2;
                rhs.theTrees[ i ] = nullptr;
                break;
              case 4: /* Only carry */
                theTrees[ i ] = carry;
                carry = nullptr;
                break;
              case 3: /* this and rhs */
                carry = combineTrees( t1, t2 );
                theTrees[ i ] = rhs.theTrees[ i ] = nullptr;
                break;
              case 5: /* this and carry */
                carry = combineTrees( t1, carry );
                theTrees[ i ] = nullptr;
                break;
              case 6: /* rhs and carry */
                carry = combineTrees( t2, carry );
                rhs.theTrees[ i ] = nullptr;
                break;
              case 7: /* All three */
                theTrees[ i ] = carry;
                carry = combineTrees( t1, t2 );
                rhs.theTrees[ i ] = nullptr;
                break;
            }
        }

        for( auto & root : rhs.theTrees )
            root = nullptr;
        rhs.currentSize = 0;
    }    

    /************************************************************
     * swap()  ： 交换两个二项队列
     ************************************************************/
    void swap( Bqueue<value_type> &rhs)
    {
        std::swap( currentSize, rhs.currentSize );
        std::swap( theTrees, rhs.theTrees );
    }


protected:
    virtual void out(ostream& os, node_ptr ptr) const
    {
        outer<node_type>(width(ptr)).out(os,ptr);
    }
  
public:
    ostream& out(ostream& os) const 
    {
        int i;
        // 跳过空树
        for( i = 0; theTrees[ i ] == nullptr; ++i )
            ;

        // 当遇到第一棵非空树的时候开始输出
        for( ; i < theTrees.size( ); ++i )
            if( theTrees[ i ] != nullptr )
            {
              out(os,theTrees[i]);
              std::cout<<endl<<endl;
            }
        return os;
    }

};

template <typename T>
ostream& operator<<(ostream& os, const Bqueue<T>& rhs) { return rhs.out(os); }
}

#endif
