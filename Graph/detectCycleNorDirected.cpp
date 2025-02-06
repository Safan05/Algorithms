#include <iostream>
#include <vector>
using namespace std;

// Utility function to detect cycle in an undirected graph
bool isCyclicUtil(vector<vector<int>>& adj, int u, vector<bool>& visited, int parent) {
    // Mark the current node as visited
    visited[u] = true;

    // Recur for all the vertices adjacent to this vertex
    for (int x : adj[u]) {
        // If an adjacent vertex is not visited, recur for it
        if (!visited[x]) {
            if (isCyclicUtil(adj, x, visited, u))
                return true;
        }
        // If an adjacent vertex is visited and not the parent of the current vertex,
        // then there is a cycle
        else if (x != parent)
            return true;
    }
    return false;
}

// Function to detect cycle in an undirected graph
bool isCyclic(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);

    // Call the recursive helper function to detect cycle in different DFS trees
    for (int i = 0; i < V; i++) {
        if (!visited[i] && isCyclicUtil(adj, i, visited, -1))
            return true;
    }
    return false;
}

// Driver function
int main() {
    int V = 5; // Number of vertices
    vector<vector<int>> adj(V);

    // Adding edges to the graph (undirected)
    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(3);
    adj[4].push_back(1); // This edge creates a cycle

    // Function call
    if (isCyclic(adj, V))
        cout << "Contains Cycle" << endl;
    else
        cout << "No Cycle" << endl;

    return 0;
}