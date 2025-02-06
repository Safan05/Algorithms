#include <iostream>
#include <vector>
using namespace std;

// Utility function to detect cycle in a directed graph
bool isCyclicUtil(vector<vector<int>>& adj, int u,
    vector<bool>& visited, vector<bool>& recStack) {

    if (!visited[u]) {

        // Mark the current node as visited 
        // and part of recursion stack
        visited[u] = true;
        recStack[u] = true;

        // Recur for all the vertices adjacent 
        // to this vertex
        for (int x : adj[u]) {
            if (!visited[x] &&
                isCyclicUtil(adj, x, visited, recStack))
                return true;
            else if (recStack[x])
                return true;
        }
    }

    // Remove the vertex from recursion stack
    recStack[u] = false;
    return false;
}

// Function to detect cycle in a directed graph
bool isCyclic(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);

    // Call the recursive helper function to 
    // detect cycle in different DFS trees
    for (int i = 0; i < V; i++) {
        if (!visited[i] &&
            isCyclicUtil(adj, i, visited, recStack))
            return true;
    }

    return false;
}

// Driver function
int main() {
    int V = 4;
    vector<vector<int>> adj(V);

    // Adding edges to the graph
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(2);
    adj[2].push_back(0);
    adj[2].push_back(3);
    adj[3].push_back(3);

    // Function call
    if (isCyclic(adj, V))
        cout << "Contains Cycle" << endl;
    else
        cout << "No Cycle" << endl;

    return 0;
}