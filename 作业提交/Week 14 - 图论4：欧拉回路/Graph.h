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
#include<algorithm>
#include"MyList_iterator.h"
#define MAX_DISTANCE 1000000001 // 设定一个不可能达到的路长上限
using namespace std;

class Edge_type
{
    public:
        int u; // 起点
        int v; // 终点
        int w; // 权重
        int index;
        bool flag;
        Edge_type* next;  // 下一条边
        Edge_type():u(0),v(0),w(0),index(0),flag(false),next(nullptr){}

};

class Vertex_type
{
    public:
        int data;   // 节点也许是有数据的
        int InDegree;
        int OutDegree;
        int flow;
        int prev;   // 存储路径的上一个节点
        int index;
        int branch;
        int low;
        int num;
        bool visited;
        bool flag; //可以被当做是割点的判断
        Edge_type* firstEdge;  // 存储第一条边
        Vertex_type():data(0),InDegree(0),OutDegree(0),branch(0),flag(false),flow(-1),prev(0),index(0),firstEdge(nullptr){}
        // 打印点的状态
        friend ostream& operator<<(ostream& out,Vertex_type& u)
        {
            out<<u.index<<":";
            Edge_type* tmp = u.firstEdge;
            for(; tmp!=nullptr ; tmp=tmp->next)
                out<<"("<<tmp->u<<"->"<<tmp->v<<"|"<<tmp->w<<") ";
            out<<endl;
        }
};

class Graph
{
public:
    int VerNum;  // 顶点数量
    int EdgeNum;
    int BranchNum;
    vector<Vertex_type> Vertex_list;
    vector<int> PostOrder;

public: // 基本函数
    Graph()
    {
        VerNum = 0;
        EdgeNum = 0;
        BranchNum = 0;
        Vertex_list = vector<Vertex_type>(10);
        PostOrder = vector<int>(10);
    }
    Graph(int vn):VerNum(vn),EdgeNum(0){
        // 采用邻接表存储图,并且默认顶点的下标从 1 开始
        BranchNum = 0;
        Vertex_list = vector<Vertex_type>(VerNum+10);
        PostOrder = vector<int>(VerNum+10);
        for(int i=1 ; i<=VerNum ; i++)
        {
            Vertex_list[i].index = i;
            PostOrder[i] = i;
        }
    }
    Graph(Graph& rhs):VerNum(rhs.VerNum),EdgeNum(0)
    {
        BranchNum = 0;
        Vertex_list = vector<Vertex_type>(VerNum+10);
        PostOrder = vector<int>(VerNum+10);
        for(int i=1 ; i<=VerNum ; i++)
        {
            PostOrder[i] = i;
            Vertex_list[i].index = i;
            Vertex_list[i].branch = rhs.Vertex_list[i].branch;
            Edge_type* tmp = rhs.Vertex_list[i].firstEdge;
            for(; tmp!=nullptr ; tmp=tmp->next)
            {
                Add_Edge(tmp->u,tmp->v,tmp->w);
            }
        } 
    }
    
    ~Graph()
        {Vertex_list.clear();}

    Graph& operator=(Graph &rhs)
    {
        VerNum = rhs.VerNum;
        BranchNum = rhs.BranchNum;
        Vertex_list.resize(VerNum);
        PostOrder.resize(VerNum);
        for(int i=1 ; i<=VerNum ; i++)
        {
            PostOrder[i] = i;
            Vertex_list[i].index = i;
            Vertex_list[i].branch = rhs.Vertex_list[i].branch;
            Edge_type* tmp = rhs.Vertex_list[i].firstEdge;
            for(; tmp!=nullptr ; tmp=tmp->next)
            {
                Add_Edge(tmp->u,tmp->v,tmp->w);
            }
        } 
        return *this;
    }

    Graph& operator=(Graph && rhs)
    {
        VerNum = std::move(rhs.VerNum);
        EdgeNum = std::move(rhs.EdgeNum);
        BranchNum = std::move(rhs.BranchNum);
        Vertex_list = std::move(rhs.Vertex_list);
        PostOrder = std::move(rhs.PostOrder);
        return *this;
    }

    bool isEmpty() const               {return VerNum == 0;}
    const int Vertexes_num() const     {return VerNum;}
    const int Edges_num() const        {return EdgeNum;}
    // 访问图的度数信息
    const int indegree(int idx) const  {return Vertex_list[idx].InDegree;}
    const int outdegree(int idx) const {return Vertex_list[idx].OutDegree;}
    const double degrees() const       {return (double)EdgeNum/2;}

    // 重载下标运算符
    Vertex_type& operator[](int idx)
    {
        return Vertex_list[idx];
    }

