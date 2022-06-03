#pragma once
#ifndef AVLTREE_H
#define AVLTREE_H
#include"print.h"
#define MAJVERSION 1
#define SUBVERSION 0
#define MINVERSION 39
#define BUILDYEAR 2022
#define MODIFIEDYEAR 2022

#include"assert.h"
namespace DSAA {
	template<typename T>
	class btree
	{
	private:
		struct Avlnode
		{
			T data;
			Avlnode* lch;
			Avlnode* rch;
			int height;

			Avlnode(const T& x = T(), Avlnode* L = nullptr, Avlnode* R = nullptr, int h = 0)
				:data(x), lch(L), rch(R), height(h) {}
			Avlnode(T&& x = T(), Avlnode* L = nullptr, Avlnode* R = nullptr, int h = 0)
				:data(std::move(x)), lch(L), rch(R), height(h) {}
		};

	public:  //公开的接口
		//typedef typename node<T> node_type;  //定义公开的节点类型
		typedef T value_type;
		typedef Avlnode Avlnode_type;
		typedef Avlnode_type* Avlnode_ptr;
		typedef unsigned long size_type;
		static const int ALLOWED_IMBALANCE = 1;
		btree() : siz(0), root(nullptr) { }

		btree(const btree& rhs) :siz(rhs.siz), root(clone_time(rhs.root)) {}  //复制构造函数（克隆）

		btree(btree&& rhs) :siz(std::move(rhs.siz)), root(std::move(rhs.root))  //移动构造函数，那棵树移过来，然后那棵树就没有了
		{                                                      //两棵树的指针指向同一个根节点
			rhs.siz = 0;
			rhs.root = nullptr;
		}

		~btree() { makeEmpty(); }  //析构函数，调用清空函数

		void makeEmpty() { makeEmpty(this->root); }

		void insert_time(const T& x) { insert_time(x, this->root); }
		void insert(const T& x) { insert(x, this->root); }
		void insert(T&& x) { insert(x, this->root); }
		void remove(const T& x) { remove(x, this->root); }

		const T& findMin() const { return findMin(this->root)->data; }
		const T& findMax() const { return findMax(this->root)->data; }

		bool contains_time(const T& x) { return contains_time(x, this->root); }
		bool contains(const T& x) { return contains(x, this->root); }
		bool isEmpty() const { return siz == 0;/*root==nullptr;*/ }
		size_type size() const { return siz; }
		//int time_clone() const { return tim_clone; }
		//int time_insert() const { return tim_insert; }
		//int time_contains() const { return tim_contains; }

		void printTree(ostream& out = cout) const {
			if (isEmpty())
				out << "Empty tree." << endl;
			else
				printTree(root, out);
		}

		btree& assign(const btree& rhs) {   
			if (this != &rhs) {
				if (root != rhs.root) {
					makeEmpty();
					root = clone(rhs.root);
					siz == rhs.siz;
					return *this;
				}
			}
			return *this;
		}

		btree& assign(btree&& rhs) {
			if (this != &rhs) {
				if (root != rhs.root) {
					makeEmpty();
					root = clone(rhs.root);
					siz == rhs.siz;
					rhs.root = nullptr;
					rhs.siz = 0;
					return *this;
				}	
			}
			return *this;
		}
		
		//btree& assign(const btree& rhs) {   //外部接口
		//	if (this != &rhs) {
		//		copyassign(root, rhs.root);
		//		siz == rhs.siz;
		//		return *this;
		//	}
		//	return *this;
		//}

		/*btree& assign(btree&& rhs) {
			if (this != &rhs) {
				moveassign(root, rhs.root);
				siz == rhs.siz;
				rhs.siz = 0;
				return *this;
			}
		}*/

		btree& operator= (const btree& rhs) {    //复制赋值运算符 左值引用，把右边的树复制过来
			if (root != rhs.root) {
				makeEmpty();
				root = clone(rhs.root);
				return *this;
			}
			return *this;
		}

		btree& operator= (btree&& rhs) {    //移动赋值运算符 右值引用，右边的树没了
			if (this != &rhs) {
				makeEmpty();      //释放掉
				siz = std::move(rhs.siz);
				//root = clone(rhs.root);
				root = std::move(rhs.root);
				tim_clone += 1;
				rhs.root = nullptr;
			}
			return *this;
		}

		int height(Avlnode_ptr t) const {
			return t == nullptr ? -1 : t->height;
		}

	public:
		int tim_clone = 0;     //计算克隆时访问节点的总次数
		int tim_insert = 0;    //计算插入数据时访问节点的总次数
		int tim_contains = 0;  //计算查询数据时访问节点的总次数
		
	private:
		Avlnode* root;  //定义根节点
		size_type siz;

