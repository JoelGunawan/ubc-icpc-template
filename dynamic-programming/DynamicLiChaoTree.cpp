struct Line {
	ll m, c;

	Line(ll m, ll c) : m(m), c(c) {}

	ll operator() (ll x) {
		return 1ll * m * x + 1ll * c;
	}

	ld intersect(Line other) {
		return (ld) (c - other.c) / (ld) (other.m - m);
	}
};

struct DynamicLiChaoTree {
	struct Node {
		Line line;
		Node *left, *right;

		Node() {}
		Node(Line L) {
			line = L;
			left = right = nullptr;
		}
	};

	ll boundL, boundR;
	Node *root;

	DynamicLiChaoTree() {}
	DynamicLiChaoTree(ll boundL, ll boundR) :
		boundL(boundL), boundR(boundR), root(new Node(Line(0, INF)))
	{}

	// Important: Nodes are of the form [L, R) instead of [L, R]

	void insert(Node *cur, ll l, ll r, Line newLine) {
		ll mid = l + (r - l) / 2;
		bool lless = newLine(l) < cur->line(l);
		bool mless = newLine(mid) < cur->line(mid);

		if (mless) {swap(newLine, cur->line);}

		if (r == l + 1) {return;}

		if (lless ^ mless) {
			if (!cur->left) cur->left = new Node(Line(0, INF));
			insert(cur->left, l, mid, newLine);
		} else {
			if (!cur->right) cur->right = new Node(Line(0, INF));
			insert(cur->right, mid, r, newLine);
		}
	}
	void insert(Line newLine) {insert(root, boundL, boundR, newLine);}

	ll query(Node *cur, ll l, ll r, ll idx) {
		ll ret = cur->line(idx);

		if (r == l + 1) {return ret;}

		ll mid = l + (r - l) / 2;
		if (idx < mid) {
			if (cur->left) ret = min(ret, query(cur->left, l, mid, idx));
		} else {
			if (cur->right) ret = min(ret, query(cur->right, mid, r, idx));
		}
		return ret;
	}
	ll query(ll idx) {return query(root, boundL, boundR, idx);}
};
