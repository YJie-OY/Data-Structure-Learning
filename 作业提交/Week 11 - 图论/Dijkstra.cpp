#include<iostream>
#include<fstream>
#include<cstdio>
#include"Graph.h"
using namespace std;
#define MAX_DISTANCE 1000000001 // 设定一个不可能达到的路长上限
int main()
{
    // 文件流导入信息
    int N=0,M=0;
    ifstream input_file;
    input_file.open("input2.txt",ios::in);
    input_file>>N>>M;
    Graph MyGraph(N);
    int u=0;
    int v=0;
    int w=0;
    for(int i=1 ; i<=M ; i++)
    {
        input_file>>u>>v>>w;
        MyGraph.Add_Edge(u,v,w);
    }
    // MyGraph.print_graph();
    int start = 0;
    input_file>>start;
    int dis[N+1];
    // dis 用于存储起点到每一个点的距离,最终时将变成到每一个点的最短距离.
    for(int i=1 ; i<=N ; i++)
        dis[i] = MAX_DISTANCE;
    dis[start] = 0;
    // known用于存储第i个点的最短路径是否已知.
    bool known[N+1] = {0};
    int num_unknown = N;

    /**************************************************
     * Dijkstra算法基本思路
     * (1)遍历当前所有不知最短路的点,也就是 known=flase的点.从遍历的点中,找到目前距离最小的点.
     * (2)以找到的最小距离点为中心点,更新所有未知点到起点的距离 ： dis[未知点] = min{dis[未知点],dis[最小点]+最小点与未知点的距离}
     * 一些信息：初始的时候,最小点就是它本身,通过邻接表访问距离.
     * ***********************************************/
    while(num_unknown > 0)
    {
        // 遍历所有未知点,找到最小距离点
        int dist_now = MAX_DISTANCE;
        int min_vertex = 0;
        for(int i=1 ; i<=N ; i++)
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
        Graph::Vertex_type a_vertex = MyGraph.get_vertex(min_vertex);
        Graph::Edge_type* an_Edge = a_vertex.firstEdge;
        for(;an_Edge!=nullptr;an_Edge=an_Edge->next)
        {
             int distance = an_Edge->w;
             if(dis[an_Edge->v] > dis[min_vertex] + distance)
             {
                dis[an_Edge->v] = dis[min_vertex] + distance;
                Graph::Vertex_type &vertex=MyGraph.get_vertex(an_Edge->v);
                vertex.prev = min_vertex; 
             }
        }
    }
    printf("%d %d\n",1,dis[1]);
    for(int i=2 ; i<=N ; i++)
    {
        printf("%d %d ",i,dis[i]);
        MyGraph.print_path(i);
        printf("\n");
    }
    return 0;

}




/******************************************************************************************
-----------------------------------------------------------------------------------------
任务三：实现 “Dijkstra” 算法
-----------------------------------------------------------------------------------------
目    的：对于标号为 1, 2, ..., N 的 N 个顶点的边赋权有向图以及源顶点 s，计算由 s 到其余
          所有顶点的最短路径

数据规格：
 1. 输入：输入数据由三部分组成
          第一部分包含两个非负整数 N、M，其中 N 为给定有向图顶点个数，M 为其边数
          第二部分有 M 个三元组 x、y、w，表示顶点 x 到顶点 y 有带实数权 w 的边
          第三部分为源顶点标号 s
 2. 输出：对于给定的输入数据，输出 N 行，每行的第一部分为一个顶点的标号 K，紧接一个空格后
          的第二部分是一个表示由源 s 到顶点 K 的最短路径长的实数，在一个空格后的第三部分
          是若干正整数，表示由源 s 到顶点 K 的一条最短路径的顶点序列

数据样例：
 1. 输入:

7 12
1 2 2
1 4 1
2 4 3
2 5 10
3 1 4
3 6 5
4 3 2
4 5 2
4 6 8
4 7 4
5 7 6
7 6 1
1

 2. 输出：(注意，输出可能不唯一)

1 0
2 2 1 2
3 3 1 4 3
4 1 1 4
5 3 1 4 5
6 6 1 4 7 6
7 5 1 4 7
******************************************************************************************/    