		void insert_time(const T& x, Avlnode*& t) {
			if (t == nullptr) {
				tim_insert += 1;
				t = new Avlnode(x, nullptr, nullptr);
			}
			else if (x < t->data) {
				tim_insert += 1;
				insert_time(x, t->lch);
			}
			else if (x > t->data) {
				tim_insert += 1;
				insert_time(x, t->rch);
			}
			else
				;
			siz++;
			balance(t);
		}
		void insert(const T& x, Avlnode*& t) {
			if (t == nullptr) {
				t = new Avlnode(x, nullptr, nullptr);
			}
			else if (x < t->data)
				insert(x, t->lch);
			else if (x > t->data)
				insert(x, t->rch);
			else
				;
			siz++;
			balance(t);
		}

		void insert(T&& x, Avlnode*& t) {
			if (t == nullptr) {
				t = new Avlnode(std::move(x), nullptr, nullptr);
			}
			else if (x < t->data)
				insert(std::move(x), t->lch);
			else if (x > t->data)
				insert(std::move(x), t->rch);
			balance(t);
		}

		void remove(const T& x, Avlnode_ptr& t) {
			if (t == nullptr)
				return;
			else if (x < t->data)
				remove(x, t->lch);
			else if (x > t->data)
				remove(x, t->rch);
			else if (t->lch != nullptr && t->rch != nullptr) {
				t->data = findMin(t->rch)->data;
				remove(t->data, t->rch);
			}
			else {
				Avlnode_ptr old = t;
				t = (t->lch != nullptr) ? t->lch : t->rch;
				delete old;
			}
			siz--;
			balance(t);
		}

		void balance(Avlnode_ptr& t) {
			if (t == nullptr) return;
			if (height(t->lch) - height(t->rch) > ALLOWED_IMBALANCE) {
				if (height(t->lch->lch) >= height(t->lch->rch))
					rotateWithLeftChild(t);
				else
					doubleWithLeftChild(t);
			}
			else if (height(t->rch) - height(t->lch) > ALLOWED_IMBALANCE) {
				if (height(t->rch->rch) >= height(t->rch->lch))
					rotateWithRightChild(t);
				else
					doubleWithRightChild(t);
			}
			t->height = max(height(t->lch), height(t->rch)) + 1;
		}

		void rotateWithLeftChild(Avlnode_ptr& k2) { //单旋转：左儿子变为根节点
			Avlnode_ptr k1 = k2->lch;
			if (k1->rch == nullptr)
				k2->lch = nullptr;
			else 
				k2->lch = k1->rch;
			k1->rch = k2;
			k2->height = max(height(k2->lch), height(k2->rch)) + 1;
			k1->height = max(height(k1->lch), k2->height) + 1;
			k2 = k1;
		}

		void rotateWithRightChild(Avlnode_ptr& k1) { //单旋转：右儿子变为根节点
			Avlnode_ptr k2 = k1->rch;
			if (k2->lch == nullptr) 
				k1->rch = nullptr;
			else
				k1->rch = k2->lch;
			k2->lch = k1;
			k1->height = max(height(k1->lch), height(k1->rch)) + 1;
			k2->height = max(height(k2->lch), k1->height) + 1;
			k1 = k2;
		}

		void doubleWithLeftChild(Avlnode_ptr& k3) { //双旋转：左儿子变为根节点
			rotateWithRightChild(k3->lch);
			rotateWithLeftChild(k3);
		}

		void doubleWithRightChild(Avlnode_ptr& k3) { //双旋转：右儿子变为根节点
			rotateWithLeftChild(k3->rch);
			rotateWithRightChild(k3);
		}

		/*Avlnode_ptr findMin(Avlnode_ptr t) const {
			assert(t == nullptr);
			return (t->lch = nullptr ? t : findMin(t->lch));
		}*/
		Avlnode_ptr findMin(Avlnode_ptr t) const {
			if (t == nullptr)
				return nullptr;
			if (t->lch == nullptr)
				return t;
			else
				return findMin(t->lch);
		}

		/*Avlnode_ptr findMax(Avlnode_ptr t) const {
			assert(t != nullptr);
			return { t->rch = nullptr ? t : findMin(t->rch) };
		}*/
		Avlnode_ptr findMax(Avlnode_ptr t) const {
			if (t != nullptr)
				while (t->rch != nullptr)
					t = t->rch;
			return t;
		}

		bool contains_time(const T& x, Avlnode_ptr t) {
			if (t == nullptr) {
				tim_contains += 1;
				return false;
			}
			else if (x < t->data) {
				tim_contains += 1;
				return contains_time(x, t->lch);
			}
			else if (x > t->data) {
				tim_contains += 1;
				return contains_time(x, t->rch);
			}
			else 
				tim_contains += 1;
			return true;
		}