    //打印图,查看图现在的状态
    void print_graph()
    {
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("the number of vertexes = %d \n",VerNum);
        printf("the number of edges  = %d \n",EdgeNum);
        for(int i=1 ; i<=VerNum ; i++)
        {
            printf("%2d : ",i);
            Edge_type* tmp = Vertex_list[i].firstEdge;
            for(; tmp!=nullptr ; tmp=tmp->next)
                printf("(%d->%d|%d) ",tmp->u,tmp->v,tmp->w);
            printf("\n");
        }
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
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

    void print_PostOrder()
    {
        for(int i=1 ; i<=VerNum ; i++)
            printf("%d ",PostOrder[i]);
        printf("\n");
    }
    // 这个函数在找不到边的时候没有报错警告,仅仅是返回一个没有意义的边.
    Edge_type& get_Edge(int u,int v)
    {
        Edge_type* tmp = Vertex_list[u].firstEdge;
        for(; tmp!=nullptr ; tmp=tmp->next)
        {
            if (tmp->v == v)
            {
                return *tmp;
            }
            
        }
        cout<<"We didn't find the Edge you want!"<<endl;
        Edge_type* nothing = new Edge_type;
        return *nothing;

    }

    int flag_num(int branch = 0)
    {
        int num = 0;
        for(int i=1 ; i<=VerNum ; i++)
            if(Vertex_list[i].branch == branch && Vertex_list[i].flag == true)
                num++;
        return num;
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
        // 当前顶点没有边的时候需要特殊处理一下
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
        EdgeNum++;
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
            EdgeNum--;
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
                EdgeNum--;
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

    void clear_visited()
    {
        for(int i=1 ; i<=VerNum ; i++)
            Vertex_list[i].visited = false;
    }

    void clear_flag()
    {
        // 清除点的标记以及边的标记
        for(int i=1 ; i<=VerNum ; i++)
        {
            Vertex_list[i].flag = false;
            Edge_type* tmp = Vertex_list[i].firstEdge;
            for(; tmp!=nullptr ; tmp=tmp->next)
                tmp->flag = false;
        }
    }



public: // 图论算法
    /**************************************************************************
     * 拓扑排序基本思路
     * (1)寻找入度为0的点
     * (2)删除该点的邻接边,更新剩余顶点的入度信息;
     * (3)执行(1)(2),直到所有点都已不在图中
     * 注意：为了不对原图进行修改而只是获取信息，因此创建了一个副本
     * **********************************************************************/
    void topsort()
    {
        Graph tmp_Graph(*this);
        int num = 0;
        bool flag[tmp_Graph.Vertexes_num()+1] = {0};
        while(num < tmp_Graph.Vertexes_num())
        {
            for(int i=1 ; i<=tmp_Graph.Vertexes_num() ;i++)
            {
                if(flag[i] == true) continue;
                if(tmp_Graph.indegree(i) != 0) continue;
                tmp_Graph.Del_Vertex(i);
                flag[i] = true;
                ++num;
                cout<<i<<" ";
            }
        }
    }

    /****************************************************************************************
     * Dijkstra算法基本思路
     * (1)遍历当前所有不知最短路的点,也就是 known=flase的点.从遍历的点中,找到目前距离最小的点.
     * (2)以找到的最小距离点为中心点,更新所有未知点到起点的距离 ： dis[未知点] = min{dis[未知点],dis[最小点]+最小点与未知点的距离}
     * 一些信息：初始的时候,最小点就是它本身,通过邻接表访问距离.
     * *************************************************************************************/
    void Dijkstra(int start)
    {
        int dis[VerNum+1];
        // dis 用于存储起点到每一个点的距离,最终时将变成到每一个点的最短距离.
        for(int i=1 ; i<=VerNum ; i++)
            dis[i] = MAX_DISTANCE;
        dis[start] = 0;
        // known用于存储第i个点的最短路径是否已知.
        bool known[VerNum+1] = {0};
        int num_unknown = VerNum;

        while(num_unknown > 0)
        {
            // 遍历所有未知点,找到最小距离点
            int dist_now = MAX_DISTANCE;
            int min_vertex = 0;
            for(int i=1 ; i<=VerNum ; i++)
            {
                if(known[i]==false && dist_now > dis[i])
                {
                    dist_now = dis[i];
                    min_vertex = i;
                }
            } 
            known[min_vertex] = true;
            num_unknown--;
            // 获取这个顶点的邻接表
            Edge_type* tmp = Vertex_list[min_vertex].firstEdge;
            for(; tmp!=nullptr; tmp=tmp->next)
            {
                int distance = tmp->w;
                if(dis[tmp->v] > dis[min_vertex] + distance)
                {
                    dis[tmp->v] = dis[min_vertex] + distance;
                    Vertex_list[tmp->v].prev = min_vertex; 
                }
            }
        }
        printf("%d %d\n",1,dis[1]);
        for(int i=2 ; i<=VerNum ; i++)
        {
            printf("%d %d ",i,dis[i]);
            print_path(i);
            printf("\n");
        }
    }
    
    /******************************************************************************************
     * Ford fulkerson方法获取网络最大流,采用 BFS 实现.
     * 
     * MaxFlow(int src,int des)函数大致步骤：
     * 信息申请: 
     * 1. residual[n+1][n+1] : 用于记录残量,residual[a][b]代表a节点到b节点的残量.
     * 2. prev[n+1] : Vertex_type 属性,用于记录前驱; prev[i] 表示i节点的前驱
     * 3. flow[n+1] : Vertex_type 属性,用于记录到当前节点的流; flow[i] 表示i节点所属路径的流,显然它应该是这条路上的最小残量.
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
    
    // 构造网络图,实际上是在原图的基础上增加负向边的存在.
    Graph BulidNet()
    {
        Graph theNet(*this);
        for(int i=1 ; i<=VerNum ; i++)
        {
            Edge_type* tmp = theNet[i].firstEdge;
            for(; tmp!=nullptr ; tmp=tmp->next)
            {
                // 标记一下正向边
                if(tmp->w != 0)
                {
                    tmp->flag = true;
                    theNet.Add_Edge(tmp->v,tmp->u,0);
                }
            }
        }
        return theNet;
    }
    
    int BFS(int src,int des,Graph& theNet)
    {
        queue<int> MyQueue;
        int flow[VerNum+1];
        while (!MyQueue.empty())
            MyQueue.pop();
        for(int i=1 ; i<=VerNum ; i++)
            theNet[i].prev = -1;

        flow[src] = MAX_DISTANCE;
        theNet[src].prev = 0;

        MyQueue.push(src);
        while(!MyQueue.empty())
        {
            int index = MyQueue.front();
            MyQueue.pop();
            if(index == des)
                break;
            Edge_type* tmp = theNet[index].firstEdge;
            for(; tmp!=nullptr ; tmp=tmp->next)
            {
                if(tmp->v!=src && tmp->w>0 && theNet[tmp->v].prev == -1)
                {
                    theNet[tmp->v].prev = index;
                    flow[tmp->v] = min(flow[index],tmp->w);
                    MyQueue.push(tmp->v);
                }
            }
        }
        if(theNet[des].prev == -1)
            return -1;
        else
            return flow[des];
    }

    int MaxFlow(int src,int des)
    {
        // 构造网络
        Graph theNet(VerNum);
        theNet = BulidNet();
        int increasement = 0;
        int sumflow = 0;
        while((increasement = BFS(src,des,theNet)) != -1)
        {
            sumflow += increasement;
            int k = des;
            while(k!=src)
            {
                int last = theNet[k].prev;
                Edge_type& forward = theNet.get_Edge(last,k);
                forward.w -= increasement;
                Edge_type& backward = theNet.get_Edge(k,last);
                backward.w += increasement;
                k = last;
            }
        }
        // this->print_graph();
        for(int i=1 ; i<=VerNum ; i++)
        {
            Edge_type* tmp=Vertex_list[i].firstEdge;
            for(; tmp!=nullptr ; tmp=tmp->next)
            {
                Edge_type theNet_Edge = theNet.get_Edge(tmp->u,tmp->v);
                printf("%d %d %d\n",tmp->u,tmp->v,tmp->w-theNet_Edge.w);
            }
        }
        return sumflow;
    }




    /******************************************************************************
     * Tarjan 求割点算法,维护两个重要的数组. dfn[n]和low[n]
     * 任务1: 判断无向图的连通性，如果不连通，那么意味着不只有一个连通分支。对每一个连通分支都要寻找割点。
     * 任务2: 判断连通分支的双连通性，利用 Tarjan 割点算法，找出当前连通分支的割点，并且输出每一个割点的标号。
     * 对于任务1:
     * 连通分支实际上是原图的子图,这里采用对点进行标记的方法,而不是额外的构建的 Graph.
     * 因此,只需要对 sub_class == 0 的点进行深搜,直到所有的点都被标好类就可以了.
     * 对于任务2:判断无向图的双连通性.
     * 
     * *****************************************************************************/
    int DFS_Connnect(int u,int branch_name=0,int num=0)
    {
        if(Vertex_list[u].visited == true)
            return num;
        
        Vertex_list[u].visited = true;
        Vertex_list[u].branch = branch_name;
        num++;

        Edge_type* tmp = Vertex_list[u].firstEdge;
        for(; tmp!=nullptr ; tmp=tmp->next)
        {
            num = DFS_Connnect(tmp->v,branch_name,num);
        }
        return num;
    }

    // 检测割点,不包含对根的检测
    int findArt(int u,int count=0)
    {
        Vertex_list[u].visited = true;
        Vertex_list[u].low = Vertex_list[u].num = ++count;
        printf("count = %d, vertex[%d],low = %d,num = %d\n",count,u,Vertex_list[u].low,Vertex_list[u].num);

        if(count == 1)
        {
            int child = 0;
            Edge_type* tmp = Vertex_list[u].firstEdge;
            for(; tmp!=nullptr ; tmp=tmp->next)
            {
                printf("Edge : %d -> %d \n",tmp->u,tmp->v);
                if(Vertex_list[tmp->v].visited == false) // 没有访问过,是一条前向边
                {
                    child++;
                    Vertex_list[tmp->v].prev = tmp->u;
                    count = findArt(tmp->v,count);
                    printf("Vertex[%d].low = %d Vertex[%d].low = %d\n",tmp->u,Vertex_list[tmp->u].low,tmp->v,Vertex_list[tmp->v].low);
                    // 如果这个节点回不去 u , 说明 u 是一个割点.
                    if(Vertex_list[tmp->v].low >= Vertex_list[u].num)
                    {
                        Vertex_list[u].flag = true;
                    }
                    Vertex_list[u].low = min(Vertex_list[tmp->u].low,Vertex_list[tmp->v].low);
                }
                else // 说明可能是一条背向边
                {
                    if(Vertex_list[tmp->u].prev != tmp->v) // 并且访问的并不是他的父亲
                        Vertex_list[u].low = min(Vertex_list[u].low,Vertex_list[tmp->v].num);
                }
            }
            if(child >= 2)
                Vertex_list[u].flag = true;
            else           
                Vertex_list[u].flag = false;
        }

        Edge_type* tmp = Vertex_list[u].firstEdge;
        for(; tmp!=nullptr ; tmp=tmp->next)
        {
            if(Vertex_list[tmp->v].visited == false) // 没有访问过,是一条前向边
            {
                printf("Edge : %d -> %d \n",tmp->u,tmp->v);
                Vertex_list[tmp->v].prev = tmp->u;
                count = findArt(tmp->v,count);
                // 如果这个节点回不去 u , 说明 u 是一个割点.
                printf("Vertex[%d].low = %d Vertex[%d].low = %d\n",tmp->u,Vertex_list[tmp->u].low,tmp->v,Vertex_list[tmp->v].low);
                if(Vertex_list[tmp->v].low >= Vertex_list[u].num) 
                {
                    Vertex_list[u].flag = true;
                }
                Vertex_list[u].low = min(Vertex_list[tmp->u].low,Vertex_list[tmp->v].low);
            }
            else // 说明可能是一条背向边
            {
                if(Vertex_list[tmp->u].prev != tmp->v) // 并且访问的并不是他的父亲
                    Vertex_list[u].low = min(Vertex_list[u].low,Vertex_list[tmp->v].num);
            }
        }
        return count;

    }

    void Tarjan()
    {
        // 清空分支信息
        BranchNum=0;
        clear_visited();
        clear_flag();
        for(int i=1 ; i<=VerNum ; i++)
        {
            if(Vertex_list[i].visited == false)
                DFS_Connnect(i,++BranchNum,0);
        }
        clear_visited();

        for(int i=1 ; i<=BranchNum ; i++)
        {
            for(int j=1 ; j<=VerNum ; j++)
            {
                if(Vertex_list[j].branch == i)
                {
                    findArt(j,0);
                }
                break;
            }
            // 打印结果
            printf("%d: %d ",i,flag_num(i));
            for(int j=1 ; j<=VerNum ; j++)
            {
                if(Vertex_list[j].branch == i && Vertex_list[j].flag == true)
                {
                    printf("%d ",j);
                }
            }
            printf("\n");
        }
    }





    /****************************************************************************************
     * Kosaraju算法 : 求有向图的强连通分支.
     * (1) 编写BulidReverse() 生成一个反向图（邻接表）。
     * (2)对图 G 进行DFS_G(),生成一个后序遍历序列。还需要的点属性为 `visited`. 
     *      后序遍历存储在成员属性 PostOrder中。
     * (3)对图 G 的逆图 进行DFS_G_Reverse(),寻找强连通分量.
     * *************************************************************************************/
    // 返回当前图的逆图
    Graph BulidReverse()
    {
        Graph R_Graph(VerNum);
        for(int i=1 ; i<=VerNum ; i++)
        {
            Edge_type* tmp = Vertex_list[i].firstEdge;
            for(; tmp!=nullptr ; tmp=tmp->next)
            {
                R_Graph.Add_Edge(tmp->v,tmp->u,tmp->w);
            }
        }
        // R_Graph.print_graph();
        return R_Graph;
    }

    // 从一个点开始访问,构建一个后序遍历序列并且保存到 PostOrder 中.
    int DFS_G(int u,int num)
    {
        if(Vertex_list[u].visited == true)
            return num;
        else
            Vertex_list[u].visited = true;

        Edge_type* tmp = Vertex_list[u].firstEdge;
        for(; tmp!=nullptr ; tmp=tmp->next)
        {
            num = DFS_G(tmp->v,num);
        }
        PostOrder[++num] = u;
        return num;
    }

    int DFS_G_Reverse(int u)
    {
        if(Vertex_list[u].visited == true)
            return 0;
        else
            Vertex_list[u].visited = true;
        printf("%d ", u);
        Edge_type* tmp = Vertex_list[u].firstEdge;
        for(; tmp!=nullptr ; tmp=tmp->next)
        {
            DFS_G_Reverse(tmp->v);
        }
        return 0;
    }

    // 结果在理论上没有毛病,但是需要在输出形式上做出一点修改.
    void Kosaraju(int u)
    {

        // 对图 G 进行DFS构造一个后序遍历的序列
        // 千万注意：这里得到的序列必须反向后才能使用,因为我们要找编号最大的.
        int num = 0;
        for(int i=1 ; i<=VerNum ; i++)
        {
            if(Vertex_list[i].visited == false)
            {
                num = DFS_G(i,num);
                // printf("%d\n",num);
            }
        }

        // print_PostOrder();
        clear_visited();

        // 创建逆图
        Graph R_Graph;
        R_Graph = BulidReverse();

        // R_Graph.print_graph();

        // 对逆图进行深搜,注意这里我们是从编号最大的开始搜起.
        for(int i=VerNum ; i>=1 ; i--)
        {
            if(R_Graph[PostOrder[i]].visited == false)
            {
                R_Graph.DFS_G_Reverse(PostOrder[i]);
                printf("\n");
            }
        }
    }

    /***********************************************************
     * 默认是一个无向图,此处不做检测.
     * 欧拉回路实现算法:
     * 1. 判断图是否连通;
     * 2. 判断图中的每一个顶点是否都是偶顶点
     * 3. 深搜开始
     * *********************************************************/
    void DFS_Euler(int u,List<int> &the_path)
    {
        Edge_type* tmp = Vertex_list[u].firstEdge;
        for(; tmp!=nullptr ; tmp=tmp->next)
        {
            Del_Edge(tmp->u,tmp->v);
            Del_Edge(tmp->v,tmp->u);
            the_path.push_back(tmp->v);
            // printf("%d ",tmp->v);
            DFS_Euler(tmp->v,the_path);
            return ;
        }
    }
    
    
    
    void EulerCircuit(int start)
    {
        // 清除标记
        clear_visited();
        clear_flag();

        // 判断是否连通
        if(VerNum != DFS_Connnect(start,1,0))
        {
            printf("The Graph is not connected!");
            return;
        }
        // 判断是否所有顶点都是偶顶点
        bool flag = false;
        for(int i=1 ; i<=VerNum ; i++)
        {
            if(Vertex_list[i].InDegree % 2 != 0)
            {
                printf("顶点[%d]不是偶顶点",i);
                flag = true;
            }
        }
        if(flag)
        {
            printf("含有奇顶点,不存在欧拉回路!");
            return ;
        }

        Graph copy(*this);
        // copy.print_graph();
        List<int> main_path;
        main_path.push_back(start);
        copy.DFS_Euler(start,main_path);
        printf("The initial main_path is \n");
        main_path.print_List();
        while(copy.Edges_num() != 0)
        {
           List<int>::iterator itr=main_path.begin();
            for(; itr!=main_path.end() ; itr++)
            {
                if(copy.Vertex_list[*itr].firstEdge != nullptr)
                {
                    List<int> tmp_path;
                    copy.DFS_Euler(*itr,tmp_path);

                    main_path.splice(itr+1,tmp_path,tmp_path.begin(),tmp_path.end());
                    printf("Now the new main_path is \n");
                    main_path.print_List();
                }
            }
        }


        
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


