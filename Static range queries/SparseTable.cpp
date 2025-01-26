#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstdio>
#include <cstring>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cmath>
#include <bitset>
#include <stack>
#include <math.h>
using namespace std;
#define ll long long
#define int long long
#define endl "\n"
#define read(a) for(auto &i: a) cin>>i
#define write(a) for(auto &i: a) cout<<i<<" "
#define SafanMan ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(0);
// overlapping
int queryErricto(vector<vector<int>> sparse, int l, int r) {
    int k = 0;
    int len = r - l + 1;
    while ((1LL << (k+1)) <= len)
        k++;
    return max(sparse[l][k], sparse[r - (1LL << k) + 1][k]);
}
// no overlapping
int query(vector<vector<int>> sparse, int l, int r) {
    if (l == r)
        return sparse[l][0];
    int k = 0;
    int len = r - l + 1;
    while ((1LL << (k + 1)) <= len)
        k++;
    return max(sparse[l][k], query(sparse,l+(1LL<<k)-1,r));
}
void solve() {
    int n;
    cin >>n;
    vector<int> a(n);
    vector<vector<int>> sparse(n, vector<int>(log2(n) + 1, -1));
    // sparseTable Build
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sparse[i][0] = a[i];
    }
    for (int i = 1; i <= log2(n); i++) {
        for (int j = 0; j < n; j++) {
            if (j + (1LL<<i) <= n) {
                sparse[j][i] = max(sparse[j][i-1],sparse[j][i-1]+(1LL<<(i-1)));
            }
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout<< query(sparse, l, r);
    }
}

signed main() {
    SafanMan
        int t{ 1 };
      //cin >> t;
    while (t--)
    {
        solve();
    }
}