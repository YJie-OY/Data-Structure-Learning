#ifndef LHEAP_H
#define LHEAP_H

#include "dsexceptions.h"
#include <iostream>
#include "sim_iobtr_Lheap.h"
#include <initializer_list>
using namespace std;


// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// T findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// ******************ERRORS********************************
// Throws UnderflowException as warranted
namespace DSAA
{

template <typename T>
class Lheap
{

private:
    struct LheapNode
    {
        T         data;
        LheapNode *lch;
        LheapNode *rch;
        int        npl;

        LheapNode( const T & e, LheapNode *lt = nullptr, LheapNode *rt = nullptr, int np = 0 )
          : data{ e }, lch{ lt }, rch{ rt }, npl{ np } { }
        
        LheapNode( T && e, LheapNode *lt = nullptr,LheapNode *rt = nullptr, int np = 0 )
          : data{ std::move( e ) }, lch{ lt }, rch{ rt }, npl{ np } { }
    };
public:
    typedef  LheapNode       node_type;
    typedef  node_type*      node_ptr;
    typedef  T               value_type;
    typedef  unsigned long   size_type;
    

private:
    node_ptr root;
    size_type siz;

    /****************************************************************
     * Internal method to merge two roots.
     * Deals with deviant cases and calls recursive merge1.
     ****************************************************************/
    node_ptr merge( node_ptr h1, node_ptr h2 )
    {
        if( h1 == nullptr )
            return h2;
        if( h2 == nullptr )
            return h1;
        if( h1->data < h2->data )
            return merge1( h1, h2 );
        else
            return merge1( h2, h1 );
    }

    /****************************************************************
     * Internal method to merge two roots.
     * Assumes trees are not empty, and h1's root contains smallest item.
     ****************************************************************/
    node_ptr  merge1( node_ptr h1, node_ptr h2 )
    {
        if( h1->lch == nullptr )   // Single node
            h1->lch = h2;       // Other fields in h1 already accurate
        else
        {
            h1->rch = merge( h1->rch, h2 );
            if( h1->lch->npl < h1->rch->npl )
                swapChildren( h1 );
            h1->npl = h1->rch->npl + 1;
        }
        return h1;
    }

    /****************************************************************
     * Swaps t's two children.
     ****************************************************************/
    void swapChildren( node_ptr t )
    {
        node_ptr tmp = t->lch;
        t->lch = t->rch;
        t->rch = tmp;
    }

    /****************************************************************
     * Internal method to make the tree empty.
     * WARNING: This is prone to running out of stack space;
     *          exercises suggest a solution.
     ****************************************************************/
    void reclaimMemory( node_ptr t )
    {
        if( t != nullptr )
        {
            reclaimMemory( t->lch );
            reclaimMemory( t->rch );
            delete t;
        }
    }
    
    /****************************************************************
     * Internal method to clone subtree.
     * WARNING: This is prone to running out of stack space.
     *          exercises suggest a solution.
     ****************************************************************/
    node_ptr  clone( node_ptr t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new LheapNode{ t->data, clone( t->lch ), clone( t->rch ), t->npl };
    }

    size_type count(node_ptr &t) const
    {
        if(t == nullptr)
            return 0;
        else
            return count(t->lch) + count(t->rch) + 1;
    }

public:
/***********************************  基础函数  ***********************************/ 
    Lheap( ) : root{ nullptr },siz(0)
      { }
    Lheap( const Lheap & rhs ) : root{ nullptr },siz(0)
      { 
        root = clone( rhs.root );
        siz = count(root);
       }
    
    Lheap( Lheap && rhs ) : root{ rhs.root },siz(rhs.siz)
    {
        rhs.root = nullptr;
        siz = count(root);
    }
    Lheap(const initializer_list<value_type> &v):root(nullptr),siz(0)
    {
        for(auto it : v)
            insert(it);
    }
    
    ~Lheap( )
      { makeEmpty( ); }
    
    
    /**********************************************************************
     * Deep copy.
     **********************************************************************/
    Lheap & operator=( const Lheap & rhs )
    {
        Lheap copy = rhs;
        std::swap( *this, copy );
        std::swap(siz , copy.siz);
        return *this;
    }
        
    /**********************************************************************
     * Move.
     **********************************************************************/
    Lheap & operator=( Lheap && rhs )
    {
        std::swap( root, rhs.root );
        std::swap( siz , rhs.siz);
        
        return *this;
    }
    
    /**********************************************************************
     * Returns true if empty, false otherwise.
     **********************************************************************/
    bool isEmpty() const
      { return root == nullptr; }

    /**********************************************************************
     * Returns the size of the heap
     **********************************************************************/
    size_type size() const
        {return siz;}
    /**********************************************************************
     * Find the smallest item in the priority queue.
     * Return the smallest item, or throw Underflow if empty.
     **********************************************************************/
    const T & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return root->data;
    }

    /**********************************************************************
     * Inserts x; duplicates allowed.
     **********************************************************************/
    void insert( const T & x )
      { root = merge( new LheapNode{ x }, root ); siz++; }

    void insert( T && x )
      { root = merge( new LheapNode{ std::move( x ) }, root );  siz++ ;}

    /**********************************************************************
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     **********************************************************************/
    void deleteMin( )
    {
        if( isEmpty( ) )
            throw UnderflowException{ };

        node_ptr oldRoot = root;
        root = merge( root->lch, root->rch );
        siz--;
        delete oldRoot;
    }
    void deleteMin( T & minItem )
    {
        minItem = findMin( );
        deleteMin( );
    }

    /**********************************************************************
     * Make the priority queue logically empty.
     **********************************************************************/
    void makeEmpty( )
    {
        reclaimMemory( root );
        root = nullptr;
        siz = 0;
    }

    /**********************************************************************
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     **********************************************************************/
    void merge( Lheap & rhs )
    {
        if( this == &rhs )    // Avoid aliasing problems
            return;
        root = merge( root, rhs.root );
        siz = count(root);
        rhs.root = nullptr;
    }

    /**********************************************************************
     * swap the heap
     **********************************************************************/ 
    void swap(Lheap<value_type> &rhs)
    {
        std::swap(this->root,rhs.root);
        std::swap(this->siz ,rhs.siz );
    }
protected:
    virtual void out(ostream& os, node_ptr ptr) const
    {
        outer<node_type>(width(ptr)).out(os,ptr);
    }

public:
    ostream& out(ostream& os) const 
    {
        out(os,root);
        return os;
    }

};

template <typename T>
ostream& operator<<(ostream& os, const Lheap<T>& rhs) { return rhs.out(os); }

}

#endif