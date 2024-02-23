segment_tree seg;
void dfs(int nd) {
    vis[nd] = 1;
    subtree[nd] = 1;
    for(int i = 1; i < 17; ++i) {
        par[i][nd] = par[i - 1][par[i - 1][nd]];
    }
    for(auto i : edges[nd]) {
        if(!vis[i]) {
            depth[i] = depth[nd] + 1;
            par[0][i] = nd;
            dfs(i);
            child[nd].push_back(i);
            subtree[nd] += subtree[i];
        }
    }
    for(auto &i : child[nd])
        if(subtree[i] > subtree[child[nd][0]])
            swap(i, child[nd][0]);
}
int in[lim], ti, root[lim];
void dfs2(int nd) {
    in[nd] = ti++;
    for(auto i : child[nd]) {
        root[i] = (i == child[nd][0] ? root[nd] : i);
        dfs2(i);
    }
}
int lca(int u, int v) {
    if(depth[u] > depth[v]) {
        swap(u, v);
    }
    // depth v lebih besar
    for(int i = 16; i >= 0; --i) {
        if(depth[par[i][v]] >= depth[u])
            v = par[i][v];
    }
    if(u == v)
        return u;
    for(int i = 16; i >= 0; --i) {
        if(par[i][v] != par[i][u])
            u = par[i][u], v = par[i][v];
    }
    return par[0][u];
}
int query(int u, int v) {
    // u itu yg root
    if(depth[u] > depth[v])
        swap(u, v);
    int res = 0;
    while(root[v] != root[u]) {
        res = max(res, (int)seg.query(in[root[v]], in[v]));
        v = par[0][root[v]];
        if(depth[u] > depth[v])
            swap(u, v);
    }
    res = max(res, (int)seg.query(in[u], in[v]));
    return res;
}
// for update, use same as query, just change to update