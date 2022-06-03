/************************************************************************************
 * 启    发 : 树在插入和删除的过程中可能会变得比较平衡
 * 
 * 问    题 : 有没有必要使用一定的开销去刻意构造/维持一棵平衡二叉树？
 * ******* : 1. 某些场景下对树的高度其实没有太大的要求,即使树不平衡,效率依旧可以接受.
 * ******* : 2. 基于对问题的认识,一棵一开始不平衡的树在反复的形态变化过程中是否会趋于
 *           平衡,所以没有必要刻意的去构造. 
 * 
 * 现    象 : 当某个数据被查询的时候,这个数据以及与这个数据相关度高的数据容易被反复查询
 * 
 * 结    论 : 对于某些更加容易被访问的元素,我们应该把它放在更加接近根节点的地方,而对于
 *          不常被访问的元素,那么就尽可能的把这个元素放到离根更加远的地方.
 * 
 * 实现思想 : 我们认为当前被查询的节点以及以这个节点为根的所有子节点都变得重要了,因而把
 *          这棵子树上提,并且把当前节点作为新的根节点.
 * 
 * 注    意 : 
 ************************************************************************************/
#include "sim_iobtr.h"
#include<iostream>
using namespace std;
namespace DSAA
{

typedef size_t size_type;
template <typename T>
class spltree
{
public:
    typedef          T              value_type;
    typedef          unsigned long  size_type;
public:
    struct splnode
    {
        value_type element;
        splnode* left;
        splnode* right;

        splnode(const value_type &ele = 0 , splnode* l=nullptr , splnode* r=nullptr)
        :element(ele),left(l),right(r) {}

        splnode(value_type && ele=0 , splnode* l=nullptr , splnode* r=nullptr)
        :element(std::move(ele)),left(l),right(r) {}
    };

public:
    typedef          splnode        node_type;
    typedef          splnode*       node_ptr;   
private:
    splnode* root;
    size_type siz;
    static const int ALLOWED_IMBALANCED = 1;

   /****************************************************************************
     * clone()     : 对以 t 为根的树克隆出一份副本
     ****************************************************************************/
    splnode* clone(const splnode* t) const
    {
        if(t == nullptr) return nullptr;
        return new splnode(t->element,clone(t->left),clone(t->right));
    }

