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
#include <string>
#include <cmath>
#include <bitset>
#include <stack>
#include <math.h>
using namespace std;
#define int long long
#define endl "\n"
#define read(a) for(auto &i: a) cin>>i
#define write(a) for(auto &i: a) cout<<i<<" "
#define SuperSafan ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(0);
#pragma warning(suppress : 4996)
const int N = 2e5 + 10; bool visited[N]; vector<vector<pair<int, int>>> adj(N); int dis[N]; int parent[N];
void Dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0,start });
    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        pq.pop();
        int node = p.second; int cost = p.first;
        if (visited[node]) continue;
        visited[node] = 1;
        dis[node] = cost;
        for (int i = 0; i < adj[node].size(); i++) {
            if (!visited[adj[node][i].first]) {
                pq.push({ cost + adj[node][i].second,adj[node][i].first });
            }
        }
    }
}
signed main() {
    // freopen("mex.in", "r", stdin);
   // freopen("mex.in", "r", stdout);
    SuperSafan
        int t;
    cin >> t;
    while (t--) {
        int n, a, b;
        cin >> n >> a >> b;
        for (int i = 0; i < n; i++) {
            int u, v, c;
            cin >> u >> v>>c;
            adj[u].push_back({ v, c });
           // adj[v].push_back({ u, c });
        }
        Dijkstra(0);
        for (int i = 0; i <= n; i++)
            cout << dis[i] << " ";
    }
}
/*
1
10 2 3
5 2 1 3 4 3 2 1 7 8
*/
/*
5 1 1
1 2 10
1 3 4
2 3 8
2 4 10
3 4 2
4 5 5
*/