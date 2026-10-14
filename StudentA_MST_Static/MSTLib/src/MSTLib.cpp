#include "MSTLib.h"
#include <algorithm>
#include <queue>
#include <numeric>
#include <set>

namespace MSTLib {

// ---------- Допоміжна структура DSU для Краскала ----------
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

// ---------- Алгоритм Пріма ----------
std::vector<Edge> prim(int n, const std::vector<Edge>& edges) {
    std::vector<Edge> result;
    if (n <= 0) return result;

    // Список суміжності: (сусід, вага)
    std::vector<std::vector<std::pair<int,int>>> adj(n);
    for (const auto& e : edges) {
        if (e.u < 0 || e.u >= n || e.v < 0 || e.v >= n) continue;
        adj[e.u].push_back({e.v, e.weight});
        adj[e.v].push_back({e.u, e.weight});
    }

    std::vector<bool> inMST(n, false);
    // Мін-купа: (вага, вершина, батько)
    using Item = std::tuple<int,int,int>;
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;

    inMST[0] = true;
    for (auto& [to, w] : adj[0]) pq.push({w, to, 0});

    while (!pq.empty() && (int)result.size() < n - 1) {
        auto [w, v, u] = pq.top(); pq.pop();
        if (inMST[v]) continue;
        inMST[v] = true;
        result.push_back({u, v, w});
        for (auto& [to, ww] : adj[v]) {
            if (!inMST[to]) pq.push({ww, to, v});
        }
    }
    return result;
}

// ---------- Алгоритм Краскала ----------
std::vector<Edge> kruskal(int n, const std::vector<Edge>& edges) {
    std::vector<Edge> result;
    if (n <= 0) return result;

    std::vector<Edge> sorted = edges;
    std::sort(sorted.begin(), sorted.end(),
              [](const Edge& a, const Edge& b){ return a.weight < b.weight; });

    DSU dsu(n);
    for (const auto& e : sorted) {
        if (e.u < 0 || e.u >= n || e.v < 0 || e.v >= n) continue;
        if (dsu.unite(e.u, e.v)) {
            result.push_back(e);
            if ((int)result.size() == n - 1) break;
        }
    }
    return result;
}

// ---------- Сумарна вага ----------
int treeWeight(const std::vector<Edge>& tree) {
    int sum = 0;
    for (const auto& e : tree) sum += e.weight;
    return sum;
}

// ---------- Перевірка кісткового дерева ----------
bool isSpanningTree(int n, const std::vector<Edge>& tree) {
    if (n <= 0) return false;
    if ((int)tree.size() != n - 1) return false;

    // Перевірка коректності вершин
    for (const auto& e : tree) {
        if (e.u < 0 || e.u >= n || e.v < 0 || e.v >= n) return false;
        if (e.u == e.v) return false;
    }

    // Перевірка зв'язності та відсутності циклів
    DSU dsu(n);
    for (const auto& e : tree) {
        if (!dsu.unite(e.u, e.v)) return false; // цикл
    }

    int root = dsu.find(0);
    for (int i = 1; i < n; ++i) {
        if (dsu.find(i) != root) return false;
    }
    return true;
}

} // namespace MSTLib