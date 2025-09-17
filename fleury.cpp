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
