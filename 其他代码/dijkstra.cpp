#include <iostream>
using namespace std;
#include "graph.h"
#include <vector>
#include<fstream>
#include <queue>

int findmindist(graph& gra) {
	int minv;
	for (int i = 1; i <= gra.vnums(); i++) {
		if (gra[i].known == false) {
			minv = i;
			cout << minv << endl;
			break;
		}
	}
	//cout << "*********************flag111*********************" << endl;
	for (int i = 1; i <= gra.vnums(); i++) {
		if (gra[i].known == true)
			continue;
		else {
			//cout << "*********************flag222*********************" << endl;
			if (gra[i].dist < gra[minv].dist)
				minv = i;
		}
		//cout << "*********************flag333*********************" << endl;
	}
	return minv;
}

void dijkstra(graph& gra,int x) {
	int unknown_num = gra.vnums();
	gra[x].dist = 0;   
	while (unknown_num != 0) {
		//cout << "*********************flag*********************" << endl;
		vertex& v = gra[findmindist(gra)];
		v.known = true;
		unknown_num--;
		for (int i = 0; i < v.adj.size(); i++) {
			if (!v.adj[i].endvtx.known) {
				if (v.dist + v.adj[i].weight < v.adj[i].endvtx.dist) {
					v.adj[i].endvtx.dist = v.dist + v.adj[i].weight;
					v.adj[i].endvtx.path = v.index;
				}
			}
		}
	}
}

int main() {
	int n, m;
	ifstream input_file;
	input_file.open("input2.txt",ios::in);
	cout << "请分别输入图的顶点个数和图的边数：";
	input_file >> n >> m;
	graph gra(n);
	cout << "请输入" << m << "个三元组 x、y、w，表示顶点 x 到顶点 y 有带实数权 w 的边：" << endl;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		input_file >> a >> b >> c;
		gra.addedge(a, b, c);
	}
	cout << "请输入源顶点标号 s：";
	int s;
	input_file >> s;
	gra.print();
	cout<<"test"<<endl;

	dijkstra(gra, s);
	for (int i =1 ; i <= gra.vnums(); i++) {
		cout << gra[i].index << " " << gra[i].dist << " ";

		gra.print_path(i);
		cout << endl;
	}
	return 0;
}

