#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
using namespace std;

class arc;

class vertex
{
public:
    vertex(int x = -1, int in = 0, int out = 0, int d = 100000000, bool flag = false, int p = 0)
        :index(x), indegree(in), outdegree(out), dist(d), known(flag), path(p) { }
public:
    int index;  //顶点的标号（从1开始）
    int indegree;  //入度
    int outdegree; //出度
    vector<arc> adj;  //以该顶点为起点的邻边
    int dist;
    bool known;
    int path;

};

class arc
{
public:
    arc(vertex& begin, vertex& end, int w)
        :beginvtx(begin), endvtx(end), weight(w) { }
public:
    vertex& beginvtx;  //起点
    vertex& endvtx;    //终点
    int weight;       //权重
};

class graph
{
public:
    graph(int n) :vtxnum(n), arcnum(0), v(n) {
        for (int i = 0; i < n; i++) {
            v[i].index = i + 1;
        }
    }
    ~graph() {
        v.clear();
        vtxnum = 0;
        arcnum = 0;
    }
    //获取标号为i的顶点
    vertex& operator[](int i) {
        return v[i - 1];
    }
    //判定指定图是否为空图
    bool empty() const {
        return vtxnum == 0;
    }
    //获得图的顶点数
    int vnums() const { return vtxnum; }
    //获得图的边数
    int edgenums() const { return arcnum; }
    //添加边
    void addedge(int beginidx, int endidx, int w) {
        arc edge(v[beginidx - 1], v[endidx - 1], w);
        v[beginidx - 1].adj.push_back(edge);
        v[beginidx - 1].outdegree++;
        v[endidx - 1].indegree++;
        arcnum++;
    }
    //输出图
    void print() {
        for (int i = 0; i < vtxnum; i++) {
            cout << v[i].index << ":" << " 入度:" << v[i].indegree << " 出度:" << v[i].outdegree << "  以该顶点为起点的邻边：";
            for (int j = 0; j < v[i].adj.size(); j++) {
                cout << v[i].adj[j].beginvtx.index << "->" << v[i].adj[j].endvtx.index << "(w=" << v[i].adj[j].weight << ")  ";
            }
            cout << endl;
        }
    }
    void print_path(int s,int x) {
        if (v[x-1].path != s) {
            print_path(s, v[x-1].path);
        }
        cout << x << " ";
    }

public:
    vector<vertex> v;  //图的顶点
    int vtxnum;  //图的顶点数
    int arcnum;  //图的边数
};

#endif
