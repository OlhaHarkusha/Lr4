#include <iostream>
#include <windows.h>   // LoadLibrary, GetProcAddress, FreeLibrary, HMODULE

// ─────────────────────────────────────────────────────────────
// 1. Структура — ОБОВ'ЯЗКОВО до typedef.
//    Має ТОЧНО збігатися з тією, що в MSTLib.dll:
//    той самий порядок і типи полів.
// ─────────────────────────────────────────────────────────────
struct MSTEdge {
    int u;
    int v;
    int weight;
};

// ─────────────────────────────────────────────────────────────
// 2. Типи покажчиків на функції з DLL.
//    Сигнатури мають ТОЧНО збігатися з реалізацією в DLL.
// ─────────────────────────────────────────────────────────────
typedef int (*PrimFunc)(int, const MSTEdge*, int, MSTEdge*, int*);
typedef int (*KruskalFunc)(int, const MSTEdge*, int, MSTEdge*, int*);
typedef int (*WeightFunc)(const MSTEdge*, int);
typedef int (*IsSpanningTreeFunc)(int, const MSTEdge*, int);

int main() {
    // ─────────────────────────────────────────────────────────────
    // КРОК 1. Завантажуємо DLL у пам'ять процесу
    // ─────────────────────────────────────────────────────────────
    HMODULE hLib = LoadLibrary(TEXT("MSTLib.dll"));
    if (!hLib) {
        std::cerr << "ERROR: cannot load MSTLib.dll (error code "
                  << GetLastError() << ")\n";
        return 1;
    }
    std::cout << "DLL loaded successfully!\n";

    // ─────────────────────────────────────────────────────────────
    // КРОК 2. Отримуємо адреси функцій за іменами
    // (завдяки extern "C" у DLL імена не декоровані)
    // ─────────────────────────────────────────────────────────────
    auto mstPrim = reinterpret_cast<PrimFunc>(
        GetProcAddress(hLib, "mstPrim"));
    auto mstKruskal = reinterpret_cast<KruskalFunc>(
        GetProcAddress(hLib, "mstKruskal"));
    auto mstTreeWeight = reinterpret_cast<WeightFunc>(
        GetProcAddress(hLib, "mstTreeWeight"));
    auto mstIsSpanningTree = reinterpret_cast<IsSpanningTreeFunc>(
        GetProcAddress(hLib, "mstIsSpanningTree"));

    // ─────────────────────────────────────────────────────────────
    // КРОК 3. Перевіряємо, що всі функції знайдено
    // ─────────────────────────────────────────────────────────────
    if (!mstPrim || !mstKruskal || !mstTreeWeight || !mstIsSpanningTree) {
        std::cerr << "ERROR: one or more functions not found in DLL\n";
        FreeLibrary(hLib);
        return 1;
    }
    std::cout << "All functions resolved successfully!\n\n";

    // ─────────────────────────────────────────────────────────────
    // КРОК 4. Використовуємо функції через покажчики
    // ─────────────────────────────────────────────────────────────
    const int n = 5;
    MSTEdge edges[] = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3},
        {1, 3, 8}, {1, 4, 5}, {2, 4, 7},
        {3, 4, 9}
    };
    const int edgeCount = 7;

    MSTEdge tree[10];
    int treeSize = 0;

    // 4.1. Алгоритм Пріма
    int rcPrim = mstPrim(n, edges, edgeCount, tree, &treeSize);
    if (rcPrim == 0) {
        std::cout << "Prim MST weight = "
                  << mstTreeWeight(tree, treeSize) << "\n";
        std::cout << "Prim is spanning tree: "
                  << mstIsSpanningTree(n, tree, treeSize) << "\n";
    } else {
        std::cout << "Prim: graph is disconnected or error!\n";
    }

    // 4.2. Алгоритм Краскала
    int rcKruskal = mstKruskal(n, edges, edgeCount, tree, &treeSize);
    if (rcKruskal == 0) {
        std::cout << "Kruskal MST weight = "
                  << mstTreeWeight(tree, treeSize) << "\n";
        std::cout << "Kruskal is spanning tree: "
                  << mstIsSpanningTree(n, tree, treeSize) << "\n";
    } else {
        std::cout << "Kruskal: graph is disconnected or error!\n";
    }

    // 4.3. Перевірка, що обидва алгоритми дають однакову вагу
    MSTEdge treePrim[10], treeKruskal[10];
    int sizePrim = 0, sizeKruskal = 0;
    mstPrim(n, edges, edgeCount, treePrim, &sizePrim);
    mstKruskal(n, edges, edgeCount, treeKruskal, &sizeKruskal);
    std::cout << "\nPrim weight == Kruskal weight: "
              << (mstTreeWeight(treePrim, sizePrim) ==
                  mstTreeWeight(treeKruskal, sizeKruskal) ? "yes" : "no")
              << "\n";

    // ─────────────────────────────────────────────────────────────
    // КРОК 5. Граничні випадки (Edge Cases)
    // ─────────────────────────────────────────────────────────────
    std::cout << "\n--- Edge cases ---\n";

    // 5.1. n == 1 → МКД порожнє, повертає 0
    MSTEdge dummy[1];
    int dummySize = -1;
    int rcN1 = mstPrim(1, nullptr, 0, dummy, &dummySize);
    std::cout << "n=1: rc=" << rcN1 << ", treeSize=" << dummySize
              << " (очікується 0, 0)\n";

    // 5.2. nullptr edges при edgeCount == 0 і n > 1
    int rcEmpty = mstPrim(n, nullptr, 0, tree, &treeSize);
    std::cout << "edges=nullptr, count=0, n=5: rc=" << rcEmpty
              << " (очікується -1)\n";

    // 5.3. nullptr outTree
    int rcNullTree = mstPrim(n, edges, edgeCount, nullptr, &treeSize);
    std::cout << "outTree=nullptr: rc=" << rcNullTree
              << " (очікується -1)\n";

    // 5.4. nullptr outTreeSize
    int rcNullSize = mstPrim(n, edges, edgeCount, tree, nullptr);
    std::cout << "outTreeSize=nullptr: rc=" << rcNullSize
              << " (очікується -1)\n";

    // 5.5. n <= 0
    int rcBadN = mstPrim(0, edges, edgeCount, tree, &treeSize);
    std::cout << "n=0: rc=" << rcBadN << " (очікується -1)\n";

    // 5.6. mstTreeWeight з nullptr → 0
    std::cout << "mstTreeWeight(nullptr, 0) = "
              << mstTreeWeight(nullptr, 0) << " (очікується 0)\n";

    // 5.7. mstIsSpanningTree з nullptr → 0
    std::cout << "mstIsSpanningTree(n=5, nullptr, 0) = "
              << mstIsSpanningTree(n, nullptr, 0) << " (очікується 0)\n";

    // 5.8. mstIsSpanningTree з неправильною кількістю ребер → 0
    MSTEdge tooFew[2] = {{0,1,2}, {1,2,3}};
    std::cout << "mstIsSpanningTree(n=5, tree=2 edges) = "
              << mstIsSpanningTree(n, tooFew, 2) << " (очікується 0)\n";

    // 5.9. Незв'язний граф (дві компоненти)
    MSTEdge disconnected[] = {{0, 1, 1}, {2, 3, 1}};
    int rcDisc = mstPrim(4, disconnected, 2, tree, &treeSize);
    std::cout << "Disconnected graph: rc=" << rcDisc
              << " (очікується -1)\n";

    // ─────────────────────────────────────────────────────────────
    // КРОК 6. Вивантажуємо DLL
    // ─────────────────────────────────────────────────────────────
    FreeLibrary(hLib);
    std::cout << "\nDLL unloaded. Done.\n";
    return 0;
}