#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<int>> adj = {
    {0, 1, 1, 0},
    {1, 0, 1, 0},
    {1, 1, 0, 1},
    {0, 0, 1, 0}
};

bool isCyclicBFS(vector<vector<int>>& adj, vector<int>& cycle) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);

    for (int start = 0; start < n; ++start) {
        if (!visited[start]) {
            queue<int> q;
            q.push(start);
            visited[start] = true;

            while (!q.empty()) {
                int v = q.front(); q.pop();
                for (int u = 0; u < n; ++u) {
                    if (adj[v][u]) {
                        if (!visited[u]) {
                            visited[u] = true;
                            parent[u] = v;
                            q.push(u);
                        } else if (parent[v] != u) {
                           
                            vector<int> path_v, path_u;
                            int x = v, y = u;
                            while (x != -1) { path_v.push_back(x); x = parent[x]; }
                            while (y != -1) { path_u.push_back(y); y = parent[y]; }
                            int i = path_v.size() - 1, j = path_u.size() - 1;
                            while (i >= 0 && j >= 0 && path_v[i] == path_u[j]) { --i; --j; }
                            ++i; ++j;
                            for (int k = 0; k <= i; ++k) cycle.push_back(path_v[k]);
                            for (int k = j - 1; k >= 0; --k) cycle.push_back(path_u[k]);
                            cycle.push_back(path_v[0]);
                            return true;
                        }
                    }
                }
            }
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
    if (isCyclicBFS(adj, cycle)) {
        cout << "Graph contains a cycle. Vertices in the cycle: ";
        for (int v : cycle) cout << v << " ";
        cout << endl;
    } else {
        cout << "Graph does not contain a cycle.\n";
    }
    return 0;
}