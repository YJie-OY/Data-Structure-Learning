# Graph

​		实现一个完整的图类，基于邻接表。

​		可以合作，三个人一组，表明成员，各自一份，说明自己的工作。



## Edge_type

完全公开的边类，用于存储边的一些必要信息

```c++
class Edge_type
{
    public:
        int u; // 起点
        int v; // 终点
        int w; // 权重
        int flow;  // 超容量
        Edge_type* next;  // 下一条边
        Edge_type():u(0),v(0),w(0),flow(0),next(nullptr){}

};
```



## Vertex_type

完全公开的点类，用于存储顶点的一些必要的信息。

```C++
class Vertex_type
{
    public:
        int data;   // 节点也许是有数据的
        int InDegree; // 顶点入度
        int OutDegree;  // 顶点出度
        int prev;   // 存储路径的上一个节点
        Edge_type* firstEdge;  // 存储第一条边
        Vertex_type():data(0),InDegree(0),OutDegree(0),prev(0),firstEdge(nullptr){}
};
```



## Graph

>  实现图类，应该包含基本的图类操作以及基本的算法。

### 基础数据成员

```C++
public:
    int VerNum;  // 顶点数量
    int EdgeNum;
    vector<Vertex_type> Vertex_list;

```



### 基础函数

```C++
public: // 基本函数
    Graph(int vn):VerNum(vn),EdgeNum(0){
        // 采用邻接表存储图,并且默认顶点的下标从 1 开始.
        Vertex_list = vector<Vertex_type>(VerNum+10);
    }
    
    ~Graph()
    {
      Vertex_list.clear();
    }
```



### 查询函数

```C++
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
```



### 修改器

```C++
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
```





### 基本算法

#### 拓扑排序

​		得到一个拓扑排序并且不能对原图有影响

#### 迪杰斯特拉算法

​		得到以start为原点到所有别的边的最短路，并且打印出来



#### 网络最大流算法

​		结合广搜的网络最大流算法。采用 Ford-fulkerson 方法。

​		对网络的要求，首先他应该是输入的有向边对应的对称闭包；其中正向边应该有权重，初始时残量应该等于权重（权重就是容量），而负向边没有权重，但是也可以有残量，这个残量表示反向超容量。因而在进入算法之前，应该构造一个当前图的对称闭包。初始时正向超容量就是权重，负向超容量应该为0，故可以直接在权重上做手脚。由于涉及到残量的更改，因此网络必须具有修改某一条边的权重的能力，修改这一步是容易的，但是获取一条边却相对比较低效。





#### 无向图的双连通性判别

