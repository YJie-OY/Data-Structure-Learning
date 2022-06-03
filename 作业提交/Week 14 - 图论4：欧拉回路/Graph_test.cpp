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


    // cout<<MyGraph[2]<<endl;

    // Graph MyGraph2(MyGraph);
    // MyGraph2.Add_Edge(1,3,10);
    // MyGraph2.print_graph();
    // MyGraph.print_graph();
    // printf("The result of topsort is \n");
    // MyGraph.topsort();
    // printf("=========================================");



    
    // printf("============================= MaxFlow()测试 =========================\n");
    // Graph MaxFlow_test;
    // MaxFlow_test = Myinput("input3.txt",true,true);
    // MaxFlow_test.print_graph();
    // printf("%d\n",MaxFlow_test.MaxFlow(1,MaxFlow_test.Vertexes_num()));

    // printf("============================= BulidNet()测试 =========================\n");
    // MyGraph3 = MyGraph3.BulidNet();
    // MyGraph3.print_graph();

    
    // printf("============================= getedge()测试 =========================\n");
    // Edge_type& tmp = MyGraph3.get_Edge(1,2);
    // tmp.w = 8;
    // MyGraph3.print_graph();

    // printf("============================= Kosaraju()测试 =========================\n");

    // printf("++++ 图信息导入 ++++\n");
    // Graph MyGraph4;
    // MyGraph4 = Myinput("input5.txt",false);
    // MyGraph4.print_graph();
    // printf("++++ 算法测试 ++++\n");
    // MyGraph4.Kosaraju(1);

    // printf("============================= BuildReverse()测试 =========================\n");
    // Graph tmpGraph4;
    // tmpGraph4 = MyGraph4.BulidReverse();
    // // tmpGraph4.print_graph();



    // printf("============================= Tarjan()测试 =========================\n");
    // printf("++++ 图信息导入 ++++\n");
    // Graph Tarjan_test;
    // Tarjan_test = Myinput("input4.1.txt",false,true);
    // Tarjan_test.print_graph();
    // printf("++++ 算法检测 ++++\n");
    // Tarjan_test.Tarjan();

    // printf("============================= EulerCircuit()测试 =========================\n");
    printf("++++ 图信息导入 ++++\n");
    Graph EulerCircuit_test;
    EulerCircuit_test = Myinput("input6.txt",false,false);
    EulerCircuit_test.print_graph();
    printf("++++ 算法检测 ++++\n");
    EulerCircuit_test.EulerCircuit(1);

    return 0;
}