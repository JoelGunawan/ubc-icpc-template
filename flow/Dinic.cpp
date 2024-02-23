// Network Flow
// Complexity O(n^3 log) in worst case if binary search
// Still do pretty well without binary search
// Tested with: https://cses.fi/problemset/task/1695/
#include <bits/stdc++.h>
 
using namespace std;
 
struct Dinic {
		struct Edge {
		int v,pos,flow,cap;
 
		Edge(){}
		Edge(int _v, int _pos, int _flow, int _cap) {
			v = _v;
			pos = _pos;
			flow = _flow;
			cap = _cap;
		}
	};
 
	int n;
	vector <vector<Edge>> adj;
	vector <int> ptr,dis;
 
	Dinic(int _n) {
		n = _n;
		adj.resize(n + 5);
		ptr = dis = vector <int> (n + 5, 0);
	}
 
	void addEdge(int u, int v, int cap, int rcap = 0) {
		Edge a = Edge(v, adj[v].size(), 0, cap);
		Edge b = Edge(u, adj[u].size(), 0, rcap);
		adj[u].push_back(a);
		adj[v].push_back(b);
	}
 
	bool bfs(int s, int t) {
		ptr = dis = vector <int>(n + 5);
 
		dis[s] = 1;
		queue <int> q({s});
		while (q.size()) {
			int u = q.front(); q.pop();
 
			for (Edge e : adj[u]) if (dis[e.v] == 0 && e.flow < e.cap) {
				dis[e.v] = dis[u] + 1;
				q.push(e.v);
			}
		}
		return dis[t] > 0;
	}
 
	int dfs(int u, int t, int flow) {
		if (u == t)
			return flow;
 
		for (int &i = ptr[u]; i < (int) adj[u].size(); i++) {
			Edge &e = adj[u][i];	
			int dif = e.cap - e.flow;
			if (dis[u] + 1 != dis[e.v] || dif == 0)
				continue;
 
			if (int val = dfs(e.v, t, min(flow, dif)) > 0) {
				e.flow += val; adj[e.v][e.pos].flow -= val;
				return val;
			}
		}
		return 0;
	}
 
	void mincut(int s, int t) {
		int res = 0;
		while (bfs(s, t)) 
			while (int val = dfs(s, t, (int) 1e9))
				res += val;
		cout << res << "\n";
		bfs(s, t);
		for (int i = 1; i <= n; i++) 
		for (Edge e : adj[i])
			if (dis[i] > 0 && dis[e.v] == 0)
				cout << i << " " << e.v << "\n";
	}
};