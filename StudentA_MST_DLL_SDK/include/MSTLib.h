#pragma once

#ifdef MSTLIB_EXPORTS
#define MSTLIB_API extern "C" __declspec(dllexport)
#else
#define MSTLIB_API extern "C" __declspec(dllimport)
#endif

struct MSTEdge {
    int u;
    int v;
    int weight;
};

MSTLIB_API int mstPrim(int n,
                       const MSTEdge* edges,
                       int edgeCount,
                       MSTEdge* outTree,
                       int* outTreeSize);

MSTLIB_API int mstKruskal(int n,
                          const MSTEdge* edges,
                          int edgeCount,
                          MSTEdge* outTree,
                          int* outTreeSize);

MSTLIB_API int mstTreeWeight(const MSTEdge* tree, int treeSize);

MSTLIB_API int mstIsSpanningTree(int n,
                                 const MSTEdge* tree,
                                 int treeSize);