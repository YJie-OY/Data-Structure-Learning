#ifndef MYLIST
#define MYLIST
#include"MyAlgorithm.h"
template <typename value_type>
class List
{
public:
    typedef size_t size_type;
        

private: // 私有数据成员
        struct Node
        {
            value_type data;
            Node* prev;
            Node* next;

            Node(const value_type& d=value_type(), Node* p = nullptr, Node* n =nullptr)
            :data(d),prev(p),next(n){}

            Node(const value_type && d=value_type(), Node* p = nullptr, Node* n =nullptr)
            :data(d),prev(p),next(n){}
        };

        Node* head ;
        Node* tail ;

        size_type siz ;

        void init()
        {
            siz = 0;
            head = new Node(0,nullptr,nullptr);
            tail = new Node(0,nullptr,nullptr);
            head -> next = tail;
            tail ->prev = head;
        }

public: // 公有数据成员
        class const_iterator
        {
            protected:
                Node* current;

                const_iterator(Node* p):current(p){}

                value_type& retrieve() const
                    {return current->data;}
                
                friend class List<value_type>;

            public:
                const_iterator():current(nullptr){}

                const value_type& operator*() const 
                    {return retrieve();}

                const_iterator& operator++()
                {
                    current = current->next;
                    return *this;
                }

                const_iterator operator++( int )
                {
                    const_iterator old = *this;
                    ++(*this);
                    return old;
                }

                const_iterator& operator--()
                {
                    current = current->prev;
                    return *this;
                }

                const_iterator operator--(int)
                {
                    const_iterator old = *this;
                    --(*this);
                    return old;
                }

                bool operator==(const const_iterator &rhs) const 
                    { return current == rhs.current;}

                bool operator!=(const const_iterator &rhs) const 
                    { return current != rhs.current;}

                const_iterator operator+(size_type dis)
                {
                    const_iterator tmp = *this;
                    for(int i=0 ; i<dis ; i++)
                        ++tmp;
                    return tmp;
                }
                
                const_iterator operator-(size_type dis)
                {
                    const_iterator tmp = *this;
                    for(int i=0 ; i<dis ; i++)
                        --tmp;
                    return tmp;
                }
        };

        class iterator:public const_iterator
        {
            protected:
                iterator(Node* p):const_iterator(p) {}

                friend class List<value_type>;
            
            public:
                value_type& operator*() 
                    {return const_iterator::retrieve();}

                const value_type& operator*() const 
                    {return const_iterator::retrieve();}

                // 重载++运算符，返回新值
                iterator & operator++()
                {
                    this->current = this->current->next;
                    return *this;
                }       
                // 重载++运算符，返回旧值
                iterator operator++(int)
                {
                    iterator old=*this;
                    ++(*this);
                    return old;
                }

                iterator& operator--()
                {
                    this->current = this->current->prev;
                    return *this;
                }

                iterator operator--(int)
                {
                    iterator old = *this;
                    --(*this);
                    return old;
                }

                iterator operator+(size_type dis)
                {
                    iterator tmp = *this;
                    for(int i=0 ; i<dis ; i++)
                        ++tmp;
                    return tmp;
                }

                iterator operator-(size_type dis)
                {
                    iterator tmp = *this;
                    for(int i=0 ; i<dis; i++)
                        --tmp;
                    return tmp;
                }
                
        };

        class const_reverse_iterator
        {
            protected:
                Node* current;

                const_reverse_iterator(Node* p):current(p){}

                value_type& retrieve() const
                    {return current->data;}
                
                friend class List<value_type>;

            public:
                const_reverse_iterator():current(nullptr){}

                const value_type& operator*() const 
                    {return retrieve();}

                const_reverse_iterator& operator++()
                {
                    current = current->prev;
                    return *this;
                }

                const_reverse_iterator operator++( int )
                {
                    const_iterator old = *this;
                    ++(*this);
                    return old;
                }

                const_reverse_iterator& operator--()
                {
                    current = current->next;
                    return *this;
                }

                const_reverse_iterator operator--(int)
                {
                    const_reverse_iterator old = *this;
                    --(*this);
                    return old;
                }

                bool operator==(const const_reverse_iterator &rhs) const 
                    { return current == rhs.current;}

                bool operator!=(const const_reverse_iterator &rhs) const 
                    { return current != rhs.current;}

                const_reverse_iterator operator+(size_type dis)
                {
                    const_reverse_iterator tmp = *this;
                    for(int i=0 ; i<dis ; i++)
                        ++tmp;
                    return tmp;
                }
                
                const_reverse_iterator operator-(size_type dis)
                {
                    const_reverse_iterator tmp = *this;
                    for(int i=0 ; i<dis ; i++)
                        --tmp;
                    return tmp;
                }
        };

        class reverse_iterator:public const_reverse_iterator
        {
            protected:
                reverse_iterator(Node* p):const_reverse_iterator(p) {}

                friend class List<value_type>;
            
            public:
                value_type& operator*() 
                    {return const_reverse_iterator::retrieve();}

                const value_type& operator*() const 
                    {return const_reverse_iterator::retrieve();}

