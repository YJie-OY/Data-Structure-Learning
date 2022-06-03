#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE
#include<iostream>
// #include<initialize_list>
using namespace std;
template<typename Comparable>
class BinarySearchTree
{
public:
    /******************* 二叉树节点定义 *******************/
    struct BinaryNode
    {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Comparable  &theElement , BinaryNode* lt=nullptr, BinaryNode* rt=nullptr ):element(theElement),left(lt),right(rt)
            {}
        BinaryNode(Comparable  &&theElement , BinaryNode* lt=nullptr, BinaryNode* rt=nullptr ):element(std::move(theElement)),left(lt),right(rt)
            {}
        
        /************ 禁止复制构造和赋值 **************/
        BinaryNode(const BinaryNode&) = delete;
        BinaryNode& operator= (const BinaryNode& ) = delete;
        BinaryNode& operator= (      BinaryNode&&) = delete;
    };

private:
    BinaryNode* root;
    size_t siz;

protected:
    /**************************************************************************
     * 功     能 : 找出以 t 为根节点的树中的最小节点
     *************************************************************************/
    BinaryNode* findMin(BinaryNode* t) const
    {
        if (t == nullptr)
            {return nullptr;}
        if (t->left == nullptr)
            {return t;}
        return findMin(t->left);
        
    }
    
    /***************************************************************************
     * 功     能 : 找出以 t 为根节点的树中的最大节点
     ***************************************************************************/
    BinaryNode* findMax(BinaryNode* t) const
    {
        if(t != nullptr)
            while(t->right != nullptr)
                t = t->right;
        return t;
    }

    /****************************************************************************
     * 功     能 : 查询元素 x 是否在以t为根的树中
     ***************************************************************************/
    
    bool contains(const Comparable &x,BinaryNode *t)
    {
        if(t == nullptr)
            return false;
        else if (x < t->element)
            {return contains(x,t->left);}
        else if (x > t->element)
            {return contains(x,t->right);}
        else
            {return true;}        
        
    }

    /****************************************************************************
     * 功     能 : 插入元素 x , 并且维持二叉排序树的形态
     ***************************************************************************/
    void insert(const Comparable &x , BinaryNode* &t)
    {
        if(t == nullptr)
        {
            t = new BinaryNode(x,nullptr,nullptr);
            siz++;
        }
        else if(x < t->element)
            insert(x,t->left);
        else if(x > t->element)
            insert(x,t->right);

        return ;
    }

    void insert(Comparable &&x , BinaryNode* &t)
    {
        if(t == nullptr)
        {
            t = new BinaryNode(std::move(x),nullptr,nullptr);
            siz++;
        }
        else if(x < t->element)
            insert(std::move(x),t->left);
        else if(x > t->element)
            insert(std::move(x),t->right);
        
        return ;
        
    }

    /****************************************************************************
     * 功     能 : 删除元素 x
     ****************************************************************************/
    
    void remove(const Comparable &x , BinaryNode* &t)
    {
        if(t == nullptr)
            return ;
        if(x < t->element)
            remove(x,t->left);
        else if(x > t->element)
            remove(x,t->right);
        else if(t->left != nullptr && t->right != nullptr)
        {
            t->element = findMin(t->right)->element;
            remove(t->element,t->right);
        }
        else
        {
            BinaryNode* old = t;
            t = (t->left != nullptr)?t->left : t->right;
            delete old;
            siz--;
        }
    }    
    
    /****************************************************************************
     * 功     能 : 删除以t为根节点的树
     ****************************************************************************/
    void makeEmpty(BinaryNode* &t)
    {
        if (t != nullptr)
        {
            /* code */
            makeEmpty(t->right);
            makeEmpty(t->left);
            delete t;
        }
        siz = 0;
        t = nullptr;
        
    }
    
    /****************************************************************************
     * 功     能 : 克隆出一棵以 t 为根节点的树
     ****************************************************************************/
    BinaryNode* clone(const BinaryNode* t) const
    {
        if(t == nullptr)
            return nullptr;
        else
            return new BinaryNode(t->element,clone(t->left),clone(t->right));
    }
    /****************************************************************************
    * 功    能 : 计算树的大小.
    ***************************************************************************/ 
    size_t count(BinaryNode* t) const
    {
        if(t == nullptr) return 0;
        return count(t->left) + count(t->right) + 1;
    }

    /****************************************************************************
     * 功     能 : 中序遍历打印整棵树,二叉排序树的中序遍历是顺序的.
     ****************************************************************************/
    void printTree(BinaryNode *t,ostream &out)
    {

        if(t!=nullptr)
        {
            printTree(t->left,out);
            out << t->element << "  ";
            printTree(t->right,out);
        }
    }


