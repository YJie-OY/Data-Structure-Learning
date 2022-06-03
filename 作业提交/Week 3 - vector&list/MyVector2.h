#ifndef MYVECTOR
#define MYVECTOR

#include <iostream>
#include "MyAlgorithm.h"

template <typename value_type>
class Vector
{
private:
    typedef size_t size_type;
    static const int SPARE_CAPACITY  = 10;
    value_type* v;
    size_type siz;
    size_type cap;

public:
    class const_iterator
    {
        protected:
            Vector<value_type>* vptr;
            size_type index; 
            friend class Vector<value_type>;

            value_type& retrieve() const
                {return (*vptr)[index];}

        public:
            const_iterator(Vector<value_type>* str=NULL,size_type idx=0)
                :vptr(str),index(idx){}

            const value_type& operator*() const
                {return (*vptr)[index];}

            const_iterator& operator++()
            {
                index++;
                return *this;
            }

            const_iterator operator++( int )
            {
                const_iterator old(*this);
                ++(*this);
                return old;
            }
            
            const_iterator& operator--()
            {
                index--;
                return *this;
            }

            const_iterator operator--( int )
            {
                const_iterator old(*this);
                --(*this);
                return old;
            }

            bool operator==(const const_iterator &rhs) const
                {return index == rhs.index;}

            bool operator!=(const const_iterator &rhs)
                {return index != rhs.index;}

            const_iterator operator+(size_type dis)
            {
                const_iterator tmp(*this);
                tmp.index += dis;
                return tmp;
            } 

            const_iterator operator-(size_type dis)
            {
                const_iterator tmp(*this);
                tmp.index -= dis;
                return tmp;
            }
    };
    
    class iterator: public const_iterator
    {
        protected:
            iterator(Vector<value_type>* str=NULL,size_type idx=0)
                :const_iterator(str,idx){}
            friend class Vector<value_type>;
        public:

            value_type& operator*()
                {return const_iterator::retrieve();}
            
            const value_type& operator*() const
                {return const_iterator::retrieve();}

            iterator& operator++()
            {
                this->index++;
                return *this;
            }

            iterator operator++( int ) 
            {
                iterator old(*this);
                ++(*this);
                return old;
            }

            iterator& operator--()
            {
                this->index--;
                return *this;
            }
            iterator operator--( int )
            {
                iterator old(*this);
                --(*this);
                return old;
            }

            iterator operator+(size_type dis)
            {
                iterator tmp(*this);
                tmp.index += dis;
                return tmp;
            } 

            iterator operator-(size_type dis)
            {
                iterator tmp(*this);
                tmp.index -= dis;
                return tmp;
            }
    };
    
    class const_reverse_iterator
    {
        protected:
            Vector<value_type>* vptr;
            size_type index; 
            friend class Vector<value_type>;

            value_type& retrieve() const
                {return (*vptr)[index];}

        public:
            const_reverse_iterator(Vector<value_type>* str=NULL,size_type idx=0)
                :vptr(str),index(idx){}

            const value_type& operator*() const
                {return (*vptr)[index];}

            const_reverse_iterator& operator++()
            {
                index--;
                return *this;
            }

            const_reverse_iterator operator++( int )
            {
                const_reverse_iterator old(*this);
                ++(*this);
                return old;
            }
            
            const_reverse_iterator& operator--()
            {
                index++;
                return *this;
            }

            const_reverse_iterator operator--( int )
            {
                const_reverse_iterator old(*this);
                --(*this);
                return old;
            }

            bool operator==(const const_reverse_iterator &rhs) const
                {return index == rhs.index;}

            bool operator!=(const const_reverse_iterator &rhs)
                {return index != rhs.index;}

            const_reverse_iterator operator+(size_type dis)
            {
                const_reverse_iterator tmp(*this);
                tmp.index -= dis;
                return tmp;
            } 

            const_reverse_iterator operator-(size_type dis)
            {
                const_reverse_iterator tmp(*this);
                tmp.index += dis;
                return tmp;
            }

            
    };
    
    class reverse_iterator: public const_reverse_iterator
    {
        protected:
            reverse_iterator(Vector<value_type>* str=NULL,size_type idx=0)
                :const_reverse_iterator(str,idx){}
            friend class Vector<value_type>;
        public:

            value_type& operator*()
                {return const_reverse_iterator::retrieve();}
            
