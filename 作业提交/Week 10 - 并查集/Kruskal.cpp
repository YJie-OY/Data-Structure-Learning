#include"djset.h"
#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
/*************************************************************************
 * 算法流程：
 * 1. 每一条边,按照边权排序
 * 2. 按照边权从小到大取边(a,b)
 *      2.1 若 find(a) == find(b) 说明生成树中已经有边,跳过。
 *      2.2 若 find(a) != find(b) 说明生成树中没有边,累加权值,标记当前边.
 *      2.3 若 集合中已经有N-1条边,结束.
 * 3. 输出生成树的权值和.
 * 4. 遍历所有边,并且把标记了的边输出出来.
 * ***********************************************************************/
struct Edge_type
{
    int x;
    int y;
    int w;
    bool chosen = false;
    friend ostream &operator<<(ostream &out, Edge_type e)
    {
        out<<e.x<<" "<<e.y;
    }
};
bool cmp(const Edge_type& a,const Edge_type& b)
{
    return a.w<b.w;
}
int main()
{
    int N=0,M=0;
    cout<<"请输入N、M:";
    cin>>N>>M;
    int x[M+1]={0};
    int y[M+1]={0};
    int w[M+1]={0};
    int sum_weight = 0;
    cout<<"请输入每一条边以及权重：";
    Edge_type Edges[M+1];
    for(int i=0 ; i<M ; i++)
    {
        cin>>Edges[i].x; 
        cin>>Edges[i].y;
        cin>>Edges[i].w;
    }
    sort(Edges,Edges+M,cmp);
    // cout<<"------------ 排序后结果 --------------"<<endl;
    // for(int i=0 ; i<M ; i++)
    //     cout<<Edges[i]<<endl;


    djset Min_tree(N+1);
    for(int i=0 ; i<M ; i++)
    {
        if(Min_tree.find(Edges[i].x) == Min_tree.find(Edges[i].y))
            continue;
        else
        {
            Min_tree.unionSets(Edges[i].x,Edges[i].y);
            sum_weight += Edges[i].w;
            Edges[i].chosen=true;
            // Min_tree.print_father();
        }
    }
    cout<<sum_weight<<endl;
    for(int i=0 ;i<M ; i++)
    {
        if(Edges[i].chosen == true)
            cout<<Edges[i]<<endl;
    }

}


































/*
-----------------------------------------------------------------------------------------
任务三：实现 “Kruskal” 算法
-----------------------------------------------------------------------------------------
目    的：对于给定标号为 1, 2, ..., N 的 N 个顶点的边赋权无向连通图，计算其最小生成树。

数据规格：
 1. 输入：输入数据由两部分组成
          第一部分包含两个非负整数 N、M，其中 N 为给定无向图顶点个数，M 为无向图的边数
          第二部分有 M 个三元组 x、y、w，表示顶点 x 与顶点 y 之间有带实数权 w 的边
 2. 输出：对于给定的输入数据，输出 N 行，第一行为一个实数，表示最小生成树边权的和，第二
          到第 N 行为两个正整数，表示最小生成树的所有边

数据样例：
输入:
7 12
1 2 2
1 4 1
1 3 4
2 4 3
2 5 10
3 4 2
3 6 5
4 5 7
4 6 8
4 7 4
5 7 6
6 7 1

输出：(注意，输出不唯一)

16
1 4
6 7
1 2

3 4
4 7
5 7
*/


