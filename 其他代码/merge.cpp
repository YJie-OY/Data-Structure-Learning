#include<iostream>
#include<vector>
#include"merge.h"
using namespace std;

int main()
{
    int array[10]= {10,9,8,7,6,5,4,3,2,1};
    int*temp=new int[10];
    
    mergeSort(array,temp,0,9);
 
    output_info(array, 10, 0);

    cout << endl;
    cout << "move=" << g_move << endl;
    cout << "loop=" << g_loop << endl;
    delete[] temp;
    return 0;
}