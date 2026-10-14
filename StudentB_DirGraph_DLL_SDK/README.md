# DirGraphLib — Контракт бібліотеки (версія 1.0)

## Призначення
Бібліотека для аналізу орієнтованих графів: топологічне сортування,
перевірка циклів, степені входу/виходу.

## Типи даних
struct DirEdge { int from; int to; };
- from, to — індекси вершин (0 .. n-1).

## Функції

### int topologicalSort(int n, const DirEdge* edges, int edgeCount, int* outOrder)
Топологічне сортування.
- outOrder — масив розміром >= n.
Повертає: 0 — успіх; -1 — цикл або помилка.

### int hasCycle(int n, const DirEdge* edges, int edgeCount)
Повертає: 1 — цикл є; 0 — циклу немає; -1 — помилка.

### int inDegree(int n, const DirEdge* edges, int edgeCount, int v)
Повертає степінь входу вершини v, або -1 при помилці.

### int outDegree(int n, const DirEdge* edges, int edgeCount, int v)
Повертає степінь виходу вершини v, або -1 при помилці.

## Граничні умови
- n <= 0: помилка (-1).
- edgeCount < 0: помилка (-1).
- edgeCount > 0 і edges == nullptr: помилка (-1).
- Некоректні індекси вершин: помилка (-1).
- Порожній граф (n >= 1, edgeCount == 0): топологічне сортування повертає
  вершини у порядку 0..n-1, hasCycle повертає 0.

## Двійкова сумісність
- extern "C", версія API: 1.0