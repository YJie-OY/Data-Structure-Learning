#include<iostream>
#include<time.h>
#include<cstdlib>
#include<cmath>
#include"MySort.h"
using namespace std;

template<typename Comparable>
void MergeSort(vector<Comparable> &a,int start,int stop)
{
    vector<Comparable> tmp(a.size());
    MergeSort(a,tmp,start,stop);
}

// 这个函数用于检验数组array是否已经有序
template<typename Comparable>
bool func_test(vector<Comparable> &array)
{
    for(int i=0 ; i<array.size()-1  ; i++)
    {
        if(array[i] > array[i+1])
            return false;
    }
    return true;
}

int main()
{

    cout<<endl<<"/******************************  功能测试  **********************************/"<<endl;
    vector<int> test = {123,234,1,34,6,4,0,8,19,39,45,3};
    cout<<endl<<"排序前：";
    for(int i=0 ; i<test.size() ; i++)
        cout<<test[i]<<"  ";

    MergeSort<int>(test,0,test.size()-1);

    cout<<endl<<"排序后：";
    for(int i=0 ; i<test.size() ; i++)
        cout<<test[i]<<"  ";

    cout<<endl<<"经过检测,vector test"<<(func_test(test)?"已经":"不是")<<"从小到大排序"<<endl;
    

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
    MergeSort<int>(Vector1,0,Vector1.size()-1);
    clock_t end1 = clock();
    cout<<"Running Time N=1000     \t: \t" << (double) (end1 - start)/CLOCKS_PER_SEC*1000<<"    \t ms "<<endl;

    MergeSort<int>(Vector2,0,Vector2.size()-1);
    clock_t end2 = clock();
    cout<<"Running Time N=10000    \t: \t" << (double) (end2 - end1)/CLOCKS_PER_SEC*1000<<"    \t ms"<<endl;

    MergeSort<int>(Vector3,0,Vector3.size()-1);
    clock_t end3 = clock();
    cout<<"Running Time N=100000   \t: \t" << (double) (end3 - end2)/CLOCKS_PER_SEC*1000<<"   \t ms"<<endl;

    MergeSort<int>(Vector4,0,Vector4.size()-1);
    clock_t end4 = clock();
    cout<<"Running Time N=1000000  \t: \t" << (double) (end4 - end3)/CLOCKS_PER_SEC*1000<<" \t ms"<<endl;

    MergeSort<int>(Vector5,0,Vector5.size()-1);
    clock_t end5 = clock();
    cout<<"Running Time N=10000000 \t: \t" << (double) (end5 - end4)/CLOCKS_PER_SEC*1000<<"\t ms"<<endl;

    MergeSort<int>(Vector6,0,Vector6.size()-1);
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