#include<iostream>
#include<time.h>
#include<cstdlib>
#include<cmath>
#include"MySort.h"
using namespace std;
template<typename Comparable>
// 这个函数用于检验数组array是否已经有序
bool func_test(vector<Comparable> &array)
{
    for(int i=0 ; i<array.size()-1  ; i++)
    {
        if(array[i] > array[i+1])
        {
            if(i-1>=0) cout<<i-1<<"  "<<array[i-1]<<endl;
            cout<<i<<"  "<<array[i]<<endl;
            cout<<i+1<<"  "<<array[i+1]<<endl;
            if(i+2<array.size()) cout<<i+2<<"  "<<array[i+2]<<endl;
            return false;
        }
           
    }
    return true;
}


int main()
{



    cout<<endl<<"/******************************  插入排序功能测试  **********************************/"<<endl;
    vector<int> test = {123,234,1,34,6,4,0,8,19,39,45,3};
    cout<<endl<<"排序前：";
    for(int i=0 ; i<test.size() ; i++)
        cout<<test[i]<<"  ";
    cout<<endl<<"经过检测,vector test"<<(func_test(test)?"已经":"不是")<<"从小到大排序"<<endl;
    InsertionSort(test,0,test.size()-1);
    cout<<endl<<"排序后：";
    for(int i=0 ; i<test.size() ; i++)
        cout<<test[i]<<"  ";
    cout<<endl<<"经过检测,vector test"<<(func_test(test)?"已经":"不是")<<"从小到大排序"<<endl;

    cout<<endl<<"/******************************  快速排序功能测试  **********************************/"<<endl;
    vector<int> test2 = {123,234,1,34,6,4,0,8,19,39,45,3};
    for(int i=0 ; i<100 ; i++)
        test2.push_back(rand());
    cout<<endl<<"排序前：";
    for(int i=0 ; i<test2.size() ; i++)
        cout<<test2[i]<<"  ";
    cout<<endl<<"经过检测,vector test2"<<(func_test(test2)?"已经":"不是")<<"从小到大排序"<<endl;
    
    cout<<endl;
    QuickSort(test2,0,test2.size()-1);
    cout<<endl<<"排序后：";
    for(int i=0 ; i<test2.size() ; i++)
        cout<<test2[i]<<"  ";

    cout<<endl<<"经过检测,vector test2"<<(func_test(test2)?"已经":"不是")<<"从小到大排序"<<endl;

    cout<<endl<<"/******************************  快速排序功能测试2  **********************************/"<<endl;
    vector<int> test3 = {1,3,4,1,4,5,6,12,2,54};
    cout<<endl<<"排序前：";
    for(int i=0 ; i<test3.size() ; i++)
        cout<<test3[i]<<"  ";
    cout<<endl<<"经过检测,vector test3"<<(func_test(test3)?"已经":"不是")<<"从小到大排序"<<endl;
    QuickSort(test3,0,test3.size()-1);
    cout<<endl<<"排序后：";
    for(int i=0 ; i<test3.size() ; i++)
        cout<<test3[i]<<"  ";
    cout<<endl<<"经过检测,vector test3"<<(func_test(test3)?"已经":"不是")<<"从小到大排序"<<endl;


    cout<<endl<<"/******************************  快速排序功能测试3  - 防止死循环 **********************************/"<<endl;
    vector<int> test4 = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    cout<<endl<<"排序前：";
    for(int i=0 ; i<test4.size() ; i++)
        cout<<test4[i]<<"  ";
    cout<<endl<<"经过检测,vector test4"<<(func_test(test4)?"已经":"不是")<<"从小到大排序"<<endl;
    QuickSort(test4,0,test4.size()-1);
    cout<<endl<<"排序后：";
    for(int i=0 ; i<test4.size() ; i++)
        cout<<test4[i]<<"  ";
    cout<<endl<<"经过检测,vector test4"<<(func_test(test4)?"已经":"不是")<<"从小到大排序"<<endl;

    cout<<endl<<"/******************************  性能测试  **********************************/"<<endl;
    vector<int> Vector(1);
    for (int i=0 ; i<100000000 ; i++)
        Vector.push_back(rand()*rand()%200000000);

    vector<int> Vector1(Vector.begin(),Vector.begin()+1000);
    vector<int> Vector2(Vector.begin(),Vector.begin()+10000);
    vector<int> Vector3(Vector.begin(),Vector.begin()+100000);
    vector<int> Vector4(Vector.begin(),Vector.begin()+1000000);
    vector<int> Vector5(Vector.begin(),Vector.begin()+10000000);
    vector<int> Vector6(Vector.begin(),Vector.begin()+100000000);


    clock_t start = clock();

    QuickSort<int>(Vector1,0,Vector1.size()-1);
    clock_t end1 = clock();
    cout<<"Running Time N=1000     \t: \t" << (double) (end1 - start)/CLOCKS_PER_SEC*1000<<"    \t ms "<<endl;

    

    QuickSort<int>(Vector2,0,Vector2.size()-1);
    clock_t end2 = clock();
    cout<<"Running Time N=10000    \t: \t" << (double) (end2 - end1)/CLOCKS_PER_SEC*1000<<"    \t ms"<<endl;
    

    QuickSort<int>(Vector3,0,Vector3.size()-1);
    clock_t end3 = clock();
    cout<<"Running Time N=100000   \t: \t" << (double) (end3 - end2)/CLOCKS_PER_SEC*1000<<"   \t ms"<<endl;

    QuickSort<int>(Vector4,0,Vector4.size()-1);
    clock_t end4 = clock();
    cout<<"Running Time N=1000000  \t: \t" << (double) (end4 - end3)/CLOCKS_PER_SEC*1000<<" \t ms"<<endl;

    QuickSort<int>(Vector5,0,Vector5.size()-1);
    clock_t end5 = clock();
    cout<<"Running Time N=10000000 \t: \t" << (double) (end5 - end4)/CLOCKS_PER_SEC*1000<<"\t ms"<<endl;

    QuickSort<int>(Vector6,0,Vector6.size()-1);
    clock_t end6 = clock();
    cout<<"Running Time N=100000000\t: \t" << (double) (end6 - end5)/CLOCKS_PER_SEC*1000<<"\t ms"<<endl;

    cout<<"经过检测,vector1"<<(func_test(Vector1)?"已经":"不是")<<"从小到大排序"<<endl;
    cout<<"经过检测,vector2"<<(func_test(Vector2)?"已经":"不是")<<"从小到大排序"<<endl;
    cout<<"经过检测,vector3"<<(func_test(Vector3)?"已经":"不是")<<"从小到大排序"<<endl;
    cout<<"经过检测,vector4"<<(func_test(Vector4)?"已经":"不是")<<"从小到大排序"<<endl;
    cout<<"经过检测,vector5"<<(func_test(Vector5)?"已经":"不是")<<"从小到大排序"<<endl;
    cout<<"经过检测,vector6"<<(func_test(Vector6)?"已经":"不是")<<"从小到大排序"<<endl;

    return 0 ;
}
