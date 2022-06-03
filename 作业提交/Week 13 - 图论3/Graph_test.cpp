#include<iostream>
#include<fstream>
#include<cstdio>
#include"Graph.h"
using namespace std;

Graph Myinput(string Filename,bool weight = false)
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
    }
    return tmpGraph;
}
int main()
{
    // int N=0,M=0;
    // ifstream input_file;
    // input_file.open("input1.txt",ios::in);
    // input_file>>N>>M;
    // printf("%d  %d\n",N,M);
    // Graph MyGraph(N);
    // int u=0;
    // int v=0;
    // printf("============================= Add_Edge() + print_graph()测试 =========================\n");
    // for(int i=1 ; i<=M ; i++)
    // {
    //     input_file>>u>>v;
    //     // 无边权的图,默认边权为1.
    //     MyGraph.Add_Edge(u,v,1);
    // }
    // MyGraph.print_graph();
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

    // int N3=0,M3=0;
    // ifstream input_file3;
    // input_file3.open("input3.txt",ios::in);
    // input_file3>>N3>>M3;
    // printf("%d  %d\n",N3,M3);
    // Graph MyGraph3(N3);
    // u=0;
    // v=0;
    // int w=0;


    // for(int i=1 ; i<=M3 ; i++)
    // {
    //     input_file3>>u>>v>>w;
    //     // 无边权的图,默认边权为1.
    //     MyGraph3.Add_Edge(u,v,w);
    // }
    // MyGraph3.print_graph();

    // printf("============================= MaxFlow()测试 =========================\n");
    // printf("%d\n",MyGraph3.MaxFlow(1,N3));

    // printf("============================= BulidNet()测试 =========================\n");
    // MyGraph3 = MyGraph3.BulidNet();
    // MyGraph3.print_graph();

    
    // printf("============================= getedge()测试 =========================\n");
    // Edge_type& tmp = MyGraph3.get_Edge(1,2);
    // tmp.w = 8;
    // MyGraph3.print_graph();

    printf("============================= Myinput()测试 =========================\n");
    Graph MyGraph4;
    MyGraph4 = Myinput("input5.txt",false);
    // MyGraph4.print_graph();


    printf("============================= BuildReverse()测试 =========================\n");
    Graph tmpGraph4;
    tmpGraph4 = MyGraph4.BulidReverse();
    // tmpGraph4.print_graph();

    printf("============================= Kosaraju()测试 =========================\n");
    MyGraph4.Kosaraju(1);


    Graph MyGraph5;
    MyGraph5 = Myinput("input4.1.txt",false);
    MyGraph5.print_graph();

    MyGraph5.Tarjan();

    return 0;
}