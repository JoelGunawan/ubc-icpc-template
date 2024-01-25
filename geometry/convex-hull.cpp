// header file
#include <bits/stdc++.h>
#define endl "\n"
#define ll long long
#define pb push_back
#define fi first
#define se second
using namespace std;
ll cross_product(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c) {
    b.fi -= a.fi;
    c.fi -= a.fi;
    b.se -= a.se;
    c.se -= a.se;
    return b.fi * c.se - c.fi * b.se;
}
vector<pair<ll, ll>> convex_hull(vector<pair<ll, ll>> a) {
  int n = a.size();
  sort(a.begin(), a.end());
  vector<pair<ll, ll>> s;
  s.pb(a[0]);
  s.pb(a[1]);
  for(int i = 2; i < n; ++i) {
    while(s.size() > 1 && cross_product(s[s.size() - 2], s[s.size() - 1], a[i]) < 0)
      s.pop_back();
    s.pb(a[i]);
  }
  vector<pair<ll, ll>> ans;
  for(auto i : s)
    ans.pb(i);
  ans.pop_back();
  s.clear();
  s.pb(a[n - 1]);
  s.pb(a[n - 2]);
  for(int i = n - 3; i >= 0; --i) {
    while(s.size() > 1 && cross_product(s[s.size() - 2], s[s.size() - 1], a[i]) < 0)
      s.pop_back();
    s.pb(a[i]);
  }
  for(auto i : s)
    ans.pb(i);
  ans.pop_back();
  return ans;
}