   /****************************************************************************
     * count()     : 统计以t为根节点的树的结点个数
     ****************************************************************************/
    size_type count(const splnode* t) const
    {
        if(t == nullptr) return 0;
        return count(t->left) + count(t->right) + 1;
    }


 
    /****************************************************************************
     * makeEmpty()  : 删除节点,置为空树
     ****************************************************************************/
    void makeEmpty(splnode* & t)
    {
        if(t == nullptr) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

     /**************************************************************************
     * findmin()   : 找出以 t 为根节点的树中的最小节点
     *************************************************************************/
    splnode* findmin(splnode* t) const
    {
        if(t == nullptr) throw "Empty Tree when finding the minimum!";
        if(t!=nullptr)
            while(t->left != nullptr)
                t = t->left;
        // 可以考虑查找最小值时候的伸展作用
        //if(t!=root) splay(t->element,root);
        return t;

    }

     /***************************************************************************
     * findmax()    : 找出以 t 为根节点的树中的最大节点
     ***************************************************************************/
    splnode* findmax(splnode* t) const
    {
        if(t == nullptr) throw "Empty Tree when finding the maximum!";
        if(t != nullptr)
            while(t->right != nullptr)
                t = t->right;
                
        // 可以考虑查找最大值时候的伸展作用
        //if(t!=root) splay(t->element,root);
        return t;
    }

     /****************************************************************************
     * insert()     : 插入元素 x , 并且维持二叉排序树的平衡性.
     * 返回值       : 返回是否插入成功,若已经有元素,那么返回插入失败,反之成功.
     ***************************************************************************/
    void insert(splnode* & t , const value_type & x)
    {
        if(t == nullptr)
        {
            siz++;
            t = new splnode(x,nullptr,nullptr);
        }
        else if(x < t->element)
            {insert(t->left,x);}
        else if(x > t->element)
            {insert(t->right,x);}
        // cout<<*this<<endl;
        
    }


    /****************************************************************************
     * remove()     : 删除元素 x
     ****************************************************************************/
    
    void remove(splnode* &t,const value_type & x)
    {
        if(t == nullptr)       return ;
        else if(x < t->element)     remove(t->left , x);
        else if(x > t->element)     remove(t->right , x);

        else if(t->left != nullptr && t->right != nullptr)
        {
            t->element = findmin(t->right)->element;
            remove(t->right,t->element);
        }
        else
        {
            splnode* oldnode = t;
            t = (t->left == nullptr)?t->right:t->left;
            delete oldnode;
            oldnode = nullptr;
            siz--;
        }

    }

    /****************************************************************************
     * printTree()     : 打印出整棵树，中序打印
     ****************************************************************************/
    void printTree(splnode* t,ostream &out)
    {
        if(t != nullptr)
        {
            printTree(t->left,out);
            out << t->element << " ";
            printTree(t->right,out);
        }
    }



   /****************************************************************************
     * contains()     : 查询元素 x 是否在以 t 为根的树中
     * 当元素在树中时,考虑伸展。
    ****************************************************************************/
    bool contains(splnode* t, const value_type & x)
    {
        if(t != nullptr)
        {
            if(x < t->element) return contains(t->left,x);
            if(x > t->element) return contains(t->right,x);
            
            if(root->element != x) splay(x,root);
            return true;
        }
        return false;
    }

    /***************************************************************************
     * splay() : 将元素 x 所在的节点旋转至 t 的位置
     **************************************************************************/
    void splay(const value_type & x , splnode* & t)
    {
        if(t == nullptr) return;
        if(x == t->element) return;

        if(x > t->element) splay(x,t->right);
        if(x < t->element) splay(x,t->left);

        if(t->left!=nullptr)
            if (t->left->element == x)
            {
                RightRotate(t);
                return;
            }
            
        if(t->right != nullptr)
            if(t->right->element == x)
            {
                LeftRotate(t);
                return;
            }
    }
    /***************************************************************************
     * RightRotate()  : 右旋,将左节点k1旋转至k2的位置
     **************************************************************************/
    void RightRotate(splnode* & k2)
    {
    
        splnode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;                // 这一步是非常重要的
    }

    /***************************************************************************
     * LeftRotate()   : 左旋,将右节点k1旋转至k2的位置
     **************************************************************************/
    void LeftRotate(splnode* & k2)
    {
        // cout<<"LL应该左旋"<<endl;

        splnode* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2 = k1;                // 这一步是非常重要的
    }

public:

    /***************************************************************************
     * spltree()    : 构造函数
     *                  1. 默认构造函数
     *                  2. 复制构造函数
     *                  3. 移动构造函数
     *                  4. 初始化列表构造函数
     **************************************************************************/
    /*********************    默认构造函数    *********************/
    spltree()
    :root(nullptr),siz(0){}

    /*********************    复制构造函数    *********************/
    spltree(const spltree & rhs)
    {
        this->root = clone(rhs.root);
        this->siz  = count(root); 
    }

    /*********************    移动构造函数    *********************/
    spltree(const spltree &&rhs)
    {
        this->root = clone(std::move(rhs.root));
        this->siz  = count(root);
        cout<<"using the constructor(move)"<<endl;
    }

    /*********************    结点(/移动)构造函数    *********************/
    spltree(const splnode* & rhs)
    {
        this->root = clone(rhs);
        this->siz  = count(root);
    }

    spltree(splnode* && rhs)
    {
        this->root = std::move(rhs);
        this->siz  = count(root);
        rhs = nullptr;
    }
  
    /*******************   初始化列表构造函数  *******************/
    spltree(const std::initializer_list<value_type> &v):root(nullptr),siz(0)
    {
        for(auto it : v)
        {
            insert(it);
        }

    }

    /***************************************************************************
     * ~spltree()     :  析构函数,删除整棵树并且结束当前树的生命.
     **************************************************************************/
    ~spltree()
        {makeEmpty();}


    /***************************************************************************
     * spltree& operator=() : 赋值重载
     *                      1. 复制赋值重载
     *                      2. 移动赋值重载
     *                      3. 初始化列表赋值重载
     **************************************************************************/

    /*******************      复制赋值重载      *******************/
    spltree& operator=(const spltree & rhs)
    {
        if(this != &rhs)
        {
            makeEmpty();
            this->root = clone(rhs.root);
            this->siz  = count(root);
        }
        return *this;
    }

    /*******************      移动赋值重载     *******************/
    spltree& operator=(const spltree &&rhs)
    {
        if(this != &rhs)
        {
            makeEmpty();
            this->root = rhs.root;
            this->siz  = rhs.siz ;
            rhs.root   = nullptr ;
        }
        return *this;
    }

    /*******************  初始化列表赋值重载  *******************/
    spltree& operator=(const std::initializer_list<value_type> & v)
    {
        makeEmpty();
        for(auto iter : v)
            insert(iter);
    }



public: //基本函数

    /***************************************************************************
     * size()     : 查询树的大小
     * empty()    : 查询是否为空树 
     **************************************************************************/
    size_type size()  const {return siz;}

    bool      empty() const {return root==nullptr;}

public: // 查询函数

     /***************************************************************************
      * 功     能 : 对于给定的值x，确定指定avl树中是否存在结点其数据域的值
                 恰好与x的值相等。若回答肯定，返回true，否则返回false.
     ***************************************************************************/
    bool contains(const value_type& x) {return contains(root,x);}



     /***************************************************************************
      * 功     能 : 对于指定的 avl 树返回所有节点数据域的值的最小/大值
      *             建议: 如果 avl 树为空,则抛出异常.
      **************************************************************************/
    const value_type& findmin() const 
    {
        try
        {
            value_type x = findmin(root)->element;

        }
        catch(const char* msg)
        {
            cerr<<msg<<endl;
        }

        return findmin(root)->element;
    }

    value_type& findmin()
    {
        try
        {
            value_type x = findmin(root)->element;
        }
        catch(const char* msg)
        {
            cerr<<msg<<endl;
        }

        return findmin(root)->element;
    }

    const value_type& findmax() const
    {
        try
        {
            value_type x = findmax(root)->element;

        }
        catch(const char* msg)
        {
            cerr<<msg<<endl;
        }

        return findmax(root)->element;
    }
    value_type& findmax()
    {
        try
        {
            value_type x = findmax(root)->element;
        }
        catch(const char* msg)
        {
            cerr<<msg<<endl;
        }

        return  findmax(root)->element;
    }



public:
    
     /***************************************************************************
      * 功      能 : 插入函数,在保持 spltree 排序性的前提下将新元素加入其中
      * 返  回  值 : 如果确实有新元素加入,返回true,否则返回false
     ****************************************************************************/
    bool insert(const value_type  &x)
    {
        size_type tmp = siz;
        insert(root,x);
        return tmp<siz?true:false;
    }
    bool insert(      value_type &&x)
    {
        size_type tmp = siz;
        insert(root,std::move(x));
        return tmp<siz?true:false;
    }
    
    /***************************************************************************
      * 功      能 : 对于给顶元素删除指定 avl 树种其数据域的值恰好等于此元素的结点
      * 返  回  值 : 如果确实有新元素加入,返回true,否则返回false
     **************************************************************************/
    bool remove(const value_type & x)
    {
        size_type tmp = siz;
        remove(root,x);
        return tmp>siz?true:false;
    }




    /***************************************************************************
     * 功      能 : 删除树
     **************************************************************************/
    void makeEmpty()
        {makeEmpty(root); siz = 0;}


    /***************************************************************************
     * 功      能 : 打印出整棵树，如果为空树那么返回警告信息
     **************************************************************************/
    void printTree(ostream& out = cout)
    {
        if(empty())
            out<<"Empty tree!"<<endl;
        else
        {
            cout<<" the size =  " <<siz <<endl;
            printTree(root,out);
        }
        cout<<endl<<endl;
    }

protected:
    virtual void out(ostream& os, node_ptr ptr) const
    {
        outer<node_type>(width(ptr)).out(os,ptr);
    }

public:
    ostream& out(ostream& os) const { out(os,root); return os; }
};

template <typename T>
ostream& operator<<(ostream& os, const spltree<T>& rhs) { return rhs.out(os); }

}