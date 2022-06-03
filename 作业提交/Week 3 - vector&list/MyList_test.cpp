#include<iostream>
using namespace std;

#include"MyList_iterator.h"
#include"MyAlgorithm.h"
List<int> mylist;
void test_output()
{
    cout<<"Size =  "<<mylist.size()<<endl;
    for(List<int>::iterator itr0 = mylist.begin(); itr0!= mylist.end() ; itr0++)
    {
        cout<< *itr0 << "  ";
    }
    cout<<endl<<endl<<endl;
}

int main()
{
     cout<<"====== test for push_back() ======"<<endl;
     mylist.push_back(111);
     mylist.push_back(222);
     mylist.push_back(333);
     mylist.push_back(444);
     mylist.push_back(555);
     mylist.push_back(666);
     mylist.push_back(777);
     mylist.push_back(888);
    test_output();

    
    cout<<"====== test for push_front(123) ======"<<endl;
    mylist.push_front(123);
    test_output();

    cout<<"====== test for front() ======"<<endl;
    cout<<mylist.front()<<endl<<endl<<endl;

    cout<<"====== test for back() ======"<<endl;
    cout<<mylist.back()<<endl<<endl<<endl;

    
    cout<<"====== test for pop_front() ======"<<endl;
    mylist.pop_front();
    test_output();

    cout<<"====== test for pop_back() ======"<<endl;
    mylist.pop_back();
    test_output();

    cout<<"====== test for insert(itr+2,999) ======"<<endl;
    List<int>::iterator itr = mylist.begin();
    mylist.insert(itr+2,999);
    test_output();
    
    cout<<"====== test for erase(itr+2) ======"<<endl;
    mylist.erase(itr+2);
    test_output();

    cout<< " ====== test for  resize(5) ====== "<<endl;
    mylist.resize(5);   
    test_output();

    cout<< " ====== test for  resize(8) ====== "<<endl;
    mylist.resize(8,666);
    test_output();

    cout<<" ======== test for merge() ========"<<endl;
    List<int> mylist_2(1,0);
    mylist_2.push_back(123);
    mylist_2.push_back(223);
    mylist_2.push_back(323);
    mylist_2.push_back(667);
    mylist_2.push_back(1000);
    mylist_2.push_back(1000);
    mylist.merge(mylist_2);
    test_output();


    cout<<" ======== test for unique() ========"<<endl;
    mylist.unique();
    test_output();

    cout<<" ======== test for remove(1111) ========"<<endl;
    mylist.push_back(1111);
    mylist.push_back(1111);
    mylist.push_back(1111);
    mylist.insert(mylist.begin()+7,1111);
    test_output();
    mylist.remove(1111);
    test_output();

    cout<<" ======== test for reverse() ========"<<endl;
    mylist.reverse();
    test_output();

    cout<<" ======== test for splice() =========="<<endl;
    List<int>::iterator pos = mylist.begin()+3;
    List<int> mylist_3(5,999);
    List<int>::const_iterator first = mylist_3.begin();
    List<int>::const_iterator last = mylist_3.begin()+3;
    mylist.splice(pos,mylist_3,first,last);
    cout<<"the new Size of the mylist_3 = " << mylist_3.size()<<endl;
    test_output();

    cout<<" ======= test for swap() ==========" <<endl;
    List<int> mylist_4(5,1234);
    mylist.swap(mylist_4);
    cout<<"Size of mylist_4 =  "<<mylist_4.size()<<endl;
    for(List<int>::iterator itr0 = mylist_4.begin(); itr0!= mylist_4.end() ; itr0++)
    {
        cout<< *itr0 << "  ";
    }
    cout<<endl;
    test_output();
    
    cout<<"========= test for reverse_iterator ======="<<endl;
    mylist.swap(mylist_4);
    test_output();
    List<int>::reverse_iterator ritr = mylist.rbegin();
    for(;ritr!=mylist.rend() ; ritr++)
        cout<<*ritr<<"  ";
    cout<<endl<<endl<<endl;





    cout<<" ========= test for clear() ========="<<endl;
    mylist.clear();
    mylist_2.clear();
    mylist_3.clear();
    mylist_4.clear();
    test_output();


    cout<<"율율율율"<<endl;
    

    return 0;
}
