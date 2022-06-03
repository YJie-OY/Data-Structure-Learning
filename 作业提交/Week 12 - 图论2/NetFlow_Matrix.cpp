#include<iostream>
#include<cstdio>
#include<fstream>
#include<algorithm>
#include<queue>
using namespace std;

// 数据准备
const int MAXSIZE = 101;
int N=0,M=0;
int capacity[MAXSIZE][MAXSIZE] = {0};
int residual[MAXSIZE][MAXSIZE]={0};
int Myprev[MAXSIZE] = {0};
int flow[MAXSIZE] = {0};
queue<int> MyQueue;

// 函数
int BFS(int src,int des)
{
    while (!MyQueue.empty())  //队列清空
        MyQueue.pop();
    for (int i = 1; i <= M; ++i) {
        Myprev[i] = -1;
    }
    Myprev[src] = 0;
    flow[src] = 1000000001;
    MyQueue.push(src);
    while (!MyQueue.empty()) {
        int index = MyQueue.front();
        MyQueue.pop();
        if (index == des)  //找到了增广路径
            break;
        for (int i = 1; i <= M ; ++i) 
        {
            if (i != src && residual[index][i] > 0 && Myprev[i] == -1) 
            {
                Myprev[i] = index;                                  //记录前驱
                flow[i] = min(residual[index][i], flow[index]);  //关键：迭代的找到增量
                MyQueue.push(i);
            }
        }
    }
    if (Myprev[des] == -1)  //残留图中不再存在增广路径
        return -1;
    else
        return flow[des];
}
int MaxFlow(int src,int des)
{
  int increasement = 0;
  int sumflow = 0;
  while ((increasement = BFS(src, des)) != -1) 
  {
        sumflow += increasement;
        int k = des;  //利用前驱寻找路径
        while (k != src) 
        {
            int last = Myprev[k];
            residual[last][k] -= increasement;  //改变正向边的残量
            residual[k][last] += increasement;  //改变反向边的残量
            k = last;
        }
  }
  return sumflow;
}
int main()
{
    ifstream input_file;
    input_file.open("input.txt",ios::in);
    input_file>>N>>M;

    int u=0,v=0,w=0;
    for(int i=1 ; i<=M ; i++)
    {
        input_file>>u>>v>>w;
        capacity[u][v] = w;
        residual[u][v] = w;
    }

    // 打印最大流
    cout<<MaxFlow(1,N)<<endl;

    // 打印出每一条边上的流量
    for(int i=1 ; i<=N ; i++)
    {
        for(int j=1 ; j<=N ; j++)
        {
            if(capacity[i][j] != 0)
                printf("%d %d %d\n",i,j,capacity[i][j]-residual[i][j]);
        }
    }
}