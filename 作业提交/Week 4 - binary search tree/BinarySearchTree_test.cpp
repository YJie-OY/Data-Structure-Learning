#include"BinarySearchTree.h"
#include<iostream>
using namespace std;
int main()
{
    BinarySearchTree<int> Mytree;
    BinarySearchTree<int> Mytree2;

    BinarySearchTree<char>::BinaryNode a('a'), c('c'), b('b',&a,&c), e('e'), g('g'), f('f',&e,&g), d('d',&b,&f);
    BinarySearchTree<char>::BinaryNode h('h'), j('j'), i('i',&h,&j), l('l'), n('n'), m('m',&l,&n), k('k',&i,&m);
    BinarySearchTree<char>::BinaryNode r('r',&d,&k);

    cout<<"/*************** test for constructor(with BinaryNode) ***************/"<<endl;
    BinarySearchTree<char> Mytree3( &r );
    Mytree3.printTree(cout);

    cout<<"/*************** test for insert() ***************/"<<endl;
    Mytree.insert(1);
    Mytree.insert(5);
    Mytree.insert(2);
    Mytree.insert(9);
    Mytree.insert(11);
    Mytree.insert(20);
    Mytree.insert(6);
    Mytree.printTree(cout);

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
    cout<<"Mytree2 is "<< (Mytree2.isEmpty()? " " : "not") <<"empty  after makeEmpty()  "<<endl<<endl;



}