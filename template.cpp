#include <bits/stdc++.h>
#define fi first
#define se second 
#define mp make_pair 
#define ALL(x) x.begin(), x.end()
#define pb push_back
using namespace std;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

template <typename T1, typename T2> bool mini(T1 &a, T2 b) {
    if (a > b) {a = b; return true;} return false;
}

template <typename T1, typename T2> bool maxi(T1 &a, T2 b) {
    if (a < b) {a = b; return true;} return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // g++ file_name.cpp -o main && ./main < file.inp
}

