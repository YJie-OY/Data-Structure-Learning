#include"djset.h"
#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;

int main()
{
    djset set1(8);
cout<<endl<<"/*********************************  功能测试  *********************************/"<<endl;

    cout<<"/******************** print_father() 测试 *********************/"<<endl;
    cout<<"the status of set1 is"<<endl;
    set1.print_father();
    

    cout<<endl<<"/******************** size() 测试 ****************************/"<<endl;
    cout<<"the size of the set1 is  " ;
    cout<<set1.size()<<endl;

    cout<<endl<<"/******************** union() 测试 ****************************/"<<endl;
    set1.unionSets(1,2);
    set1.unionSets(3,5);
    set1.unionSets(0,7);
    set1.unionSets(3,4);
    set1.unionSets(0,6);
    set1.print_father();

    cout<<endl<<"/******************** find() 测试 ****************************/"<<endl;
    for(int i=0 ; i<set1.size() ; i++)
        printf("%d ---- %d\n",i,set1.find(i));

    cout<<endl<<"/******************** 复制构造测试 ****************************/"<<endl;
    djset set2(set1);
    set2.print_father();

    cout<<endl<<"/******************** swap()测试 ****************************/"<<endl;
    djset set3(8);
    cout<<"the status of the set3 is  " <<endl;
    set3.print_father();

    set3.swap(set1);
    cout<<"After swap, the status of the set3 is  " <<endl;
    set3.print_father();

    cout<<"After swap, the status of the set1 is  "<<endl ;
    set1.print_father();
  

}