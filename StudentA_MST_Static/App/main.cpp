#include <iostream>
#include "MSTLib.h"

int main() {
    int n = 4;
    std::vector<MSTLib::Edge> edges = {
        {0, 1, 1}, {1, 2, 2}, {2, 3, 3},
        {0, 3, 10}, {0, 2, 4}, {1, 3, 5}
    };

    auto primTree = MSTLib::prim(n, edges);
    auto kruskalTree = MSTLib::kruskal(n, edges);

    std::cout << "Prim weight: " << MSTLib::treeWeight(primTree) << "\n";
    std::cout << "Kruskal weight: " << MSTLib::treeWeight(kruskalTree) << "\n";
    std::cout << "Prim is spanning tree: "
              << (MSTLib::isSpanningTree(n, primTree) ? "yes" : "no") << "\n";
    std::cout << "Kruskal is spanning tree: "
              << (MSTLib::isSpanningTree(n, kruskalTree) ? "yes" : "no") << "\n";
    return 0;
}