#include<iostream>
#include<fstream>
#include<cstdio>
#include"Graph.h"
using namespace std;
int main()
{
    // 文件流导入信息
    int N=0,M=0;
    ifstream input_file;
    input_file.open("input1.txt",ios::in);
    input_file>>N>>M;
    Graph MyGraph(N);
    int u=0;
    int v=0;
    for(int i=1 ; i<=M ; i++)
    {
        input_file>>u>>v;
        MyGraph.Add_Edge(u,v,1);
    }
    MyGraph.print_graph();
    /*******************************************************
     * 拓扑排序基本思路
     * (1)寻找入度为0的点
     * (2)删除该点的邻接边,更新剩余顶点的入度信息;
     * (3)执行(1)(2),直到所有点都已不在图中
     * ***************************************************/
    int num=0;
    bool flag[N+1] = {0};
    int toplist[N+1]={0};
    while(num<N)
    {
        for (int i=1 ;i<=N ;i++)
        {
            if(flag[i] == true) continue;
            if(MyGraph.indegree(i) != 0) continue;
            MyGraph.Del_Vertex(i);
            toplist[++num] = i;
            flag[i] = true;
        }
    }
    for(int i=1 ; i<=N ; i++)
        printf("%d ",toplist[i]);

    
    return 0;
}




































/******************************************************************************************
-----------------------------------------------------------------------------------------
任务二：实现 “DAG的拓扑排序” 算法并讨论其时间复杂度
-----------------------------------------------------------------------------------------
目    的：对于给定标号为 1, 2, ..., N 的 N 个顶点的DAG，计算其顶点的拓扑全序序列。

数据规格：
 1. 输入：输入数据由两部分组成
          第一部分包含两个非负整数 N、M，其中 N 为给定图顶点个数，M 为其边数
          第二部分有 M 对不超过 N 的正整数 x、y，表示顶点 x 到顶点 y 之间有边
 2. 输出：对于给定的输入数据，输出一行以一个空格分隔的正整数，其恰好是输入数据
          所确定的有向无环图顶点集的拓扑全序序列。

数据样例：
 1. 输入:

17 22
1 4
2 4 2 5 2 6
4 3 4 8 4 9 4 10 4 11 4 12
5 11
6 7 6 10 6 11
9 14
10 13 10 15 10 16
11 12 11 16
15 14
16 17

 2. 输出：(注意，输出可能不唯一)

1 2 4 5 6 7 8 9 10 11 12 13 15 16 17 3 14
******************************************************************************************/    
