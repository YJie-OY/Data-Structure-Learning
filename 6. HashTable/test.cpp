#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include<random>
#include<ctime>
#include "SeparateChain.h"

using namespace std;
int main( )
{
    cout<<endl<<"=====================插入测试====================="<<endl;
    Hash<int> ta;
    Hash<int> tb;
    Hash<int> tc;
    Hash<int> td;
    
    clock_t starta = clock();
    for(int i = 0; i < 100; ++i)
        ta.insert(i);
    clock_t enda = clock();
    cout<<"插入个数为：100."<<"插入时间为："<<(double)(enda - starta)/CLOCKS_PER_SEC*1000<<" ms \t"<<endl;


    clock_t startb = clock();
    for(int i = 0; i < 1000; ++i)
        tb.insert(i);
    clock_t endb = clock();
    cout<<"插入个数为：1000."<<"插入时间为："<<(double)(endb - startb)/CLOCKS_PER_SEC*1000<<" ms \t"<<endl;


    clock_t startc = clock();
    for(int i = 0; i < 10000; ++i)
        tc.insert(i);
    clock_t endc = clock();
    cout<<"插入个数为：10000."<<"插入时间为："<<(double)(endc - startc)/CLOCKS_PER_SEC*1000<<" ms \t"<<endl;


    clock_t startd = clock();
    for(int i = 0; i < 100000; ++i)
        td.insert(i);
    clock_t endd = clock();
    cout<<"插入个数为：100000."<<"插入时间为："<<(double)(endd - startd)/CLOCKS_PER_SEC*1000<<" ms \t"<<endl;



    cout<<endl<<"=====================删除测试====================="<<endl;
    clock_t startaa = clock();
    for(int i = 0; i < 100; ++i)
        ta.remove(i);
    clock_t endaa = clock();
    cout<<"删除个数为：100."<<"删除时间为："<<(double)(endaa - startaa)/CLOCKS_PER_SEC*1000<<" ms \t"<<endl;


    clock_t startbb = clock();
    for(int i = 0; i < 1000; ++i)
        tb.remove(i);
    clock_t endbb = clock();
    cout<<"删除个数为：1000."<<"删除时间为："<<(double)(endbb - startbb)/CLOCKS_PER_SEC*1000<<" ms \t"<<endl;


    clock_t startcc = clock();
    for(int i = 0; i < 10000; ++i)
        tc.remove(i);
    clock_t endcc = clock();
    cout<<"删除个数为：10000."<<"删除时间为："<<(double)(endcc - startcc)/CLOCKS_PER_SEC*1000<<" ms \t"<<endl;


    clock_t startdd = clock();
    for(int i = 0; i < 100000; ++i)
        td.remove(i);
    clock_t enddd = clock();
    cout<<"删除个数为：100000."<<"删除时间为："<<(double)(enddd - startdd)/CLOCKS_PER_SEC*1000<<" ms \t"<<endl;
    return 0;
}