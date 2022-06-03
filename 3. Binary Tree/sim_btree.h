// encoding=utf8
#ifndef SIM_BTREE_H
#define SIM_BTREE_H
/*** sim_btree.h **************************************************************
 * OS            : GNU/Linux 5.16.14-100.fc34.x86_64 2022-03-11 20:24:01
 * Compiler      : g++ (GCC) 11.2.1 20220127 (Red Hat 11.2.1-9)
 * Encoding      : zh_CN.UTF-8
 * Date          : 2022-03-18 11:28:30 (1647574110.084200854)
 * Last Modified : 2022-03-22 13:26:16 (1647926776.247855637)
 *****************************************************************************/
#include "sim_iobtr.h"
/*** Versions ****************************************************************/
#define MAJVERSION 1
#define SUBVERSION 0
#define MINVERSION 39
#define BUILDYEAR 2022
#define MODIFIEDYEAR 2022
/*****************************************************************************/
/*** Note *********************************************************************
 * If the Chinese characters in this file do not print properly, you may try to
 * setup the encoding of your operating system or your reader to Unicode-8. You
 * may also convert the encoding of this file to your encoding by some encoding
 * converting software.
 * All Rights Reserved by Prinse Wang, Goldwe Tech, Inc.
 *****************************************************************************/
/*** Description **************************************************************
 *****************************************************************************/
/*** Analysis *****************************************************************
 *****************************************************************************/

namespace DSAA
{

template <typename T>
class btree
{
    struct node
    {
        T data;
        node* lch;
        node* rch;
        node() : data(T()), lch(nullptr), rch(nullptr)
        {
        }
        node(const T& x, node* L=nullptr, node* R=nullptr)
        : data(x), lch(L), rch(R)
        {
        }
        node(T&& x, node* L=nullptr, node* R=nullptr)
        : data(std::move(x)), lch(L), rch(R)
        {
        }
        node(const node&) = delete;
        node& operator= (const node& ) = delete;
        node& operator= (      node&&) = delete;
    };

public:
    typedef          T              value_type;
    typedef          node           node_type;
    typedef          node_type*     node_ptr;
    typedef          unsigned long  size_type;

private:
    size_type siz;
    node* root;

private:
    node* clone(node_ptr ptr)
    {
        if (ptr == nullptr) { return nullptr; }
        return new node(ptr->data, clone(ptr->lch), clone(ptr->rch));
    }

    void clear(node_ptr ptr)
    {
        if (ptr == nullptr) return;
        clear(ptr->lch);
        clear(ptr->rch);
        delete ptr;
    }

    bool contains(const T& x, node_ptr t) const
    {
        if (t == nullptr) return false;
        if (t->data == x) return true;
        return contains(x,t->lch) || contains(x,t->rch);
    }

    size_type count(node_ptr ptr) const
    {
        if (ptr == nullptr) return 0;
        return count(ptr->lch)+count(ptr->rch)+1;
    }

public:
    btree() : siz(0), root(nullptr)
    {
    }
    btree(node_ptr ptr) : siz(0), root(nullptr)
    {
        root = clone(ptr);
        siz  = count(root);
    }
    btree(const btree& rhs) : siz(rhs.siz), root(clone(rhs.root))
    {
    }
    btree(btree&& rhs) : siz(rhs.siz), root(rhs.root)
    {
        rhs.siz  = 0;
        rhs.root = nullptr;
    }
   ~btree() { clear(); }

    btree& operator= (const btree& rhs)
    {
        if (this != &rhs)
        {
            clear();
            siz = rhs.siz;
            clone();
        }
        return *this;
    }
    btree& operator= (btree&& rhs)
    {
        if (this != &rhs)
        {
            clear();
            siz = rhs.siz;
            root = rhs.root;
            rhs.root = nullptr;
        }
        return *this;
    }

    size_type size() const { return siz; }
    bool empty    () const { return siz==0; /*root==nullptr;*/ }

    void clear()
    {
        clear(root);
        siz  = 0;
        root = nullptr;
    }

    bool contains(const T& x) const { return contains(x,root); }

protected:
    virtual void out(ostream& os, node_ptr ptr) const
    {
        outer<node_type>(width(ptr)).out(os,ptr);
    }

public:
    ostream& out(ostream& os) const { out(os,root); return os; }
};

template <typename T>
ostream& operator<<(ostream& os, const btree<T>& rhs) { return rhs.out(os); }

}

/*****************************************************************************/

#undef MAJVERSION
#undef SUBVERSION
#undef MINVERSION
#undef BUILDYEAR
#undef MODIFIEDYEAR

/*****************************************************************************/

#endif

