#include <iostream>
#include "MSTLib.h"

int main() {
    const int n = 5;
    MSTEdge edges[] = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3},
        {1, 3, 8}, {1, 4, 5}, {2, 4, 7},
        {3, 4, 9}
    };
    int edgeCount = 7;

    MSTEdge tree[10];
    int treeSize = 0;

    int rcPrim = mstPrim(n, edges, edgeCount, tree, &treeSize);
    if (rcPrim == 0) {
        std::cout << "Prim MST weight = " << mstTreeWeight(tree, treeSize) << "\n";
        std::cout << "Is spanning tree: "
                  << mstIsSpanningTree(n, tree, treeSize) << "\n";
    } else {
        std::cout << "Prim: graph is disconnected or error!\n";
    }

    int rcKruskal = mstKruskal(n, edges, edgeCount, tree, &treeSize);
    if (rcKruskal == 0) {
        std::cout << "Kruskal MST weight = " << mstTreeWeight(tree, treeSize) << "\n";
    } else {
        std::cout << "Kruskal: error!\n";
    }

    return 0;
}