            const value_type& operator*() const
                {return const_reverse_iterator::retrieve();}

            reverse_iterator& operator++()
            {
                this->index--;
                return *this;
            }

            reverse_iterator operator++( int ) 
            {
                reverse_iterator old(*this);
                ++(*this);
                return old;
            }

            reverse_iterator& operator--()
            {
                this->index++;
                return *this;
            }
            reverse_iterator operator--( int )
            {
                reverse_iterator old(*this);
                --(*this);
                return old;
            }

            reverse_iterator operator+(size_type dis)
            {
                reverse_iterator tmp(*this);
                tmp.index -= dis;
                return tmp;
            } 

            reverse_iterator operator-(size_type dis)
            {
                reverse_iterator tmp(*this);
                tmp.index += dis;
                return tmp;
            }
    };


public: // 基本函数表

//  ====== 构造函数 ====== 
// 功能   : 设定容器规模并且规定初始化的值
// 参数   :
// - initSize : 容器规模
// - value    : 用于初始化的值
// 返回值 : 无
// 复杂度 : initSize
//  ====== 构造函数 ====== 
    Vector(size_type initSize=0,const value_type& value=0):siz(initSize),cap(initSize+SPARE_CAPACITY)
    {
        v = new value_type[cap];
        for(int i=0 ; i<siz ; i++)
            v[i] = value;
    }


//  ====== 复制构造函数 ====== 
// 功能   : 利用已有的容器初始化当前容器
// 参数   :
// - other : 用于初始化的容器
// 返回值 : 无
// 复杂度 : other.size()
//  ====== 复制构造函数 ====== 
    Vector(const Vector& other) 
    {
        this->siz = other.siz;
        this->cap = other.cap;
        v = new value_type[cap];
        for(int i=0 ; i<other.size() ; i++)
            v[i] = other.v[i];
    }



//  ====== 赋值重载 ====== 
// 功能   : 利用已有的容器赋值到当前目标容器
// 参数   :
// - other : 用于初始化的容器
// 返回值 : 目标容器
// 复杂度 : other.size()
//  ====== 赋值重载 ====== 
    Vector& operator=(const Vector& other)
    {
        Vector copy = other;
        std::swap(*this,copy);
        return *this;
    } 


//  ====== 析构函数 ====== 
// 功能   : 删除容器，释放空间
// 参数   : 无
// 返回值 : 无
// 复杂度 : v的长度
//  ====== 析构函数 ======  
    ~Vector() {delete[] v;}
                                             
    


public: // 迭代器相关

    iterator begin()
        {return iterator(this,0);}

    iterator end()
        {return iterator(this,siz);}

    const_iterator cbegin()
        {return const_iterator(this,0);}

    const_iterator cend()
        {return const_iterator(this,siz);}

    reverse_iterator rbegin()
        {return reverse_iterator(this,siz-1);}

    reverse_iterator rend()
        {return reverse_iterator(this,0);}

    const_reverse_iterator crbegin()
        {return const_reverse_iterator(this,siz-1);}

    const_reverse_iterator crend()
        {return const_reverse_iterator(this,0);}


public: // 访问查询函数
    bool empty() const
        {return siz == 0;}

    size_type size() const
        {return siz;}

    size_type capacity() const
        {return cap;}

public: // 元素访问
    value_type& operator[](size_type pos)
        {return v[pos];}
    
    value_type& at(const size_type pos)
    {
        if(pos < 0 || pos >= siz)
        {
            std::cout<<"Error:Index out of range!\n";
            return v[0];
        }
        return v[pos];
    }

    value_type& front()
        {return v[0];}

    value_type& back()
        {return v[siz-1];}

public: // 修改器
    
    void clear()
        {siz = 0;}

// ======== reserve() =========
// 功能  : 改变容器大小,分为两种情况.
//      (1)若容量增大,申请新的空间,那么将原容器元素完全保留至新的空间;
//      (2)若容量减少以至于小于当前数据集规模,那么我们只保留新容量大小的数据,为了达到释放空间的目的,同样需要申请新的空间,并且维护数据集规模
// 返回值 : 无
// 参数  : newCapacity - 新的容量
// 复杂度 : 不大于新容量

