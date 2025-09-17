#include <bits/stdc++.h>
using namespace std;

using namespace std;

struct Edge {
    int to, id;
};

struct Graph {
    int vertexCount;
    vector<vector<Edge>> adj;
    
    void init(int v) {
        vertexCount = v;
        adj.assign(v, {});
    }

    void addEdge(int u, int v, int id) {
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    bool isEulerian() {
        int start_node = -1;
        for (int i = 0; i < vertexCount; ++i) {
            if (!adj[i].empty()) {
                start_node = i;
                break;
            }
        }
        if (start_node == -1) return true;

        vector<bool> visited(vertexCount, false);
        stack<int> s;
        s.push(start_node);
        visited[start_node] = true;
        while (!s.empty()) {
            int u = s.top(); s.pop();
            for (const auto& edge : adj[u]) {
                if (!visited[edge.to]) {
                    visited[edge.to] = true;
                    s.push(edge.to);
                }
            }
        }

        for (int i = 0; i < vertexCount; ++i) {
            if (!adj[i].empty() && !visited[i]) return false;
        }

        for (int i = 0; i < vertexCount; i++) {
            if (adj[i].size() % 2 != 0) return false;
        }
        return true;
    }

    void finalizeAdj() {
        for (int i = 0; i < vertexCount; i++) {
            sort(adj[i].begin(), adj[i].end(), [](const Edge &a, const Edge &b) {
                return a.to < b.to;
            });
        }
    }

    // Fungsi untuk menghasilkan Final Cycle yang benar
    vector<int> findEulerianCycle(int M) {
        vector<int> cycle;
        if (!isEulerian()) return cycle;

        vector<int> edge_ptr(vertexCount, 0);
        vector<bool> used_edges(M, false);
        stack<int> s;
        
        int start_node = 0;
        for (int i = 0; i < vertexCount; ++i) {
            if (!adj[i].empty()) {
                start_node = i;
                break;
            }
        }
        s.push(start_node);

        while (!s.empty()) {
            int u = s.top();
            bool has_edge = false;
            while(edge_ptr[u] < adj[u].size()){
                Edge& edge = adj[u][edge_ptr[u]];
                if (!used_edges[edge.id]) {
                    used_edges[edge.id] = true;
                    s.push(edge.to);
                    has_edge = true;
                    break;
                }
                edge_ptr[u]++;
            }

            if (!has_edge) {
                cycle.push_back(u);
                s.pop();
            }
        }
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }

    vector<vector<int>> findSubtours(int M) {
        vector<vector<int>> subtours;
        vector<bool> used_edges(M, false);

        for (int i = 0; i < vertexCount; ++i) {
            for (const auto& start_edge : adj[i]) {
                if (!used_edges[start_edge.id]) {
                    vector<int> current_tour;
                    int start_node = i;
                    int current_node = start_node;

                    do {
                        current_tour.push_back(current_node);
                        bool found_next = false;
                        for (const auto& edge : adj[current_node]) {
                            if (!used_edges[edge.id]) {
                                used_edges[edge.id] = true;
                                current_node = edge.to;
                                found_next = true;
                                break;
                            }
                        }
                        if (!found_next) break; // Seharusnya tidak terjadi di graf Euler
                    } while (current_node != start_node);
                    
                    current_tour.push_back(start_node);
                    subtours.push_back(current_tour);
                }
            }
        }
        return subtours;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    Graph g;
    g.init(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v, i);
    }
    g.finalizeAdj();

    vector<int> finalCycle = g.findEulerianCycle(M);

    if (finalCycle.empty() || finalCycle.front() != finalCycle.back()) {
        cout << "euler path not found\n";
        return 0;
    }

    // Panggil fungsi findSubtours untuk mendapatkan hasil yang benar
    vector<vector<int>> subtours = g.findSubtours(M);

    cout << "eulerian path found:\n";

    cout << "Final Cycle : ";
    for (size_t i = 0; i < finalCycle.size(); i++) {
        cout << finalCycle[i];
        if (i + 1 < finalCycle.size()) cout << " - ";
    }
    cout << "\n";

    cout << "Subtours:\n";
    for (size_t i = 0; i < subtours.size(); i++) {
        cout << i + 1 << ". ";
        for (size_t j = 0; j < subtours[i].size(); j++) {
            cout << subtours[i][j];
            if (j + 1 < subtours[i].size()) cout << " - ";
        }
        cout << "\n";
    }

    return 0;
}
