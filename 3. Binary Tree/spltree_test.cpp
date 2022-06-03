#include"spltree.h"
#include<iostream>
#include<time.h>
#include<cstdlib>
#include<vector>
const int ARRAY_SIZE = 100000000;
using namespace std;

typedef DSAA::spltree<int>   btr_type;
typedef btr_type::size_type size_type;
typedef btr_type::node_type node_type;
typedef btr_type::node_ptr  node_ptr;


typedef DSAA::spltree<char>  cbtr_type;
typedef cbtr_type::size_type csize_type;
typedef cbtr_type::node_type cnode_type;
typedef cbtr_type::node_ptr  cnode_ptr;

namespace DSAA
{
    ostream& operator<< (ostream& os, const node_type& rhs)
    {
        return os << '[' << rhs.element << ']';
    }

    ostream& operator<< (ostream& os, const cnode_type & rhs)
    {
        return os << '[' << rhs.element << ']';
    }
}
template <typename T>
void copy_constructor_test(DSAA::spltree<T> A_tree)
{
    cout<<"the copy constructor is successful!" <<endl;
    cout<<A_tree<<endl;
}

int main()
{

    int* array = new int [ARRAY_SIZE] ;
    for(long long i=0 ; i<ARRAY_SIZE ; i++)
    {
        array[i] = rand();
    }

    cout<<"/****************************** test for constructor(default) ******************************/"<<endl;
    btr_type Mytree;
    btr_type Tree_list[6];
    vector<btr_type> v(3);
    btr_type* ptr = new btr_type[3];
    cout<<Mytree<<endl;



    cout<<"/****************************** test for operator= with initializer_list ******************************/"<<endl;
    Mytree = {6,7,8,9,10,123,12312,343,767,8984,0,34,45,213,456};
    cout<<"Mytree from  operator= with initializer_list  is like "<< endl <<Mytree<<endl;



    cout<<"/****************************** test for constructor(copy) ******************************/"<<endl;
    cnode_type a('a'), c('c'), b('b',&a,&c), e('e'), g('g'), f('f',&e,&g), d('d',&b,&f);
    cnode_type h('h'), j('j'), i('i',&h,&j), l('l'), n('n'), m('m',&l,&n), k('k',&i,&m);
    cnode_type r('r',&d,&k);  
    cbtr_type char_tree( &r );
    char_tree.printTree(cout);
    cout<<"The char_tree is like "<< endl <<char_tree<<endl;

    btr_type Mytree2(Mytree);
    cout<<"Mytree2 from copy constructor  is like "<< endl <<Mytree2<<endl;

    btr_type Mytree3;
    for(int i=0 ; i<20 ; i++)
        Mytree3.insert(array[i]);
    copy_constructor_test<int>(Mytree3);
 

    cout<<"/****************************** test for constructor(move) ******************************/"<<endl;
    btr_type tmp_tree = {1,2,3,4};
    btr_type Mytree4(std::move(tmp_tree));
    cout<<"Mytree4 from constructor(move)  is like "<< endl <<Mytree4<<endl;



    cout<<endl<<endl<<"/****************************** test for operator= : Mytree4 = Mytree ******************************/"<<endl;
    Mytree4 = Mytree3;
    cout<<"Mytree4 from operator=  is like "<< endl <<Mytree4<<endl;
    


    cout<<endl<<endl<<"/****************************** test for basic function : size() ******************************/"<<endl;
    cout<<"the size of mytree is "<<Mytree.size()<<endl;



    cout<<endl<<endl<<"/****************************** test for makeEmpty() + empty() ******************************/"<<endl;
    Mytree4.makeEmpty();
    cout<<"Mytree is "<< (Mytree.empty()? " " : "not ") <<"empty   "<<endl;
    cout<<"Mytree4  is "<< (Mytree4.empty()? " " : "not ") <<"empty  after makeEmpty()  "<<endl<<endl;

    


    cout<<endl<<endl<<"/****************************** test for findMin()/findmax() ******************************/"<<endl;
    cout<<"The minmum of Mytree is :"<<Mytree.findmin()<<endl<<endl;
    cout<<"The maxmum of Mytree is :"<<Mytree.findmax()<<endl<<endl;



    cout<<endl<<endl<<"/****************************** test for insert() ******************************/"<<endl;
    cout<<"======= test for bool ==========="<<endl;
    cout<<"insert 555 to Mytree is " << (Mytree.insert(555)?"":"not ") << "successful!"<<endl;
    cout<<"insert 10  to Mytree is " << (Mytree.insert(10 )?"":"not ") << "successful!"<<endl;
    cout<< Mytree <<endl;


    cout<<" ============= 性能测试 ============= "<<endl;
    clock_t start = clock();
    // for(int i=0 ; i<1000 ; i++)
    //     Tree_list[0].insert(i);
    // clock_t end1 = clock();
    // cout<<"Running Time 1: " << (double) (end1 - start)/CLOCKS_PER_SEC*1000<<"    ms \t" <<"Height = "<<Tree_list[0].theHeight()<<"\t size = "<<Tree_list[0].size()<<endl;

    // for(int i=0 ; i<10000 ; i++)
    //     Tree_list[1].insert(i);
    // clock_t end2 = clock();
    // cout<<"Running Time 2: " << (double) (end2 - end1)/CLOCKS_PER_SEC*1000<<"    ms \t" <<"Height = "<<Tree_list[1].theHeight()<<"\t size = "<<Tree_list[1].size()<<endl;

    // for (int i = 0; i < 100000; i++)
    //     Tree_list[2].insert(i);
    // clock_t end3 = clock();
    // cout<<"Running Time 3: " << (double) (end3 - end2)/CLOCKS_PER_SEC*1000<<"   ms \t" <<"Height = "<<Tree_list[2].theHeight()<<"\t size = "<<Tree_list[2].size()<<endl;

    // for (long long  i = 0; i < 1000000; i++)
    //     Tree_list[3].insert(i);
    // clock_t end4 = clock();
    // cout<<"Running Time 4: " << (double) (end4 - end3)/CLOCKS_PER_SEC*1000<<"  ms \t" <<"Height = "<<Tree_list[3].theHeight()<<"\t size = "<<Tree_list[3].size()<<endl;

    // for (long long  i = 0; i < 10000000; i++)
    //     Tree_list[4].insert(i);
    // clock_t end5 = clock();
    // cout<<"Running Time 5: " << (double) (end5 - end4)/CLOCKS_PER_SEC*1000<<" ms \t" <<"Height = "<<Tree_list[4].theHeight()<<"\t size = "<<Tree_list[4].size()<<endl;


















    cout<<endl<<endl<<"/****************************** test for contains() ******************************/"<<endl;
    cout<<"=========== test for bool ==========="<<endl;
    cout << 5 <<  " is" << (Mytree.contains(5) ? " " : " not ") << "in Mytree" << endl;
    cout << 767 <<  " is" << (Mytree.contains(767) ? " " : " not ") << "in Mytree" << endl;
    cout<< Mytree <<endl;

    // cout<<"=========== 性能测试 ============"<<endl;
    // clock_t start3 = clock();
    // for(int i=0 ; i<1000 ; i++)
    //     Tree_list[0].contains(1);
    // clock_t end3_1 = clock();
    // cout<<"Running Time 1: " << (double) (end3_1 - start3)/CLOCKS_PER_SEC*1000<<"    ms \t" <<"Height = "<<Tree_list[0].theHeight()<<"\t size = "<<Tree_list[0].size()<<endl;

    // for(int i=0 ; i<10000 ; i++)
    //     Tree_list[1].contains(1);
    // clock_t end3_2 = clock();
    // cout<<"Running Time 2: " << (double) (end3_2 - end3_1)/CLOCKS_PER_SEC*1000<<"    ms \t" <<"Height = "<<Tree_list[1].theHeight()<<"\t size = "<<Tree_list[1].size()<<endl;

    // for (int i = 0; i < 100000; i++)
    //     Tree_list[2].contains(1);
    // clock_t end3_3 = clock();
    // cout<<"Running Time 3: " << (double) (end3_3 - end3_2)/CLOCKS_PER_SEC*1000<<"   ms \t" <<"Height = "<<Tree_list[2].theHeight()<<"\t size = "<<Tree_list[2].size()<<endl;

    // for (long long  i = 0; i < 1000000; i++)
    //     Tree_list[3].contains(1);
    // clock_t end3_4 = clock();
    // cout<<"Running Time 4: " << (double) (end3_4 - end3_3)/CLOCKS_PER_SEC*1000<<"  ms \t" <<"Height = "<<Tree_list[3].theHeight()<<"\t size = "<<Tree_list[3].size()<<endl;

    // for (long long  i = 0; i < 10000000; i++)
    //     Tree_list[4].contains(1);
    // clock_t end3_5 = clock();
    // cout<<"Running Time 5: " << (double) (end3_5 - end3_4)/CLOCKS_PER_SEC*1000<<" ms \t" <<"Height = "<<Tree_list[4].theHeight()<<"\t size = "<<Tree_list[4].size()<<endl;













    cout<<endl<<endl<<"/****************************** test for remove() ******************************/"<<endl;
    cout<<"Removment(10) of Mytree is "<< (Mytree.remove(10)?"Successful!":"Unsuccessful!")<<endl;
    cout<<"Removment(101) of Mytree is "<< (Mytree.remove(101)?"Successful!":"Unsuccessful!")<<endl;
    cout<<Mytree<<endl;

    // cout<<"=========== 性能测试 ============"<<endl;
    // clock_t start2 = clock();

    // for(int i=0 ; i<1000 ; i++)
    //     Tree_list[0].remove(array[i]);
    // clock_t end2_1 = clock();
    // cout<<"Running Time 1: " << (double) (end2_1 - start2)/CLOCKS_PER_SEC*1000<<"    ms\t" <<"Height = "<<Tree_list[0].theHeight()<<"\t size = "<<Tree_list[0].size()<<endl;

    // for(int i=0 ; i<10000 ; i++)
    //     Tree_list[1].remove(array[i]);
    // clock_t end2_2 = clock();
    // cout<<"Running Time 2: " << (double) (end2_2 - end2_1)/CLOCKS_PER_SEC*1000<<"    ms\t" <<"Height = "<<Tree_list[1].theHeight()<<"\t size = "<<Tree_list[1].size()<<endl;

    // for (int i = 0; i < 100000; i++)
    //     Tree_list[2].remove(array[i]);
    // clock_t end2_3 = clock();
    // cout<<"Running Time 3: " << (double) (end2_3 - end2_2)/CLOCKS_PER_SEC*1000<<"   ms\t" <<"Height = "<<Tree_list[2].theHeight()<<"\t size = "<<Tree_list[2].size()<<endl;

    // for (long long  i = 0; i < 1000000; i++)
    //     Tree_list[3].remove(array[i]);
    // clock_t end2_4 = clock();
    // cout<<"Running Time 4: " << (double) (end2_4 - end2_3)/CLOCKS_PER_SEC*1000<<"  ms\t" <<"Height = "<<Tree_list[3].theHeight()<<"\t size = "<<Tree_list[3].size()<<endl;

    // for (long long  i = 0; i < 10000000; i++)
    //     Tree_list[4].remove(array[i]);
    // clock_t end2_5 = clock();
    // cout<<"Running Time 5: " << (double) (end2_5 - end2_4)/CLOCKS_PER_SEC*1000<<" ms\t" <<"Height = "<<Tree_list[4].theHeight()<<"\t size = "<<Tree_list[4].size()<<endl;







    delete[] array;
    return 0;
}