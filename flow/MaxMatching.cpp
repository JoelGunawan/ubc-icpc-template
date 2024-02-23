// Matching on Bipartite Graph
// Complexity: O(n sqrt n)
// Tested with: https://judge.yosupo.jp/problem/bipartitematching
// Note: to achieve "arbitrary" (not maximum) flow with lower bound:
// - Create a new graph with a new source s' and a new sink t'
// - if there is an edge from u => v with cap(u, v) >= dem(u, v)
// - cap(s', v) += dem(u, v)
// - cap(u, t') += dem(u, v)
// - cap(t, s) += oo
// - cap(u, v) += cap(u, v) - dem(u, v)
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;
const int oo = 1e9;

struct HopCroft {
	int n,m,t;
	vector <vector <int>> adj;
	vector <int> vis, dis, match, matched;

	HopCroft(int _n, int _m) {
		n = _n;
		m = _m;
		adj.resize(n + 5);
        vis = dis = matched = vector <int> (n + 5, 0);
        match.assign(m + 5, -1);
	}

	void add(int u, int v) {
		adj[u].push_back(v);
	}

	bool bfs() {
		for (int i = 0; i < n; i++)
			dis[i] = oo;

		queue <int> q;

		for (int i = 0; i < n; i++)
			if (!matched[i])
				q.push(i), dis[i] = 0;

		bool ok = false;
		while (q.size()) {
			int u = q.front(); q.pop();

			for (int v : adj[u]) {
				if (match[v] < 0)
					ok = true; 
				else if (dis[match[v]] == oo) {
					dis[match[v]] = dis[u] + 1;
					q.push(match[v]);
				}
			}
		}

		return ok;
	}

	bool dfs(int u) {
		if (vis[u] == t)
			return false;
		vis[u] = t;
		for (int v : adj[u]) if (match[v] == -1) {
			match[v] = u;
			matched[u] = true;
			return true;
		}

		for (int v : adj[u]) if (match[v] != -1 && dis[match[v]] == dis[u] + 1 && dfs(match[v]))  {
			match[v] = u;
			matched[u] = true;
			return true;
		}
		return false;
	}

	void maxmatch() {
		int res = 0;
		t = 0;
		while (bfs()) {
			t++;
			for (int i = 0; i < n; i++) {
				if (!matched[i] && dfs(i))
					res++;
			}
		}
		// cout << res << "\n";

		// for (int  i = 0; i < m; i++)
		// 	if (match[i] >= 0)
		// 		cout << match[i] << " " << i << "\n";
	}
};