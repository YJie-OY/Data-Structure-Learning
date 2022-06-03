#include<iostream>
#include<fstream>
#include<cstdio>
#include"Graph.h"
using namespace std;
int main()
{
    int N=0,M=0;
    ifstream input_file;
    input_file.open("input1.txt",ios::in);
    input_file>>N>>M;
    printf("%d  %d\n",N,M);
    Graph MyGraph(N);
    int u=0;
    int v=0;
    printf("============================= Add_Edge() + print_graph()测试 =========================\n");
    for(int i=1 ; i<=M ; i++)
    {
        input_file>>u>>v;
        // 无边权的图,默认边权为1.
        MyGraph.Add_Edge(u,v,1);
    }
    MyGraph.print_graph();
    printf("============================ Vertexes_num() 测试 =============================\n");
    printf("the number of vertexes = %d\n",MyGraph.Vertexes_num());

    printf("============================ Edges_num() 测试 =============================\n");
    printf("the number of edges = %d\n",MyGraph.Edges_num());

    printf("=========================== isEmpty() 测试 ==================================\n");
    printf("Mygraph is %s empty!\n",MyGraph.isEmpty()?"":"not");

    printf("=========================== degrees() 测试 =================================\n");
    printf("the degree of mygraph  = %.1f \n",MyGraph.degrees());

    printf("=========================== indegree() 测试 =================================\n");
    printf("the indegree of vertex 1 = %d\n",MyGraph.indegree(1));
    printf("the indegree of vertex 4 = %d\n",MyGraph.indegree(4));
    printf("the indegree of vertex 10 = %d\n",MyGraph.indegree(10));

    printf("=========================== outdegree() 测试 =================================\n");
    printf("the outdegree of vertex 1 = %d\n",MyGraph.outdegree(1));
    printf("the outdegree of vertex 4 = %d\n",MyGraph.outdegree(4));
    printf("the outdegree of vertex 10 = %d\n",MyGraph.outdegree(10));

    printf("=========================== Del_Edge() 测试 =================================\n");
    printf("indegree of 5 = %d, indegree of 4 = %d\n",MyGraph.indegree(5),MyGraph.indegree(4));
    MyGraph.Del_Edge(2,5);
    MyGraph.Del_Edge(1,4);
    printf("indegree of 5 = %d, indegree of 4 = %d\n",MyGraph.indegree(5),MyGraph.indegree(4));
    MyGraph.print_graph();

    printf("=========================== Del_Vertex() 测试 =================================\n");
    printf("indegree of 12 = %d , outdegree of 4 = %d\n",MyGraph.indegree(12),MyGraph.outdegree(4));
    MyGraph.Del_Vertex(4);
    printf("indegree of 12 = %d , outdegree of 4 = %d\n",MyGraph.indegree(12),MyGraph.outdegree(4));
    MyGraph.print_graph();

    return 0;
}