#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int a, b, w;
	bool operator<(const Edge &y) const { return w < y.w; }
};

int main() {
	int M = 4;
	set<Edge> v;
	for (int i = 0; i < M; ++i) {
		int a, b, w;
		cin >> a >> b >> w;
		v.insert({a, b, w});
	}
	for (Edge e : v) cout << e.a << " " << e.b << " " << e.w << "\n";
}