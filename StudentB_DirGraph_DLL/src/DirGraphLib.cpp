#include "DirGraphLib.h"
#include <vector>
#include <queue>

namespace {
bool validate(int n, const DirEdge* edges, int edgeCount) {
    if (n <= 0) return false;
    if (edgeCount < 0) return false;
    if (edgeCount > 0 && edges == nullptr) return false;
    for (int i = 0; i < edgeCount; ++i) {
        if (edges[i].from < 0 || edges[i].from >= n) return false;
        if (edges[i].to < 0 || edges[i].to >= n) return false;
    }
    return true;
}
} // namespace

extern "C" {

DIRGRAPH_API int topologicalSort(int n, const DirEdge* edges, int edgeCount,
                                 int* outOrder) {
    if (!validate(n, edges, edgeCount) || !outOrder) return -1;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> indeg(n, 0);
    for (int i = 0; i < edgeCount; ++i) {
        adj[edges[i].from].push_back(edges[i].to);
        ++indeg[edges[i].to];
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);

    int idx = 0;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        outOrder[idx++] = v;
        for (int to : adj[v]) {
            if (--indeg[to] == 0) q.push(to);
        }
    }
    return (idx == n) ? 0 : -1; // -1, якщо є цикл
}

DIRGRAPH_API int hasCycle(int n, const DirEdge* edges, int edgeCount) {
    if (!validate(n, edges, edgeCount)) return -1;
    std::vector<int> order(n);
    int rc = topologicalSort(n, edges, edgeCount, order.data());
    if (rc == 0) return 0;
    return 1;
}

DIRGRAPH_API int inDegree(int n, const DirEdge* edges, int edgeCount, int v) {
    if (!validate(n, edges, edgeCount)) return -1;
    if (v < 0 || v >= n) return -1;
    int deg = 0;
    for (int i = 0; i < edgeCount; ++i) {
        if (edges[i].to == v) ++deg;
    }
    return deg;
}

DIRGRAPH_API int outDegree(int n, const DirEdge* edges, int edgeCount, int v) {
    if (!validate(n, edges, edgeCount)) return -1;
    if (v < 0 || v >= n) return -1;
    int deg = 0;
    for (int i = 0; i < edgeCount; ++i) {
        if (edges[i].from == v) ++deg;
    }
    return deg;
}

} // extern "C"