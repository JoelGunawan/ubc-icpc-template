struct node {
  // fi -> count of on
  // se -> length of subarray
  // cnt -> propagate to top
  node *l, *r;
};
const int lim = 1e5 + 5;
struct dynamic_segment_tree {
  node *head = new node();
  int size, node_cnt = 0;
  vector<pair<node*, int>> merging;
  void merge(node *cur, int cl, int cr, node *upd) {
    int mid = (cl + cr) >> 1;
    if(cl == mid) {
      if(upd->l)
        cur->l = upd->l;
      else
        delete upd->l;
    }
    else if(upd->l) {
      if(!cur->l)
        cur->l = upd->l;
      else
        merge(cur->l, cl, mid, upd->l);
    }
    if(mid + 1 == cr) {
      if(upd->r)
        cur->r = upd->r;
      else
        delete upd->r;
    }
    else if(upd->r) {
      if(!cur->r)
        cur->r = upd->r;
      else {
        merge(cur->r, mid + 1, cr, upd->r);
      }
    }
    if(!cur->l) {
      cur->l = new node();
    }
    if(!cur->r) {
      cur->r = new node();
    }
    delete upd;
  }
  void get(node *nd, int cl, int cr) {
    if(cl == cr)
      merging.push_back({nd, cl});
    else {
      int mid = (cl + cr) >> 1;
      if(nd->l)
        get(nd->l, cl, mid);
      if(nd->r)
        get(nd->r, mid + 1, cr);
      delete nd;
    }
  }
};
int sz;
struct disjoint_set {
  int head[lim], size[lim];
  dynamic_segment_tree a[lim];
  disjoint_set() {
    memset(head, -1, sizeof(head));
    fill(size, size + lim, 1);
  }
  int find_head(int nd) {
    while(head[nd] != -1)
      nd = head[nd];
    return nd;
  }
  bool merge(int x, int y) {
    x = find_head(x), y = find_head(y);
    if(x != y) {
      if(size[x] < size[y])
        swap(x, y);
      if(a[x].node_cnt < a[y].node_cnt) {
        swap(a[x], a[y]);
      }
      size[x] += size[y];
      head[y] = x;
      // merge every node of y to x
      // implement merging
      a[x].merge(a[x].head, 0, sz, a[y].head);
    }
    return x != y;
  }
};
disjoint_set dsu;
vector<pair<int, int>> edges[lim];
bool vis[lim];
void dfs(int nd) {
  vis[nd] = 1;
  for(auto i : edges[nd]) {
    if(!vis[i.first]) {
      dfs(i.first);
      dsu.merge(i.first, nd);
    }
  }
}