		bool contains(const T& x, Avlnode_ptr t) {
			if (t == nullptr) 
				return false;
			else if (x < t->data) 
				return contains(x, t->lch);
			else if (x > t->data) 
				return contains(x, t->rch);
			else 
				cout << "The data is in the tree." << endl;
			return true;
		}

		void makeEmpty(Avlnode_ptr& t) {
			if (t != nullptr) {  //判断节点t是否存在
				makeEmpty(t->lch);
				makeEmpty(t->rch);
				delete t;
			}
			t = nullptr;
		}

		void printTree(Avlnode_ptr t, ostream& out) const {
			if (t != nullptr) {
				printTree(t->lch, out);
				out << t->data << " ";
				printTree(t->rch, out);
			}
		}

		Avlnode_ptr clone_time(Avlnode_ptr t) {
			if (t == nullptr)
				return nullptr;
			else {
				tim_clone += 1;
				return new Avlnode(t->data, clone_time(t->lch), clone_time(t->rch));
			}
		}

		Avlnode_ptr clone(Avlnode_ptr t)const {
			if (t == nullptr)
				return nullptr;
			else
				return new Avlnode(t->data, clone(t->lch), clone(t->rch));
		}

		/*Avlnode_ptr copyassign(Avlnode_ptr rptr) {
			if (this != rptr) {
				makeEmpty();
				this = clone(rptr);
			}
		}*/
		/*void copyassign(Avlnode_ptr& lptr, Avlnode_ptr& rptr) {
			if (lptr != rptr) {
				makeEmpty(lptr);
				lptr = clone(rptr);
			}
		}*/
		/*void moveassign(Avlnode_ptr& lptr, Avlnode_ptr& rptr) {
			if (lptr != rptr)
			{
				makeEmpty(lptr);
				lptr = rptr;
				rptr = nullptr;
			}
		}*/

	public:
		ostream& out(ostream& os) const { out(os, root); return os; }

	protected:
		virtual void out(ostream& os, Avlnode_ptr ptr) const
		{
			outer<Avlnode_type>(width(ptr)).out(os, ptr);
		}
	};
	template <typename T>
	ostream& operator<<(ostream& os, const btree<T>& rhs) { return rhs.out(os); }
}

#undef MAJVERSION
#undef SUBVERSION
#undef MINVERSION
#undef BUILDYEAR
#undef MODIFIEDYEAR

#endif

//template<typename T>
//class bstree :public btree<T>
//{
//public:
//	typedef typename btree<T> parent_type;
//	typedef parent_type::value_type value_type;
//	typedef parent_type::node_ptr node_type;
//	typedef parent_type::size_type size_type;
//
//public:
//	btree& operator= (const btree& rhs) = delete;
//	btree& operator= (btree&& rhs) = delete;
//
//	bool contains(const T& x, node* t) const {
//		if (t == nullptr) return false;
//		if (t->data == x) return true;
//		return x < t->data ? contains(x, t->lch) : contains(x, t->rch);
//	}
//
//	bstree() :siz(0), root(nullptr) {}
//
//	bstree(const btree& rhs) :siz(rhs.siz), root(clone(rhs.root)) {}  //复制构造函数（克隆）
//
//	bstree(bstree&& rhs) :siz(rhs.siz), root(rhs.root)  //移动构造函数，那棵树移过来，然后那棵树就没有了
//	{                                  //两棵树的指针指向同一个根节点
//		rhs.siz = 0;
//		rhs.root = nullptr;
//	}
//
//	~bstree() { makeEmpty(); }  //析构函数，调用清空函数
//
//	void insert(const T& x) {
//		insert(x, this->root);
//
//	}
//
//	const T& findMin() { return findMin(root); }
//	T& findMin() { return findMin(root); }
//	const T& findMax() { return findMax(root); }
//	T& findMax() { return findMax(root); }
//
//	bool insert(const T& x) { return insert(x, root); }
//	bool insert(T&& x) { return insert(std::move(x), root); }
//	bool remove(const T& x) { return remove(x, root); }
//
//
//
//protected:
//	const T& findMin(node* ptr) const {
//		assert(ptr != nullptr);
//		return (ptr->lch = nullptr ? ptr->data : findMin(ptr->lch);
//	}
//	T& findMin(node* ptr) {
//		assert(ptr != nullptr);
//		return (ptr->lch = nullptr ? ptr->data : findMin(ptr->lch);
//	}
//	const T& findMax(node* ptr) const {
//		assert(ptr != nullptr);
//		return (ptr->rch = nullptr ? ptr->data : findMax(ptr->rch);
//	}
//	T& findMax(node* ptr) {
//		assert(ptr != nullptr);
//		return (ptr->rch = nullptr ? ptr->data : findMax(ptr->rch);
//	}
//
//private:
//	
//};