/***********************************************
 * 本代码使用邻接表(Adjacency List)来存储图结构
 * 在类外,顶点下标通常为 1~N 
 **********************************************/
#ifndef _GRAPH_
#define _GRAPH_
#include<iostream>
#include<vector>
#include<cstdio>
#include<queue>
using namespace std;

class Graph
{
public:
    class Edge_type
    {
        public:
            int u; // 起点
            int v; // 终点
            int w; // 权重
            int flow;
            Edge_type* next;  // 下一条边
            Edge_type():u(0),v(0),w(0),flow(0),next(nullptr){}

    };
    class Vertex_type
    {
        public:
            int data;   // 节点也许是有数据的
            int InDegree;
            int OutDegree;
            int prev;   // 存储路径的上一个节点
            Edge_type* firstEdge;  // 存储第一条边
            Vertex_type():data(0),InDegree(0),OutDegree(0),prev(0),firstEdge(nullptr){}
    };

public:
    int vernum;
    int Edgenum;
    vector<Vertex_type> Vertex_list;

public: // 基本函数
    Graph(int vn):vernum(vn),Edgenum(0){
        Vertex_list = vector<Vertex_type>(vernum+10);
    }
    
    ~Graph()
    {
      Vertex_list.clear();
    }

    bool isEmpty() const               {return vernum == 0;}
    const int Vertexes_num() const     {return vernum;}
    const int Edges_num() const        {return Edgenum;}
    const int indegree(int idx) const  {return Vertex_list[idx].InDegree;}
    const int outdegree(int idx) const {return Vertex_list[idx].OutDegree;}
    const double degrees() const       {return (double)Edgenum/2;}

    Vertex_type& operator[](int idx)
    {
        return Vertex_list[idx];
    }

    
    void print_graph()
    {
        printf("+++++++++++++++++++++++++++++++++ printing +++++++++++++++++++++++++++++++++\n");
        printf("the number of vertexes = %d \n",vernum);
        printf("the number of edges  = %d \n",Edgenum);
        for(int i=1 ; i<=vernum ; i++)
        {
            printf("%2d : ",i);
            Edge_type* tmp = Vertex_list[i].firstEdge;
            for(; tmp!=nullptr ; tmp=tmp->next)
                printf("(%d->%d|%d) ",tmp->u,tmp->v,tmp->w);
            printf("\n");
        }
        printf("+++++++++++++++++++++++++++ Successfully printed ! +++++++++++++++++++++++++++\n");
    }

    void print_path(int u)
    {
        if(Vertex_list[u].prev != 0)
        {
            print_path(Vertex_list[u].prev);
            printf(" ");
        }
        printf("%d",u);
    }
    // 打印出最大流算法后在每一条边上分配的流量
    void print_flow()  
    {
        for(int i=1 ; i<=vernum ; i++)
        {
            Edge_type* tmp = Vertex_list[i].firstEdge;
            for(; tmp!=nullptr ; tmp=tmp->next)
                printf("%d %d %d\n",tmp->u,tmp->v,tmp->flow);
        }
    }

public: // 修改器
    // 增加一条边
    void Add_Edge(int u,int v,int w)
    {
        Edge_type* an_Edge = new Edge_type;
        an_Edge->u = u;
        an_Edge->v = v;
        an_Edge->w = w;

        // 获取当前起点的最后一条边
        Edge_type* end_Edge = Vertex_list[u].firstEdge; 
        if(end_Edge == nullptr)
            Vertex_list[u].firstEdge = an_Edge;
        else
        {
            while(end_Edge->next != nullptr) end_Edge=end_Edge->next;
            end_Edge->next = an_Edge;
        }


        Vertex_list[u].OutDegree++;
        Vertex_list[v].InDegree++;
        Edgenum++;
    }
    // 删除一条边
    void Del_Edge(int u,int v)
    {
        // 对第一条边就是所寻边的情况进行特殊处理
        if(Vertex_list[u].firstEdge->v == v)
        {
            Edge_type* tmp = Vertex_list[u].firstEdge;
            Vertex_list[u].firstEdge = tmp->next;
            delete tmp;
            Edgenum--;
            Vertex_list[u].OutDegree--;
            Vertex_list[v].InDegree--;
            return ;
        }
        // 其他时候有必要记录前一条边.
        Edge_type* prev = Vertex_list[u].firstEdge;
        Edge_type* tmp = prev->next;
        for(; tmp!=nullptr ; tmp=tmp->next)
        {
            if(tmp->v == v)
            {
                prev->next = tmp->next;
                delete tmp;
                Edgenum--;
                Vertex_list[u].OutDegree--;
                Vertex_list[v].InDegree--;
                break;
            }
            prev = tmp;
        }
        return ;
    }
    // 将一个点所有的边删掉,实际上就意味着这个点终止状态为firstEdge=nullptr
    void Del_Vertex(int u)
    {
        while(Vertex_list[u].firstEdge != nullptr)
            Del_Edge(u,Vertex_list[u].firstEdge->v);
    }
    
    Vertex_type& get_vertex(int u)
    {
        return Vertex_list[u];
    }

// public: //算法查询
    // 这里的二维数组并没有处理好
    // int BFS(int src,int des,int residual[][8],int flow[], int prev[])
    // {
    //     queue<int> MyQueue;
    //     for(int i=0 ; i<=vernum ; i++)
    //         prev[i] = -1;
    //     flow[src] = 0x3f3f3f;
    //     MyQueue.push(src);
    //     // 当队列不为空时
    //     while( !MyQueue.empty() )
    //     {
    //         int index = MyQueue.front();
    //         if(index == des)
    //             break;
            
