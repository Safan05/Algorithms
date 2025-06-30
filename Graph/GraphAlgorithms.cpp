#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 1005;

// ==============================================
// GRAPH REPRESENTATION
// ==============================================

// Adjacency List (most common)
vector<vector<int>> adj;
vector<vector<pair<int, int>>> wadj; // weighted adjacency list

// Adjacency Matrix
int matrix[MAXN][MAXN];

// Edge List
struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

// ==============================================
// GRAPH TRAVERSAL
// ==============================================

// DFS - Depth First Search
vector<bool> visited;
vector<int> dfs_order;

void dfs(int u) {
    visited[u] = true;
    dfs_order.push_back(u);
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

// BFS - Breadth First Search
vector<int> bfs(int start) {
    vector<int> dist(adj.size(), -1);
    queue<int> q;
    
    dist[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

// ==============================================
// SHORTEST PATH ALGORITHMS
// ==============================================

// Dijkstra's Algorithm
vector<int> dijkstra(int start, int n) {
    vector<int> dist(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto& edge : wadj[u]) {
            int v = edge.first;
            int w = edge.second;
            
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// Bellman-Ford Algorithm (handles negative weights)
vector<int> bellman_ford(int start, int n, vector<Edge>& edges) {
    vector<int> dist(n, INF);
    dist[start] = 0;
    
    // Relax edges n-1 times
    for (int i = 0; i < n - 1; i++) {
        for (auto& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }
    
    // Check for negative cycles
    for (auto& e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
            cout << "Negative cycle detected!" << endl;
            return {};
        }
    }
    
    return dist;
}

// Floyd-Warshall Algorithm (All pairs shortest path)
void floyd_warshall(int n) {
    // Initialize matrix with INF, 0 for diagonal
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) matrix[i][j] = 0;
            else if (matrix[i][j] == 0) matrix[i][j] = INF;
        }
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][k] != INF && matrix[k][j] != INF) {
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                }
            }
        }
    }
}

// ==============================================
// MINIMUM SPANNING TREE
// ==============================================

// Union-Find (Disjoint Set Union)
vector<int> parent, rank_;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return;
    
    if (rank_[px] < rank_[py]) {
        parent[px] = py;
    } else if (rank_[px] > rank_[py]) {
        parent[py] = px;
    } else {
        parent[py] = px;
        rank_[px]++;
    }
}

// Kruskal's Algorithm
int kruskal(int n, vector<Edge>& edges) {
    parent.resize(n);
    rank_.resize(n, 0);
    
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    
    sort(edges.begin(), edges.end());
    
    int mst_weight = 0;
    int edges_added = 0;
    
    for (auto& e : edges) {
        if (find(e.u) != find(e.v)) {
            unite(e.u, e.v);
            mst_weight += e.w;
            edges_added++;
            
            if (edges_added == n - 1) break;
        }
    }
    
    return mst_weight;
}

// Prim's Algorithm
int prim(int n) {
    vector<bool> in_mst(n, false);
    vector<int> key(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    key[0] = 0;
    pq.push({0, 0});
    
    int mst_weight = 0;
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (in_mst[u]) continue;
        
        in_mst[u] = true;
        mst_weight += key[u];
        
        for (auto& edge : wadj[u]) {
            int v = edge.first;
            int w = edge.second;
            
            if (!in_mst[v] && w < key[v]) {
                key[v] = w;
                pq.push({key[v], v});
            }
        }
    }
    
    return mst_weight;
}

// ==============================================
// TOPOLOGICAL SORTING
// ==============================================

// Kahn's Algorithm (BFS-based)
vector<int> topological_sort_bfs(int n) {
    vector<int> indegree(n, 0);
    
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> topo_order;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);
        
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    return topo_order;
}

// DFS-based Topological Sort
vector<int> topo_dfs;
vector<bool> topo_visited;

void topo_dfs_util(int u) {
    topo_visited[u] = true;
    
    for (int v : adj[u]) {
        if (!topo_visited[v]) {
            topo_dfs_util(v);
        }
    }
    
    topo_dfs.push_back(u);
}

vector<int> topological_sort_dfs(int n) {
    topo_visited.assign(n, false);
    topo_dfs.clear();
    
    for (int i = 0; i < n; i++) {
        if (!topo_visited[i]) {
            topo_dfs_util(i);
        }
    }
    
    reverse(topo_dfs.begin(), topo_dfs.end());
    return topo_dfs;
}

// ==============================================
// CYCLE DETECTION
// ==============================================

// Cycle Detection in Undirected Graph
bool has_cycle_undirected(int n) {
    vector<bool> vis(n, false);
    
    function<bool(int, int)> dfs_cycle = [&](int u, int parent) -> bool {
        vis[u] = true;
        
        for (int v : adj[u]) {
            if (v == parent) continue;
            
            if (vis[v] || dfs_cycle(v, u)) {
                return true;
            }
        }
        return false;
    };
    
    for (int i = 0; i < n; i++) {
        if (!vis[i] && dfs_cycle(i, -1)) {
            return true;
        }
    }
    return false;
}

