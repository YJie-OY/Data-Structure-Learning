/********************************************************************************
 * 作      业 : 实现 AVL 树,并且测试所有的公开函数,并且上交测试文件.
 * 
 * 
 * 思  考  题 : P149 - 4.14 用 BinarySearchTree 做实验.
 * 
 * 其      它 : (1)有关于非二叉树向二叉树的转换.(2)如何计算树的高度.(考试可能要考)
 * 
 * 性 能 要 求: 各种操作符合指定的时间复杂度。
          1. 默认构造/移动构造/移动赋值/基本函数         - 常量时间复杂度
          2. 复制构造/复制赋值/初始化表构造/初始化表赋值 - 线性时间复杂度
          3. 查询/插入/删除                             - 对数时间复杂度

 * 测 试 要 求: 检查所实现avltree类的对象是否具备上述要求的功能和性能。
 * 
 ********************************************************************************/ 
#include "sim_iobtr.h"
#include<iostream>
using namespace std;
namespace DSAA
{

typedef size_t size_type;
template <typename T>
class avltree
{
public:
    typedef          T              value_type;
    typedef          unsigned long  size_type;
public:
    struct avlnode
    {
        value_type element;
        avlnode* left;
        avlnode* right;
        int height;

        avlnode(const value_type &ele = 0 , avlnode* l=nullptr , avlnode* r=nullptr , int h = 0)
        :element(ele),left(l),right(r),height(h) {}

        avlnode(value_type && ele=0 , avlnode* l=nullptr , avlnode* r=nullptr , int h = 0)
        :element(std::move(ele)),left(l),right(r),height(h) {}
    };

public:
    typedef          avlnode        node_type;
    typedef          avlnode*       node_ptr;   
private:
    avlnode* root;
    size_type siz;
    static const int ALLOWED_IMBALANCED = 1;

   /****************************************************************************
     * clone()     : 对以 t 为根的树克隆出一份副本
     ****************************************************************************/
    avlnode* clone(const avlnode* t) const
    {
        if(t == nullptr) return nullptr;
        return new avlnode(t->element,clone(t->left),clone(t->right),t->height);
    }

   /****************************************************************************
     * count()     : 统计以t为根节点的树的结点个数
     ****************************************************************************/
    size_type count(const avlnode* t) const
    {
        if(t == nullptr) return 0;
        return count(t->left) + count(t->right) + 1;
    }


 
    /****************************************************************************
     * makeEmpty()  : 删除节点,置为空树
     ****************************************************************************/
    void makeEmpty(avlnode* & t)
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
    avlnode* findmin(avlnode* t) const
    {
        if(t == nullptr) throw "Empty Tree when finding the minimum!";
        if(t!=nullptr)
            while(t->left != nullptr)
                t = t->left;
        return t;

    }

     /***************************************************************************
     * findmax()    : 找出以 t 为根节点的树中的最大节点
     ***************************************************************************/
    avlnode* findmax(avlnode* t) const
    {
        if(t == nullptr) throw "Empty Tree when finding the maximum!";
        if(t != nullptr)
            while(t->right != nullptr)
                t = t->right;
        return t;
    }

     /****************************************************************************
     * insert()     : 插入元素 x , 并且维持二叉排序树的平衡性.
     * 返回值       : 返回是否插入成功,若已经有元素,那么返回插入失败,反之成功.
     ***************************************************************************/
    void insert(avlnode* & t , const value_type & x)
    {
        if(t == nullptr)
        {
            siz++;
            t = new avlnode(x,nullptr,nullptr);
        }
        else if(x < t->element)
            {insert(t->left,x);}
        else if(x > t->element)
            {insert(t->right,x);}
        // cout<<*this<<endl;
        balance(t);
    }

   /****************************************************************************
     * contain()     : 查询元素 x 是否在以 t 为根的树中
     ****************************************************************************/
    bool contains(avlnode* t, const value_type & x)
    {
        if(t != nullptr)
        {
            if(x < t->element) return contains(t->left,x);
            if(x > t->element) return contains(t->right,x);
            return true;
        }
        return false;
    }

    /****************************************************************************
     * remove()     : 删除元素 x
     ****************************************************************************/
    