                // 重载++运算符，返回新值
                reverse_iterator & operator++()
                {
                    this->current = this->current->prev;
                    return *this;
                }       
                // 重载++运算符，返回旧值
                reverse_iterator operator++(int)
                {
                    reverse_iterator old=*this;
                    ++(*this);
                    return old;
                }

                reverse_iterator& operator--()
                {
                    this->current = this->current->next;
                    return *this;
                }

                reverse_iterator operator--(int)
                {
                    reverse_iterator old = *this;
                    --(*this);
                    return old;
                }

                reverse_iterator operator+(size_type dis)
                {
                    reverse_iterator tmp = *this;
                    for(int i=0 ; i<dis ; i++)
                        ++tmp;
                    return tmp;
                }

                reverse_iterator operator-(size_type dis)
                {
                    reverse_iterator tmp = *this;
                    for(int i=0 ; i<dis; i++)
                        --tmp;
                    return tmp;
                }
                
        };


public:  // 基本函数表

        // 构造函数
        List(const size_type Count=0 , const value_type& value=0)
        {
            init();
            if(Count != 0)
            {
                for(int i=0 ; i<Count ; i++)
                    {insert(begin(),value);}
                siz = Count;
            }
                
        }

        // 复制构造函数
        List(const List& rhs)
        {
            init();
            for(iterator itr = rhs.begin() ; itr!=rhs.end() ; itr++)
                push_back(*itr);
        }

        // 赋值重载
        List& operator=(const List&  rhs)
        {
            List copy = rhs;
            std::swap(*this,copy);
            return *this;
        }

        // 析构函数
        ~ List()
        {
            clear();
            delete head;
            delete tail;
        }




public: // 迭代器相关

        // 返回第一个节点（不是头结点）
        iterator begin() 
            {return head->next;}

        // 返回尾结点
        iterator end() 
            {return tail;}

        const_iterator cbegin() const
            {return head->next;}

        const_iterator cend() const 
            {return tail;}

        reverse_iterator rbegin()
            {return tail;}
        reverse_iterator rend()
            {return head;}

        const_reverse_iterator crbegin()
            {return tail;}
        const_reverse_iterator crend()
            {return head;}

public: // 属性访问函数

        // 查询链表的数据规模
        size_type size() const 
            {return siz;}
    
        // 查询链表是否为空
        bool empty() const 
            {return siz==0;}

public: // 元素访问函数

        // 查询第一个节点存储的数据
        value_type& front()
            {return *begin();}

        const value_type& front() const 
            {return *begin();}

        // 查询最后一个节点的数据
        value_type& back()
            {return *--end();}

        const value_type& back() const 
            {return *--end();}


public: // 修改函数

        // 清除链表中的元素
        void clear()
            {while(!empty()) pop_front();}

        // 前段插入
        void push_front(const value_type& x)
            {insert(begin(),x);}

        // 前段插入
        void push_front(const && x)
            {insert(begin(),std::move(x));}

        // 后端插入
        void push_back(const value_type& x)
            {insert(end(),x);}

        void push_back(const value_type&& x)
            {insert(end(),std::move(x));}

        // 前段删除
        void pop_front()
            {erase(begin());}
        
        // 后端删除
        void pop_back()
            {erase(--end());}

// =========== insert()  ===========
// 功能  : 在itr所指向的位置插入元素
// 参数  :
// - itr : 需要插入元素的位置
// - x   : 需要插入的元素的值
// 返回值 : 返回指向新元素的迭代器
// 复杂度 : 常数
        iterator insert(iterator itr,const value_type& x)
        {
            Node* point = itr.current;
            siz++;
            Node* newNode = new Node(x,point->prev,point);
            point->prev->next = newNode;
            point->prev = newNode;
            return --itr;
        }
        iterator insert(iterator itr,const value_type&& x)
        {
            Node* point = itr.current;
            siz++;
            Node* newNode = new Node(std::move(x),point->prev,point);
            point->prev->next = newNode;
            point->prev = newNode;          
            return point->prev;
        }

// =========== erase()  ===========
// 功能  : 在itr所指向的位置删除元素
// 参数  :
// - itr : 需要删除元素的位置
// 返回值 : 返回删除位置的迭代器
// 复杂度 : 常数

        iterator erase(iterator itr)
        {
            Node* point = itr.current;
            siz--;
            point->prev->next = point->next;
            point->next->prev = point->prev;
            iterator behind = point->next;
            delete point;
            return behind;
        }
        
        iterator erase(iterator from,iterator to)
        {
            for(iterator itr = from ; itr!=to ; itr++)
                itr = erase(itr);
            return to;
        }

// =========== swap()  ===========
// 功能  : 交换两个链表的内容
// 参数  :
// - other : 需要交换内容的另一个链表
// 返回值 : 无
// 复杂度 : 常数

