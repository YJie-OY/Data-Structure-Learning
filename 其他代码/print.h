#pragma once
// encoding=utf8
#ifndef SIM_IOBTR_H
#define SIM_IOBTR_H
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

namespace DSAA
{
    /******************************************************************************
     * 这个辅助函数确定以 t 为根的二叉树的结点的最大输出长度
     *****************************************************************************/
    template <typename NODE_T>
    unsigned long width(const NODE_T* t)
    {
        ostringstream ss;
        return trv(ss, t).str().size();
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
        return out(trv(trv(ss, t->lch), t->rch), *t);
    }

    /******************************************************************************
     * 这个辅助函数确定以 T 类型对象 rhs 的输出长度
     *****************************************************************************/
    template <typename T>
    unsigned long len(const T& rhs)
    {
        std::ostringstream ss;
        return out(ss, rhs).str().size();
    }
    /******************************************************************************
     * 输出二叉树的控制类型: 通过中序遍历以 NODE_T 类型指针
     * 所指向结点为根的二叉树，遍历访问结点的操作为输出结点
     *****************************************************************************/
    template <typename NODE_T>
    class outer
    {
        const char x = ' ' ^ '|';
        string Indent, eXpand;

    public:
        outer(unsigned long L) : Indent(L + 3, ' '), eXpand(L + 1, '-') {}
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
                outsubt(os, t->rch, s + e + Indent, ' ');
                /*****************************************
                 * 输出缩进串、指针箭头，然后输出根结点
                 ****************************************/
                os << s << "o->" << *t;
                /*****************************************
                 * 如果有子结点则输出延长线
                 ****************************************/
                if (t->lch != nullptr || t->rch != nullptr)
                {
                    os << eXpand.substr(len(*t)) << '+';
                }
                os << '\n';
                /*****************************************
                 * 缩进增加, 遍历左子树
                 ****************************************/
                outsubt(os, t->lch, s + char(e ^ x) + Indent, '|');
            }
        }

        void out(ostream& os, NODE_T* t, string s = "") const
        {
            if (t != nullptr)
            {
                outsubt(os, t->rch, s + ' ' + Indent, ' ');
                os << s << "o->" << *t;
                if (t->lch != nullptr || t->rch != nullptr)
                {
                    os << eXpand.substr(len(*t)) << '+';
                }
                os << '\n';
                outsubt(os, t->lch, s + ' ' + Indent, '|');
            }
        }
    };
}

#undef MAJVERSION
#undef SUBVERSION
#undef MINVERSION
#undef BUILDYEAR
#undef MODIFIEDYEAR

#endif
