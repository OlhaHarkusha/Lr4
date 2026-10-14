#pragma once
#include <vector>

namespace MSTLib {

struct Edge {
    int u;
    int v;
    int weight;
};

// Алгоритм Пріма. Повертає список ребер МКД.
std::vector<Edge> prim(int n, const std::vector<Edge>& edges);

// Алгоритм Краскала. Повертає список ребер МКД.
std::vector<Edge> kruskal(int n, const std::vector<Edge>& edges);

// Сумарна вага списку ребер.
int treeWeight(const std::vector<Edge>& tree);

// Чи є набір ребер кістковим деревом для графа з n вершин.
bool isSpanningTree(int n, const std::vector<Edge>& tree);

} // namespace MSTLib