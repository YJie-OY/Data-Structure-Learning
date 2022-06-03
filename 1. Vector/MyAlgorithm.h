#ifndef MYALGORITHM
#define MYALGORITHM
#include<iostream>
/* ============= copy() =============
功能
    复制 [first, last) 所定义的范围中的元素到始于 d_first 的另一范围。
    若 dfirst 在复制范围中，需要用 copy_back()代替
参数
- first:开始复制的位置
- last: 结束复制的位置
- d_first: 目标范围的起始
返回值
    指向目标范围中最后复制元素的下个元素的输出迭代器。
复杂度
    last - first
 ============= copy() ============= */

template<class Input_iterator, class Output_iterator>
Output_iterator Copy(Input_iterator first, Input_iterator last, Output_iterator d_first)
{
    while (first != last) 
        *d_first++ = *first++;
    return d_first;
}

/* ============= copy_backward() =============
功能
    复制来自 [first, last) 所定义范围的元素，到终于 d_last 的范围。以逆序复制元素（首先复制末元素），但保持其相对顺序。
    若 dlast 在复制范围中，需要用 copy() 代替
参数
- first:开始复制的位置
- last: 结束复制的位置
- d_first: 目标范围的起始
返回值
    指向最后复制元素的迭代器。
复杂度
    last - first
 ============= copy_backward() ============= */

template< class Input_iterator, class Output_iterator >
Output_iterator Copy_backward(Input_iterator first, Input_iterator last, Output_iterator d_last)
{
    while (first != last) 
        *(--d_last) = *(--last);
    return d_last;
}

/* ============= move() =============
功能介绍
    移动范围 [first, last) 中的元素到始于 d_first 的另一范围，从首元素开始逐次到末元素。
    此操作后被移动范围中的元素将仍然含有适合类型的合法值，但不必与移动前的值相同。

参数
- first, last:要移动的元素范围
- d_first:目标范围起始。若 d_first 在范围 [first, last) 中则行为未定义。

返回值
    指向最后移动元素后一位置的迭代器
复杂度
    last - first

============= move() ============= */

template<class Input_iterator, class Output_iterator>
Output_iterator move(Input_iterator first, Input_iterator last, Output_iterator d_first)
{
   while (first != last)
       *d_first++ = std::move(*first++);
   return d_first;
}

/* ============= move_backward() =============
功能介绍
    移动范围 [first, last) 中的元素到终于 d_last 的另一范围，从末元素开始逐次到首元素。
    此操作后被移动范围中的元素将仍然含有适合类型的合法值，但不必与移动前的值相同。

参数
- first, last:要移动的元素范围
- d_last:目标范围末尾。若 d_last 在范围 [first, last) 中则行为未定义。
返回值
    目标范围中的迭代器，指向最后移动的元素。
复杂度
    last - first
============= move_backward() ============= */
template<class Input_iterator, class Output_iterator>
Output_iterator move_backward(Input_iterator first, Input_iterator last, Output_iterator d_last)
{
   while (first != last)
       *(--d_last) = std::move(*(--last));
   return d_last;
}

/* ============= fill() =============
功能介绍
    赋值给定的 value 给 [first, last) 中的元素。
参数
- first, last:要移动的元素范围
- value: 要赋的值
返回值
    无
复杂度
    last - first
============= Fill() ============= */
template< class Input_iterator, class value_type >
void Fill(Input_iterator first, Input_iterator last, const value_type& value)
{
    for (; first != last; ++first) 
        *first = value;
}
#endif