    void reserve(size_type newCapacity)
    {
        value_type* tmp  = new value_type[newCapacity];
        if(newCapacity > cap)
            {Copy<iterator,value_type*>(begin(),end(),&tmp[0]);}
        else if(newCapacity<cap)
        {
            Copy<iterator,value_type*>(begin(),begin()+newCapacity,&tmp[0]);
            if(siz > newCapacity)
                {siz = newCapacity;}
        }
        delete[] v;
        v = tmp;
        cap = newCapacity;
    }

// ======== resize() =========
// 功能  : 重设容器的数据集规模，分两种情况
//     (1) siz >= newSize : 缩小数据集规模到其首 newSize 个
//     (2) siz < newSize : 补充新的元素,新元素的值由 value 指定。若 cap < newSize , 则需要扩容。
// 参数  :
// - newSize : 数据集指定规模
// - value   : 新的元素的指定值
// 返回值 : 无
// 复杂度 : 与 siz 和 newSize 间的差成线性。若容量小于 newSize 则可能有重分配所致的额外复杂度。 


    void resize(size_type newSize, const value_type value = 0)
    {
        if(siz < newSize)
        {
            if(cap < newSize) 
                reserve(newSize+SPARE_CAPACITY);
            size_type dis = newSize - siz;
            Fill<iterator,value_type>(end(),end()+dis,value);
        } 
        siz = newSize; 
    }


    void pop_back()
        { if(siz > 0) --siz; }
        
    void pop_front()
        {erase(begin());}

    void push_back(const value_type& value)
        {insert(end(),value);}

    void push_front(const value_type& value)
        {insert(begin(),value);}

// ========= insert() ==========
// 功能  : 在 pos 前插入 value
// 参数  :
// - pos   : 插入元素的位置
// - value : 插入的元素的值
// 返回值 : 无
// 复杂度 : siz-pos呈线性
    iterator insert(iterator pos, const value_type value)
    {
        if(siz+1 > cap)
            {reserve(cap+SPARE_CAPACITY);}
        Copy_backward<iterator,iterator>(pos,end(),end()+1);
        v[pos.index] = value;
        siz++;
        return pos;
    }

// ========= erase() ===========
// 功能  : 删除 pos 上的元素, 使得后面的元素前移
// 参数  :
// - pos   : 删除元素的位置
// 返回值 : 无
// 复杂度 : siz-pos 线性
    iterator erase(iterator pos)
    {
        Copy<iterator,iterator>(pos+1,end(),pos);
        siz--;
        return pos;
    }


// ======== swap() ===========
// 功能  : 将内容与 other 交换
// 参数  : 
// - other : 与之交换内容的容器
// 返回值 : 无
// 复杂度 : 常数

    void swap(Vector& other)
    {
        value_type* tmp = other.v;
        other.v = this->v;
        this->v = tmp;
        std::swap(this->siz,other.siz);
        std::swap(this->cap,other.cap);
    }
};

# endif





/* 
========= 数据成员类型 ==========

	template <typename T>
	typedef T value_type;
	typedef size_t size_type;
    
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

 ========= 数据成员类型 ==========


 ========= 数据成员 ==========

    value_type* v;
    size_type siz;
    size_type cap;

========= 成员函数-基本函数表 =========

	Vector(size_type,size_type,value_type)		        // 构造函数
    Vector(const Vector& other)                         // 复制构造函数
    ~Vector()                                           // 析构函数
    Vector& operator=(const Vector& other);             // 替换容器的内容

========= 成员函数-基本函数表 =========




========= 成员函数- 元素访问 =========

    value_type& at(size_type pos);                                   // 访问元素,包含边界检测
    value_type& operator[](size_type pos);
    value_type& front();
    value_type& back();

========= 成员函数- 元素访问 =========


========= 成员函数- 迭代器相关 =========

    iterator begin();
    iterator end();

    const_iterator cbegin();
    const_iterator cend();

    reverse_iterator rbegin();
    reverse_iterator rend();

    const_reverse_iterator rcbegin();
    const_reverse_iterator rcend();

========= 成员函数- 迭代器相关 =========


========= 成员函数- 容量相关 =========

    const bool empty() const;
    const size_type size() const;
    const size_type capacity() const;
    const size_type max_size() const;

========= 成员函数- 容量相关 =========


========= 成员函数- 修改器 =========

    void clear();
    iterator insert();
    iterator erase();
    void push_back();
    void pop_back();
    void swap();
    void resize();
    void reserve();

========= 成员函数- 修改器 =========
*/