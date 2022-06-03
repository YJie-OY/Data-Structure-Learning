#include<iostream>
#include<fstream>
#include<cstdio>
#include"Graph.h"
using namespace std;

// 图的信息导入函数, weight->有无权重， Direction->是否是有向边
Graph Myinput(string Filename,bool weight = false,bool Direction=true)
{
    int N=0,M=0;
    ifstream input_file;
    input_file.open(Filename,ios::in);
    input_file>>N>>M;
    // printf("%d  %d\n",N,M);
    Graph tmpGraph(N);
    int u=0;
    int v=0;
    int w=1;

    for(int i=1 ; i<=M ; i++)
    {
        if(weight == false)
            input_file>>u>>v;
        else
            input_file>>u>>v>>w;
        // 无边权的图,默认边权为1.
        tmpGraph.Add_Edge(u,v,w);
        if(Direction == false)
            tmpGraph.Add_Edge(v,u,w);
    }
    return tmpGraph;
}

int main()
{
    printf("////////////////////////////////////////////////////////////////////////////\n");
    printf("//////////////////////////   基础功能检测   /////////////////////////////////\n");
    printf("////////////////////////////////////////////////////////////////////////////\n");
    // Graph MyGraph1;
    // MyGraph1 = Myinput("input1.txt",true);
    // printf("MyGraph1展示\n");
    // MyGraph1.print_graph();
    // printf("============================ Vertexes_num() 测试 =============================\n");
    // printf("the number of vertexes = %d\n",MyGraph.Vertexes_num());

    // printf("============================ Edges_num() 测试 =============================\n");
    // printf("the number of edges = %d\n",MyGraph.Edges_num());

    // printf("=========================== isEmpty() 测试 ==================================\n");
    // printf("Mygraph is %s empty!\n",MyGraph.isEmpty()?"":"not");

    // printf("=========================== degrees() 测试 =================================\n");
    // printf("the degree of mygraph  = %.1f \n",MyGraph.degrees());

    // printf("=========================== indegree() 测试 =================================\n");
    // printf("the indegree of vertex 1 = %d\n",MyGraph.indegree(1));
    // printf("the indegree of vertex 4 = %d\n",MyGraph.indegree(4));
    // printf("the indegree of vertex 10 = %d\n",MyGraph.indegree(10));

    // printf("=========================== outdegree() 测试 =================================\n");
    // printf("the outdegree of vertex 1 = %d\n",MyGraph.outdegree(1));
    // printf("the outdegree of vertex 4 = %d\n",MyGraph.outdegree(4));
    // printf("the outdegree of vertex 10 = %d\n",MyGraph.outdegree(10));

    // printf("=========================== Del_Edge() 测试 =================================\n");
    // printf("indegree of 5 = %d, indegree of 4 = %d\n",MyGraph.indegree(5),MyGraph.indegree(4));
    // MyGraph.Del_Edge(2,5);
    // MyGraph.Del_Edge(1,4);
    // printf("indegree of 5 = %d, indegree of 4 = %d\n",MyGraph.indegree(5),MyGraph.indegree(4));
    // MyGraph.print_graph();

    // printf("=========================== Del_Vertex() 测试 =================================\n");
    // printf("indegree of 12 = %d , outdegree of 4 = %d\n",MyGraph.indegree(12),MyGraph.outdegree(4));
    // MyGraph.Del_Vertex(4);
    // printf("indegree of 12 = %d , outdegree of 4 = %d\n",MyGraph.indegree(12),MyGraph.outdegree(4));
    // MyGraph.print_graph();



    printf("////////////////////////////////////////////////////////////////////////////\n");
    printf("////////////////////////////   算法测试   ///////////////////////////////////\n");
    printf("////////////////////////////////////////////////////////////////////////////\n");


    printf("\n============================= topsort()测试 =========================\n");
    // 求拓扑排序
    printf("++++ 图信息导入 ++++\n");
    Graph topsort_test;
    topsort_test = Myinput("input1.txt",false,true);
    topsort_test.print_graph();

    printf("++++ 算法检测 ++++\n");
    printf("The result of topsort is \n");
    topsort_test.topsort();
    printf("\n");


    printf("\n============================= MaxFlow()测试 =========================\n");
    // 求网络的最大流
    printf("++++ 图信息导入 ++++\n");
    Graph MaxFlow_test;
    MaxFlow_test = Myinput("input3.txt",true,true);
    MaxFlow_test.print_graph();

    printf("++++ 算法检测 ++++\n");
    printf("%d\n",MaxFlow_test.MaxFlow(1,MaxFlow_test.Vertexes_num()));


    printf("\n============================= Kosaraju()测试 =========================\n");
    // 有向图的各个强连通分支
    printf("++++ 图信息导入 ++++\n");
    Graph Kosaraju_test;
    Kosaraju_test = Myinput("input5.txt",false);
    Kosaraju_test.print_graph();

    printf("++++ 算法测试 ++++\n");
    Kosaraju_test.Kosaraju(1);



    printf("\n============================= Tarjan()测试 =========================\n");
    // 求图的割点
    printf("++++ 图信息导入 ++++\n");
    Graph Tarjan_test;
    Tarjan_test = Myinput("input4.1.txt",false,true);
    Tarjan_test.print_graph();

    printf("++++ 算法检测 ++++\n");
    Tarjan_test.Tarjan();

    printf("\n============================= EulerCircuit()测试 =========================\n");
    // 求图的欧拉回路
    printf("++++ 图信息导入 ++++\n");
    Graph EulerCircuit_test;
    EulerCircuit_test = Myinput("input6.txt",false,false);
    EulerCircuit_test.print_graph();

    printf("++++ 算法检测 ++++\n");
    EulerCircuit_test.EulerCircuit(1);

    return 0;
}