    //         for(int i=1 ; i<=vernum ; i++)
    //         {
    //             if(i!= src && residual[index][i]>0 && prev[i]==-1)
    //             {
    //                 prev[i] = index;
    //                 flow[i] = min(residual[index][i],flow[index]);
    //                 MyQueue.push(i);
    //             }
    //         }
    //     }
    //     if(prev[des] == -1)
    //         return -1;
    //     else
    //         return flow[des];
    // }


    // 基于 Ford fulkerson算法(标号法)的网络最大流求解.
//     int Maxflow(int src,int des)
//     {
//         // 妥协了,用邻接矩阵存储残图信息;
//         int residual[vernum+1][vernum+1];
//         int flow[vernum+1] = {0};
//         int prev[vernum+1] = {0};

//         // 初始化残图信息,先全部初始化为0,然后在根据已有的邻接表使得存在边的残量初始化为容量.
//         for(int i=1 ; i<=vernum ; i++)
//             for(int j=1 ; j<=vernum ; j++)
//                 residual[i][j] = 0;
//         for(int i=1 ; i<=vernum ; i++)
//         {
//             Edge_type* tmp = Vertex_list[i].firstEdge;
//             for(; tmp!=nullptr ; tmp=tmp->next)
//                 residual[tmp->u][tmp->v] = tmp->w;
//         }
//         // 检查一下残图初始化有没有问题
//         // for(int i=1 ; i<=vernum ; i++)
//         // {
//         //     for(int j=1 ; j<=vernum ; j++)
//         //         printf("%d ",residual[i][j]);
//         //     printf("\n");
//         // }

//         int increasement = 0;
//         int sumflow = 0;
//         while( (increasement=BFS(1,vernum,residual,flow,prev) != -1))
//         {
//             sumflow+=increasement;

//             int k = des;
//             while (k != src)
//             {
//                 int Last_vertex = prev[k];
//                 residual[Last_vertex][k] -= increasement;
//                 residual[k][Last_vertex] += increasement;
//                 k = Last_vertex;
//             }
//         }
        
//         // 更新边的流量信息
//         for(int i=1 ; i<=vernum ; i++)
//         {
//             Edge_type* tmp = Vertex_list[i].firstEdge;
//             for(; tmp!=nullptr ; tmp=tmp->next)
//             {
//                 tmp->flow = tmp->w - residual[tmp->u][tmp->v];
//             }
//         }
//         return sumflow;
//     }
};


#endif

/*************************************************************************************
 ************************************** 一些笔记 **************************************
 * (1)图中顶点用一个一维数组存储，当然也可以用单链表来存储，
 * 不过用数组可以较容易的读取顶点信息，更加方便。另外，对于顶点数组中，
 * 每个数据元素还需要存储指向第一个邻接点的指针，以便于查找该顶点的边信息。
 * (2)  图中每个顶点vi的所有邻接点构成一个线性表，
 * 由于邻接点的个数不定，所以用单链表存储，无向图称为顶点vi的边表，有向图则称为以vi为弧尾的出边表。
 ***********************************************************************************************/

/******************************************************************************************
-----------------------------------------------------------------------------------------
任务一：
-----------------------------------------------------------------------------------------
目    的：建立 图类 的C++类 - 基于C++11语言规范标准
          为简单起见，以下用 图 来指代上述数据结构

类 型 名：graf 或 graph (建议)
          为简单起见，以下用 GRAF 来指代上述类型名
          另以 VTX 和 ARC 分别指代顶点类型和边类型

基本成分：适当设计以便支持各种图论算法
          1. VTX 类型: (建议)表示为基本数据(如数据集元素、元素相关
                             性辅助信息等)及邻居顶点序列数据结构
          2. ARC 类型: (建议)表示为基本数据(如权值等)边的端点信息
          3. GRAF类型: (建议)表示为顶点序列的数据结构

功能要求：1. 可有效声明图对象
          2. 可有效获得图的顶点数、边数、顶点(出/入)度数
          3. 可有效判定指定图是否为空图
******************************************************************************************/    


/******************************************************************************************
 * Ford fulkerson方法获取网络最大流,采用 BFS 实现.
 * 
 * MaxFlow(int src,int des)函数大致步骤：
 * 信息申请: 
 * 1. residual[n+1][n+1] : 用于记录残量,residual[a][b]代表a节点到b节点的残量.
 * 2. prev[n+1] : 用于记录前驱; prev[i] 表示i节点的前驱
 * 3. flow[n+1] : 用于记录到当前节点的流; flow[i] 表示i节点所属路径的流,显然它应该是这条路上的最小残量.
 * 算法主体:
 * 1. 初始化数据 : 最大流量 sumflow 初始为0;
 * 2. 利用 BFS 算法找到一条增广路,返回一个增量并且记为increasement ,同时路径信息已经被保留在每个节点的prev中.
 * 3.1 如果increasement = -1 , 那么说明不存在增广路, 那么结束算法并且返回 sumflow;
 * 3.2 如果increasement > 0 , 那么说明存在并且找到了一条增广路, 累加流量(sumflow += increasement),
 *     从终点开始,并且将路径上的节点做反向边的增加,其中若一个节点的prev!=-1,那么说明这个节点是当前增广路上的一个节点.
 * 
 * BFS(int src, int des) 函数大致步骤:
 * 1. 初始化数据: (1)所有的节点prev应该为-1 (2)申请一个队列MyQueue,队列一开始应该为空. 
 * 2. 将起点加入到队列当中;
 * 3. 逐个遍历队列中的点,并且将这些点的邻居全部加入队列当中,同时修改这些邻居的prev;
 * 4. 当邻居中出现终点的时候,说明已经找到一条增广路,那么退出循环,并且返回终点的流flow[des];
 * *******************************************************************************************/