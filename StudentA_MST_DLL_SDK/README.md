# MSTLib — Контракт бібліотеки

**Версія API:** 1.0
**Тип:** динамічна бібліотека (DLL)
**Мова:** C++20, C-ABI (`extern "C"`)
**Призначення:** побудова та аналіз мінімальних кісткових дерев (МКД)
у неорієнтованих зважених графах.

---

## 1. Типи даних

struct MSTEdge {
    int u;       // індекс початкової вершини (0 .. n-1)
    int v;       // індекс кінцевої вершини   (0 .. n-1)
    int weight;  // вага ребра
};

Граф задається кількістю вершин `n` та масивом ребер `edges`
довжиною `edgeCount`.

---

## 2. Функції

### int mstPrim(int n, const MSTEdge* edges, int edgeCount,
              MSTEdge* outTree, int* outTreeSize)
Побудова МКД алгоритмом Пріма.

Параметри:
- n            — кількість вершин (>= 1)
- edges        — масив ребер (може бути nullptr, якщо edgeCount == 0)
- edgeCount    — кількість ребер (>= 0)
- outTree      — вихідний масив для ребер МКД (розмір >= n-1)
- outTreeSize  — вихідна кількість ребер у МКД

Повертає:
-  0 — успіх (МКД побудовано, *outTreeSize == n-1)
- -1 — помилка (некоректні параметри або граф незв'язний)

### int mstKruskal(int n, const MSTEdge* edges, int edgeCount,
                 MSTEdge* outTree, int* outTreeSize)
Те саме, але алгоритмом Краскала.

### int mstTreeWeight(const MSTEdge* tree, int treeSize)
Повертає сумарну вагу ребер дерева.
Якщо tree == nullptr або treeSize <= 0 — повертає 0.

### int mstIsSpanningTree(int n, const MSTEdge* tree, int treeSize)
Перевіряє, чи є набір ребер кістковим деревом.
Повертає: 1 — так, 0 — ні.

---

## 3. Граничні умови
- n == 1: МКД порожнє, *outTreeSize = 0, повертається 0.
- edgeCount == 0 і n > 1: граф незв'язний, повертається -1.
- outTree == nullptr або outTreeSize == nullptr: повертається -1.
- Ребра з некоректними індексами вершин (< 0 або >= n) ігноруються.
- Петля (u == v) у mstIsSpanningTree повертає 0.

---

## 4. Двійкова сумісність
- Використовується extern "C" — імена функцій не декоруються.
- Експортовані імена: mstPrim, mstKruskal, mstTreeWeight, mstIsSpanningTree.
- Версія API: 1.0