#include "MSTLib.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>

namespace {
struct DSU {
    std::vector<int> parent, rank;
    explicit DSU(int n) : parent(n), rank(n, 0) {
        std::iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return false;
        if (rank[ra] < rank[rb]) std::swap(ra, rb);
        parent[rb] = ra;
        if (rank[ra] == rank[rb]) ++rank[ra];
        return true;
    }
};
} // namespace

extern "C" {

MSTLIB_API int mstPrim(int n, const MSTEdge* edges, int edgeCount,
                       MSTEdge* outTree, int* outTreeSize) {
    if (n <= 0 || !outTreeSize) return -1;
    *outTreeSize = 0;
    if (n == 1) return 0;
    if (!edges || !outTree) return -1;

    std::vector<std::vector<std::pair<int,int>>> adj(n);
    for (int i = 0; i < edgeCount; ++i) {
        const auto& e = edges[i];
        if (e.u < 0 || e.u >= n || e.v < 0 || e.v >= n) continue;
        adj[e.u].push_back({e.v, e.weight});
        adj[e.v].push_back({e.u, e.weight});
    }

    std::vector<bool> inMST(n, false);
    using Item = std::tuple<int,int,int>;
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;

    inMST[0] = true;
    for (auto& [to, w] : adj[0]) pq.push({w, to, 0});

    int count = 0;
    while (!pq.empty() && count < n - 1) {
        auto [w, v, u] = pq.top(); pq.pop();
        if (inMST[v]) continue;
        inMST[v] = true;
        outTree[count++] = {u, v, w};
        for (auto& [to, ww] : adj[v]) {
            if (!inMST[to]) pq.push({ww, to, v});
        }
    }
    *outTreeSize = count;
    return (count == n - 1) ? 0 : -1; // -1, якщо граф незв'язний
}

MSTLIB_API int mstKruskal(int n, const MSTEdge* edges, int edgeCount,
                          MSTEdge* outTree, int* outTreeSize) {
    if (n <= 0 || !outTreeSize) return -1;
    *outTreeSize = 0;
    if (n == 1) return 0;
    if (!edges || !outTree) return -1;

    std::vector<MSTEdge> sorted(edges, edges + edgeCount);
    std::sort(sorted.begin(), sorted.end(),
              [](const MSTEdge& a, const MSTEdge& b){ return a.weight < b.weight; });

    DSU dsu(n);
    int count = 0;
    for (const auto& e : sorted) {
        if (e.u < 0 || e.u >= n || e.v < 0 || e.v >= n) continue;
        if (dsu.unite(e.u, e.v)) {
            outTree[count++] = e;
            if (count == n - 1) break;
        }
    }
    *outTreeSize = count;
    return (count == n - 1) ? 0 : -1;
}

MSTLIB_API int mstTreeWeight(const MSTEdge* tree, int treeSize) {
    if (!tree || treeSize <= 0) return 0;
    int sum = 0;
    for (int i = 0; i < treeSize; ++i) sum += tree[i].weight;
    return sum;
}

MSTLIB_API int mstIsSpanningTree(int n, const MSTEdge* tree, int treeSize) {
    if (n <= 0 || !tree || treeSize != n - 1) return 0;
    for (int i = 0; i < treeSize; ++i) {
        if (tree[i].u < 0 || tree[i].u >= n) return 0;
        if (tree[i].v < 0 || tree[i].v >= n) return 0;
        if (tree[i].u == tree[i].v) return 0;
    }
    DSU dsu(n);
    for (int i = 0; i < treeSize; ++i) {
        if (!dsu.unite(tree[i].u, tree[i].v)) return 0;
    }
    int root = dsu.find(0);
    for (int i = 1; i < n; ++i) {
        if (dsu.find(i) != root) return 0;
    }
    return 1;
}

} // extern "C"