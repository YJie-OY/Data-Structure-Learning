#include<iostream>
using namespace std;
#include<stddef.h>
#include"Avltree.h"
#include "stdio.h"    
#include "stdlib.h"    
#include "time.h" 
typedef DSAA::btree<int>   btr_type;
typedef btr_type::size_type size_type;
typedef btr_type::Avlnode_type Avlnode_type;
typedef btr_type::Avlnode_ptr  Avlnode_ptr;

namespace DSAA {
	ostream& operator<< (ostream& os, const Avlnode_type& rhs)
	{
		return os << '[' << rhs.data << ']';
	}
}

// ����һ�� min ~ max ֮����������� min, max
int rand(int min, int max)
{
	srand((unsigned int)time(NULL));

	return rand() % (max - min + 1) + min;
}

btr_type t;
int main() {
	cout << "======����insert()����======" << endl;

	t.insert(1);
	t.insert(69);
	t.insert(34);
	t.insert(4);
	t.insert(2);
	t.insert(9);
	t.insert(3);
	t.insert(-13);
	t.insert(-5);
	t.insert(0);
	t.insert(6);
	t.insert(99);
	
	cout << "======����printTree()����======" << endl;
	cout << "The data in 't' goes from small to large is: ";
	t.printTree();
	cout << endl << endl;
	cout << "Tree 't': " << endl;
	cout << t;

	cout << endl << endl << endl;
	cout << "======����remove(2)����:�Ƴ����к��е�����======" << endl;
	t.remove(2);
	cout << "Tree 't': " << endl;
	cout << t;

	cout << endl << endl << endl;
	cout << "======����remove(134)����:�Ƴ����в����е�����======" << endl;
	t.remove(134);
	cout << "Tree 't': " << endl;
	cout << t;

	cout << endl << endl << endl;
	cout << "======����findmin()����======" << endl;
	cout << "the smallest data in the tree is: " << t.findMin() << endl;

	cout << endl << endl;
	cout << "======����findmax()����======" << endl;
	cout << "the largest data in the tree is: " << t.findMax() << endl;

	cout << endl << endl;
	cout << "======����cantains(34)����======" << endl;
	t.contains(34);
	cout << endl << endl;

	cout << "======���Ը��ƹ��캯����clone()����:��t����t2======" << endl;
	btr_type t2;
	t2.btree::btree(t);
	cout << "Tree 't2': " << endl;
	cout << t2;
	cout << endl << endl << endl;

	cout << "======����size()����======" << endl;
	cout << "The size of the tree is:��" << t.size() << endl;
	cout << endl << endl;

	cout << "======����assign()����������t��ֵ���µ���t3======" << endl;
	btr_type t3;
	t3.assign(t);
	cout << "Tree 't3': " << endl;
	cout << t3;
	cout << endl << endl << endl;

	cout << "======����makeEmpty()����======" << endl;
	t.makeEmpty();
	cout << "Tree 't': ";
	cout << t;
	cout << endl << endl;


	cout << "======�ƶ���ֵʱ��ʱ�临�Ӷ�(����ʱ��)======" << endl;
	cout << "*    ��t2����11���ڵ㣬����ֵbtr_type(t2)�ƶ���ֵ����t_move" << endl;
	btr_type t_move;
	t_move = btr_type(t2);
	cout << "Tree 't_move': " << endl;
	cout << t_move;
	cout << endl;
	cout << "*====�ƶ���ֵ��ɺ󣬷������нڵ���ܴ���Ϊ�� " << t_move.tim_clone << endl;
	cout << "*====���ڷ��ʽڵ��ܴ����븳ֵ�ڵ������޹أ������ƶ���ֵ��Ҫ���ĳ���ʱ�䡣" << endl << endl<< endl;


	cout << "======���ø��ƹ��캯��ʱ��ʱ�临�Ӷȣ�����ʱ�䣩======" << endl;
	cout << "*    ��t3����11���ڵ㣬��t3���ƹ�����t_copy" << endl;
	btr_type t_copy;
	t_copy.btree::btree(t3);
	cout << "Tree 't_copy': " << endl;
	cout << t_copy;
	cout << endl;
	cout << "*====���ƹ�����ɺ󣬷������нڵ���ܴ���Ϊ�� " << t_copy.tim_clone << endl;
	cout << "*====����11��11�������ʽڵ��ܴ������ڸ��ƽڵ����������Ե��ø��ƹ��캯����Ҫ��������ʱ�䡣" << endl << endl<< endl;

	cout << "======���в���ڵ�ʱ��ʱ�临�Ӷȣ�����ʱ�䣩======" << endl;
	cout << "*    �������200��0-1000֮�����������������a��" << endl;
	cout << "*    ������a�е���ͨ��insert()��������һ�ÿ���t4" << endl;
	cout << "*    �����������з������нڵ���ܴ���" << endl;

	btr_type t4;
	int a[200];
	int b[200];
	for (int i = 0; i < 200; i++) {
		a[i] = rand() % (1000);
	}
	for (int i = 0; i < 200; i++) {
		t4.insert_time(a[i]);
	}

	cout << "Tree 't4': " << endl;
	cout << t4;
	cout << endl;
	cout << "*====������ɺ󣬷������нڵ���ܴ���Ϊ�� " << t4.tim_insert << endl;
	cout << "*====��֪logN��log200��7.645�����ϼ������ɵ�ÿ�β���ķ��ʽڵ�ƽ������Ϊ ";
	float tim_in = t4.tim_insert;
	printf("%4.3f", tim_in / 200);
	cout << endl;
	cout << "*====˵�����˼�����ƫС����Ϊ�������ݲ��ϲ��룬��t4������������N��0��Ϊ200��" << endl;
	cout << "*====����7.645��" << tim_in / 200 << "��Ϊ�ӽ���˵������������Ҫ���Ķ���ʱ�䡣" << endl << endl;

	cout << "======���в�ѯ�ڵ�ʱ��ʱ�临�Ӷ�======" << endl;
	cout << "*    ���������200��0-1000֮�����������������b��" << endl;
	cout << "*    ͨ��contains()��������t4�в�ѯ����b�е���" << endl;
	cout << "*    �����ѯ�����з������нڵ���ܴ���" << endl << endl;

	for (int i = 0; i < 200; i++) {
		b[i] = rand() % (1000);
	}
	for (int i = 0; i < 200; i++) {
		t4.contains_time(b[i]);
	}

	cout << "*====��ѯ��ɺ󣬷������нڵ���ܴ���Ϊ�� " << t4.tim_contains << endl;
	cout << "*====��֪log200��7.645�����ϼ������ɵ�ÿ�β�ѯ�ķ��ʽڵ�ƽ������Ϊ ";
	float tim_con = t4.tim_contains;
	printf("%4.3f", tim_con/200);
	cout << endl;
	cout << "*====����7.645��" << tim_con / 200 << "��Ϊ�ӽ���˵����ѯ������Ҫ���Ķ���ʱ�䡣" << endl;

	return 0;
}


//btr_type t4;
//int a[500];
//for (int i = 0; i < 500; i++) {
//	a[i] = rand() % (200);
//}
//clock_t start1, finish1;
//double  duration1;
///* ����һ���¼�������ʱ��*/
//cout << "Time to insert 500 data is";
//start1 = clock();
//for (int i = 0; i < 500; i++) {
//	t4.insert_time(a[i]);
//}
//finish1 = clock();
//duration1 = (double)(finish1 - start1) / CLOCKS_PER_SEC;
//printf("%50.49f seconds\n", duration1);
//cout << t4.time() << endl;
//
////cout << t4;
//
//clock_t start2, finish2;
//double  duration2;
///* ����һ���¼�������ʱ��*/
//cout << "Time to copy 500 times is";
//start2 = clock();
//for (int i = 0; i < 500; i++) {
//	t4.contains_time(a[i]);
//}
//finish2 = clock();
//duration2 = (double)(finish2 - start2) / CLOCKS_PER_SEC;
//printf("%50.49f seconds\n", duration2);
//cout << t4.time_contains() << endl;
