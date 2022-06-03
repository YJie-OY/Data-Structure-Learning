// encoding=utf8
#ifndef SIM_IOBTR_H
#define SIM_IOBTR_H
/*** sim_iobtr.h **************************************************************
 * OS            : GNU/Linux 5.16.14-100.fc34.x86_64 2022-03-11 20:24:01
 * Compiler      : g++ (GCC) 11.2.1 20220127 (Red Hat 11.2.1-9)
 * Encoding      : zh_CN.UTF-8
 * Date          : 2022-03-18 11:28:30 (1647574110.084200854)
 * Last Modified : 2022-03-22 13:43:37 (1647927817.320855276)
 *****************************************************************************/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using std::ostream;
using std::ostringstream;
using std::string;
/*** Versions ****************************************************************/
#define MAJVERSION 1
#define SUBVERSION 0
#define MINVERSION 55
#define BUILDYEAR 2022
#define MODIFIEDYEAR 2022
/*****************************************************************************/
/*** Note *********************************************************************
 * If the Chinese characters in this file do not print properly, you may try to
 * setup the encoding of your operating system or your reader to Unicode-8. You
 * may also convert the encoding of this file to your encoding by some encoding
 * converting software.
 * All nchs Reserved by Prinse Wang, Goldwe Tech, Inc.
 *****************************************************************************/
/*** Description **************************************************************
 *****************************************************************************/
/*** Analysis *****************************************************************
 *****************************************************************************/
/************************************ 注意事项 *************************
 * 在 Prine 的代码中 左右指针的 lch 和 rch
 * 在 自己的代码 中 ，左右指针分别是 lch 和 nch
 *********************************************************************/
namespace DSAA
{

/******************************************************************************
 * 这个辅助函数确定以 t 为根的二叉树的结点的最大输出长度
 *****************************************************************************/
template <typename NODE_T>
unsigned long width(const NODE_T* t)
{
    ostringstream ss;
    return trv(ss,t).str().size(); 
}

/******************************************************************************
 * 这个辅助函数将输出项总在串流开始位置输出
 *****************************************************************************/
template <typename T>
ostringstream& out(ostringstream& ss, const T& rhs)
{
    ss.seekp(0) << rhs;
    return ss;
}

/******************************************************************************
 * 这个辅助函数后序遍历二叉树
 *****************************************************************************/
template <typename NODE_T>
ostringstream& trv(ostringstream& ss, const NODE_T* t)
{
    if (t == nullptr) return ss;
    return out(trv(trv(ss,t->lch),t->nch), *t);
}

/******************************************************************************
 * 这个辅助函数确定以 T 类型对象 rhs 的输出长度
 *****************************************************************************/
template <typename T>
unsigned long len(const T& rhs)
{
    std::ostringstream ss;
    return out(ss,rhs).str().size();
}

/******************************************************************************
 * 输出二叉树的控制类型: 通过中序遍历以 NODE_T 类型指针
 * 所指向结点为根的二叉树，遍历访问结点的操作为输出结点
 *****************************************************************************/
template <typename NODE_T>
class outer
{
    const char x = ' '^'|';
    string Indent, eXpand;

public:
    outer(unsigned long L) : Indent(L+3,' '), eXpand(L+1,'-') {}
    /**********************************************************
     * 将以 t 所指向结点为根的子树向 os 输出. s 为辅助的缩进串
     *********************************************************/
    void outsubt(ostream& os, NODE_T* t, string s, char e) const
    {
        if (t != nullptr)
        {
            /*****************************************
             * 缩进增加, 遍历右子树
             ****************************************/
            outsubt(os, t->nch, s+e+Indent, ' ');
            /*****************************************
             * 输出缩进串、指针箭头，然后输出根结点
             ****************************************/
            os << s << "o->" << *t;
            /*****************************************
             * 如果有子结点则输出延长线
             ****************************************/
            if (t->lch !=nullptr || t->nch != nullptr)
            {
                os << eXpand.substr(len(*t)) << '+';
            }
            os << '\n';
            /*****************************************
             * 缩进增加, 遍历左子树
             ****************************************/
            outsubt(os, t->lch, s+char(e^x)+Indent, '|');
        }
    }

    void out(ostream& os, NODE_T* t, string s="") const
    {
        if (t != nullptr)
        {
            outsubt(os, t->nch, s + ' ' + Indent, ' ');
            os << s << "o->" << *t;
            if (t->lch !=nullptr || t->nch != nullptr)
            {
                os << eXpand.substr(len(*t)) << '+';
            }
            os << '\n';
            outsubt(os, t->lch, s + ' ' + Indent, '|');
        }
    }
};

/******************************************************************************
 * template <typename T>
 * class btree
 * {
 * protected:
 *     struct node
 *     {
 *         T data;
 *         node *lch, *nch;
 *     };
 * 
 * public:
 *     typedef typename node<value_type>   node_type;
 *     typedef          node_type*         node_ptr;
 * 
 * private:
 *     node_ptr root;
 * 
 * protected:
 *     virtual void out(ostream& os, node_ptr ptr) const
 *     {
 *         outer<node_type>(width(ptr)).out(os,ptr);
 *     }
 *
 * public:
 *     ostream& out(ostream& os) const { out(os,root); return os; } 
 * };
 *****************************************************************************/

/******************************************************************************
 * template <typename T>
 * ostream& operator<<(ostream& os, const btree<T>& rhs) { return rhs.out(os); }
 *****************************************************************************/

}

/*****************************************************************************/

#undef MAJVERSION
#undef SUBVERSION
#undef MINVERSION
#undef BUILDYEAR
#undef MODIFIEDYEAR

/*****************************************************************************/

#endif

