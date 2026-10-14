#pragma once

#ifdef DIRGRAPH_EXPORTS
#define DIRGRAPH_API extern "C" __declspec(dllexport)
#else
#define DIRGRAPH_API extern "C" __declspec(dllimport)
#endif

struct DirEdge {
    int from;
    int to;
};

// Топологічне сортування. Повертає 0 — успіх, -1 — цикл або помилка.
DIRGRAPH_API int topologicalSort(int n, const DirEdge* edges, int edgeCount,
                                 int* outOrder);

// Перевірка наявності циклу. 1 — є цикл, 0 — немає, -1 — помилка.
DIRGRAPH_API int hasCycle(int n, const DirEdge* edges, int edgeCount);

// Степінь входу вершини v. -1 — помилка.
DIRGRAPH_API int inDegree(int n, const DirEdge* edges, int edgeCount, int v);

// Степінь виходу вершини v. -1 — помилка.
DIRGRAPH_API int outDegree(int n, const DirEdge* edges, int edgeCount, int v);