public:
    /*************** 基础函数 ****************/
    BinarySearchTree():root(nullptr),siz(0){}

    BinarySearchTree(const BinaryNode* node)
    {
        root = clone(node);
        siz = count(root);
    }

    BinarySearchTree(const BinarySearchTree &rhs):root(nullptr)
    {
        root = clone(rhs.root);
        siz = count(root);
    }
    BinarySearchTree(BinarySearchTree && rhs):root(nullptr)
    {
        root = clone(std::move(rhs.root));
        siz = count(root);
    }

    BinarySearchTree(const std::initializer_list<Comparable> & v):root(nullptr),siz(0)
    {

        for(auto iter : v)
        {

            insert(iter);
        }
  
    }

    // void assgin(const BinarySearchTree& rhs);

    ~BinarySearchTree()
        {makeEmpty();}



public:
     /****************************************************************************
     * 功    能 : 查找树的最大元素/最小元素;
     ***************************************************************************/
    const Comparable& findMin() const
        {return findMin(root)->element;}
    const Comparable& findMax() const
        {return findMax(root)->element;}



    /****************************************************************************
     * 功    能 : 查询元素 x 是否在以t为根的树中;
     * 问    题 : 此处同样不能用 const 修饰函数, 为什么?
     ***************************************************************************/    
    bool contains (const Comparable &x) 
        {return contains(x,root);}


    /****************************************************************************
     * 功    能 : 查询是否为空树;
    ****************************************************************************/
    bool isEmpty() const
        {return root==nullptr;}

    /****************************************************************************
     * 功    能 : 查询树的大小;
    ****************************************************************************/
    size_t size()
        {return siz;}
public:
    /****************************************************************************
     * 功     能 : 重载赋值运算符.
    ****************************************************************************/
    BinarySearchTree & operator=(const BinarySearchTree &rhs)
    {
        if(this != &rhs)
        {
            makeEmpty();
            this->root = clone(rhs.root);
            this->siz = rhs.siz;
        }
        return *this;
    }
    BinarySearchTree & operator=(BinarySearchTree &&rhs)
    {
        if(this != &rhs)
        {
            makeEmpty();
            this->root = rhs.root;
            this->siz = rhs.siz;
            rhs.root = nullptr;
        }
        return *this;
    }

public:

    /****************************************************************************
     * 功    能 : 打印出整棵树
     * 问    题 : 为什么这里不能用 const 来修饰函数?(书上使用了,但是实际上在这里修改了out的值)
     ****************************************************************************/
    void printTree(ostream &out = cout) 
    {
        if(isEmpty())
            out<<"Empty tree!"<<endl;
            
        else
        {
            cout<<"the size of the tree is :  "<<siz<<endl;
            printTree(root,out);
        }

        cout<<endl<<endl;
    }

    /****************************************************************************
     * 功    能 : 删除整棵树
     ****************************************************************************/
    void makeEmpty()
        {makeEmpty(root);}





    /****************************************************************************
     * 功    能 : 插入元素 x
     ****************************************************************************/
    void insert(const Comparable &x)
        {insert(x,root);}

    void insert(Comparable &&x)
        {insert(x,root);}



    /****************************************************************************
     * 功    能 : 删除元素 x
     ****************************************************************************/
    void remove(const Comparable &x)
        {remove(x,root);}
};

#endif