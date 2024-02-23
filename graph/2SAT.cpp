// 2 SAT 
// Complexity O(n)
// Tested with: https://cses.fi/problemset/task/1684/

#include <bits/stdc++.h>
#define fi first
#define se second 
#define mp make_pair 
#define ALL(x) x.begin(), x.end()
#define bit(x) (1LL << (x))
#define getbit(x, i) (((x) >> (i)) & 1)
#define pb push_back
using namespace std;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

template <typename T1, typename T2> bool mini(T1 &a, T2 b) {
    if (a > b) {a = b; return true;} return false;
}

template <typename T1, typename T2> bool maxi(T1 &a, T2 b) {
    if (a < b) {a = b; return true;} return false;
}

const double pi = acos(-1);
const int oo = 1e9;
const long long ooo = 1e18;

struct SAT {
    int n, cnt;
    vector <vector <int>> adj, revadj;
    vector <int> order, vis, comp;  

    SAT (int _n) {
        n = 2 * _n;
        adj.resize(n);
        revadj.resize(n);
        vis = comp = vector <int> (n, 0);
        order.clear();
    }

    void addEdge(int a, int b) {
    	adj[a ^ 1].push_back(b);
        adj[b ^ 1].push_back(a);
        revadj[a].push_back(b ^ 1);
        revadj[b].push_back(a ^ 1);
    }

    void dfs1(int u) {
        vis[u] = true;
        for (int v : adj[u]) 
            if (!vis[v])
                dfs1(v);
        order.push_back(u);
    }	

    void dfs2(int u) {
        vis[u] = true;
        for (int v : revadj[u]) 
            if (!vis[v])
                dfs2(v);
        comp[u] = cnt;
    }

    vector <int> solve() {
        for (int i = 0; i < n; i++) 
            if (!vis[i])
                dfs1(i);
    
        for (int i = 0; i < n; i++)
            vis[i] = 0;
    
        reverse(order.begin(), order.end());
    
        for (int i : order) 
            if (!vis[i])
                cnt++, dfs2(i);

        for (int i = 0; i < n; i += 2)
            if (comp[i] == comp[i ^ 1])
                return vector <int> (1, -1);

        vector <int> trueValues;
        for (int i = 0; i < n; i += 2) 
            if (comp[i] < comp[i ^ 1]) 
                trueValues.push_back(i >> 1);
        return trueValues;
    }

};