// Cycle Detection in Directed Graph
bool has_cycle_directed(int n) {
    vector<int> color(n, 0); // 0: white, 1: gray, 2: black
    
    function<bool(int)> dfs_cycle = [&](int u) -> bool {
        color[u] = 1;
        
        for (int v : adj[u]) {
            if (color[v] == 1 || (color[v] == 0 && dfs_cycle(v))) {
                return true;
            }
        }
        
        color[u] = 2;
        return false;
    };
    
    for (int i = 0; i < n; i++) {
        if (color[i] == 0 && dfs_cycle(i)) {
            return true;
        }
    }
    return false;
}

// ==============================================
// STRONGLY CONNECTED COMPONENTS
// ==============================================

// Kosaraju's Algorithm
vector<vector<int>> rev_adj;
vector<bool> scc_visited;
vector<int> finish_order;
vector<int> component;

void dfs1(int u) {
    scc_visited[u] = true;
    for (int v : adj[u]) {
        if (!scc_visited[v]) {
            dfs1(v);
        }
    }
    finish_order.push_back(u);
}

void dfs2(int u, int comp_id) {
    component[u] = comp_id;
    for (int v : rev_adj[u]) {
        if (component[v] == -1) {
            dfs2(v, comp_id);
        }
    }
}

int kosaraju(int n) {
    scc_visited.assign(n, false);
    finish_order.clear();
    component.assign(n, -1);
    
    // First DFS to get finish times
    for (int i = 0; i < n; i++) {
        if (!scc_visited[i]) {
            dfs1(i);
        }
    }
    
    // Second DFS on reversed graph
    reverse(finish_order.begin(), finish_order.end());
    int comp_count = 0;
    
    for (int u : finish_order) {
        if (component[u] == -1) {
            dfs2(u, comp_count++);
        }
    }
    
    return comp_count;
}

// ==============================================
// BIPARTITE GRAPH
// ==============================================

bool is_bipartite(int n) {
    vector<int> color(n, -1);
    
    function<bool(int, int)> dfs_bipartite = [&](int u, int c) -> bool {
        color[u] = c;
        
        for (int v : adj[u]) {
            if (color[v] == -1) {
                if (!dfs_bipartite(v, 1 - c)) {
                    return false;
                }
            } else if (color[v] == color[u]) {
                return false;
            }
        }
        return true;
    };
    
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            if (!dfs_bipartite(i, 0)) {
                return false;
            }
        }
    }
    return true;
}

// ==============================================
// MAXIMUM FLOW
// ==============================================

// Ford-Fulkerson with DFS
vector<vector<int>> capacity;
vector<vector<int>> flow_adj;

bool dfs_path(int source, int sink, vector<int>& parent) {
    vector<bool> vis(capacity.size(), false);
    stack<int> st;
    st.push(source);
    vis[source] = true;
    
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        
        for (int v : flow_adj[u]) {
            if (!vis[v] && capacity[u][v] > 0) {
                vis[v] = true;
                parent[v] = u;
                if (v == sink) return true;
                st.push(v);
            }
        }
    }
    return false;
}

int max_flow(int source, int sink, int n) {
    vector<int> parent(n);
    int total_flow = 0;
    
    while (dfs_path(source, sink, parent)) {
        int path_flow = INF;
        
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, capacity[u][v]);
        }
        
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
        }
        
        total_flow += path_flow;
    }
    
    return total_flow;
}

// ==============================================
// UTILITY FUNCTIONS
// ==============================================

void add_edge(int u, int v) {
    adj[u].push_back(v);
}

void add_weighted_edge(int u, int v, int w) {
    wadj[u].push_back({v, w});
}

void add_undirected_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void add_undirected_weighted_edge(int u, int v, int w) {
    wadj[u].push_back({v, w});
    wadj[v].push_back({u, w});
}

void init_graph(int n) {
    adj.assign(n, vector<int>());
    wadj.assign(n, vector<pair<int, int>>());
    visited.assign(n, false);
}

// ==============================================
// EXAMPLE USAGE
// ==============================================

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;
    
    init_graph(n);
    
    cout << "Enter edges (u v) for unweighted graph:" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    
    // Example usage of algorithms
    cout << "\n=== GRAPH ALGORITHMS DEMO ===" << endl;
    
    // DFS
    cout << "DFS from vertex 0: ";
    dfs(0);
    for (int x : dfs_order) cout << x << " ";
    cout << endl;
    
    // BFS
    cout << "BFS distances from vertex 0: ";
    vector<int> distances = bfs(0);
    for (int i = 0; i < n; i++) {
        cout << "d[" << i << "]=" << distances[i] << " ";
    }
    cout << endl;
    
    // Check if bipartite
    cout << "Is bipartite: " << (is_bipartite(n) ? "YES" : "NO") << endl;
    
    // Check for cycle
    cout << "Has cycle (directed): " << (has_cycle_directed(n) ? "YES" : "NO") << endl;
    
    // Topological sort
    vector<int> topo = topological_sort_bfs(n);
    if (topo.size() == n) {
        cout << "Topological order: ";
        for (int x : topo) cout << x << " ";
        cout << endl;
    } else {
        cout << "Graph has cycle, no topological order exists" << endl;
    }
    
    return 0;
}
