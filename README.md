# euler_algorithm_kelompok_1

Group Number: 1 

Group Members:
-	Alif Muflih Jauhary (5025241003)
-	Rayen Yeriel Mangiwa (5025241262)
-	Makna Alam Pratama (5025241077)

### Fleury 

Fleury.png

Test case 1:
```bash
4 4
0 1
0 2
2 3
1 2
```
Output:
```bash
eulerian path found:
2 1 1 0 0 2 2 3
```

Test case 2:
```bash
4 7
0 1
1 0
1 2
2 0
1 3
3 1
3 2
```
Output:
```bash
euler path not found
```


```bash
#include <bits/stdc++.h>
using namespace std;

struct graph {
    long vertexCount, edgeCount;
    vector<vector<long>> adjList;
    
    void init(long v) {
        vertexCount = v;
        edgeCount = 0;
        adjList.assign(vertexCount, {}); // langsung kosongin
    }

    void add_edge(long vertex1, long vertex2) {
        adjList[vertex1].push_back(vertex2);
        adjList[vertex2].push_back(vertex1);
        edgeCount++;
    }

    void eulerUtil(long u, vector<long> &path) {
    while (!adjList[u].empty()) {
        long v = adjList[u].back();
        adjList[u].pop_back();

        auto it = find(adjList[v].begin(), adjList[v].end(), u);
        if (it != adjList[v].end()) adjList[v].erase(it);

        // catat edge dua kali: (u,v) lalu (v,u)
        path.push_back(u);
        path.push_back(v);

        eulerUtil(v, path);
    }
}

    void eulerPath(vector<long> &path) {
        long start = 0;
        vector<long> oddVertices;

        for (long i = 0; i < vertexCount; i++) {
            if (adjList[i].size() % 2 != 0) oddVertices.push_back(i);
        }

        if (oddVertices.size() == 2) start = oddVertices[0];
        else if (oddVertices.size() == 0) start = 0;
        else return; // tidak ada Eulerian path/cycle

        // path.push_back(start);   // mulai dari start
        eulerUtil(start, path);
    }
};

int main() {
    int N, M;
    cin >> N >> M;
    graph g;
    g.init(N);

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    vector<long> path;
    g.eulerPath(path);

    if (!path.empty()) {
        cout << "eulerian path found:\n";
        for (long x : path) cout << x << " ";
        cout << "\n";
    } else {
        cout << "euler path not found\n";
    }

    return 0;
}

```

hielholzer.png

Test case 1:
```bash
12 16
0 1
1 2
2 3
3 0
0 4
4 5
5 0
0 6
6 7
7 0
0 8
8 9
9 0
2 10
10 11
11 2
```
Output:
```bash
eulerian path found:
Final Cycle : 0 - 1 - 2 - 10 - 11 - 2 - 3 - 0 - 4 - 5 - 0 - 6 - 7 - 0 - 8 - 9 - 0
Subtours:
1. 0 - 1 - 2 - 3 - 0
2. 0 - 4 - 5 - 0
3. 0 - 6 - 7 - 0
4. 0 - 8 - 9 - 0
5. 2 - 10 - 11 - 2
```

Test case 1:
```bash
3 2
0 1
1 2
```
Output:
```bash
euler path not found
```


```bash
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
```
