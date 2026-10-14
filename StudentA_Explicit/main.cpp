#include <iostream>
#include <windows.h>

// ─────────────────────────────────────────────────────────────
// 1. Структура — ОБОВ'ЯЗКОВО до typedef
// ─────────────────────────────────────────────────────────────
struct DirEdge {
    int from;
    int to;
};

// ─────────────────────────────────────────────────────────────
// 2. Типи покажчиків на функції
// ─────────────────────────────────────────────────────────────
typedef int (*TopoSortFunc)(int, const DirEdge*, int, int*);
typedef int (*HasCycleFunc)(int, const DirEdge*, int);
typedef int (*DegreeFunc)(int, const DirEdge*, int, int);

int main() {
    // ── КРОК 1. Завантажуємо DLL ──
    HMODULE hLib = LoadLibrary(TEXT("DirGraphLib.dll"));
    if (!hLib) {
        std::cerr << "ERROR: cannot load DirGraphLib.dll (error code "
                  << GetLastError() << ")\n";
        return 1;
    }
    std::cout << "DLL loaded successfully!\n";

    // ── КРОК 2. Отримуємо адреси функцій ──
    auto topologicalSort = reinterpret_cast<TopoSortFunc>(
        GetProcAddress(hLib, "topologicalSort"));
    auto hasCycle = reinterpret_cast<HasCycleFunc>(
        GetProcAddress(hLib, "hasCycle"));
    auto inDegree = reinterpret_cast<DegreeFunc>(
        GetProcAddress(hLib, "inDegree"));
    auto outDegree = reinterpret_cast<DegreeFunc>(
        GetProcAddress(hLib, "outDegree"));

    // ── КРОК 3. Перевіряємо, що функції знайдено ──
    if (!topologicalSort || !hasCycle || !inDegree || !outDegree) {
        std::cerr << "ERROR: one or more functions not found in DLL\n";
        FreeLibrary(hLib);
        return 1;
    }
    std::cout << "All functions resolved successfully!\n\n";

    // ── КРОК 4. Використовуємо функції ──
    const int n = 6;
    DirEdge edges[] = {
        {5, 2}, {5, 0}, {4, 0}, {4, 1},
        {2, 3}, {3, 1}
    };
    const int edgeCount = 6;

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

    // ── КРОК 5. Граничні випадки ──
    std::cout << "\n--- Edge cases ---\n";

    int orderEmpty[6];
    int rcEmpty = topologicalSort(n, nullptr, 0, orderEmpty);
    std::cout << "Empty graph: rc=" << rcEmpty << "\n";
    if (rcEmpty == 0) {
        std::cout << "  order: ";
        for (int i = 0; i < n; ++i) std::cout << orderEmpty[i] << " ";
        std::cout << "\n";
    }

    int rcNull = topologicalSort(n, edges, edgeCount, nullptr);
    std::cout << "nullptr outOrder: rc=" << rcNull << " (очікується -1)\n";

    int rcBadN = hasCycle(0, edges, edgeCount);
    std::cout << "n=0: rc=" << rcBadN << " (очікується -1)\n";

    int rcBadV = inDegree(n, edges, edgeCount, 999);
    std::cout << "inDegree(v=999): rc=" << rcBadV << " (очікується -1)\n";

    DirEdge cyc[] = {{0,1}, {1,2}, {2,0}};
    int rcCyc = hasCycle(3, cyc, 3);
    std::cout << "Cycle graph hasCycle: " << rcCyc << " (очікується 1)\n";

    // ── КРОК 6. Вивантажуємо DLL ──
    FreeLibrary(hLib);
    std::cout << "\nDLL unloaded. Done.\n";
    return 0;
}