// g++ -std=gnu++11 -O2 -x c++ -o _test
// encoding=utf8
/*** test_sim_btree.cc ********************************************************
 * OS            : GNU/Linux 5.16.14-100.fc34.x86_64 2022-03-11 20:24:01
 * Compiler      : g++ (GCC) 11.2.1 20220127 (Red Hat 11.2.1-9)
 * Encoding      : zh_CN.UTF-8
 * Date          : 2022-03-20 11:24:46 (1647746686.808827152)
 * Last Modified : 2022-03-22 13:29:38 (1647926978.632516648)
 *****************************************************************************/
/*** Versions ****************************************************************/
const int MAJVERSION = 1;
const int SUBVERSION = 0;
const int MINVERSION = 72;
const int BUILDYEAR = 2022;
const int MODIFIEDYEAR = 2022;
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
#include "sim_btree.h"
#include "avltree.h"
using namespace std;

typedef DSAA::btree<char>   btr_type;
typedef btr_type::size_type size_type;
typedef btr_type::node_type node_type;
typedef btr_type::node_ptr  node_ptr;

namespace DSAA
{
ostream& operator<< (ostream& os, const node_type& rhs)
{
    return os << '[' << rhs.data << ']';
}
}

int main(int argc, char* argv[])
{
    node_type a('a'), c('c'), b('b',&a,&c), e('e'), g('g'), f('f',&e,&g), d('d',&b,&f);
    node_type h('h'), j('j'), i('i',&h,&j), l('l'), n('n'), m('m',&l,&n), k('k',&i,&m);
    node_type r('r',&d,&k);

    btr_type t1(&r);
    cout << "The size of the binary tree t1: " << t1.size() << endl;
    cout << t1 << endl;

    btr_type t2(t1);
    cout << "The size of the binary tree t2: " << t2.size() << endl;
    cout << t2 << endl;

    l.lch = new node_type(50);

    cout << "The size of the binary tree t1: " << t1.size() << endl;
    cout << t1 << endl;

    btr_type t3(&r);
    cout << "The size of the binary tree t3: " << t3.size() << endl;
    cout << t3 << endl;

    btr_type t4(move(t3));
    cout << "The size of the binary tree t3: " << t3.size() << endl;
    cout << t3 << endl;
    cout << "The size of the binary tree t4: " << t4.size() << endl;
    cout << t4 << endl;

    int x = 50, y = 60;
    cout << x <<  " is" << (t4.contains(x) ? " " : " not ") << "in binary tree t4" << endl;
    cout << y <<  " is" << (t4.contains(y) ? " " : " not ") << "in binary tree t4" << endl;

    cout << "Now, clear the binary tree t4" << endl;
    t4.clear();
    cout << "The size of the binary tree t4: " << t4.size() << endl;
    cout << t4 << endl;

    return 0;
}