    void remove(avlnode* &t,const value_type & x)
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
            avlnode* oldnode = t;
            t = (t->left == nullptr)?t->right:t->left;
            delete oldnode;
            oldnode = nullptr;
            siz--;
        }
        balance(t);

    }

    /****************************************************************************
     * printTree()     : 打印出整棵树，中序打印
     ****************************************************************************/
    void printTree(avlnode* t,ostream &out)
    {
        if(t != nullptr)
        {
            printTree(t->left,out);
            out << t->element << " ";
            printTree(t->right,out);
        }
    }

    /***************************************************************************
     * 功      能 : 计算高度，并且处理节点为空的情况，避免非法访问
     **************************************************************************/
    int height(avlnode* &t) const
    {
        return ((t==nullptr)?-1:t->height);
    }


    /***************************************************************************
     * balance()   : 判断失衡类型并且维持平衡
     **************************************************************************/
    void balance(avlnode* &t)
    {
        if(t == nullptr) return ;
        if(height(t->left) - height(t->right) > ALLOWED_IMBALANCED ) // 左子树高于右子树
        {
            // cout<<"left > right"<<endl;
            if(height(t->left->left) >= height(t->left->right))
                RightRotate(t);
            else
                LR_Rotate(t);
        }
        else
        {
            if(height(t->right) - height(t->left) > ALLOWED_IMBALANCED)  // 右子树高于左子树
            {
                // cout<<"right > left"<<endl;

                if(height(t->right->right) >= height(t->right->left))
                    LeftRotate(t);
                else
                    RL_Rotate(t);
            }
        }
        t->height = max(height(t->left),height(t->right)) + 1;
        // cout<<*this<<endl;

    }

    /***************************************************************************
     * RightRotate()  : LL 应该右旋
     **************************************************************************/
    void RightRotate(avlnode* & k2)
    {
        // cout<<"LL应该右旋"<<endl;
        avlnode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left) , height(k2->right)) + 1;
        k1->height = max(height(k1->left) , k2->height) + 1;
        k2 = k1;                // 这一步是非常重要的
    }

    /***************************************************************************
     * LeftRotate()   : RR 应该左旋
     **************************************************************************/
    void LeftRotate(avlnode* & k2)
    {
        // cout<<"LL应该左旋"<<endl;

        avlnode* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->left) , height(k2->right)) + 1;
        k1->height = max(height(k1->right),k2->height) + 1;
        k2 = k1;                // 这一步是非常重要的
    }


    /***************************************************************************
     * LR_Rotate() : LR双旋转 - 先左旋后右旋
     **************************************************************************/
    void LR_Rotate(avlnode* & k3)
    {
        // cout<<"LR应该先左旋后右旋"<<endl;
        LeftRotate(k3->left);
        RightRotate(k3);
    }


    /***************************************************************************
     * RL_Rotate()  : RL双旋转 - 先右旋再左旋
     **************************************************************************/
    void RL_Rotate(avlnode* & k3)
    {
        // cout<<"RL应该先右旋再左旋"<<endl;
        RightRotate(k3->right);
        LeftRotate(k3);
    }

public:

    /***************************************************************************
     * avltree()    : 构造函数
     *                  1. 默认构造函数
     *                  2. 复制构造函数
     *                  3. 移动构造函数
     *                  4. 初始化列表构造函数
     **************************************************************************/
    /*********************    默认构造函数    *********************/
    avltree()
    :root(nullptr),siz(0){}

    /*********************    复制构造函数    *********************/
    avltree(const avltree & rhs)
    {
        this->root = clone(rhs.root);
        this->siz  = count(root); 
    }

    /*********************    移动构造函数    *********************/
    avltree(const avltree &&rhs)
    {
        this->root = clone(std::move(rhs.root));
        this->siz  = count(root);
        cout<<"using the constructor(move)"<<endl;
    }

    /*********************    结点(/移动)构造函数    *********************/
    avltree(const avlnode* & rhs)
    {
        this->root = clone(rhs);
        this->siz  = count(root);
    }

    avltree(avlnode* && rhs)
    {
        this->root = std::move(rhs);
        this->siz  = count(root);
        rhs = nullptr;
    }
  
    /*******************   初始化列表构造函数  *******************/
    avltree(const std::initializer_list<value_type> &v):root(nullptr),siz(0)
    {
        for(auto it : v)
        {
            insert(it);
        }

    }

    /***************************************************************************
     * ~avltree()     :  析构函数,删除整棵树并且结束当前树的生命.
     **************************************************************************/
    ~avltree()
        {makeEmpty();}


    /***************************************************************************
     * avltree& operator=() : 赋值重载
     *                      1. 复制赋值重载
     *                      2. 移动赋值重载
     *                      3. 初始化列表赋值重载
     **************************************************************************/

    /*******************      复制赋值重载      *******************/
    avltree& operator=(const avltree & rhs)
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
    avltree& operator=(const avltree &&rhs)
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
    avltree& operator=(const std::initializer_list<value_type> & v)
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

    int       theHeight() const {return root->height;}


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
      * 功      能 : 插入函数,在保持 avl 树排序性的前提下将新元素加入其中
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
ostream& operator<<(ostream& os, const avltree<T>& rhs) { return rhs.out(os); }

}
