/***********************************************
 * 本代码使用邻接表(Adjacency List)来存储图结构
 * 在类外,顶点下标通常为 1~N 
 **********************************************/
#ifndef _GRAPH_
#define _GRAPH_
#include<iostream>
#include<vector>
#include<cstdio>
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
            Edge_type* next;  // 下一条边
            Edge_type():u(0),v(0),w(0),next(nullptr){}

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
    int dist(int u,int v)
    {
        Edge_type* tmp = Vertex_list[u].firstEdge;
        for(;tmp!=nullptr;tmp=tmp->next)
        {
            if(tmp->v == v)
                return tmp->w;
        }
        return 10000001;
    }

    
    void print_graph()
    {
        printf("+++++++++++++++++++++++++++ printing +++++++++++++++++++++++++++\n");
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

public: // 修改器
    // 增加一条边
    void Add_Edge(int u,int v,int w)
    {
        Edge_type* an_Edge = new Edge_type;
        an_Edge->u = u;
        an_Edge->v = v;
        an_Edge->w = w;

        an_Edge->next = Vertex_list[u].firstEdge;
        Vertex_list[u].firstEdge = an_Edge;

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