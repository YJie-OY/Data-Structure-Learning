
#ifndef MYVECTOR
#define MYVECTOR

#include<algorithm>
#include<utility>
#include<assert.h>

template <typename T>
class Vector
{
	public:
		typedef int pos_t;
		static const int SPARE_CAPACITY  = 10;
	private:

		T* v;
		size_t siz;
		size_t cap;

	public: // 特殊函数的实现

		explicit Vector(size_t initSize = 0,size_t initCapacity = 0,int x=0);
		~Vector();
	
	public: // 访问函数的实现

		// 查询数据集规模
		size_t size() const;

		// 查询容量
		size_t capacity() const;

		// 判断数据集是否为空
		bool empty() const;

		// 更改容器容量
		void reserve(size_t newCapacity)
		{
			T* tmp = new T[newCapacity];
			// 当容量小于数据集的时候,我们减掉一部分数据集
			if(newCapacity <= siz)
			{
				for(int i=0 ; i<newCapacity ; ++i)
					tmp[i]=v[i];
				siz = newCapacity;
			}
			else
			{
				// 当容量扩大的时候，把原来的数据复制过来
				for(int i=0 ; i<siz ; ++i)
					tmp[i]=v[i];					
			}

			delete[] v;
			v = tmp;
			cap = newCapacity;
		}

		// 更改数据集规模
		void resize (size_t newSize,const T& x=T())
		{
			if(newSize <= cap)
			{
				if(siz < newSize)
					for(int i=siz ; i<newSize ; ++i )
						v[i] = x;
				siz = newSize ;
				return ;
			}
			else
			{
				T* tmp=new T[newSize + SPARE_CAPACITY]; // 重新申请一块更大的内存空间

				for(int i=0;i<siz;++i) 					// 先将原向量中的数据复制过来
					tmp[i]=v[i];

				for(int i=siz;i<newSize;++i)				// 将多出的内容初始化为指定的值
					tmp[i]=x;

				delete[] v;								// 释放原来的内存空间
				v = tmp;									// 指向新的内存空间 
				siz = newSize;							// 维护数据集规模
				cap = newSize + SPARE_CAPACITY;			// 维护新的容量
				return ;
			}				 
		}


		// 在末尾插入左值元素
		void push_back(const T& x)
		{
			if(siz + 1 <= cap)
				v[siz++]=x;
			else
			{
				T* tmp=new T[siz+1 + SPARE_CAPACITY]; // 重新申请一块更大的内存空间

				for(int i=0;i<siz;++i) 					// 先将原向量中的数据复制过来
					tmp[i]=v[i];

				tmp[siz] = x;

				delete[] v;								// 释放原来的内存空间
				v = tmp;									// 指向新的内存空间 
				siz++;						// 维护数据集规模
				cap = siz + SPARE_CAPACITY;			// 维护新的容量
			}
		}

		// 在末尾插入右值元素
		void push_back(T&& x) //右值引用 
		{
			if(siz + 1 <= cap)
				v[siz++]=std::move(x);
			else
			{
				T* tmp=new T[siz+1 + SPARE_CAPACITY]; // 重新申请一块更大的内存空间

				for(int i=0;i<siz;++i) 					// 先将原向量中的数据复制过来
					tmp[i]=v[i];

				tmp[siz] = std::move(x);

				delete[] v;								// 释放原来的内存空间
				v = tmp;									// 指向新的内存空间 
				siz++;						// 维护数据集规模
				cap = siz + SPARE_CAPACITY;			// 维护新的容量
			}
			
		}

		// 删除末尾元素
		void pop_back()
		{
			if(siz == 0) return;
			else
				--siz;
		}

		// 在首部插入一个左值元素
		void push_front(const T& x)
		{
			T* tmp = new T[siz+1 + SPARE_CAPACITY];
			tmp[0] = x;
			for(int i=1 ; i<siz+1 ; i++)
				tmp[i] = v[i-1];
			delete[] v;
			v = tmp;
			siz++;
			cap = siz + SPARE_CAPACITY;
		}

