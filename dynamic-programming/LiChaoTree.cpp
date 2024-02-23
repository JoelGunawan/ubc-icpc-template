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

struct LiChaoTree {
	int sz;
	vector<Line> seg;

	LiChaoTree(int sz) : sz(sz) {
		seg.assign((sz + 2) << 2, Line(0, INF));
	}

	// Important: Nodes are of the form [L, R) instead of [L, R]

	void insert(int pos, int l, int r, Line newLine) {
		int mid = (l + r) >> 1;
		bool lless = newLine(l) < seg[pos](l);
		bool mless = newLine(mid) < seg[pos](mid);

		if (mless) {swap(newLine, seg[pos]);}

		if (r == l + 1) {return;}

		int lc = pos << 1, rc = lc | 1;
		if (lless ^ mless) {insert(lc, l, mid, newLine);}
		else {insert(rc, mid, r, newLine);}
	}
	void insert(Line newLine) {insert(1, 1, sz, newLine);}

	ll query(int pos, int l, int r, int idx) {
		if (r == l + 1) {return seg[pos](idx);}

		int mid = (l + r) >> 1, lc = pos << 1, rc = lc | 1;
		if (idx < mid) {return min(seg[pos](idx), query(lc, l, mid, idx));}
		else {return min(seg[pos](idx), query(rc, mid, r, idx));}
	}
	ll query(int idx) {return query(1, 1, sz, idx);}
};