        void swap(List& other)
        {
            Node* tmp = this->head;
            this->head = other.head;
            other.head = tmp;

            tmp = this->tail;
            this->tail = other.tail;
            other.tail = tmp;

            size_type tmpsize = siz;
            siz = other.size();
            other.siz = tmpsize;
        }

// =========== resize()  ===========
// 功能  : 修改链表的大小，若指定的大小比当前大小要小，那么就缩小链表，反之，用指定元素补充。
// 参数  :
// - newSize : 指定的大小。
// - value : 指定的元素
// 返回值 : 无
// 复杂度 : |siz - newSize|
        void resize(const size_type newSize,const value_type& value = 0)
        {
            if(siz < newSize)
            {
                size_type dis = newSize - siz;
                for(int i=0 ; i<dis; i++ )
                    {push_back(value);}
            }
            if(siz > newSize)
            {
                size_type dis = siz - newSize;
                for(int i=0 ; i<dis; i++ )
                    {pop_back();}
            }
        }

 public: // 操作

//=========== merge()  ===========
// 功能  : 修改链表的大小，若指定的大小比当前大小要小，那么就缩小链表，反之，用指定元素补充。
// 参数  :
// - other : 需要合并的容器
// 返回值 : 无
// 复杂度 : 最坏情况下，两个链表中的元素都要比较一遍，复杂度为 this->size() + other.size();
        void merge(List& other)
        {
            iterator begin1 = this->begin();
            iterator end1 = this->end();
            iterator begin2 = other.begin();
            iterator end2 = other.end();

            while(begin1 != end1 && begin2 != end2)
            {
                if(*begin2 < *begin1)
                {
                    insert(begin1,*begin2);
                    begin2++;
                }
                else
                    {begin1++;}

            }
            while (begin2 != end2)
            {
                insert(end1,*begin2);
                begin2++;
            }
        }

//=========== splice()  ===========
// 功能  : 将一个指定链表中的一段插入到目标链表中的指定位置,插入后删除指定链表
// 参数  :
// - pos : 需要插入的位置
// - other: 指定的链表
// - first:插入元素的起点
// - last : 插入元素的终点
// 返回值 : 无
// 复杂度 : first-last + other.size()
        void splice(iterator pos, List& other,const_iterator first, const_iterator last)
        {
            for(;first != last ; first++)
                {insert(pos,*first);}
            other.clear();
        }



//=========== remove()  ===========
// 功能  : 删除指定的数值
// 参数  : 指定的数值
// 返回值 : 无
// 复杂度 : this->size()

        void remove(const value_type& value)
        {
            iterator itr = begin();
            for(;itr != end() ; itr++)
            {
                if (*itr == value)
                    {erase(itr);}
            }
        }
//=========== unique()  ===========
// 功能  : 删除在连续重复的元素，在一段连续重复的元素段中，只保留一个元素。
// 参数  : 无
// 返回值 : 无
// 复杂度 : this->size()
        void unique()
        {
            iterator itr = begin();
            for(; itr!=end() ; itr++)
            {
                while( *itr == *(itr+1))
                    erase(itr+1);
            }
        }

//=========== reverse()  ===========
// 功能  : 反转链表
// 参数  : 无
// 返回值 : 无
// 复杂度 : this->size() 、 this->size()/2(第二个算法)
        // void reverse()
        // {
        //     if(head == nullptr || head ->next == nullptr)
        //         return;
        //     Node* p;
        //     Node* temp;
        //     p = head->next;
        //     while (p->prev != nullptr)
        //     {
        //         temp = p->prev;
        //         p->prev = p->next;
        //         p->next = temp;
        //         if (p->prev == nullptr) 
        //             {break;}
        //         else
        //             {p = p->prev;}
        //     }
        //     head->prev = head->next;
        //     head->next = nullptr;

        //     tail->next = tail->next;
        //     tail->prev = nullptr;

        //     Node* tmp = head;
        //     head = tail;
        //     tail = tmp;
        // }

        void reverse()
        {
            iterator front = begin() + 1;
            iterator back  = end()   - 1;
            for(int i=0 ; i<siz/2 ; i++)
            {
                value_type tmp = *front;
                *front = *back;
                *back  = tmp  ;
                front++;
                back --;
            }
        }

            
};
# endif

/* 
========= 数据成员类型 ==========

	template <typename value_type>
	typedef size_t size_type;
    
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

 ========= 数据成员类型 ==========


 ========= 数据成员 ==========

    Node* head;
    Node* tail;
    size_type siz;

========= 成员函数-基本函数表 =========

	Vector(size_type,size_type,value_type)		        // 构造函数
    Vector(const List& other)                         // 复制构造函数
    ~Vector()                                           // 析构函数
    Vector& operator=(const List& other);             // 替换容器的内容

========= 成员函数-基本函数表 =========




========= 成员函数- 元素访问 =========

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

========= 成员函数- 容量相关 =========


========= 成员函数- 修改器 =========

    void clear();
    iterator insert();
    iterator erase();
    void push_back();
    void pop_back();
    void swap();
    void resize();

========= 成员函数- 修改器 =========

========= 成员函数 - 操作 =========

    void merge (List&  other);                               // 合并两个链表
    void merge (List&& other);

    void splice(const_iterator pos, List&  other)           // 从 list 转移元素给另一个
    void splice(const_iterator pos, List&& other )

    void remove(const value_type& value)                    

    void reverse();

    void unique();

========= 成员函数 - 操作 =========

*/






