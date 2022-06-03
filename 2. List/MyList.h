#ifndef MYLIST
#define MYLIST

template <typename T>

class List
{
    public:
        typedef int pos_t;

    private: // 私有数据成员
        struct Node
        {
            T value;
            Node* prev;
            Node* next;

            Node(const T & v=T(), Node* p = NULL, Node* n = NULL)
            :value(v),prev(p),next(n){}

           Node(const T && v=T(), Node* p = nullptr, Node* n =nullptr)
           :value(v),prev(p),next(n){}

            Node(const Node& rhs)
            :value(rhs.value),prev(rhs.prev),next(rhs.next){}
        };

        Node* head;
        Node* tail;
        size_t siz;

//        void init(); 


    public:  // 特殊方法

        // 构造函数
        List()
        {
        	head = new Node(-1,nullptr,tail);
        	tail = new Node(-1,head,nullptr);
			
            siz = 0;
        }


        // 析构函数
        ~ List()
        {
            Node* point=head->next;
            for(int i=0 ; i<siz ; i++)
            {
                point = point->next;
                delete point->prev;
            }
            delete head;
            delete tail;
        }


    public: // 访问函数

        // 返回第一个节点（不是头结点）
        T& begin() {return head->next->value;}
        const T& begin() const{return head->next->next;}

        // 返回尾结点
        T& end() {return tail->prev->value;}
        const T& end() const {return tail->prev->value;}

        // 查询链表的数据规模
        size_t size() const {return siz;}
    
        // 查询链表是否为空
        bool empty() const {return siz==0;}

    public: // 修改函数

        // 清除链表中的元素
        void clear()
        {
            while(!empty())
                pop_front();
        }

        // 前段插入元素
        void push_front(const T& x)
        {
            Node* newNode = new Node(x,head,head->next);
            head->next->prev = newNode;
            head->next = newNode;
            siz++;
        }

        // 前段插入元素（右值）
       void push_front(const && x)
       {
           Node* newNode = new Node(std::move(x),head,head->next);
           head->next->prev = newNode;
           head->next = newNode;
           siz++;
       }

        // 后端插入元素
        void push_back(const T& x)
        {
            Node* newNode = new Node(x,tail->prev,tail);
            tail->prev->next = newNode;
            tail->prev = newNode;
            siz++;
        }

        // 后端插入元素（右值）
       void push_back(const T&& x)
       {
           Node* newNode = new Node(std::move(x),tail->prev,tail);
           tail->prev->next = newNode;
           tail->prev = newNode;
           siz++;
       }

        // 前段删除元素
        void pop_front()
        {
            Node* tmp = head->next;
            head->next = tmp->next;
            tmp->next->prev = head;
            delete tmp;
            siz--;
        }
        
        // 后端删除元素
        void pop_back()
        {
            Node* tmp = tail->prev;
            tail->prev = tmp->prev;
            tmp->prev->next = tail;
            delete tmp;
            siz--;
        }

        // 在第 pos 个节点前面插入新的元素
        void insert(pos_t pos,const T& x)
        {
            Node* point = head->next;
            for(int i=0 ; i<pos ; i++)
                point = point->next;
            
            Node* newNode = new Node(x,point->prev,point);
            point->prev->next = newNode;
            point->prev = newNode;
            siz++;
        }

        // 在第 pos 个节点前面插入新的元素
       void insert(pos_t pos,const T&& x)
       {
           Node* point = head->next;
           for(int i=0 ; i<pos ; i++)
               point = point->next;
           
           Node* newNode = new Node(std::move(x),point->prev,point);
           point->prev->next = newNode;
           point->prev = newNode;
           siz++;
       }

        // 删除位置 pos 上的元素
        void erase(pos_t pos)
        {
            Node* point = head->next;
            for(int i=0 ; i<pos ; i++)
                point = point->next;
            point->prev->next = point->next;
            point->next = point->prev;
            delete point;
            siz--;           
        }
        
        // 删除从 from 到 to 的所有元素
        void erase(pos_t from,pos_t to)
        {
            for(int i= from ; i<=to ;i++)
                erase(i);
        }

        // 通过下标运算符访问元素
        T operator[](pos_t pos)
        {
            if(pos<0 || pos>=siz)
            {
                cout<<"Error:Out of index!"<<endl;
                return -1;
            }
            else
            {
                Node* point = head->next;
                for(int i=0 ; i<pos ; i++)
                    point = point->next;
                return point->value;
            }
        }
      
};

/* 特殊方法表
    List()              // 构造函数

*/


/* 访问函数表

    size_t size() const; 		// 查询链表规模
	bool empty() const; 		// 判断链表是否为空

*/

/* 修改函数表

    void clear()            // 清除链表中的所有元素

	void push_back()		// 末尾插入元素
	void push_front()		// 首部插入元素
	void pop_back()			// 末尾删除元素
	void pop_front()		// 首部删除元素

	void insert(pos_t,int)	// 在位置 pos 插入元素
	void erase(pos_t)		// 删除位置 pos 上的元素

    void operator[]() const; // 重载下标运算符

*/





























#endif
