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


public: // ����������

//  ====== ���캯�� ====== 
// ����   : �趨������ģ���ҹ涨��ʼ����ֵ
// ����   :
// - initSize : ������ģ
// - value    : ���ڳ�ʼ����ֵ
// ����ֵ : ��
// ���Ӷ� : initSize
//  ====== ���캯�� ====== 
    Vector(size_type initSize=0,const value_type& value=0):siz(initSize),cap(initSize+SPARE_CAPACITY)
    {
        v = new value_type[cap];
        for(int i=0 ; i<siz ; i++)
            v[i] = value;
    }


//  ====== ���ƹ��캯�� ====== 
// ����   : �������е�������ʼ����ǰ����
// ����   :
// - other : ���ڳ�ʼ��������
// ����ֵ : ��
// ���Ӷ� : other.size()
//  ====== ���ƹ��캯�� ====== 
    Vector(const Vector& other) 
    {
        this->siz = other.siz;
        this->cap = other.cap;
        v = new value_type[cap];
        for(int i=0 ; i<other.size() ; i++)
            v[i] = other.v[i];
    }



//  ====== ��ֵ���� ====== 
// ����   : �������е�������ֵ����ǰĿ������
// ����   :
// - other : ���ڳ�ʼ��������
// ����ֵ : Ŀ������
// ���Ӷ� : other.size()
//  ====== ��ֵ���� ====== 
    Vector& operator=(const Vector& other)
    {
        Vector copy = other;
        std::swap(*this,copy);
        return *this;
    } 


//  ====== �������� ====== 
// ����   : ɾ���������ͷſռ�
// ����   : ��
// ����ֵ : ��
// ���Ӷ� : v�ĳ���
//  ====== �������� ======  
    ~Vector() {delete[] v;}
                                             
    


public: // ���������

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


public: // ���ʲ�ѯ����
    bool empty() const
        {return siz == 0;}

    size_type size() const
        {return siz;}

    size_type capacity() const
        {return cap;}

public: // Ԫ�ط���
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

public: // �޸���
    
    void clear()
        {siz = 0;}

// ======== reserve() =========
// ����  : �ı�������С,��Ϊ�������.
//      (1)����������,�����µĿռ�,��ô��ԭ����Ԫ����ȫ�������µĿռ�;
//      (2)����������������С�ڵ�ǰ���ݼ���ģ,��ô����ֻ������������С������,Ϊ�˴ﵽ�ͷſռ��Ŀ��,ͬ����Ҫ�����µĿռ�,����ά�����ݼ���ģ
// ����ֵ : ��
// ����  : newCapacity - �µ�����
// ���Ӷ� : ������������

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
// ����  : �������������ݼ���ģ�����������
//     (1) siz >= newSize : ��С���ݼ���ģ������ newSize ��
//     (2) siz < newSize : �����µ�Ԫ��,��Ԫ�ص�ֵ�� value ָ������ cap < newSize , ����Ҫ���ݡ�
// ����  :
// - newSize : ���ݼ�ָ����ģ
// - value   : �µ�Ԫ�ص�ָ��ֵ
// ����ֵ : ��
// ���Ӷ� : �� siz �� newSize ��Ĳ�����ԡ�������С�� newSize ��������ط������µĶ��⸴�Ӷȡ� 


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
// ����  : �� pos ǰ���� value
// ����  :
// - pos   : ����Ԫ�ص�λ��
// - value : �����Ԫ�ص�ֵ
// ����ֵ : ��
// ���Ӷ� : siz-pos������
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
// ����  : ɾ�� pos �ϵ�Ԫ��, ʹ�ú����Ԫ��ǰ��
// ����  :
// - pos   : ɾ��Ԫ�ص�λ��
// ����ֵ : ��
// ���Ӷ� : siz-pos ����
    iterator erase(iterator pos)
    {
        Copy<iterator,iterator>(pos+1,end(),pos);
        siz--;
        return pos;
    }


// ======== swap() ===========
// ����  : �������� other ����
// ����  : 
// - other : ��֮�������ݵ�����
// ����ֵ : ��
// ���Ӷ� : ����

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
========= ���ݳ�Ա���� ==========

	template <typename T>
	typedef T value_type;
	typedef size_t size_type;
    
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

 ========= ���ݳ�Ա���� ==========


 ========= ���ݳ�Ա ==========

    value_type* v;
    size_type siz;
    size_type cap;

========= ��Ա����-���������� =========

	Vector(size_type,size_type,value_type)		        // ���캯��
    Vector(const Vector& other)                         // ���ƹ��캯��
    ~Vector()                                           // ��������
    Vector& operator=(const Vector& other);             // �滻����������

========= ��Ա����-���������� =========




========= ��Ա����- Ԫ�ط��� =========

    value_type& at(size_type pos);                                   // ����Ԫ��,�����߽���
    value_type& operator[](size_type pos);
    value_type& front();
    value_type& back();

========= ��Ա����- Ԫ�ط��� =========


========= ��Ա����- ��������� =========

    iterator begin();
    iterator end();

    const_iterator cbegin();
    const_iterator cend();

    reverse_iterator rbegin();
    reverse_iterator rend();

    const_reverse_iterator rcbegin();
    const_reverse_iterator rcend();

========= ��Ա����- ��������� =========


========= ��Ա����- ������� =========

    const bool empty() const;
    const size_type size() const;
    const size_type capacity() const;
    const size_type max_size() const;

========= ��Ա����- ������� =========


========= ��Ա����- �޸��� =========

    void clear();
    iterator insert();
    iterator erase();
    void push_back();
    void pop_back();
    void swap();
    void resize();
    void reserve();

========= ��Ա����- �޸��� =========
*/