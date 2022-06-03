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
     * �����������ȷ���� t Ϊ���Ķ������Ľ�������������
     *****************************************************************************/
    template <typename NODE_T>
    unsigned long width(const NODE_T* t)
    {
        ostringstream ss;
        return trv(ss, t).str().size();
    }

    /******************************************************************************
     * ���������������������ڴ�����ʼλ�����
     *****************************************************************************/
    template <typename T>
    ostringstream& out(ostringstream& ss, const T& rhs)
    {
        ss.seekp(0) << rhs;
        return ss;
    }
    /******************************************************************************
     * ������������������������
     *****************************************************************************/
    template <typename NODE_T>
    ostringstream& trv(ostringstream& ss, const NODE_T* t)
    {
        if (t == nullptr) return ss;
        return out(trv(trv(ss, t->lch), t->rch), *t);
    }

    /******************************************************************************
     * �����������ȷ���� T ���Ͷ��� rhs ���������
     *****************************************************************************/
    template <typename T>
    unsigned long len(const T& rhs)
    {
        std::ostringstream ss;
        return out(ss, rhs).str().size();
    }
    /******************************************************************************
     * ����������Ŀ�������: ͨ����������� NODE_T ����ָ��
     * ��ָ����Ϊ���Ķ��������������ʽ��Ĳ���Ϊ������
     *****************************************************************************/
    template <typename NODE_T>
    class outer
    {
        const char x = ' ' ^ '|';
        string Indent, eXpand;

    public:
        outer(unsigned long L) : Indent(L + 3, ' '), eXpand(L + 1, '-') {}
        /**********************************************************
         * ���� t ��ָ����Ϊ���������� os ���. s Ϊ������������
         *********************************************************/
        void outsubt(ostream& os, NODE_T* t, string s, char e) const
        {
            if (t != nullptr)
            {
                /*****************************************
                 * ��������, ����������
                 ****************************************/
                outsubt(os, t->rch, s + e + Indent, ' ');
                /*****************************************
                 * �����������ָ���ͷ��Ȼ����������
                 ****************************************/
                os << s << "o->" << *t;
                /*****************************************
                 * ������ӽ��������ӳ���
                 ****************************************/
                if (t->lch != nullptr || t->rch != nullptr)
                {
                    os << eXpand.substr(len(*t)) << '+';
                }
                os << '\n';
                /*****************************************
                 * ��������, ����������
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