		// 在首部插入一个右值元素
		void push_front(T&& x)
		{
			T* tmp = new T[siz+1 + SPARE_CAPACITY];
			tmp[0] = std::move(x);
			for(int i=1 ; i<siz+1 ; i++)
				tmp[i] = v[i];
			delete[] v;
			v = tmp;
			siz++;
			cap = siz + SPARE_CAPACITY;			
		}

		// 删除首部的元素
		void pop_front()
		{
			T* tmp = new T[siz + SPARE_CAPACITY];
			for(int i=0 ; i<siz-1 ; i++)
				tmp[i] = v[i+1];
			delete[] v;
			v = tmp;
			siz--;
			cap = siz + SPARE_CAPACITY;
		}

		// 在位置 pos 插入元素
		pair<bool,pos_t> insert(pos_t pos,const T& x)
		{
			if(siz+1 > cap or pos > siz)
				return pair<bool,pos_t>(false,pos);
			else
			{
				T* tmp = new T[siz+1 + SPARE_CAPACITY];
				for(int i=0 ; i<pos ; i++)
					tmp[i] = v[i];
				tmp[pos] = x;
				for(int i=pos+1 ; i<siz+1 ; ++i)
					tmp[i] = v[i-1];

				delete[] v;
				v = tmp;
				siz++;
				cap = siz + SPARE_CAPACITY;
				return pair<bool,pos_t>(true,pos);
			}
		}

		// 删除在位置 Pos 上的元素
		pair<bool,pos_t> erase(pos_t pos)
		{
			if(pos > siz)
				return pair<bool,pos_t>(false,pos);
			else
			{
				T* tmp = new T[siz + SPARE_CAPACITY];
				for(int i=0 ; i<pos ; i++)
					tmp[i] = v[i];
				for(int i=pos ; i<siz-1 ; i++)
					tmp[i] = v[i+1];
				
				delete[] v;
				v = tmp;
				siz--;
				cap = siz + SPARE_CAPACITY;
				return pair<bool,pos_t>(true,pos);
			}
			
		}

		// 重载运算符，访问位置 pos 的元素，不支持修改
		const T& operator[](pos_t pos) const {return v[pos];}

		// 重载运算符，访问位置 pos 的元素，支持修改
		T& operator[](pos_t pos){return v[pos];}

		// 访问位置 pos 的元素，不支持修改	
		const T& at(pos_t pos) const
		{
			assert(pos>=0 && pos<siz);
			return v[pos];
		}

		// 访问位置 pos 的元素，支持修改
		T& at(pos_t pos)
		{
			assert(pos>=0 && pos<siz);
			return v[pos];
		}
};


#endif
/* ========= 数据成员类型 ==========
	template <typename T>
	typedef T value_type
	typedef size_t size_type
	

/*


/* 公有接口-特殊方法表
	explict vector(size_t,size_t)		// 显示构造函数，拒绝强制转换。

*/

/*
公有接口-一般方法表
	size_t size() const; 		// 查询数据集规模
	size_t capcity() const;		// 查询容量
	
	bool empty() const; 		// 判断数据集是否为空

	const T& operator[](pos_t pos) const // 查询位置 pos 上的元素，不允许修改,不包含边界检测
	T& operator[](pos_t pos)			 // 查询位置 pos 上的元素，允许修改，不包含边界检测

	const T& at(pos_t pos) const		// 查询位置 Pos 上的元素，不允许修改，包含边界检测
	T& at(pos_t pos) 					// 查询位置 pos 上的元素，允许修改，包含边界检测

	void push_back()		// 末尾插入元素
	void push_front()		// 首部插入元素
	void pop_back()			// 末尾删除元素
	void pop_front()		// 首部删除元素
	pair<bool,pos_t> insert(pos_t,int)	// 在位置 pos 插入元素
	pair<bool,pos_t> erase(pos_t)		// 删除位置 pos 上的元素

	void clear() 			// 删除容器中所有的元素

	void resize()			// 修改数据集规模
	void reserve()			// 修改容器的容量


*/
