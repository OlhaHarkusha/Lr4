#include <iostream>
#include "DirGraphLib.h"

int main() {
    const int n = 6;
    DirEdge edges[] = {
        {5, 2}, {5, 0}, {4, 0}, {4, 1},
        {2, 3}, {3, 1}
    };
    int edgeCount = 6;

    int order[6];
    int rc = topologicalSort(n, edges, edgeCount, order);

    if (rc == 0) {
        std::cout << "Topological order: ";
        for (int i = 0; i < n; ++i) std::cout << order[i] << " ";
        std::cout << "\n";
    } else {
        std::cout << "Graph has a cycle or error!\n";
    }

    std::cout << "inDegree(1)  = " << inDegree(n, edges, edgeCount, 1) << "\n";
    std::cout << "outDegree(5) = " << outDegree(n, edges, edgeCount, 5) << "\n";
    std::cout << "hasCycle     = " << hasCycle(n, edges, edgeCount) << "\n";

    return 0;
}