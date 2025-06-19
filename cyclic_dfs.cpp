#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj = {
    {0, 1, 1, 0},
    {1, 0, 1, 0},
    {1, 1, 0, 1},
    {0, 0, 1, 0}
};

bool dfs(int v, int parent, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& path, vector<int>& cycle) {
    visited[v] = true;
    path.push_back(v);

    for (int u = 0; u < adj.size(); ++u) {
        if (adj[v][u]) {
            if (!visited[u]) {
                if (dfs(u, v, adj, visited, path, cycle)) return true;
            } else if (u != parent) {
                auto it = find(path.begin(), path.end(), u);
                if (it != path.end()) {
                    cycle.assign(it, path.end());
                    cycle.push_back(u);
                }
                return true;
            }
        }
    }
    path.pop_back();
    return false;
}

bool isCyclicDFS(vector<vector<int>>& adj, vector<int>& cycle) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<int> path;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (dfs(i, -1, adj, visited, path, cycle)) return true;
        }
    }
    return false;
}

int main() {
    int n = adj.size();
    vector<int> cycle;
    cout << "Adjacency matrix:\n";
    for (auto& row : adj) {
        for (int v : row) cout << v << " ";
        cout << endl;
    }
    if (isCyclicDFS(adj, cycle)) {
        cout << "Graph contains a cycle. Vertices in the cycle: ";
        for (int v : cycle) cout << v << " ";
        cout << endl;
    } else {
        cout << "Graph does not contain a cycle.\n";
    }
    return 0;
}