目    的：对于给定标号为 1, 2, 3, ... , N-1, N 的 N 个顶点的无向图，判别其连通性和双连通性，并给出割点集(可能是空集）采用深度优先搜索的割点算法。

连通性的判断：任何一个点之间可以相互到达。

双连通性：在无向连通图的基础上，如果图中没有割点，那么当前连通图就具有双连通性。

> 桥的概念：当把某一条边去掉之后，图就不连通了，那么这条边就是桥，当然这里和我们没有什么关系。

##### 暴力割点算法

​		依次删除某一个点，然后用DFS判断图是否还是连通的，但是这种做法效率比较低。

##### Tarjan 割点算法

引入两个重要的数组 `dfn[n]` 和 `low[n]` .

- `dfn[n]` : 用于记录节点首次被访问的时间，实际上这个时间使用被访问的顺序来表示的。
- `low[n]` : 节点通过无向边最早回溯到的时间点。

那么可以得到一个规律，对于 u 的所有子节点而言，以 v 为例子，若当 `low[v]>=dfn[u]`时，这意味着 v 没有办法回到 u 以前的点，那么这个时候如果把 u 去掉，u 的祖先就会与 u 的儿子们失联。

实验任务：

1. 判断无向图的连通性，如果不连通，那么意味着不只有一个连通分支。对每一个连通分支都要寻找割点。
2. 判断连通分支的双连通性，利用 Tarjan 割点算法，找出当前连通分支的割点，并且输出每一个割点的标号。

怎么维护 `dfn[n]` 和 `low[n]` 数组呢？一开始的时候这两个数组可以初始化为当前的时间节点。而`dfn` 初始化之后显然就不需要改动了，那么 `low` 又应该怎么维护呢？





#### 有向图的强连通分支计算

对于给定标号为 1, 2, 3, ... , N-1, N 的 N 个顶点的有向图，计算其所有强连通性分支采用双深度优先搜索策略。



强连通分量介绍：
在有向图G中，如果两个顶点vi,vj间有一条从vi到vj的有向路径，同时还有一条从vj到vi的有向路径，则称两个顶点强连通(strongly connected)。如果有向图G的每两个顶点都强连通，称G是一个强连通图。有向图的极大强连通子图，称为强连通分量(strongly connected components)



Kosaraju算法：

算法基于的实施：对于图 $G$ 的逆图 $G^T$ ，和原图有着完全相同的连通分支。也就是说，如果 $s$ 和 $t$ 在图 $G$ 中是互达的，那么 $s$ 和 $t$ 在图 $G^T$ 中也是互达的，从而找到了一个强连通分量。



算法的步骤：

`step1` ：对原图进行深度优先遍历，记录每个节点的离开时间。

`step2`：选择具有最晚离开时间的顶点，对逆图 $G^T$ 进行遍历，删除能够遍历到的顶点，同时，这些被删除的顶点构成一个强连通分量。

 `step3`：如果此时还有顶点没有被删除，那么继续 `step2`，否则算法结束。

​		在上面的算法当中，实际上第一次深度优先搜索的作用就是生成一个关于节点的后序遍历，也就是所谓记录下来的每个节点的“离开时间”。为什么要用到后序遍历来实现呢？可以知道的是，在一个后续遍历当中，有一个编号大的节点 $\alpha$ ，和一个编号小的节点 $\beta$ ，那么这必然意味着对节点 $\beta$ 的工作比节点 $\alpha$ 的工作先要完成。

​		在第二步当中，我们总是把编号最大的节点作为深度优先搜索生成树的根 $x$ 。开始对 $G^r$ 的一次搜索，假设节点 $v$ 是这次搜索当中的一个子节点。这意味着在 $G^r$ 中，存在 $x$ 到 $v$ 的一条路径，也意味着在 $G$ 中存在一条从 $v$ 到 $x$  的一条路径，这是完全没问题的，因而这一条 $x \leftrightarrow v$ 就是一条强连通分量， 也没有问题。

> 在这个过程中因为“路径”这个两个字疑惑了一下，因为下意识的认为 $x$ 到 $v$ 应该是一条线，不应该有分支。然而在实际搜索的过程中生成的是一棵树（也就是说是有分支的），也没有问题吗？确实，对于单线形状的强连通分量，我们会觉得很好理解，假设对 $G^r$ 的一次搜索生成树中存在两个分支分别记为 $x$ 到 $v$  和 $x$ 到 $w$ ，那么显然 $x$ 到 $v$ 是强连通的  ，$x$ 到 $w$ 也是强连通的，那么你简单的画一个图可以知道 $v$ 到 $w$ 必然也是强连通的，这意味着，这一次生成树上的所有点都是强连通的。

 		那么“后序遍历+编号最大”这个机制到底怎么理解呢？我认为这实际上避免了“原路返回的可能”。

参考一篇CSDN：[寻找有向图的强连通分支_rucefan的博客-CSDN博客](https://blog.csdn.net/Shimizu_Masato/article/details/7563217)

​		首先我们将上面的内容换个说法（本质上一样），如果 $x$ 到 $v$ 是一个强连通分量，那么在图 $G$ 中有 $x \rightarrow v$ 的路径，而且在图 $G^r$ 中还有 $x \rightarrow v$​ 的路径。

​		**定理1**	一个强连通分支一定在森林中的一个树上面，而不会跨越一个树到另一个树上面。

​		在 `step1` 中，对图 $G$ 生成后序遍历序列的过程中，实际上会生成若干棵深度优先搜索的树$a,b,c...$ ，这些树各有各的强连通分量，不可能有交集，这是定理1告诉我们的内容。假设有一个强连通分量跨越了两棵树，那么根据深度优先搜索，这两棵树只可能是同一棵树（这不是搞笑么）。这意味着，在 `step1`中生成的若干棵树，都会有独属于自己的强连通分量，可能一个也可能多个。

​		**定理2**	将一个强连通分支各个边反向后，还是一个强连通分支。这个是显然的，实际上要用到的就是我上面的那个说法。

​		**定理3**	经过对G图的深搜，一定不存在从先生成的树到后生成的树的边，但是反过来是有可能成立的。

​		怎么理解定理3呢？想表达什么意思呢？实际上我们在 `step2`对 $G^r$ 的深搜过程中，也是会生成多棵深度搜索树的吧？按照定理1的内容，这个时候生成的树不可能跨越在 `step1`中生成的树，否则就构成了跨越搜索树的强连通分量。那么现在可以假设

​		$a$ 是在 `step1`中对 $G$ 深搜过程中生成的一棵搜索树，而其将会对应在对图 $G^r$ 的过程中生成的 $a_1^r,a_2^r...$ 。

​		假如在`step2`我们对 $a$ 中的点随意进行开始搜索，那么就会有一个危险：一个点按照原路返回了！什么意思？假设在 $G$ 中有 $A \rightarrow B \rightarrow C$ ，那么在 $G^r$ 里面肯定会有 $C \rightarrow B \rightarrow A$ ，然而这条路并不能帮我们判别是不是强连通分量，它只是在 $G$ 反转的时候产生的一个必然产物，真正的强连通分量一般的情况是 $C$ 通过别的路径回到了 $A$ ，实际上这警示我们 ： 应该尽可能的不要从 $C$ 开始，更加一般的说，不要从一个子节点开始！！这下就能理解为什么要用“后序遍历+编号最大开始”的机制了。



##### 算法流程

1. 编写BulidReverse() 生成一个反向图（邻接表）。
2. 正向DFS，生成一个后序遍历序列。还需要的点属性为 `visited`. 这个后序遍历我们将至作为一个成员属性也是OK的。
3. 反向DFS，需要一个后序遍历序列，根据后序遍历开始深搜，没完成一次深搜，输出一个强连通分量，实际上每访问一个就直接打印就可以了，然后不同次的搜索之间要打印一个换行符。



#### 欧拉回路

​		**概念**	给定无孤立结点图G，若存在一条路，经过图中每条边一次且仅一次，该条路为欧拉路，若存在一条回路，经过图中每边一次且仅一次，该回路称为欧拉回路。

​		从某一点出发，然后走一次并且回到当前点，那么欧拉回路存在。这个过程对 DFS 来说是容易的，只要从起点出发，要求经过每个点后并且能够回到起点，那么就找到了欧拉回路。

​		怎么避免在深搜过程中大部分顶点都未遍历到但是算法就结束了？事实上在这种情况中，提前结束代表找到了一条回路，这个时候只需要继续找回路就好了，因为回路是可以合并的。

​		回路合并问题。使用自己构建的基础设施来使得插入更加高效。在这里通常使用链表来实现。

​		欧拉（回）路存在的前提：图是连通的。

​		欧拉回路存在的充要条件：每一个顶点都是偶节点。证明：欧拉回路的起点和终点必然是同一个点，出边的数量必然和入边的数量相等。

​		欧拉路径存在的充要条件：奇节点的数量为0 或 2.



##### 欧拉回路算法流程

1. 判断图是否连通
    1. 如果图不连通，那么欧拉回路不存在；
    2. 如果图是连通的，进行下一步判断。
2. 判断图是否均为偶顶点
    1. 如果存在奇顶点，那么欧拉回路不存在；
    2. 如果全是偶顶点，那么欧拉回路必然存在。
3. 使用 `dfs` 从一个偶顶点开始遍历，每一次的 `dfs` 必然能找到一个环；但问题的关键在于，我们可能只访问了图的一部分就提前结束回到起点了，而此时起点已经没有别的边可以出来。此时采取的策略是从此时已有的路径上找到一个点，并且从这个点重新出发，并且将由这个点衍生出来的圈拼接到原来的回路上，直到所有的边都被遍历完成，那么这就要我们始终维护一个链表，这个链表就是所求的欧拉回路。
    1. 从给定的起点开始深搜，构造出一个链表，被我们称为主链。



## 其他话题

#### 链表实现 O(nlogn) 的排序

​		堆排序不可避免的用到下标查询，所以在实现上不应该用链表。

​		快速排序也不划算，因为要构造一个等长的迭代器序列。

​		归并排序。中点的获取势必要扫描完一整个链表，所以光是确定中点就必须要线性时间。似乎是如此，但是实际的归并排序过程中却这却不是一个重要的问题。

​		需要用到的函数 `splice()` 和 `merge()` 

​		
