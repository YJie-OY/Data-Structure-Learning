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
    int index;  //����ı�ţ���1��ʼ��
    int indegree;  //���
    int outdegree; //����
    vector<arc> adj;  //�Ըö���Ϊ�����ڱ�
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
    vertex& beginvtx;  //���
    vertex& endvtx;    //�յ�
    int weight;       //Ȩ��
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
    //��ȡ���Ϊi�Ķ���
    vertex& operator[](int i) {
        return v[i - 1];
    }
    //�ж�ָ��ͼ�Ƿ�Ϊ��ͼ
    bool empty() const {
        return vtxnum == 0;
    }
    //���ͼ�Ķ�����
    int vnums() const { return vtxnum; }
    //���ͼ�ı���
    int edgenums() const { return arcnum; }
    //���ӱ�
    void addedge(int beginidx, int endidx, int w) {
        arc edge(v[beginidx - 1], v[endidx - 1], w);
        v[beginidx - 1].adj.push_back(edge);
        v[beginidx - 1].outdegree++;
        v[endidx - 1].indegree++;
        arcnum++;
    }
    //���ͼ
    void print() {
        for (int i = 0; i < vtxnum; i++) {
            cout << v[i].index << ":" << " ���:" << v[i].indegree << " ����:" << v[i].outdegree << "  �Ըö���Ϊ�����ڱߣ�";
            for (int j = 0; j < v[i].adj.size(); j++) {
                cout << v[i].adj[j].beginvtx.index << "->" << v[i].adj[j].endvtx.index << "(w=" << v[i].adj[j].weight << ")  ";
            }
            cout << endl;
        }
    }
    void print_path(int x) {
        if (v[x-1].path != 0) {
            print_path(v[x-1].path);
        }
        cout << x << " ";
    }

public:
    vector<vertex> v;  //ͼ�Ķ���
    int vtxnum;  //ͼ�Ķ�����
    int arcnum;  //ͼ�ı���
};

#endif
