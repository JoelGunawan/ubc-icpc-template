// Min cost Max Flow 
// Tested with: https://codeforces.com/contest/237/problem/E

#include <bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
template <typename T1, typename T2> bool mini(T1 &a, T2 b) {
	if (a > b) {a = b; return true;} return false;
}
template <typename T1, typename T2> bool maxi(T1 &a, T2 b) {
	if (a < b) {a = b; return true;} return false;
}
const int N = 1e5 + 5; 
const int oo = 1e9;
 
struct MCMF {
	struct edge{ 
		int u,v, flow, cap, cost;
		edge(int _u, int _v, int _cap, int _cost) {
			u = _u;
			v = _v;
			cap = _cap;
			cost = _cost;
			flow = 0;
		}
 
		int rem() {
			return cap - flow;
		}
	};
 
	int n;
	vector <bool> inq;
	vector <int> ptr;
	vector <int> dis;
	vector <vector <int>> adj;
	vector <edge> g;
 
	void init(int _n) {
		n = _n;
		ptr.resize(n + 5);
		adj.resize(n + 5);
		inq.resize(n + 5);
		dis.resize(n + 5);
	}
 
	void addEdge(int u, int v, int cap, int cost) {
		adj[u].push_back(g.size());
		g.push_back(edge(u, v, cap,cost));
		adj[v].push_back(g.size());
		g.push_back(edge(v, u, 0, -cost));
	}
 
	bool path(int s, int t) {
		for (int i = 1; i <= n; i++) {
			dis[i] = oo;
			inq[i] = false;
			ptr[i] = -1;
		}
 
		queue <int> q({s});
		dis[s] = 0; inq[s] = true;
		while (q.size()) {
			int u = q.front(); q.pop(); inq[u] = false;
			for (int i : adj[u]) if (g[i].rem() > 0) {
				if (mini(dis[g[i].v], dis[u] + g[i].cost)) {
					if (!inq[g[i].v]) {
						q.push(g[i].v);
						inq[g[i].v] = true;
					}
					ptr[g[i].v] = i;
				}
			}
		}
		return ptr[t] != -1;
	}
 
	pair <int, int> mcmf(int s, int t) {
		int totflow = 0, totcost = 0;
		while (path(s, t)) {
			int flow = oo;
			for (int u = t; u != s; u = g[ptr[u]].u) 
				mini(flow, g[ptr[u]].rem());
			totflow += flow;
			totcost += flow * dis[t];
			for (int u = t; u != s; u = g[ptr[u]].u) {
				g[ptr[u]].flow += flow;
				g[ptr[u] ^ 1].flow -= flow;
			}
		}
		return mp(totflow, totcost);
	}
};