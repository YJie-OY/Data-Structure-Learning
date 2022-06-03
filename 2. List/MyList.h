#ifndef MYLIST
#define MYLIST

template <typename T>

class List
{
    public:
        typedef int pos_t;

    private: // ˽�����ݳ�Ա
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


    public:  // ���ⷽ��

        // ���캯��
        List()
        {
        	head = new Node(-1,nullptr,tail);
        	tail = new Node(-1,head,nullptr);
			
            siz = 0;
        }


        // ��������
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


    public: // ���ʺ���

        // ���ص�һ���ڵ㣨����ͷ��㣩
        T& begin() {return head->next->value;}
        const T& begin() const{return head->next->next;}

        // ����β���
        T& end() {return tail->prev->value;}
        const T& end() const {return tail->prev->value;}

        // ��ѯ��������ݹ�ģ
        size_t size() const {return siz;}
    
        // ��ѯ�����Ƿ�Ϊ��
        bool empty() const {return siz==0;}

    public: // �޸ĺ���

        // ��������е�Ԫ��
        void clear()
        {
            while(!empty())
                pop_front();
        }

        // ǰ�β���Ԫ��
        void push_front(const T& x)
        {
            Node* newNode = new Node(x,head,head->next);
            head->next->prev = newNode;
            head->next = newNode;
            siz++;
        }

        // ǰ�β���Ԫ�أ���ֵ��
       void push_front(const && x)
       {
           Node* newNode = new Node(std::move(x),head,head->next);
           head->next->prev = newNode;
           head->next = newNode;
           siz++;
       }

        // ��˲���Ԫ��
        void push_back(const T& x)
        {
            Node* newNode = new Node(x,tail->prev,tail);
            tail->prev->next = newNode;
            tail->prev = newNode;
            siz++;
        }

        // ��˲���Ԫ�أ���ֵ��
       void push_back(const T&& x)
       {
           Node* newNode = new Node(std::move(x),tail->prev,tail);
           tail->prev->next = newNode;
           tail->prev = newNode;
           siz++;
       }

        // ǰ��ɾ��Ԫ��
        void pop_front()
        {
            Node* tmp = head->next;
            head->next = tmp->next;
            tmp->next->prev = head;
            delete tmp;
            siz--;
        }
        
        // ���ɾ��Ԫ��
        void pop_back()
        {
            Node* tmp = tail->prev;
            tail->prev = tmp->prev;
            tmp->prev->next = tail;
            delete tmp;
            siz--;
        }

        // �ڵ� pos ���ڵ�ǰ������µ�Ԫ��
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

        // �ڵ� pos ���ڵ�ǰ������µ�Ԫ��
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

        // ɾ��λ�� pos �ϵ�Ԫ��
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
        
        // ɾ���� from �� to ������Ԫ��
        void erase(pos_t from,pos_t to)
        {
            for(int i= from ; i<=to ;i++)
                erase(i);
        }

        // ͨ���±����������Ԫ��
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

/* ���ⷽ����
    List()              // ���캯��

*/


/* ���ʺ�����

    size_t size() const; 		// ��ѯ�����ģ
	bool empty() const; 		// �ж������Ƿ�Ϊ��

*/

/* �޸ĺ�����

    void clear()            // ��������е�����Ԫ��

	void push_back()		// ĩβ����Ԫ��
	void push_front()		// �ײ�����Ԫ��
	void pop_back()			// ĩβɾ��Ԫ��
	void pop_front()		// �ײ�ɾ��Ԫ��

	void insert(pos_t,int)	// ��λ�� pos ����Ԫ��
	void erase(pos_t)		// ɾ��λ�� pos �ϵ�Ԫ��

    void operator[]() const; // �����±������

*/





























#endif
