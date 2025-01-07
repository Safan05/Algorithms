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
const int N = 1e6 + 10;
vector<pair<int, pair<int, int>>> edges;
void relax(int u, int v, int w,vector<int>& dist) {
    if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
    }
}
bool bellmanFord(int n,int src) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (auto& edge : edges) {
            relax(edge.second.first, edge.second.second, edge.first,dist);
        }
    }
    for (auto& edge : edges) {
        if (dist[edge.second.second] > dist[edge.second.first] + edge.first) {
            return false;
        }
    }
    for (auto& ans : dist)
        cout << ans << " ";
    return true;
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin>>w >> u >> v;
        edges.push_back({ w,{u,v} });
    }
    bellmanFord(n, 0);
}
signed main() {
    SafanMan
        int t{ 1 };
    //  cin >> t;
    while (t--)
    {
        solve();
    }
}