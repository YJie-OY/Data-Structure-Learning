#include<iostream>
#include<vector>
using namespace std;

extern int g_loop=0;
extern int g_move=0;
void output_info(int *buff,int len, int flag)
{
    int i;
 
    if(0 == flag)
    {
        cout << "buff: ";
    }
    else
    {
        cout << "temp: ";
    }
 
    for(i = 0; i < len; ++i)
    {
        cout << *(buff + i) << " ";
    }
 
    cout << endl;
}
/**
 * 归并排序算法（驱动程序）
 */
template<typename Comparable>
void mergeSort(vector<Comparable> & a)
{
    vector<Comparable> tmpArray(a.size());

    mergeSort(a,tmpArray,0,a.size()-1);
}
/**
 * 进行递归调用的内部方法
 * a为Comparable项的数组
 * left为子数组最左元素的下标
 */
template<typename Comparable>
void mergeSort(vector<Comparable>&a,vector<Comparable>&tmpArray,int left,int right)
{
    
    
    ++g_loop;
    if(left<right)
    {
        int center=(left+right)/2;
        mergeSort(a,tmpArray,left,center);
        mergeSort(a,tmpArray,center+1,right);
        merge(a,tmpArray,left,center+1,right);
    }
    if(right - left == 1)       /* 左右数组中只有一个数据 */
    {
        cout<< "left=" << *(a + left) << " right=" << *(a + right) << " end"<<endl;
    }
    else if(right - left == 0)  /* 左数组中有一个数据，右数组空 */
    {
        cout<< "left=" << *(a + left) << " end"<<endl;
    }
 
    cout<<endl;
}
/**
 * 合并子数组已排序两半部分的内部方法
 * a 为Comparable 项的数组
 * tmpArray为放置归并结果的数组
 * leftPos为子数组最左元素的下标
 * rightPos为后半部分起点的下标
 * rightEnd为子数组最右元素的下标
 */
template<typename Comparable>
void merge(vector<Comparable>&a,vector<Comparable>&tmpArray,
            int leftPos,int rightPos,int rightEnd)
{
    int leftEnd = rightPos -1;
    int tmpPos = leftPos;
    int numElements =rightEnd - leftPos + 1;
    //主循环
    while(leftPos<= leftEnd && rightPos<=rightEnd)
        if(a[leftPos]<=a[rightPos])
            {tmpArray[tmpPos++]=std::move(a[leftPos++]);}
        else
            {tmpArray[tmpPos++]= std::move(a[rightPos++]);}
    while(leftPos<=leftEnd)//复制前半部分的剩余元素
        tmpArray[tmpPos++]=std::move(a[leftPos++]);
    while(rightPos<=rightEnd)//复制后半部分的剩余元素
        tmpArray[tmpPos++]=std::move(a[rightPos++]);
    //将tmpArray复制回原数组a
    output_info(a, 10, 0);
 
    tmpPos = 0;
    while(leftPos <= rightEnd)
    {
        a[leftPos++] = tmpArray[tmpPos++];
        ++g_move;
    }
 
    output_info(tmpArray, 10, 1);       
}


