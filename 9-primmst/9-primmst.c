#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 200
#define MAX_VERTICES 11
#define Infinite 1000

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    int n;
    int m; 
    Edge edges[MAX_EDGES];
} GraphType;

static int distance[MAX_VERTICES]; 
static int selected[MAX_VERTICES]; 
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

// 선택되지 않은 정점 중에서 최소 가중치를 가진 정점을 반환하는 함수
int get_min_vertex(int n) {
    int v = -1;
    for (int i = 0; i < n; i++) {
        if (!selected[i] && (v == -1 || distance[i] < distance[v])) {
            v = i;
        }
    }
    return v;
}

// Prim 알고리즘을 사용하여 MST를 찾는 함수
void FindPrimMST(GraphType* g) {
    printf("Prim MST Algorithm\n");
    for (int i = 0; i < g->n; i++) {
        distance[i] = Infinite;
        selected[i] = 0;
    }

    distance[0] = 0;

    // 정점 수만큼 반복
    for (int i = 0; i < g->n; i++) {
        int u = get_min_vertex(g->n);
        if (u == -1) break;

        selected[u] = 1;

        printf("정점 %d 추가\n", u + 1);

        for (int j = 0; j < g->m; j++) {
            Edge edge = g->edges[j];
            if ((edge.u - 1 == u || edge.v - 1 == u)) {
                int v = (edge.u - 1 == u) ? edge.v - 1 : edge.u - 1;
                if (!selected[v] && edge.weight < distance[v]) {
                    distance[v] = edge.weight;
                }
            }
        }
    }
}

int main() {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);

    FindPrimMST(g);

    free(g);
    return 0;
}