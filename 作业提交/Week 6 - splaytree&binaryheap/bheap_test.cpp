#include"bheap.h"
#include<iostream>
#include<vector>
#include<initializer_list>
using namespace std;

int main()
{
    cout<<" ==================  test for constructor(initilizer_list)=================="<<endl;
    bheap<int> Mbheap1 = {1,11,22,3213,234,1212,12,34,56,28,9};
    
    cout<<" ==================  test for findmin =================="<<endl;
    cout<<Mbheap1.findmin()<<endl;

    cout<<" ==================  test for deletemin =================="<<endl;
    Mbheap1.deleteMin();
    cout<<Mbheap1.findmin()<<endl;
    Mbheap1.print();

    cout<<" ==================  test for constructor(default) + operator=(initializer_list) =================="<<endl;
    bheap<int> Mbheap2(100);
    Mbheap2 = {122,12312,12,456,123,68123,77};
    Mbheap2.print();

    cout<<" ==================  test for swap =================="<<endl;
    Mbheap2.swap(Mbheap1);
    Mbheap2.print();

    cout<<" ==================  test for operator = (rhs) =================="<<endl;
    Mbheap1 = Mbheap2;
    Mbheap1.print();

    cout<<" ==================  test for empty() =================="<<endl;
    cout<<"Mbheap2 is "<<(Mbheap2.Empty()?"empty ":"not empty ") << "without makeEmpty()"<<endl;
    Mbheap2.makeEmpty();
    cout<<"Mbheap2 is "<<(Mbheap2.Empty()?"empty ":"not empty ") << "after makeEmpty()"<<endl;


    cout<<" ==================  test for remove() =================="<<endl;
    Mbheap1.remove(2);
    Mbheap1.print();

    cout<<" ==================  test for keydec() =================="<<endl;
    Mbheap1.keydec(3,7);
    Mbheap1.print();

    cout<<" ==================  test for keyinc() =================="<<endl;
    Mbheap1.keyinc(2,100);
    Mbheap1.print();






    return 0;
}