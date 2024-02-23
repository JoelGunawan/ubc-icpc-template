// FenwickTree 2D
// Complexity: O(n log^2 n)

#include <bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define bit(n) (1LL << (n))
#define getbit(x, i) (((x) >> (i)) & 1)
#define pii pair<int, int>
#define ALL(x) x.begin(), x.end()
using namespace std;
const int M = 5e5 + 5;
const int N = 2e5 + 5;
const int mod = 1e9 + 7;
const int oo = 1e9;
const long long ooo = 1e18;
 
const double pi = acos(-1);
template<typename T1, typename T2> bool mini(T1 &a, T2 b) {if(a > b) a = b; else return 0; return 1;}
template<typename T1, typename T2> bool maxi(T1 &a, T2 b) {if(a < b) a = b; else return 0; return 1;}
 
typedef long long ll;
 
struct BIT2D {
    int n;
    vector <vector <int>> mx, yval;
 
    BIT2D(int n) {
        this->n = n;
        mx.resize(n + 1);
        yval.resize(n + 1);
    }
 
    void fakeupdate(int x, int y) {
        for (; x <= n; x += x & -x)
            yval[x].push_back(y);
    }
 
    void init() {
        for (int i = 1; i <= n; i++) {
            mx[i].assign(yval[i].size() + 1, -oo);
            sort(ALL(yval[i]));
        }
    }
 
    void update(int x, int y, int val) {
        for (; x <= n; x += x & -x) {
            int i = upper_bound(ALL(yval[x]), y) - yval[x].begin();
            for (; i < (int) mx[x].size(); i += i & -i) {
                maxi(mx[x][i], val);
            }
        }
    }
 
    int getmax(int x, int y) {
        int res = -oo;
        for (; x; x -= x & -x) {
            int i = upper_bound(ALL(yval[x]), y) - yval[x].begin();
            for (; i; i -= i & -i) {
                maxi(res, mx[x][i]);
            }
        }
        return res;
    }
};