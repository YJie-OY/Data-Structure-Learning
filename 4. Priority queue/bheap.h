 /***************************************************************************
  * 二叉堆  : 完全二叉树,是优先队列的一种普遍实现.
  * 功能建议 : decreaseKey,increaseKey,remove;(最好增加到类型当中)
  * 完全二叉树 : 十分有规律,以至于可以用数组去描述,然而二叉堆通常都是
  *             实时变动的,因而最好要用动态数组去描述.在本例中,二叉堆
  *             堆的实现通过对一个vector的封装来完成.
  * 注意    : 当使用动态数组来模拟二叉堆的时候,索引为 0 的元素不应该
  *           具有实际意义,t也就是根节点应该放在索引为 1 的位置,因为我们希望通过索引来找到其子节点,而索引为 0 
  *         的时候(0*2)是没办法用上的,然而可以作为一般的存储数据使用。
  * 模拟实验 : P207 应用案例. 
  **************************************************************************/
#include<iostream>
#include<vector>
#include<initializer_list>
using namespace std;
 template<typename Comaparable>
 class bheap
 {
private:
    int                 currentSize;
    vector<Comaparable> queue;

  /***********************************************************************************
   * bulidHeap() : 建堆.
   * 基本思想 : 往上逐层下滤.
   ***********************************************************************************/
    void bulidHeap()
    {
        for(int i=currentSize/2 ; i>0 ; ++i)
            percolateDown(i);
    }
  /***********************************************************************************
  * percolatedown() : 在堆中进行下滤的内部方法,空穴是下滤开始处的下标
  * 基本思路       :  如果要删除某个
  **********************************************************************************/
    void percolateDown(int hole)
    {
        int child;
        // 预先记录下当前空穴的值
        Comaparable tmp = std::move(queue[hole]);

        for( ; hole*2 <= currentSize ; hole = child)
        {
            // 让子节点中比较小的那个填入空穴
            child = hole*2;
            // 如果右儿子存在，并且右儿子比左儿子要小，那么应该让右儿子填入空穴，
            if(child != currentSize && queue[child + 1] < queue[child])
                ++child;

            // 如果子节点比记录下的空穴的值小，说明该子节点应该上移，因此把子节点的值填入空穴
            // 如果子节点比记录下的空穴的值大，说明此处应该是原来记录下的空穴的值的位置，因为已经不必下移了，所以循环可以结束了。
            if(queue[child] < tmp)
                queue[hole] = std::move(queue[child]);
            else 
                break;
            // 结束，使得空穴移动到子节点的位置
        }
        queue[hole] = std::move(tmp); 
    }


public:
    /***************************************************************************
     * bheap()    : 构造函数
     *                  1. 默认构造函数
     *                  2. 复制构造函数
     *                  3. 移动构造函数
     *                  4. 初始化列表构造函数
     *                  5. 序列构造函数(建议)
     **************************************************************************/
    explicit bheap(int capacity = 100):queue(capacity),currentSize(0){}

    explicit bheap(const vector<Comaparable> & item):queue(item.size()+10),currentSize(item.size())
    {
        for(int i=0 ; i<item.size() ; ++i)
            queue[i+1] = item[i];
        bulidHeap();
    }
    explicit bheap(const bheap<Comaparable> & rhs):queue(rhs.queue.size() + 10), currentSize(rhs.currentSize)
    {
        for(int i=1 ; i<=currentSize ; ++i)
            queue[i] = rhs.queue[i];
    }

    explicit bheap(const bheap<Comaparable> && rhs):queue(rhs.queue.size() + 10), currentSize(rhs.currentSize)
    {
        this->queue = std::move(rhs.queue);
    }


    bheap(const std::initializer_list<Comaparable> v):queue(1),currentSize(0)
    {
        for(auto it:v)
            insert(it);
    }


    ~bheap() {makeEmpty();}

    /***************************************************************************
     * spltree& operator=() : 赋值重载
     *                      1. 复制赋值重载
     *                      2. 移动赋值重载
     *                      3. 初始化列表赋值重载
     **************************************************************************/

    bheap& operator=(bheap<Comaparable> & rhs)
    {
        currentSize = rhs.currentSize;
        queue = rhs.queue;
    }
    

    
    bheap& operator=(std::initializer_list<Comaparable> v)
    {
        makeEmpty();
        queue.resize(10);

        for(auto it:v)
            insert(it);
        
    }



public:
    bool                Empty()  const  {return currentSize == 0 ; }
    const Comaparable & findmin() const
    {
        try
        {
            if(Empty())
                throw "Empty Tree when finding the minimum!";
        }
        catch(const char* msg)
        {
            cerr<<msg<<endl;
        }
        return queue[1];
    }


public:
 /***********************************************************************************
  * insert() ： 插入元素 x , 需要维持堆序性.
  * 思想 : 在堆尾部创建一个"空"-hole,将元素插入空,若新元素的加入不破坏堆序性,直接用新元素填空
  *         若破坏了堆序性,那么需要上滤,将当前位置的父节点填入hole中,并且使得hole向上移动
  * 终止条件:(1)当新元素比hole的父节点更大,无需上移,填入新元素
  *         (2) 当新元素已经上滤至堆顶,需要终止并且让堆顶值为新元素
  *         为了综合两种情况,事先让 queue[0] 的位置存储新元素
  ***********************************************************************************/

    void insert(const Comaparable & x )
    {
        if(currentSize == queue.size() - 1)
            queue.resize(queue.size() + 100);
        
        int hole = ++currentSize;
        Comaparable copy = x;

        queue[0] = std::move(copy);
        for( ; x<queue[hole/2] ; hole/=2)
            queue[hole] = std::move(queue[hole/2]);
        queue[hole] = std::move(queue[0]);
    }

    void insert(      Comaparable &&x )
    {
        if(currentSize == queue.size() - 1)
            queue.resize(queue.size() + 100);
        
        int hole = ++currentSize;

        queue[0] = std::move(x);
        for( ; queue[0]<queue[hole/2] ; hole/=2)
            queue[hole] = std::move(queue[hole/2]);
        queue[hole] = std::move(queue[0]);
    }

 /***********************************************************************************
  * deleteMin() : 删除最小元素(堆顶),并且维持堆序性
  * 基本思路 : 将堆顶元素删掉，并且用最后一个元素填上，显然这个元素应该是相对较大的，我们
  *             此时从堆顶开始设置空穴并且开始下溢。
  ***********************************************************************************/
    void deleteMin()
    {
        if(Empty())
        {
            // throw UnderflowException{};
            cout<<"Empty!"<<endl;
            return ;
        }

        queue[1] = std::move(queue[currentSize--]);
        percolateDown(1);
    }

    void deleteMin(Comaparable & minItem)
    {
        if(Empty())
        {
            // throw UnderflowException{};
            cout<<"Empty!"<<endl;
            return ;
        }
            
        minItem = std::move(queue[1]);
        queue[1] = std::move(queue[currentSize--]);
        percolateDown(1);
    
    }


/***********************************************************************************
  * remove(int idx) : 删除堆中索引为idx的数据并且保持堆序性
  ***********************************************************************************/  
 void remove(int idx)
 {
     if(idx > currentSize) return;
     queue[idx] = std::move(queue[currentSize--]);
     percolateDown(idx);
 }

/***********************************************************************************
  * keydec(int idx,const Comparable& d) : 将索引为idx的数据减少d并且保持堆序性
  ***********************************************************************************/
 void keydec(int idx,const Comaparable & d)
 {
     if(idx > currentSize) return ;
     queue[idx] -= d;

    int hole = idx;

     queue[0] = queue[idx];
     for(; queue[idx] < queue[hole/2] ; hole/=2)
     {
         
         
         queue[hole] = queue[hole/2];
         
     }
        
    queue[hole] = queue[0];
    

     
 }  


/***********************************************************************************
  * keyinc(int idx,const Comparable& d) : 将索引为idx的数据增加d并且保持堆序性
  ***********************************************************************************/  
 void keyinc(int idx,const Comaparable & d)
 {
     if(idx > currentSize) return ;
     queue[idx] += d;
     percolateDown(idx);
 }  
 
/***********************************************************************************
  * swap() : 交换两个堆
  ***********************************************************************************/  
    void swap(bheap<Comaparable> &rhs)
    {
        std::swap(this->currentSize,rhs.currentSize);
        vector<Comaparable> tmp_queue;
        tmp_queue = this->queue;
        this->queue = rhs.queue;
        rhs.queue = tmp_queue;
        tmp_queue.clear();
    } 



 /***********************************************************************************
  * makeEmpty() : 清空堆.
  ***********************************************************************************/
  
    void makeEmpty()
    {
        queue.clear();
        currentSize = 0;
    }
 /***********************************************************************************
  * print() : 打印当前优先队列
  ***********************************************************************************/
    void print()
    {
        if(Empty())
            cout<<"The queue is empty !!!";

        cout<<"the priority queue is like :" <<endl;
        int lineflag = 2 ;
        for(int i=1 ; i<=currentSize ; i++)
        {
            cout<<queue[i]<<"  ";
            if( i == lineflag-1 )
            {
                cout<<endl;
                lineflag *= 2;
            }
        }
        cout<<endl;
    }

 };

  


