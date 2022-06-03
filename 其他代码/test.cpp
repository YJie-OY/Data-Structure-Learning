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

// 产生一个 min ~ max 之间的数，包含 min, max
int rand(int min, int max)
{
	srand((unsigned int)time(NULL));

	return rand() % (max - min + 1) + min;
}

btr_type t;
int main() {
	cout << "======测试insert()函数======" << endl;

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
	
	cout << "======测试printTree()函数======" << endl;
	cout << "The data in 't' goes from small to large is: ";
	t.printTree();
	cout << endl << endl;
	cout << "Tree 't': " << endl;
	cout << t;

	cout << endl << endl << endl;
	cout << "======测试remove(2)函数:移除树中含有的数据======" << endl;
	t.remove(2);
	cout << "Tree 't': " << endl;
	cout << t;

	cout << endl << endl << endl;
	cout << "======测试remove(134)函数:移除树中不含有的数据======" << endl;
	t.remove(134);
	cout << "Tree 't': " << endl;
	cout << t;

	cout << endl << endl << endl;
	cout << "======测试findmin()函数======" << endl;
	cout << "the smallest data in the tree is: " << t.findMin() << endl;

	cout << endl << endl;
	cout << "======测试findmax()函数======" << endl;
	cout << "the largest data in the tree is: " << t.findMax() << endl;

	cout << endl << endl;
	cout << "======测试cantains(34)函数======" << endl;
	t.contains(34);
	cout << endl << endl;

	cout << "======测试复制构造函数和clone()函数:用t构造t2======" << endl;
	btr_type t2;
	t2.btree::btree(t);
	cout << "Tree 't2': " << endl;
	cout << t2;
	cout << endl << endl << endl;

	cout << "======测试size()函数======" << endl;
	cout << "The size of the tree is:　" << t.size() << endl;
	cout << endl << endl;

	cout << "======测试assign()函数：把树t赋值给新的树t3======" << endl;
	btr_type t3;
	t3.assign(t);
	cout << "Tree 't3': " << endl;
	cout << t3;
	cout << endl << endl << endl;

	cout << "======测试makeEmpty()函数======" << endl;
	t.makeEmpty();
	cout << "Tree 't': ";
	cout << t;
	cout << endl << endl;


	cout << "======移动赋值时的时间复杂度(常量时间)======" << endl;
	cout << "*    树t2含有11个节点，将右值btr_type(t2)移动赋值给树t_move" << endl;
	btr_type t_move;
	t_move = btr_type(t2);
	cout << "Tree 't_move': " << endl;
	cout << t_move;
	cout << endl;
	cout << "*====移动赋值完成后，访问所有节点的总次数为： " << t_move.tim_clone << endl;
	cout << "*====由于访问节点总次数与赋值节点总数无关，所以移动赋值需要消耗常量时间。" << endl << endl<< endl;


	cout << "======调用复制构造函数时的时间复杂度（线性时间）======" << endl;
	cout << "*    树t3含有11个节点，用t3复制构造树t_copy" << endl;
	btr_type t_copy;
	t_copy.btree::btree(t3);
	cout << "Tree 't_copy': " << endl;
	cout << t_copy;
	cout << endl;
	cout << "*====复制构造完成后，访问所有节点的总次数为： " << t_copy.tim_clone << endl;
	cout << "*====由于11＝11，即访问节点总次数等于复制节点总数，所以调用复制构造函数需要消耗线性时间。" << endl << endl<< endl;

	cout << "======进行插入节点时的时间复杂度（对数时间）======" << endl;
	cout << "*    随机生成200个0-1000之间的整数并存于数组a中" << endl;
	cout << "*    将数组a中的数通过insert()函数插入一棵空树t4" << endl;
	cout << "*    计算插入过程中访问所有节点的总次数" << endl;

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
	cout << "*====插入完成后，访问所有节点的总次数为： " << t4.tim_insert << endl;
	cout << "*====已知logN＝log200≈7.645，由上计算结果可得每次插入的访问节点平均次数为 ";
	float tim_in = t4.tim_insert;
	printf("%4.3f", tim_in / 200);
	cout << endl;
	cout << "*====说明：此计算结果偏小，因为随着数据不断插入，树t4所含数据总数N从0变为200）" << endl;
	cout << "*====由于7.645与" << tim_in / 200 << "较为接近，说明插入数据需要消耗对数时间。" << endl << endl;

	cout << "======进行查询节点时的时间复杂度======" << endl;
	cout << "*    再随机生成200个0-1000之间的整数并存于数组b中" << endl;
	cout << "*    通过contains()函数在树t4中查询数组b中的数" << endl;
	cout << "*    计算查询过程中访问所有节点的总次数" << endl << endl;

	for (int i = 0; i < 200; i++) {
		b[i] = rand() % (1000);
	}
	for (int i = 0; i < 200; i++) {
		t4.contains_time(b[i]);
	}

	cout << "*====查询完成后，访问所有节点的总次数为： " << t4.tim_contains << endl;
	cout << "*====已知log200≈7.645，由上计算结果可得每次查询的访问节点平均次数为 ";
	float tim_con = t4.tim_contains;
	printf("%4.3f", tim_con/200);
	cout << endl;
	cout << "*====由于7.645与" << tim_con / 200 << "较为接近，说明查询数据需要消耗对数时间。" << endl;

	return 0;
}


//btr_type t4;
//int a[500];
//for (int i = 0; i < 500; i++) {
//	a[i] = rand() % (200);
//}
//clock_t start1, finish1;
//double  duration1;
///* 测量一个事件持续的时间*/
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
///* 测量一个事件持续的时间*/
//cout << "Time to copy 500 times is";
//start2 = clock();
//for (int i = 0; i < 500; i++) {
//	t4.contains_time(a[i]);
//}
//finish2 = clock();
//duration2 = (double)(finish2 - start2) / CLOCKS_PER_SEC;
//printf("%50.49f seconds\n", duration2);
//cout << t4.time_contains() << endl;
