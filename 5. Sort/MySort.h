/*****************************************************
 * 本库中主要排序算法为归并排序,插入排序与快速排序
 * 其中插入排序的存在主要为快速排序在小区间段上排序服务
 * 本库中所有的排序总是从小到大排序
 * 本库中所有的排序区间为闭区间
 *****************************************************/
# ifndef MYSORT_H
# define MYSORT_H

#include <iostream>
#include <vector>
using namespace std;

/************************** 归并排序 ************************
 * 算法复杂度：NlogN
 * 算法稳定性：十分稳定,最坏情况不会破坏复杂度的量级,可以认为没有敌对策略.
 * 空间复杂度：2N
 * 算法思想  ： 分治算法,由两个已经有序的数组合并为一个大的有序数组。
 * 注意     ： 本代码采用闭区间[left,right]排序
 ************************** 归并排序 ************************/

template <typename Comparable>
void MergeSort(vector<Comparable> &a, vector<Comparable> &tmp ,int left, int right)
{
    if(left >= right) return;
    int mid = (left+right) / 2;
    MergeSort(a,tmp,left,mid);
    MergeSort(a,tmp,mid+1,right);

    int Lpos = left;
    int Lend = mid;
    int Rpos = mid+1;
    int Rend = right;
    int pos = left;

    while(Lpos<=Lend && Rpos<=Rend)
    {
        if(a[Lpos] <= a[Rpos])
            tmp[pos++] = a[Lpos++];
        else
            tmp[pos++] = a[Rpos++];

    }

    while(Lpos <= Lend)
        tmp[pos++] = a[Lpos++];
    
    while(Rpos <= Rend)
        tmp[pos++] = a[Rpos++];

    for(int i=left; i<=right ; i++)
    {
        // cout<<"a="<<a[i]<<"  "<<"tmp="<<tmp[i]<<endl;
        a[i] = tmp[i]; 
    }
}


/******************************** 插入排序 ********************************
 * 算法复杂度：最好：N ; 最坏：N^2
 * 算法稳定性：不稳定,敌对策略会破坏复杂度量级,最好的情况为已经有序；最坏的情况
 *            为完全逆序
 * 空间复杂度：N
 * 算法思想  ： 对于一个元素,我们想要把它插入一个正确的位置,假设其前面的元素已经有序,
 *              显然,只要逐个向前比较就可以知道其正确的位置在哪,调换后就会形成一个
 *              更大的有序数组
 * 注意      ： 本代码采用闭区间[begin,end]排序 ，由于QuickSort中将会用到插入排序，
 *              所以必须本代码必须要在Quicksort前实现
 ******************************** 插入排序 ********************************/
template <typename Comparable>
void InsertionSort(vector<Comparable> &a , int begin,int end)
{
    if(begin == end) return;
    for(int i=begin+1 ; i<=end ; i++)
    {
        Comparable tmp = a[i];
        int j = i;
        for(; j>begin && (a[j-1]>tmp); --j)
        {
                a[j] = a[j-1];
        }

        a[j]  = std::move(tmp);
        // 展示排序过程
        // for(int k=begin ; k<=end ; k++)
        //     cout<<a[k]<<" ";
        // cout<<endl;
    }
}


/******************************** 快速排序 ********************************
 * 算法复杂度：最好与平均：NlogN , 最坏：N^2
 * 算法稳定性：看上去不太稳定,敌对策略会破坏复杂度量级,但是实际上敌对策略不常出现,总体
 *             来说是一个非常不错的算法,并且其空间开销并不如归并排序那么大
 * 空间复杂度：N
 * 算法思想  ： 不再依赖于子数组的有序性
 * 注意      ： 本代码采用闭区间[start,stop]排序
 ******************************** 快速排序 ********************************/
// 三数中值分割法选取枢纽元,将left,right,middle的值大小做调整
// 将三个元中的最小元调至最左端,第二元调至最右端来用作枢纽元,最大元调至右端倒数第二作为快排末尾.
// 所以最终的结果是,a[left]为最小元,a[right]为中间元,a[center]为最大元.
template <typename Comparable>
const Comparable & median(vector<Comparable> &a, int left, int right)
{
    int center = (left+right)/2;
    if(a[left] > a[center]) std::swap(a[left],a[center]);
    if(a[left] > a[right]) std::swap(a[left],a[right]);
    if(a[right] > a[center]) std::swap(a[right],a[center]);

    return a[right];
}

template <typename Comparable>
void QuickSort(vector<Comparable> & a, int begin, int end)
{
    // 当数组数量小的时候，采用插入排序而不是快速排序
    if(begin+7 >= end)
        InsertionSort<Comparable>(a,begin,end);
    else
    {
        const Comparable &pivot = median(a,begin,end);
        int i = begin;
        int j = end-1;
        
        // 将小于主元的元素放到左边
        // 将大于主元的元素放在右边
        // 对于等于主元的元素,实际上放在哪两边都是没有关系的.可以不作处理.
        for(; ;)
        {
            // 一种情况需要特殊处理,不然会有死循环,而且不报错
            if(a[i] == a[j] && a[i]==pivot)
            {
                i++;j--;
            }
            while(a[i] < pivot) i++;
            while(a[j] > pivot) j--;

            if(i<j)
                std::swap(a[i],a[j]);
            else
                break; 
        }
        std::swap(a[i],a[end]);
        // 从这里其实也可以看出,在一轮的QuickSort中,其实确定了一个值的正确位置,也就是主元.
        QuickSort(a,begin,i-1);
        QuickSort(a,i+1,end);
    }
}


/*********************************************************************************
 * 有关排序的稳定性的介绍：
 * 若一个排序算法，对于两个关键字相同的对象,理论上来说这两个值是可以不必交换位置的,若在
 * 当前的排序算法中,这两个对象实际上没有进行交换的话,那么我们就说这个算法是稳定的,反之,我们
 * 称这个算法是不稳定的.
 *********************************************************************************/















# endif