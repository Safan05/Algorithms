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
vector<pair<int,int>> adj[N];   // adj to n , weight
vector<bool> vis(N, 0);
stack<int> topological;
void relax(int u, int v, int w,vector<int>& dist) {
    if (dist[u]!=INT_MAX && dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
    }
}
void topologicalSort(int node) {
    if (vis[node])
        return;
    vis[node] = 1;
    for (auto& adjacent : adj[node]) {
        topologicalSort(adjacent.first);
    }
    topological.push(node);
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin>> u >> v>>w;
        adj[u].push_back({ v,w });
    }
    vector<int> dist(n + 1, INT_MAX);
    dist[1] = 0;
    for (int i = 0; i <= n; i++)
        topologicalSort(i);
    while (!topological.empty()) {
        int node=topological.top(); 
        topological.pop();
        cout << node << " ";
        for (auto& edges : adj[node]) {
            relax(node, edges.first, edges.second,dist);
        }
    }
    cout << endl;
    for (int i = 0; i <= n; i++)
        cout << dist[i] << " ";
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
// in DAG , it must be directed and acyclic graph 
// so we can optimize bellmann ford , insted of relaxing all edges (n-1) time , we will relax edges in the toplogical sort order