#include<iostream>
using namespace std;

#include"MyVector2.h"
#include"MyAlgorithm.h" 
Vector<int> array(10,111);
Vector<int> array2(5,6);
void test_output()
{
    std::cout<<"size = "<<array.size()<<"   "<<"capacity = " << array.capacity()<<std::endl;
    for(int i=0 ; i<array.size();i++)
        std::cout<<array[i]<<"  ";
    std::cout<<std::endl<<std::endl;
}

int main()
{
    
    std::cout<<"============= test for Construction Function! ============="<<std::endl;
    test_output();

    std::cout<<"============= test for front() = 222 ============="<<std::endl;
    array.front() = 222;
    test_output();
    
    std::cout<<"============= test for back() = 333 ============="<<std::endl;
    array.back() = 333;
    test_output();


    std::cout<<"============= test for push_back(444)! ============= "<<std::endl;
    array.push_back(444);
	test_output();

    std::cout<<" ============= test for push_front(555)! ============= "<<std::endl;
    array.push_front(555);
    test_output();

    std::cout<<" ============= test for pop_back()! ============="<<std::endl;
	array.pop_back();
    test_output();
    
    std::cout<<" ============= test for pop_front()! ============="<<std::endl;
	array.pop_front();
    test_output();
    
    
    std::cout<<"============= test for operator[]: array[5] = 10! ============="<<std::endl;
    array[5] = 777;
    test_output();
    
    
    std::cout<<"============= test for at():array.at(6) = 20; ============="<<std::endl;
    array.at(6) = 888;
    test_output();

	 
    std::cout<<"============= test for insert(begin()+7,70)! ============="<<std::endl;
    Vector<int>::iterator itr=array.begin();
    Vector<int>::iterator p = array.insert(itr+7,999);
    test_output();

    
    
    std::cout<<"============= test for erase(itr=7)! ============="<<std::endl;
    Vector<int>::iterator p2 = array.erase(itr);
    test_output();

      
    std::cout<<"============= test for resize(20,88)! ============="<<std::endl;
	array.resize(20,111);
    test_output();

    std::cout<<"============= test1 for reserve(70)! ============="<<std::endl;
	array.reserve(70);
    test_output();

    std::cout<<"============= test2 for reserve(6)! ============= "<<std::endl;
	array.reserve(6);
    test_output();

    

    std::cout<<" ============= test for iterator ! ============= "<<std::endl;
    itr = array.begin();
    for(;itr!=array.end();itr++)
        cout<<*itr<<"  ";
    cout<<endl<<endl<<endl;


    std::cout<<" ============= test for const_iterator ! ============= "<<std::endl;

    Vector<int>::const_iterator citr = array.cbegin();
    for (; citr!=array.cend() ; citr++)
    {
        cout<<*citr<<"  ";
    }
    cout<<endl<<endl<<endl;
    

    std::cout<<" ============= test for reverse_iterator ! ============= "<<std::endl;
    Vector<int>::reverse_iterator ritr = array.rbegin();
    do
    {
        std::cout<<*ritr<<"  ";

    } while (ritr++ != array.rend());
    
    cout<<endl<<endl<<endl;



    std::cout<<" ============= test for const_reverse_iterator ! ============= "<<std::endl;
    Vector<int>::const_reverse_iterator critr = array.crbegin();
    do
    {
        std::cout<<*critr<<"  ";
    } while (critr++ != array.crend());
    
    cout<<endl<<endl<<endl;

    std::cout<<" ============= test for swap(array(5,6))! ============= "<<std::endl;
    array.swap(array2);
    test_output();



    std::cout<<" ============= test for clear()! ============= "<<std::endl;
    array.clear();
    test_output();

    cout<<"啦啦啦"<<endl;
    
    return 0;
} 
