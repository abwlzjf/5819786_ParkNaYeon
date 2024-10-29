#pragma once

#define MAX_EDGES 200
#define MAX_VERTICES 11

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES];
} DisjointSet;

typedef struct {
    int n;
    int m;
    Edge edges[MAX_EDGES];
} GraphType;

extern void graph_init(GraphType* g);
extern void GenerateGraph(GraphType* g);

extern void QuickKruskal(GraphType* g); 
extern void MinHeapKruskal(GraphType* g);