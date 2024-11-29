#include <stdio.h>
#include <stdlib.h>
#include "8-findmst.h"

#define MAX_VERTICES 11
#define MAX_EDGES 200

void graph_init(GraphType* g) {
    g->n = 0;
    g->m = 0;
}

void GenerateGraph(GraphType* g) {
    g->n = 10;
    g->m = 20;

    g->edges[0] = (Edge){ 1, 2, 3 };
    g->edges[1] = (Edge){ 1, 6, 11 };
    g->edges[2] = (Edge){ 1, 7, 12 };
    g->edges[3] = (Edge){ 2, 3, 5 };
    g->edges[4] = (Edge){ 2, 4, 4 };
    g->edges[5] = (Edge){ 2, 5, 1 };
    g->edges[6] = (Edge){ 2, 6, 7 };
    g->edges[7] = (Edge){ 2, 7, 8 };
    g->edges[8] = (Edge){ 3, 4, 2 };
    g->edges[9] = (Edge){ 3, 7, 6 };
    g->edges[10] = (Edge){ 3, 8, 5 };
    g->edges[11] = (Edge){ 4, 5, 13 };
    g->edges[12] = (Edge){ 4, 8, 14 };
    g->edges[13] = (Edge){ 4, 10, 16 };
    g->edges[14] = (Edge){ 5, 6, 9 };
    g->edges[15] = (Edge){ 5, 9, 18 };
    g->edges[16] = (Edge){ 5, 10, 17 };
    g->edges[17] = (Edge){ 7, 8, 13 };
    g->edges[18] = (Edge){ 8, 10, 15 };
    g->edges[19] = (Edge){ 9, 10, 10 };
}

// Disjoint Set 초기화
void set_init(DisjointSet* set, int n) {
    for (int i = 1; i <= n; i++) {
        set->parent[i] = i;
        set->rank[i] = 0;
    }
}

// Disjoint Set 루트
int find_set(DisjointSet* set, int u) {
    if (set->parent[u] != u)
        set->parent[u] = find_set(set, set->parent[u]);
    return set->parent[u];
}

// 두 집합을 합치기
void union_sets(DisjointSet* set, int u, int v) {
    int root_u = find_set(set, u);
    int root_v = find_set(set, v);

    if (root_u != root_v) {
        if (set->rank[root_u] > set->rank[root_v])
            set->parent[root_v] = root_u;
        else {
            set->parent[root_u] = root_v;
            if (set->rank[root_u] == set->rank[root_v])
                set->rank[root_v]++;
        }
    }
}

// 간선의 가중치를 기준으로 QuickSort를 위한 비교 함수
int compare_edges(const void* a, const void* b) {
    Edge* edge_a = (Edge*)a;
    Edge* edge_b = (Edge*)b;
    return edge_a->weight - edge_b->weight;
}

// QuickSort 기반 Kruskal 알고리즘
void QuickKruskal(GraphType* g) {
    DisjointSet set;
    Edge mst[MAX_VERTICES];
    int mst_weight = 0, mst_edges = 0;

    set_init(&set, g->n);
    qsort(g->edges, g->m, sizeof(Edge), compare_edges);

    printf("Quick Based Kruskal\n");
    for (int i = 0; i < g->m; i++) {
        Edge e = g->edges[i];
        if (find_set(&set, e.u) != find_set(&set, e.v)) {
            mst[mst_edges++] = e;
            mst_weight += e.weight;
            union_sets(&set, e.u, e.v);
            printf("Edge (%d, %d) select %d\n", e.u, e.v, e.weight);
        }
    }
    printf("\n");
}

typedef struct {
    Edge heap[MAX_EDGES];
    int size;
} MinHeap;

void init_minheap(MinHeap* h) {
    h->size = 0;
}

// MinHeap에 간선 삽입
void insert_minheap(MinHeap* h, Edge edge) {
    int i = ++(h->size);
    while (i != 1 && edge.weight < h->heap[i / 2].weight) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = edge;
}

// MinHeap에서 최소 가중치 간선 삭제
Edge delete_minheap(MinHeap* h) {
    Edge min_edge = h->heap[1];
    Edge last_edge = h->heap[h->size--];
    int parent = 1, child = 2;

    while (child <= h->size) {
        if (child < h->size && h->heap[child].weight > h->heap[child + 1].weight)
            child++;
        if (last_edge.weight <= h->heap[child].weight)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = last_edge;
    return min_edge;
}

// MinHeap 기반 Kruskal 알고리즘
void MinHeapKruskal(GraphType* g) {
    DisjointSet set;
    MinHeap heap;
    Edge mst[MAX_VERTICES];
    int mst_weight = 0, mst_edges = 0;

    set_init(&set, g->n);
    init_minheap(&heap);

    for (int i = 0; i < g->m; i++)
        insert_minheap(&heap, g->edges[i]);

    printf("MinHeap Based Kruskal\n");
    while (heap.size > 0) {
        Edge e = delete_minheap(&heap);
        if (find_set(&set, e.u) != find_set(&set, e.v)) {
            mst[mst_edges++] = e;
            mst_weight += e.weight;
            union_sets(&set, e.u, e.v);
            printf("Edge (%d, %d) select %d\n", e.u, e.v, e.weight);
        }
    }

}