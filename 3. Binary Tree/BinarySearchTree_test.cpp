#include"BinarySearchTree.h"
#include<iostream>
#include<time.h>
using namespace std;

namespace DSAA
{
    ostream& operator<< (ostream& os, const BinarySearchTree<char>::BinaryNode &rhs)
        {return os << '[' << rhs.element << ']';}
}

int main()
{
    BinarySearchTree<int> Mytree= {1,2,3,4,5,6,7,8};
    BinarySearchTree<int> Mytree2;

    BinarySearchTree<char>::BinaryNode a('a'), c('c'), b('b',&a,&c), e('e'), g('g'), f('f',&e,&g), d('d',&b,&f);
    BinarySearchTree<char>::BinaryNode h('h'), j('j'), i('i',&h,&j), l('l'), n('n'), m('m',&l,&n), k('k',&i,&m);
    BinarySearchTree<char>::BinaryNode r('r',&d,&k);
 
    BinarySearchTree<int> Mytree4 = {1,2,3,4,5};
    Mytree4.printTree();
    



    cout<<"/*************** test for constructor(with BinaryNode) ***************/"<<endl;
    BinarySearchTree<char> Mytree3( &r );
    Mytree3.printTree(cout);

    cout<<"/*************** test for insert() ***************/"<<endl;
    BinarySearchTree<int> Tree_list[5];
    clock_t start = clock();
    for(int i=0 ; i<1000 ; i++)
        Tree_list[0].insert(i);
    clock_t end1 = clock();
    for(int i=0 ; i<10000 ; i++)
        Tree_list[1].insert(i);
    clock_t end2 = clock();

/****************************************************
 * 插入 10,000 个元素的时候出现问题
 ****************************************************/
    // for (int i = 0; i < 100000; i++)
    //     Tree_list[2].insert(i);
    // clock_t end3 = clock();

    // for (long long  i = 0; i < 1000000; i++)
    //     Tree_list[3].insert(i);
    // clock_t end4 = clock();

    // for (long long  i = 0; i < 10000000; i++)
    //     Tree_list[4].insert(i);
    // clock_t end5 = clock();

    cout<<endl;
    cout<<"Running Time 1: " << (double) (end1 - start)/CLOCKS_PER_SEC*1000<<" ms " <<" size = "<<Tree_list[0].size()<<endl;
    cout<<"Running Time 2: " << (double) (end2 - end1)/CLOCKS_PER_SEC*1000<<" ms " <<" size = "<<Tree_list[1].size()<<endl;
    // cout<<"Running Time 3: " << (double) (end3 - end2)/CLOCKS_PER_SEC*1000<<" ms " <<" size = "<<Tree_list[2].size()<<endl;
    // cout<<"Running Time 4: " << (double) (end4 - end3)/CLOCKS_PER_SEC*1000<<" ms " <<" size = "<<Tree_list[3].size()<<endl;
    // cout<<"Running Time 5: " << (double) (end5 - end4)/CLOCKS_PER_SEC*1000<<" ms " <<" size = "<<Tree_list[4].size()<<endl;
    
    
    
    cout<<"/*************** test for size() ***************/"<<endl;
    cout<<"the size of Mytree is :  "<<Mytree.size()<<endl<<endl;


    cout<<"/*************** test for remove(20) ***************/"<<endl;
    Mytree.remove(20);
    Mytree.printTree(cout);

    cout<<"/*************** test for remove(8) ***************/"<<endl;
    Mytree.remove(8);
    Mytree.printTree(cout);

    cout<<"/*************** test for Mytree2 = Mytree ***************/"<<endl;
    Mytree2 = Mytree;
    Mytree2.printTree(cout);

    cout<<"/*************** test for findMin() ***************/"<<endl;
    cout<<"The minmum of Mytree is :"<<Mytree.findMin()<<endl<<endl;


    cout<<"/*************** test for findMax() ***************/"<<endl;
    cout<<"The maxmum of Mytree is :"<<Mytree.findMax()<<endl<<endl;


    cout<<"/*************** test for contains(5) / contains(7) ***************/"<<endl;
    cout << 5 <<  " is" << (Mytree.contains(5) ? " " : " not ") << "in Mytree" << endl;
    cout << 7 <<  " is" << (Mytree.contains(7) ? " " : " not ") << "in Mytree" << endl;

    cout<<"/*************** test for makeEmpty() + isEmpty() ***************/"<<endl;
    Mytree2.makeEmpty();
    cout<<"Mytree2 is "<< (Mytree2.isEmpty()? " " : "not ") <<"empty  after makeEmpty()  "<<endl;
    cout<<"Mytree  is "<< (Mytree.isEmpty()? " " : "not ") <<"empty  without makeEmpty()  "<<endl<<endl;




}