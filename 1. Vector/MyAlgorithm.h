#ifndef MYALGORITHM
#define MYALGORITHM
#include<iostream>
/* ============= copy() =============
����
    ���� [first, last) ������ķ�Χ�е�Ԫ�ص�ʼ�� d_first ����һ��Χ��
    �� dfirst �ڸ��Ʒ�Χ�У���Ҫ�� copy_back()����
����
- first:��ʼ���Ƶ�λ��
- last: �������Ƶ�λ��
- d_first: Ŀ�귶Χ����ʼ
����ֵ
    ָ��Ŀ�귶Χ�������Ԫ�ص��¸�Ԫ�ص������������
���Ӷ�
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
����
    �������� [first, last) �����巶Χ��Ԫ�أ������� d_last �ķ�Χ����������Ԫ�أ����ȸ���ĩԪ�أ��������������˳��
    �� dlast �ڸ��Ʒ�Χ�У���Ҫ�� copy() ����
����
- first:��ʼ���Ƶ�λ��
- last: �������Ƶ�λ��
- d_first: Ŀ�귶Χ����ʼ
����ֵ
    ָ�������Ԫ�صĵ�������
���Ӷ�
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
���ܽ���
    �ƶ���Χ [first, last) �е�Ԫ�ص�ʼ�� d_first ����һ��Χ������Ԫ�ؿ�ʼ��ε�ĩԪ�ء�
    �˲������ƶ���Χ�е�Ԫ�ؽ���Ȼ�����ʺ����͵ĺϷ�ֵ�����������ƶ�ǰ��ֵ��ͬ��

����
- first, last:Ҫ�ƶ���Ԫ�ط�Χ
- d_first:Ŀ�귶Χ��ʼ���� d_first �ڷ�Χ [first, last) ������Ϊδ���塣

����ֵ
    ָ������ƶ�Ԫ�غ�һλ�õĵ�����
���Ӷ�
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
���ܽ���
    �ƶ���Χ [first, last) �е�Ԫ�ص����� d_last ����һ��Χ����ĩԪ�ؿ�ʼ��ε���Ԫ�ء�
    �˲������ƶ���Χ�е�Ԫ�ؽ���Ȼ�����ʺ����͵ĺϷ�ֵ�����������ƶ�ǰ��ֵ��ͬ��

����
- first, last:Ҫ�ƶ���Ԫ�ط�Χ
- d_last:Ŀ�귶Χĩβ���� d_last �ڷ�Χ [first, last) ������Ϊδ���塣
����ֵ
    Ŀ�귶Χ�еĵ�������ָ������ƶ���Ԫ�ء�
���Ӷ�
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
���ܽ���
    ��ֵ������ value �� [first, last) �е�Ԫ�ء�
����
- first, last:Ҫ�ƶ���Ԫ�ط�Χ
- value: Ҫ����ֵ
����ֵ
    ��
���Ӷ�
    last - first
============= Fill() ============= */
template< class Input_iterator, class value_type >
void Fill(Input_iterator first, Input_iterator last, const value_type& value)
{
    for (; first != last; ++first) 
        *first = value;
}
#endif
